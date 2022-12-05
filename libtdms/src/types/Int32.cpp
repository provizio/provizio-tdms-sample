#include "types/Int32.h"
#include "types/Int32Value.h"
#include "types/Int32Array.h"

static_assert(sizeof(int) == 4, "Unexpected sizeof(int)");

std::shared_ptr<DataValue> Int32::readValue(std::ifstream &infile) const
{
  int data;
  infile.read((char *)&data, 4);
  return std::make_shared<Int32Value>(this, data);
}

std::shared_ptr<DataArray> Int32::readArray(std::ifstream &infile, unsigned int size,
                                            unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(int));
  infile.read((char *)data->data(), size * sizeof(int));
  return std::make_shared<Int32Array>(this, data, size);
}

std::shared_ptr<DataArray> Int32::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(int));
  return std::make_shared<Int32Array>(this, data, size);
}
