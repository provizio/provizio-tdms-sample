#ifndef LIBTDMS_METADATA
#define LIBTDMS_METADATA

#include <fstream>
#include <vector>
#include <memory>

#include "ObjectDefaults.h"
#include "Object.h"

class MetaData
{
public:
    typedef std::vector<std::shared_ptr<Object>> ObjectList;
    MetaData(std::ifstream &infile, std::shared_ptr<ObjectDefaults> objectDefaults);
    void readObjectCount();
    void readRawData(const bool verbose);
    void print() const;
    const ObjectList &getObjectList() const;

private:
    std::ifstream &infile;
    std::shared_ptr<ObjectDefaults> objectDefaults;
    unsigned int objectCount;
    ObjectList objects;
};

#endif // LIBTDMS_METADATA
