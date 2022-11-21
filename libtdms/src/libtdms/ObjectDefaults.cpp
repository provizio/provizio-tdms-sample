#include <iostream>

#include "libtdms/ObjectDefaults.h"
#include "libtdms/Object.h"

void ObjectDefaults::initializeObject(std::shared_ptr<Object> obj)
{
    std::string path = obj->getPath();
    if (objects.count(path))
    {
        auto old = objects[path];
        obj->properties = old->properties;
        obj->flagHasRawData = old->flagHasRawData;
        if (obj->flagHasRawData)
        {
            obj->dataType = old->dataType;
            obj->dimension = old->dimension;
            obj->nvalue = old->nvalue;
            obj->nbytes = old->nbytes;
        }
    }
    else
    {
        objects[path] = obj;
    }
}
