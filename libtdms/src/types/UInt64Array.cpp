#include "types/UInt64Array.h"

UInt64Array::UInt64Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
                         unsigned int size)
    : DataArray(type, size, 8, data)
{
}
