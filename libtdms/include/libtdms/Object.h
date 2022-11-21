#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <fstream>
#include <map>

#include "types/DataType.h"

class ObjectDefaults;
class DataValue;
class DataArray;

class Object
{
    friend class ObjectDefaults;

public:
    typedef std::pair<std::string, std::shared_ptr<DataValue>> Property;

    static std::shared_ptr<Object> makeObject(std::ifstream &infile, std::shared_ptr<ObjectDefaults> objectDefaults);

    Property readProperty();
    void readPath();
    void readRawDataInfo();
    void readPropertyCount();
    void readRawData();
    bool hasRawData() const;
    const std::string &getPath() const;
    const DataType *getDataType() const;
    std::shared_ptr<DataArray> getRawData() const;

private:
    Object(std::ifstream &infile);

    std::ifstream &infile;
    std::string path;
    std::map<std::string, std::string> properties;
    unsigned int rawDataIndex;
    bool flagHasRawData;
    unsigned int propertyCount;
    const DataType *dataType;
    int dimension;
    long long nvalue;
    long long nbytes;
    std::shared_ptr<DataArray> rawData;
};

#endif
