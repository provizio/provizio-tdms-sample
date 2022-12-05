#ifndef DATA_VALUE_H
#define DATA_VALUE_H

#include <string>

#include "types/DataType.h"

class DataValue {
public:
  DataValue(const DataType*);
  virtual ~DataValue() {}
private:
  const DataType *type;
};

#endif
