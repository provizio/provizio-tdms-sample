#ifndef TDMS_READER_H
#define TDMS_READER_H

#include <memory>

#include "ObjectDefaults.h"

class MetaData;
class TDMSData;

class TDMSReader {
public:
    TDMSReader();
    ~TDMSReader();
    void checkSizeOfTypes();
    void read(const std::string &filename, TDMSData*, const bool verbose=true);
private:
    std::shared_ptr<ObjectDefaults> objectDefaults;
    std::shared_ptr<MetaData> metaData;
    unsigned long long file_size;
    bool atEnd;
};

#endif
