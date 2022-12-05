#include "types/UInt64.h"
#include "types/UInt64Array.h"
#include "types/UInt64Value.h"

static_assert(sizeof(unsigned long long) == 8, "Unexpected sizeof(unsigned long long)");

std::shared_ptr<DataValue> UInt64::readValue(std::ifstream &infile) const
{
  unsigned long long data;
  infile.read((char *)&data, 8);
  return std::make_shared<UInt64Value>(this, data);
}

std::shared_ptr<DataArray> UInt64::readArray(std::ifstream &infile, unsigned int size,
                                             unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(unsigned long long));
  infile.read((char *)data->data(), size * sizeof(unsigned long long));
  return std::make_shared<UInt64Array>(this, data, size);
}

std::shared_ptr<DataArray> UInt64::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(unsigned long long));
  return std::make_shared<UInt64Array>(this, data, size);
}
