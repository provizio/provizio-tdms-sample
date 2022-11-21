#ifndef LIBTDMS_CHANNEL
#define LIBTDMS_CHANNEL

#include <vector>
#include <string>

#include "types/DataType.h"

class DataArray;

class Channel
{
public:
    typedef std::vector<std::shared_ptr<DataArray>> RawDataSequence;
    Channel(const std::string &name);
    const std::string &getName() const;
    void print(std::ostream &os) const;
    void setDataType(const DataType *type);
    void addRawData(const std::shared_ptr<DataArray> indata);
    unsigned int getDataCount() const;
    const std::shared_ptr<DataArray> getData() const;
    const DataType *getDataType() const;

private:
    const std::string name;
    RawDataSequence rawData;
    const DataType *dataType;
    unsigned int ndata;
    mutable std::shared_ptr<DataArray> data;
};
#endif // LIBTDMS_CHANNEL
