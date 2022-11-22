#ifndef LIBTDMS_TDMSDATA
#define LIBTDMS_TDMSDATA

#include <string>

#include "Root.h"
#include "MetaData.h"
#include "Object.h"

#include "types/DataArray.h"
#include "types/DataValue.h"

class TDMSData
{
    friend class TDMSReader;

public:
    virtual ~TDMSData() {}

    void read(const std::string &filename, bool verbose);

    int getGroupCount() const;
    std::shared_ptr<Group> getGroup(const std::string &);
    const Root &getRoot() const;
    void print(std::ostream &os) const;

protected:
    // By default appends raw data, if any
    virtual void addObject(std::shared_ptr<Group> group, std::shared_ptr<Channel> channel, std::shared_ptr<Object> object);

private:
    void storeObjects(std::shared_ptr<MetaData>);
    Root root;
    bool isRoot(const std::string &pathName) const;
    bool isGroup(const std::string &pathName) const;
};

#endif // LIBTDMS_TDMSDATA
