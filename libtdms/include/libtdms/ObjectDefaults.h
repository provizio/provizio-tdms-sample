#ifndef LIBTDMS_OBJECTDEFAULTS
#define LIBTDMS_OBJECTDEFAULTS

#include <map>
#include <memory>

#include "Object.h"

class ObjectDefaults {
public:
    void initializeObject(std::shared_ptr<Object> obj);

private:
    std::map<std::string, std::shared_ptr<Object>> objects;
};

#endif // LIBTDMS_OBJECTDEFAULTS
