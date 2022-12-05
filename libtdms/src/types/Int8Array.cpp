#include "types/Int8Array.h"
#include <iostream>

Int8Array::Int8Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size)
    : DataArray(type, size, 1, data)
{
}
