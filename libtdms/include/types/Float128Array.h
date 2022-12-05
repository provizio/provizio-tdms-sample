#ifndef FLOAT128ARRAY_H_
#define FLOAT128ARRAY_H_

#include "types/DataArray.h"

class Float128Array : public DataArray
{
public:
  Float128Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};

#endif
