#ifndef INT16_H_
#define INT16_H_

#include "types/DataType.h"

class Int16 : public DataType {
  virtual std::shared_ptr<DataValue> readValue(std::ifstream &infile) const;
  virtual std::shared_ptr<DataArray> readArray(std::ifstream &infile, unsigned int size,
      unsigned int nbytes) const;
  virtual std::shared_ptr<DataArray> newArray(unsigned int size, unsigned int nbytes) const;
  virtual void print(std::ostream &os) const {os << "Int16";}
};

#endif
