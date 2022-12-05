#ifndef TYPES_STRINGVALUE
#define TYPES_STRINGVALUE

#include "types/DataValue.h"

class StringValue : public DataValue {
public:
  StringValue(const DataType* type, const std::string &data);
  const std::string data;
};

#endif // TYPES_STRINGVALUE
