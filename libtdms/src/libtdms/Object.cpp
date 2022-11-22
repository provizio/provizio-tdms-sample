#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "libtdms/Error.h"
#include "libtdms/Object.h"
#include "libtdms/ObjectDefaults.h"
#include "types/DataType.h"
#include "types/DataTypeFactory.h"

std::shared_ptr<Object> Object::makeObject(std::ifstream &infile, std::shared_ptr<ObjectDefaults> objectDefaults)
{
    auto obj = std::shared_ptr<Object>(new Object(infile));

    objectDefaults->initializeObject(obj);
    obj->readRawDataInfo();
    obj->readPropertyCount();
    for (unsigned int i = 0; i < obj->propertyCount; ++i)
    {
        obj->readProperty();
    }

    return obj;
}

Object::Object(std::ifstream &infile)
    : infile(infile)
{
    readPath();
}

Object::Property Object::readProperty()
{
    unsigned int len;
    infile.read((char *)&len, 4);
    std::string name(len, '\0');
    infile.read(name.data(), len);
    unsigned int itype;
    infile.read((char *)&itype, 4);
    const DataType *dataType = DataTypeFactory::instanceFromIndex(itype);
    return Property(name, dataType->readValue(infile));
}

void Object::readPath()
{
    unsigned int len;
    infile.read((char *)&len, 4);
    path.resize(len);
    infile.read(path.data(), len);
}

void Object::readRawDataInfo()
{
    unsigned int rawDataIndex;
    const auto startPos = infile.tellg();
    infile.read((char *)&rawDataIndex, 4);
    flagHasRawData = (rawDataIndex != 4294967295);
    if (flagHasRawData && rawDataIndex > 0)
    {
        unsigned int itype;
        infile.read((char *)&itype, 4);
        if (itype != 0xffffffff)
        {
            dataType = DataTypeFactory::instanceFromIndex(itype);
            infile.read((char *)&dimension, 4);
            infile.read((char *)&nvalue, 8);
            if (rawDataIndex >= 28)
            {
                infile.read((char *)&nbytes, 8);
            }
        }
        else
        {
            throw Error("DAQmx raw data is not supported by this parser");
        }

        infile.seekg(startPos + (std::streamoff)rawDataIndex, std::ios_base::beg);
    }
}

void Object::readPropertyCount()
{
    infile.read((char *)&propertyCount, 4);
}

void Object::readRawData()
{
    rawData = dataType->readArray(infile, nvalue, nbytes);
}

bool Object::hasRawData() const
{
    return flagHasRawData;
}

const std::string &Object::getPath() const
{
    return path;
}

const DataType *Object::getDataType() const
{
    return dataType;
}

std::shared_ptr<DataArray> Object::getRawData() const
{
    return rawData;
}
