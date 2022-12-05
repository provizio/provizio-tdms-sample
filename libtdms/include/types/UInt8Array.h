#ifndef UINT8ARRAY_H_
#define UINT8ARRAY_H_

#include "types/DataArray.h"

class UInt8Array : public DataArray {
public:
  UInt8Array(const DataType* type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size);
};
#endif
