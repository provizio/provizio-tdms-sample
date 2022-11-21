#ifndef TYPES_DATAARRAY
#define TYPES_DATAARRAY

#include <cstdint>
#include <memory>
#include <vector>

#include "types/DataType.h"

class DataArray
{
public:
  DataArray(const DataType *type, unsigned int size, int sizeOf)
      : type(type), size(size), sizeOf(sizeOf)
  {
  }
  DataArray(const DataType *type, unsigned int size, int sizeOf, std::shared_ptr<std::vector<std::uint8_t>> data)
      : type(type), size(size), sizeOf(sizeOf), data(data)
  {
  }
  virtual ~DataArray() {}
  unsigned int getSize() const { return size; }
  int getSizeOf() const { return sizeOf; }
  std::shared_ptr<std::vector<std::uint8_t>> getData() const { return data; }

private:
  const DataType *type;
  unsigned int size;
  int sizeOf;
  std::shared_ptr<std::vector<std::uint8_t>> data;
};

#endif // TYPES_DATAARRAY
