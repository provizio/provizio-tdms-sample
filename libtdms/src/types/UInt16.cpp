#include "types/UInt16.h"
#include "types/UInt16Array.h"
#include "types/UInt16Value.h"

static_assert(sizeof(unsigned short) == 2, "Unexpected sizeof(unsigned short)");

std::shared_ptr<DataValue> UInt16::readValue(std::ifstream &infile) const
{
  unsigned short data;
  infile.read((char *)&data, 2);
  return std::make_shared<UInt16Value>(this, data);
}

std::shared_ptr<DataArray> UInt16::readArray(std::ifstream &infile, unsigned int size,
                                             unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(unsigned short));
  infile.read((char *)data->data(), size * sizeof(unsigned short));
  return std::make_shared<UInt16Array>(this, data, size);
}

std::shared_ptr<DataArray> UInt16::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(unsigned short));
  return std::make_shared<UInt16Array>(this, data, size);
}
