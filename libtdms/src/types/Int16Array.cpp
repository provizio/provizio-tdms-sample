#include "types/Int16Array.h"

Int16Array::Int16Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size)
    : DataArray(type, size, 2, data)
{
}
