#ifndef UINT16ARRAY_H_
#define UINT16ARRAY_H_

#include "types/DataArray.h"

class UInt16Array : public DataArray {
public:
  UInt16Array(const DataType* type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};

#endif
