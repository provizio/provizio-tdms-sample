#ifndef INCLUDE_PROVIZIOTDMSDATA
#define INCLUDE_PROVIZIOTDMSDATA

#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "libtdms/TDMSData.h"
#include "provizio/radar_api/core.h"

struct Extrinsics
{
    float position_x_meters; // Forward
    float position_y_meters; // Left
    float position_z_meters; // Up
    float roll_radians;
    float pitch_radians;
    float yaw_radians;
};

class ProvizioTDMSData : public TDMSData
{
public:
    ProvizioTDMSData(
        const std::string &oxtsGroupName,
        const std::string &provizioGroupName,
        std::size_t maxAccumulationFrames,
        const Extrinsics &radarExtrinsicsRelativeToOxTS,
        std::ostream &pointclouds_csv_stream,
        std::ostream &accumulated_pointclouds_csv_stream);

protected:
    void addObject(std::shared_ptr<Group> group, std::shared_ptr<Channel> channel, std::shared_ptr<Object> object) override;

private:
    void addOxtsObject(std::shared_ptr<Channel> channel, std::shared_ptr<Object> object);
    void addProvizioObject(std::shared_ptr<Channel> channel, std::shared_ptr<Object> object);
    static void pointCloudCallback(const provizio_radar_point_cloud *point_cloud,
                                   struct provizio_radar_point_cloud_api_context *context);
    static void csvHeaderToStream(std::ostream &stream);
    static void pointCloudToStream(std::ostream &stream, const provizio_radar_point_cloud &point_cloud, std::uint32_t frame_index, std::uint64_t timestamp);

    const std::string oxtsGroupName;
    const std::string provizioGroupName;
    const Extrinsics radarExtrinsicsRelativeToOxTS;

    std::ostream &pointclouds_csv_stream;
    std::ostream &accumulated_pointclouds_csv_stream;

    std::unique_ptr<provizio_radar_point_cloud_api_context> point_cloud_api_context;
    std::unique_ptr<provizio_radar_point_cloud> transformed_point_cloud;
    std::vector<provizio_accumulated_radar_point_cloud> accumulation_buffer;

    static constexpr auto nan = std::numeric_limits<double>::quiet_NaN();

    double refLat = nan;
    double refLon = nan;
    double lat = nan;
    double lon = nan;
    double alt = nan;
    double yaw = nan;
    double pitch = nan;
    double roll = nan;
    provizio_enu_fix latestFix = {{nan, nan, nan, nan}, {nan, nan, nan}};
};

#endif // INCLUDE_PROVIZIOTDMSDATA
