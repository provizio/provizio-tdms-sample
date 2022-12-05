#include "types/UInt32.h"
#include "types/UInt32Value.h"
#include "types/UInt32Array.h"

static_assert(sizeof(unsigned int) == 4, "Unexpected sizeof(unsigned int)");

std::shared_ptr<DataValue> UInt32::readValue(std::ifstream &infile) const
{
  unsigned int data;
  infile.read((char *)&data, 4);
  return std::make_shared<UInt32Value>(this, data);
}

std::shared_ptr<DataArray> UInt32::readArray(std::ifstream &infile, unsigned int size,
                                             unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(unsigned int));
  infile.read((char *)data->data(), size * sizeof(unsigned int));
  return std::make_shared<UInt32Array>(this, data, size);
}

std::shared_ptr<DataArray> UInt32::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(unsigned int));
  return std::make_shared<UInt32Array>(this, data, size);
}
