#include "types/StringArray.h"

StringArray::StringArray(const DataType *type, std::shared_ptr<std::vector<std::uint8_t>> data,
                         unsigned int size, unsigned long int nbytes)
    : DataArray(type, size, nbytes / size, data)
{
}
