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
    // define here a function to extract each specific type of data
    // this is an example to extract a value of OxTS Acceleration (Float64)
    double getDataFloat64(const std::string &group_name, const std::string &channel_name, const unsigned int index);

private:
    const std::string filename;
    void storeObjects(std::shared_ptr<MetaData>);
    Root root;
    bool isRoot(const std::string &pathName) const;
    bool isGroup(const std::string &pathName) const;
};

#endif // LIBTDMS_TDMSDATA
