#include "types/Int16.h"
#include "types/Int16Value.h"
#include "types/Int16Array.h"

std::shared_ptr<DataValue> Int16::readValue(std::ifstream &infile) const
{
  short data;
  infile.read((char *)&data, 2);
  return std::make_shared<Int16Value>(this, data);
}

std::shared_ptr<DataArray> Int16::readArray(std::ifstream &infile, unsigned int size,
                                            unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<uint8_t>>(size * sizeof(short));
  infile.read((char *)data->data(), size * sizeof(short));
  return std::make_shared<Int16Array>(this, data, size);
}

std::shared_ptr<DataArray> Int16::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<uint8_t>>(size * sizeof(short));
  return std::make_shared<Int16Array>(this, data, size);
}
