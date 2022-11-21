#include "types/BoolArray.h"

BoolArray::BoolArray(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size)
    : DataArray(type, size, 1, data)
{
}
