#ifndef TDMS_DATA_H
#define TDMS_DATA_H

#include <string>

class MetaData;
#include "Root.h"

class TDMSData {
    friend class TDMSReader;
public:
    TDMSData(const std::string &filename, bool verbose);
    ~TDMSData();

    int getGroupCount() const;
    Group* getGroup(const std::string&);
    const Root& getRoot() const;
    void print(std::ostream &os) const;
    // define here a function to extract each specific type of data 
    // this is an example to extract a value of OxTS Acceleration (Float64)
    double getDataFloat64(const std::string &group_name, const std::string &channel_name, const unsigned int index);
private:
    const std::string filename;
    void storeObjects(const MetaData*);
    Root root;
    bool isRoot(const std::string& pathName) const;
    bool isGroup(const std::string& pathName) const;
};

#endif
