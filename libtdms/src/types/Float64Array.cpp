#include "types/Float64Array.h"

Float64Array::Float64Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
                           unsigned int size)
    : DataArray(type, size, 8, data)
{
}
