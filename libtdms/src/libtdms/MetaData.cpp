#include <iostream>
#include <fstream>

#include "libtdms/MetaData.h"
#include "libtdms/Object.h"

MetaData::MetaData(std::ifstream &infile, std::shared_ptr<ObjectDefaults> objectDefaults)
    : infile(infile), objectDefaults(objectDefaults), objectCount()
{
    readObjectCount();
    
    objects.reserve(objectCount);
    for (unsigned int i = 0; i < objectCount; ++i)
    {
        objects.push_back(Object::makeObject(infile, objectDefaults));
    }
}

void MetaData::readObjectCount()
{
    infile.read((char *)&objectCount, 4);
}

void MetaData::readRawData(const bool verbose)
{
    if (verbose)
    {
        std::cout << "\nRead raw data" << std::endl;
    }
    for (ObjectList::iterator object = objects.begin();
         object != objects.end(); ++object)
    {
        if ((*object)->hasRawData())
        {
            if (verbose)
            {
                std::string path = (*object)->getPath();
                std::cout << "\t" << path << std::endl;
            }
            (*object)->readRawData();
        }
    }
}

void MetaData::print() const
{
    std::cout << "\nRead meta data" << std::endl;
    std::cout << "  Contains " << objectCount << " objects." << std::endl;
}

const MetaData::ObjectList &MetaData::getObjectList() const
{
    return objects;
}
