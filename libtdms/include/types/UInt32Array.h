#ifndef UINT32ARRAY_H_
#define UINT32ARRAY_H_

#include "types/DataArray.h"

class UInt32Array : public DataArray {
public:
  UInt32Array(const DataType* type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};

#endif
