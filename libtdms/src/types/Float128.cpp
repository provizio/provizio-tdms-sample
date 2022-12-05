#include "types/Float128.h"
#include "types/Float128Array.h"
#include "types/Float128Value.h"

static_assert(sizeof(long double) == 16, "Unexpected sizeof(long double)");

std::shared_ptr<DataValue> Float128::readValue(std::ifstream &infile) const
{
  long double data;
  infile.read((char *)&data, 16);
  return std::make_shared<Float128Value>(this, data);
}

std::shared_ptr<DataArray> Float128::readArray(std::ifstream &infile,
                                               unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(long double));
  infile.read((char *)data->data(), size * sizeof(long double));
  return std::make_shared<Float128Array>(this, data, size);
}

std::shared_ptr<DataArray> Float128::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(long double));
  return std::make_shared<Float128Array>(this, data, size);
}
