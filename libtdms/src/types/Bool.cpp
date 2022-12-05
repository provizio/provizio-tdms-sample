#include "types/Bool.h"
#include "types/BoolArray.h"
#include "types/BoolValue.h"

static_assert(sizeof(bool) == 1, "Unexpected sizeof(bool)");

std::shared_ptr<DataValue> Bool::readValue(std::ifstream &infile) const
{
  bool data;
  infile.read((char *)&data, 1);
  return std::make_shared<BoolValue>(this, data);
}

std::shared_ptr<DataArray> Bool::readArray(std::ifstream &infile, unsigned int size,
                                           unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size);
  infile.read((char *)data->data(), size);
  return std::make_shared<BoolArray>(this, data, size);
}

std::shared_ptr<DataArray> Bool::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size);
  return std::make_shared<BoolArray>(this, data, size);
}
