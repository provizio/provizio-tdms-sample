#include "types/Int64.h"
#include "types/Int64Value.h"
#include "types/Int64Array.h"

static_assert(sizeof(long long) == 8, "Unexpected sizeof(long long)");

std::shared_ptr<DataValue> Int64::readValue(std::ifstream &infile) const
{
  long long data;
  infile.read((char *)&data, 8);
  return std::make_shared<Int64Value>(this, data);
}

std::shared_ptr<DataArray> Int64::readArray(std::ifstream &infile, unsigned int size,
                                            unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(long long));
  infile.read((char *)data->data(), size * sizeof(long long));
  return std::make_shared<Int64Array>(this, data, size);
}

std::shared_ptr<DataArray> Int64::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(long long));
  return std::make_shared<Int64Array>(this, data, size);
}
