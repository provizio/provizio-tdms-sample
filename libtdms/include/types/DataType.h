#ifndef TYPES_DATATYPE
#define TYPES_DATATYPE

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

class DataValue;
class DataArray;

class DataType
{
public:
  DataType() {}
  virtual ~DataType() {}
  virtual std::shared_ptr<DataValue> readValue(std::ifstream &infile) const = 0;
  virtual std::shared_ptr<DataArray> readArray(std::ifstream &infile,
                                               unsigned int size, unsigned int nbytes) const = 0;
  virtual std::shared_ptr<DataArray> newArray(unsigned int size, unsigned int nbytes) const = 0;
  virtual void print(std::ostream &os) const {}

private:
  int itype;
};

#endif // TYPES_DATATYPE
