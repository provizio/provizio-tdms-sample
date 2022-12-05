#ifndef BOOLARRAY_H_
#define BOOLARRAY_H_

#include "types/DataArray.h"

class BoolArray : public DataArray {
public:
  BoolArray(const DataType* type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};

#endif
