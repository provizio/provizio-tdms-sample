#include <iostream>
#include <algorithm>
#include <cstring>
#include "types/DataArray.h"
#include "libtdms/TDMSData.h"
#include "libtdms/TDMSReader.h"
#include "libtdms/MetaData.h"
#include "libtdms/Object.h"
#include "libtdms/Channel.h"
#include "libtdms/Root.h"
#include "libtdms/Group.h"

TDMSData::TDMSData(const std::string &filename, bool verbose)
    : filename(filename)
{
    TDMSReader tdmsReader;
    tdmsReader.read(filename, this, verbose);
}

TDMSData::~TDMSData()
{
}

void TDMSData::storeObjects(std::shared_ptr<MetaData> metaData)
{
    const MetaData::ObjectList &objectList = metaData->getObjectList();
    for (MetaData::ObjectList::const_iterator obj = objectList.begin();
         obj != objectList.end(); ++obj)
    {
        std::string pathName = (*obj)->getPath();
        if (isRoot(pathName))
        {
        }
        else
        {
            if (isGroup(pathName))
            {
                auto group = root.getGroup(pathName);
                if (!group)
                {
                    group = std::make_shared<Group>(pathName);
                    root.addGroup(group);
                }
            }
            else
            {
                int islash = pathName.find('/', 1);
                std::string channelName = pathName.substr(islash + 1);
                std::string groupName = pathName.substr(0, islash);
                auto group = root.getGroup(groupName);
                auto channel = group->getChannel(channelName);
                if (channel == 0)
                {
                    channel = std::make_shared<Channel>(channelName);
                    group->addChannel(channel);
                }
                if ((*obj)->hasRawData())
                {
                    channel->setDataType((*obj)->getDataType());
                    channel->addRawData((*obj)->getRawData());
                }
            }
        }
    }
}

void TDMSData::print(std::ostream &os) const
{
    root.print(os);
}

bool TDMSData::isRoot(const std::string &pathName) const
{
    return pathName == "/";
}

bool TDMSData::isGroup(const std::string &pathName) const
{
    int slashCount = std::count(pathName.begin(), pathName.end(), '/');
    return slashCount == 1;
}

std::shared_ptr<Group> TDMSData::getGroup(const std::string &name)
{
    return root.getGroup(name);
}

int TDMSData::getGroupCount() const
{
    return root.getGroupCount();
}

const Root &TDMSData::getRoot() const
{
    return root;
}

double TDMSData::getDataFloat64(const std::string &group_name, const std::string &channel_name, const unsigned int index)
{
    double value;
    // find group
    auto group = root.getGroup(group_name);
    // find channel
    auto channel = group->getChannel(channel_name);
    // get data from channel
    auto data = channel->getData();
    const DataType *dataType = channel->getDataType();
    int nbytes = data->getSizeOf();
    int nelements = data->getSize();
    // extract data of specific type at input position "index"
    char *ptr = (char *)data->getData()->data();
    ptr += nbytes * index;
    std::memcpy(&value, ptr, nbytes);
    return value;
}
