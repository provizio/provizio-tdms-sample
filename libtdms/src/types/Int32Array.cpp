#include "types/Int32Array.h"

Int32Array::Int32Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size)
    : DataArray(type, size, 4, data)
{
}
