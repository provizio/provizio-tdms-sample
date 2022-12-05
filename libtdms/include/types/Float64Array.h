#ifndef FLOAT64ARRAY_H_
#define FLOAT64ARRAY_H_

#include "types/DataArray.h"

class Float64Array : public DataArray
{
public:
  Float64Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>>, unsigned int size);
};

#endif
