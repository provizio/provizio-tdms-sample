#include "types/UInt16Array.h"

UInt16Array::UInt16Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
                         unsigned int size)
    : DataArray(type, size, 2, data)
{
}
