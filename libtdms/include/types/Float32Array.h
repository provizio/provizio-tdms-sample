#ifndef FLOAT32ARRAY_H_
#define FLOAT32ARRAY_H_

#include "types/DataArray.h"

class Float32Array : public DataArray {
public:
  Float32Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};

#endif
