#ifndef INT32ARRAY_H_
#define INT32ARRAY_H_

#include "DataArray.h"

class Int32Array : public DataArray {
public:
  Int32Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};

#endif
