#ifndef FLOAT128_H_
#define FLOAT128_H_

#include "types/DataType.h"

class Float128 : public DataType {
  virtual std::shared_ptr<DataValue> readValue(std::ifstream &infile) const;
  virtual std::shared_ptr<DataArray> readArray(std::ifstream &infile, unsigned int size,
      unsigned int nbytes) const;
  virtual std::shared_ptr<DataArray> newArray(unsigned int size, unsigned int nbytes) const;
  virtual void print(std::ostream &os) const {os << "Float128";}
};

#endif
