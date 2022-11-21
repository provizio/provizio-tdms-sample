#ifndef UINT64ARRAY_H_
#define UINT64ARRAY_H_

#include "types/DataArray.h"

class UInt64Array : public DataArray
{
public:
  UInt64Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
              unsigned int size);
};

#endif
