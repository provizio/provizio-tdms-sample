#include "types/Float128Array.h"

Float128Array::Float128Array(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
                             unsigned int size)
    : DataArray(type, size, 16, data)
{
}
