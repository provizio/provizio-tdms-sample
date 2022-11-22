#include <iostream>
#include <fstream>

#include "libtdms/TDMSReader.h"
#include "libtdms/ObjectDefaults.h"
#include "libtdms/LeadIn.h"
#include "libtdms/MetaData.h"
#include "libtdms/Error.h"
#include "libtdms/TDMSData.h"

// Only these sizes are supported by libtdms
static_assert(sizeof(char) == 1, "sizeof(char) == 1 expected");
static_assert(sizeof(short) == 2, "sizeof(short) == 2 expected");
static_assert(sizeof(int) == 4, "sizeof(int) == 4 expected");
static_assert(sizeof(long long) == 8, "sizeof(long long) == 8 expected");
static_assert(sizeof(float) == 4, "sizeof(float) == 4 expected");
static_assert(sizeof(double) == 8, "sizeof(double) == 8 expected");
static_assert(sizeof(long double) == 16, "sizeof(long double) == 16 expected");
static_assert(sizeof(bool) == 1, "sizeof(bool) == 1 expected");

void TDMSReader::read(const std::string &filename,
                      TDMSData *data, const bool verbose)
{
    objectDefaults = std::make_shared<ObjectDefaults>();
    std::ifstream infile(filename.c_str(), std::ios::binary | std::ios::in);

    // Find total file size
    infile.seekg(0, std::ios::end);
    const auto file_size = infile.tellg();
    infile.seekg(0, std::ios::beg);

    metaData = 0;

    while (!infile.eof())
    {
        try
        {
            LeadIn leadIn(infile);

            if (infile.eof())
            {
                break;
            }

            if ((verbose))
            {
                leadIn.print();
            }

            const auto posAfterLeadIn = infile.tellg();
            std::streampos nextSegmentPos;

            if (leadIn.getNextSegmentOffset() == -1)
            {
                nextSegmentPos = file_size;
            }
            else
            {
                nextSegmentPos = posAfterLeadIn + (std::streamoff)leadIn.getNextSegmentOffset();
            }

            const auto dataPos = posAfterLeadIn + (std::streamoff)leadIn.getDataOffset();

            if (verbose)
            {
                printf("POS after LeadIn: %llu\n", (unsigned long long)posAfterLeadIn);
                printf("Data POS: %llu\n", (unsigned long long)dataPos);
                printf("Next Segment POS: %llu\n", (unsigned long long)nextSegmentPos);
            }

            if (leadIn.hasMetaData())
            {
                metaData = std::make_shared<MetaData>(infile, objectDefaults);
                if (verbose)
                {
                    metaData->print();
                }

                if (leadIn.hasRawData())
                {
                    infile.seekg(dataPos, std::ios_base::beg);
                    if (verbose)
                    {
                        printf("Raw data starts at POS: %llu\n", (unsigned long long)infile.tellg());
                    }

                    metaData->readRawData(verbose);

                    if (verbose)
                    {
                        printf("POS after raw data: %llu\n", (unsigned long long)infile.tellg());
                    }
                }
            }
            else if (leadIn.hasRawData())
            {
                if (verbose)
                {
                    printf("\tSegment without metadata!\n");
                }

                infile.seekg(dataPos, std::ios_base::beg);
                metaData->readRawData(verbose);

                if (verbose)
                {
                    printf("POS after raw data: %llu\n", (unsigned long long)infile.tellg());
                }
            }
            else if (verbose)
            {
                printf("\tSegment without metadata or raw data!\n");
            }

            data->storeObjects(metaData);

            infile.seekg(nextSegmentPos, std::ios_base::beg);
        }
        catch (EOFError &)
        {
            break;
        }
        catch (Error &error)
        {
            std::cout << "Caught an Error: "
                      << error.message << std::endl;
        }
    };

    if (verbose)
    {
        printf("\tEnd of file is reached!\n");
    }
}
