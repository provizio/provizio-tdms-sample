#include "types/UInt8Array.h"

UInt8Array::UInt8Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
                       unsigned int size)
    : DataArray(type, size, 1, data)
{
}
