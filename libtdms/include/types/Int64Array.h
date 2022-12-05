#ifndef INT64ARRAY_H_
#define INT64ARRAY_H_

#include "types/DataArray.h"

class Int64Array : public DataArray
{
public:
  Int64Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};
#endif
