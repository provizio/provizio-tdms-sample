#include <iostream>
#include <string.h>
#include <config.h>

#include "libtdms/TDMSData.h"

void help()
{
    std::cout << "Use: provizio-tdms-sample -option your_file_name.tdms" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-h: print help information and exit" << std::endl;
    std::cout << "-v: verbose output\n"
              << std::endl;
}

int main(int argc, char **argv)
{
    std::cout << "\nProvizio-TDMS-Sample v"
              << PROVIZIO_TDMS_SAMPLE_VERSION_MAJOR
              << "." << PROVIZIO_TDMS_SAMPLE_VERSION_MINOR
              << "\n"
              << std::endl;

    // Input arguments
    if ((argc < 2) or (argc > 3))
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

    bool verbose = false;
    if ((argc == 3) && (strcmp(argv[1], "-v") == 0))
    {
        verbose = true;
    }

    std::string fileName = (argc == 3) ? argv[2] : argv[1];

    // Parse TDMS
    TDMSData tdmsData(fileName, verbose);

    // Print final information
    int nobject = tdmsData.getGroupCount();
    tdmsData.print(std::cout);
    std::cout << std::endl;

    // Example of retrieving value for Acceleration x at index 1
    unsigned int index = 1;
    std::string group_name = "/'RT3000 UDP'";
    std::string channel_name = "'Acceleration x [m/(s^2)]'";

    double acceleration = tdmsData.getDataFloat64(group_name, channel_name, index);
    std::cout << "Acceleration x [m/(s^2)] [" << index << "]: " << acceleration << std::endl;

    return 0;
}