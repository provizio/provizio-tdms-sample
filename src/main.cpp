#include <iostream>
#include <string.h>
#include <config.h>

#include "ProvizioTDMSData.h"

void help()
{
    std::cout << "Use: provizio-tdms-sample [-option] your_file_name.tdms" << std::endl;
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

    const auto pointcloudsFile = file_name + ".pointclouds.csv";
    const auto accumulatedPointcloudsFile = file_name + ".accumulated_pointclouds.csv";
    std::fstream pointclouds_csv_stream{pointcloudsFile, std::ios_base::out};
    std::fstream accumulated_pointclouds_csv_stream{accumulatedPointcloudsFile, std::ios_base::out};

    // Parse TDMS
    const std::size_t maxAccumulationFrames = 100;
    const Extrinsics radarExtrinsicsRelativeToOxTS = {0, 0, 0, 0, 0, 0}; // TODO: to be either parsed from a config or specified as an input argument - will be discussed with JLR later
    ProvizioTDMSData tdms_data("/'RT3000 UDP'", "/'Provizio'", maxAccumulationFrames, radarExtrinsicsRelativeToOxTS, pointclouds_csv_stream, accumulated_pointclouds_csv_stream);
    tdms_data.read(file_name, verbose);

    std::cout << "Results have been written to " << pointcloudsFile << " and " << accumulatedPointcloudsFile << std::endl;

    return 0;
}
