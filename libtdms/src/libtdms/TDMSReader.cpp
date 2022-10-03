#include <iostream>
#include <fstream>

#include "libtdms/TDMSReader.h"
#include "libtdms/ObjectDefaults.h"
#include "libtdms/LeadIn.h"
#include "libtdms/MetaData.h"
#include "libtdms/Error.h"
#include "libtdms/TDMSData.h"

TDMSReader::TDMSReader()
    :   objectDefaults(0) {
}

void TDMSReader::checkSizeOfTypes() {
    std::cout << "\nsize of char should be 1: " << sizeof(char) << std::endl;
    std::cout << "size of short should be 2: " << sizeof(short) << std::endl;
    std::cout << "size of int should be 4: " << sizeof(int) << std::endl;
    std::cout << "size of long should be 4: " << sizeof(long) << std::endl;
    std::cout << "size of long long should be 8: " << sizeof(long long)
                    << std::endl;
    std::cout << "size of float should be 4: " << sizeof(float) << std::endl;
    std::cout << "size of double should be 8: " << sizeof(double) << std::endl;
    std::cout << "size of long double should be 16: " << sizeof(long double)
                    << std::endl;
    std::cout << "size of bool should be 1: " << sizeof(bool) << std::endl;
}

TDMSReader::~TDMSReader() {
    delete objectDefaults;
}

void TDMSReader::read(const std::string &filename, 
        TDMSData* data, const bool verbose) {
    if (objectDefaults) delete objectDefaults;
    objectDefaults = new ObjectDefaults();
    std::ifstream infile(filename.c_str(), std::ios::binary | std::ios::in);

    // Find total file size
	infile.seekg(0, std::ios::end);
	d_file_size = infile.tellg();
	infile.seekg(0, std::ios::beg);

    metaData = 0;
    atEnd = false;

    while (infile.tellg() < (long long)d_file_size) {
        
        LeadIn *leadIn = 0;
        try {
            leadIn = new LeadIn(infile);
        } catch (EOFError&) {
            break;
        } catch (Error& error) {
            std::cout << "caught an Error\n" << error.message << std::endl;
        }

        if (infile.eof()) break;
            
        if ((verbose)) {
            leadIn->print();
        }

        unsigned long long posAfterLeadIn = (unsigned long long)infile.tellg();
        long long nextSegmentOffset = leadIn->getNextSegmentOffset();

        if (nextSegmentOffset == -1)
            nextSegmentOffset = d_file_size;

        atEnd = (nextSegmentOffset >= (long long)d_file_size);
        long long nextOffset = (atEnd) ? d_file_size : nextSegmentOffset + (long long)infile.tellg();
        
        if (verbose){
            printf("POS after LeadIn: %llu\n", posAfterLeadIn);
            printf("Next Offset: %llu (0x%X)\n", (unsigned long long)nextOffset, (unsigned int)nextOffset);
        }

        unsigned long long offset = leadIn->getDataOffset(), total_chunk_size = 0;

        if (leadIn->hasMetaData()) {
            metaData = new MetaData(infile, objectDefaults);
            if (verbose) metaData->print();

            if (leadIn->hasRawData()){
                infile.seekg(posAfterLeadIn + offset, std::ios_base::beg);
                if (verbose)
                    printf("\tRaw data starts at POS: 0x%X\n", (unsigned int)infile.tellg());

                metaData->readRawData();

                if (verbose)
                    printf("\tPOS after metadata: 0x%X\n", (unsigned int)infile.tellg());
            }

        } else if (leadIn->hasRawData()) {

            if (verbose)
                printf("\tSegment without metadata!\n");

            total_chunk_size = nextSegmentOffset - offset;
            infile.seekg(posAfterLeadIn + offset, std::ios_base::beg);
            metaData->readRawData();

        } else if (verbose) {
            printf("\tSegment without metadata or raw data!\n");
        }

        data->storeObjects(metaData);

        if (atEnd)
            printf("Should skip to the end of file...File format error?!\n");

        if (nextSegmentOffset >= d_file_size){
            if (verbose)
                printf("\tEnd of file is reached after segment !\n");
            break;
        }

    };
    delete metaData;
}
