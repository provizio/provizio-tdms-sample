#include "ProvizioTDMSData.h"

#include <assert.h>

#include "WGS84toCartesian.hpp"
#include "linmath/linmath.h"

ProvizioTDMSData::ProvizioTDMSData(
    const std::string &oxtsGroupName,
    const std::string &provizioGroupName,
    std::size_t maxAccumulationFrames,
    const Extrinsics &radarExtrinsicsRelativeToOxTS,
    std::ostream &pointclouds_csv_stream,
    std::ostream &accumulated_pointclouds_csv_stream)
    : oxtsGroupName(oxtsGroupName),
      provizioGroupName(provizioGroupName),
      radarExtrinsicsRelativeToOxTS(radarExtrinsicsRelativeToOxTS),
      pointclouds_csv_stream(pointclouds_csv_stream),
      accumulated_pointclouds_csv_stream(accumulated_pointclouds_csv_stream),
      point_cloud_api_context(std::make_unique<provizio_radar_point_cloud_api_context>()),
      transformed_point_cloud(std::make_unique<provizio_radar_point_cloud>()),
      accumulation_buffer(maxAccumulationFrames)
{
    provizio_radar_point_cloud_api_context_init(&pointCloudCallback, this, point_cloud_api_context.get());
    provizio_accumulated_radar_point_clouds_init(accumulation_buffer.data(), accumulation_buffer.size());

    csvHeaderToStream(pointclouds_csv_stream);
    csvHeaderToStream(accumulated_pointclouds_csv_stream);
}

void ProvizioTDMSData::addObject(std::shared_ptr<Group> group, std::shared_ptr<Channel> channel, std::shared_ptr<Object> object)
{
    if (group->getName() == oxtsGroupName)
    {
        addOxtsObject(channel, object);
    }
    else if (group->getName() == provizioGroupName)
    {
        addProvizioObject(channel, object);
    }
}

void ProvizioTDMSData::addOxtsObject(std::shared_ptr<Channel> channel, std::shared_ptr<Object> object)
{
    auto getDouble = [&]() -> double
    {
        assert(object->hasRawData());
        assert(object->getRawData()->getData()->size() == sizeof(double));
        double result;
        memcpy(&result, object->getRawData()->getData()->data(), object->getRawData()->getData()->size());
        return result;
    };

    bool updateLatestFix = true;
    if (channel->getName() == "'Latitude [radians]'")
    {
        lat = getDouble() * 180.0 / M_PI;
        if (std::isnan(refLat))
        {
            refLat = lat;
        }
    }
    else if (channel->getName() == "'Longtitude [radians]'") // yep, LongTitude - due to a typo in tdms contents
    {
        lon = getDouble() * 180.0 / M_PI;
        if (std::isnan(refLon))
        {
            refLon = lon;
        }
    }
    else if (channel->getName() == "'Altitude [m]'")
    {
        alt = getDouble();
    }
    else if (channel->getName() == "'Heading [radians]'")
    {
        yaw = getDouble();
    }
    else if (channel->getName() == "'Pitch [radians]'")
    {
        pitch = getDouble();
    }
    else if (channel->getName() == "'Roll [radians]'")
    {
        roll = getDouble();
    }
    else
    {
        updateLatestFix = false;
    }

    if (updateLatestFix && !std::isnan(lat) && !std::isnan(lon) && !std::isnan(alt) && !std::isnan(yaw) && !std::isnan(pitch) && !std::isnan(roll))
    {
        const auto en = wgs84::toCartesian({refLat, refLon}, {lat, lon});
        const float oxts_x = en[0];
        const float oxts_y = en[1];
        const float oxts_z = alt;

        provizio_quaternion quaternion;
        provizio_quaternion_set_euler_angles(roll, pitch, yaw, &quaternion);
        quat q = {quaternion.x, quaternion.y, quaternion.z, quaternion.w};
        vec3 extrinsicsPosVehicle = {radarExtrinsicsRelativeToOxTS.position_x_meters, radarExtrinsicsRelativeToOxTS.position_y_meters, radarExtrinsicsRelativeToOxTS.position_z_meters};
        vec3 extrinsicsPosEnu;
        quat_mul_vec3(extrinsicsPosEnu, q, extrinsicsPosVehicle);

        latestFix.position.east_meters = oxts_x + extrinsicsPosEnu[0];
        latestFix.position.north_meters = en[1] + extrinsicsPosEnu[1];
        latestFix.position.up_meters = alt + extrinsicsPosEnu[2];
        provizio_quaternion_set_euler_angles(roll + radarExtrinsicsRelativeToOxTS.roll_radians, pitch + radarExtrinsicsRelativeToOxTS.pitch_radians, yaw + radarExtrinsicsRelativeToOxTS.yaw_radians, &latestFix.orientation);

        // So next time we update latestFix when all 6 values are received again
        lat = lon = alt = yaw = pitch = roll = nan;
    }
}

void ProvizioTDMSData::addProvizioObject(std::shared_ptr<Channel> channel, std::shared_ptr<Object> object)
{
    if (object->hasRawData())
    {
        const auto errorCode = provizio_handle_possible_radar_point_cloud_packet(
            point_cloud_api_context.get(),
            object->getRawData()->getData()->data(),
            object->getRawData()->getData()->size());

        if (errorCode != 0 && errorCode != PROVIZIO_E_SKIPPED)
        {
            std::cerr << "provizio_handle_possible_radar_point_cloud_packet failed with error code = " << errorCode;
        }
    }
}

void ProvizioTDMSData::pointCloudCallback(const provizio_radar_point_cloud *point_cloud,
                                          struct provizio_radar_point_cloud_api_context *context)
{
    const auto data = static_cast<ProvizioTDMSData *>(context->user_data);
    pointCloudToStream(data->pointclouds_csv_stream, *point_cloud, point_cloud->frame_index, point_cloud->timestamp);

    if (!std::isnan(data->latestFix.position.east_meters))
    {
        // There is a valid fix. Let's accumulate!
        for (auto iterator = provizio_accumulate_radar_point_cloud_static(point_cloud, &data->latestFix, data->accumulation_buffer.data(), data->accumulation_buffer.size());
             !provizio_accumulated_radar_point_cloud_iterator_is_end(&iterator, data->accumulation_buffer.data(), data->accumulation_buffer.size());
             provizio_accumulated_radar_point_cloud_iterator_next_point_cloud(&iterator, data->accumulation_buffer.data(), data->accumulation_buffer.size()))
        {
            provizio_accumulated_radar_point_cloud_iterator_get_point_cloud(&iterator, &data->latestFix, data->accumulation_buffer.data(), data->accumulation_buffer.size(), data->transformed_point_cloud.get(), nullptr);
            pointCloudToStream(data->accumulated_pointclouds_csv_stream, *data->transformed_point_cloud, point_cloud->frame_index, point_cloud->timestamp);
        }
    }
}

void ProvizioTDMSData::csvHeaderToStream(std::ostream &stream)
{
    stream << "Frame,Timestamp (ns),Velocity (m/s),Ground Velocity (m/s),X Position (m),Y Position (m),Z Position (m),SNR (dB)\n";
}

void ProvizioTDMSData::pointCloudToStream(std::ostream &stream, const provizio_radar_point_cloud &point_cloud, std::uint32_t frame_index, std::uint64_t timestamp)
{
    for (std::size_t i = 0; i < point_cloud.num_points_received; ++i)
    {
        const auto &point = point_cloud.radar_points[i];
        stream
            << frame_index << ","
            << timestamp << ","
            << point.radar_relative_radial_velocity_m_s << ","
            << point.ground_relative_radial_velocity_m_s << ","
            << point.x_meters << ","
            << point.y_meters << ","
            << point.z_meters << ","
            << point.signal_to_noise_ratio << "\n";
    }
}
