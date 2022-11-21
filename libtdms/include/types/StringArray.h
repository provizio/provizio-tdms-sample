#ifndef STRINGARRAY_H_
#define STRINGARRAY_H_

#include "types/DataArray.h"

class StringArray : public DataArray {
public:
  StringArray(const DataType* type, std::shared_ptr<std::vector<std::uint8_t>> data, unsigned int size,
    unsigned long int nbytes);
};

#endif
