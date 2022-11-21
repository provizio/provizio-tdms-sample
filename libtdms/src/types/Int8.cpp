#include "types/Int8.h"
#include "types/Int8Value.h"
#include "types/Int8Array.h"
#include <fstream>

static_assert(sizeof(char) == 1, "Unexpected sizeof(char)");

std::shared_ptr<DataValue> Int8::readValue(std::ifstream &infile) const
{
  char data;
  infile.read(&data, 1);
  return std::make_shared<Int8Value>(this, data);
}

std::shared_ptr<DataArray> Int8::readArray(std::ifstream &infile, unsigned int size,
                                           unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size);
  infile.read((char*)data->data(), size);
  return std::make_shared<Int8Array>(this, data, size);
}

std::shared_ptr<DataArray> Int8::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size);
  return std::make_shared<Int8Array>(this, data, size);
}
