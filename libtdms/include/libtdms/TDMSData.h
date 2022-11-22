#ifndef LIBTDMS_TDMSDATA
#define LIBTDMS_TDMSDATA

#include <string>

class MetaData;
#include "Root.h"

class TDMSData
{
    friend class TDMSReader;

public:
    TDMSData(const std::string &filename, bool verbose);
    ~TDMSData();

    int getGroupCount() const;
    std::shared_ptr<Group> getGroup(const std::string &);
    const Root &getRoot() const;
    void print(std::ostream &os) const;

private:
    const std::string filename;
    void storeObjects(std::shared_ptr<MetaData>);
    Root root;
    bool isRoot(const std::string &pathName) const;
    bool isGroup(const std::string &pathName) const;
};

#endif // LIBTDMS_TDMSDATA
