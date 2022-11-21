#ifndef META_DATA_H
#define META_DATA_H

#include <fstream>
#include <list>
#include <memory>

#include "ObjectDefaults.h"
#include "Object.h"

class MetaData
{
public:
    typedef std::list<std::shared_ptr<Object>> ObjectList;
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

#endif
