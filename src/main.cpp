#include <iostream>
#include <string.h>
#include <config.h>

#include "libtdms/TDMSData.h"

#include "provizio/radar_api/core.h"

void help()
{
    std::cout << "Use: provizio-tdms-sample [-option] your_file_name.tdms" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-h: print help information and exit" << std::endl;
    std::cout << "-v: verbose output\n"
              << std::endl;
}

class ProvizioTDMSData : public TDMSData
{
public:
    ProvizioTDMSData(const std::string &oxtsGroupName, const std::string &provizioGroupName)
        : oxtsGroupName(oxtsGroupName), provizioGroupName(provizioGroupName)
    {
    }

protected:
    void addObject(std::shared_ptr<Group> group, std::shared_ptr<Channel> channel, std::shared_ptr<Object> object) override;

private:
    const std::string oxtsGroupName;
    const std::string provizioGroupName;
};

void ProvizioTDMSData::addObject(std::shared_ptr<Group> group, std::shared_ptr<Channel> channel, std::shared_ptr<Object> object)
{
    std::cout << "addObject. Group: " << group->getName() << ". Channel: " << channel->getName() << ". Data size: " << object->getRawData()->getData()->size() << std::endl;
}

int main(int argc, char **argv)
{
    std::cout << "\nProvizio-TDMS-Sample v"
              << PROVIZIO_TDMS_SAMPLE_VERSION_MAJOR
              << "." << PROVIZIO_TDMS_SAMPLE_VERSION_MINOR
              << "\n"
              << std::endl;

    // Input arguments
    if (argc < 2 || argc > 3)
    {
        std::cout << "Use: provizio-tdms-sample (-h/-v) your_file_name.tdms" << std::endl;
        std::cout << "\nInput error: please provide a single valid *.tdms file name!\n"
                  << std::endl;
        return 1;
    }

    if ((strcmp(argv[1], "-h") == 0))
    {
        help();
        return 0;
    }

    const bool verbose = (argc == 3 && strcmp(argv[1], "-v") == 0);
    const std::string file_name = (argc == 3) ? argv[2] : argv[1];

    // Parse TDMS
    ProvizioTDMSData tdms_data("/'RT3000 UDP'", "/Provizio");
    tdms_data.read(file_name, verbose);

    return 0;
}
