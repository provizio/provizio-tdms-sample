#ifndef LIBTDMS_TDMSREADER
#define LIBTDMS_TDMSREADER

#include <memory>

#include "ObjectDefaults.h"

class MetaData;
class TDMSData;

class TDMSReader {
public:
    void read(const std::string &filename, TDMSData*, const bool verbose=true);
private:
    std::shared_ptr<ObjectDefaults> objectDefaults;
    std::shared_ptr<MetaData> metaData;
};

#endif // LIBTDMS_TDMSREADER
