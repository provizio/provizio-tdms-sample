#include "types/UInt8.h"
#include "types/UInt8Array.h"
#include "types/UInt8Value.h"

static_assert(sizeof(unsigned char) == 1, "Unexpected sizeof(unsigned char)");

std::shared_ptr<DataValue> UInt8::readValue(std::ifstream &infile) const
{
  unsigned char data;
  infile.read((char *)&data, 1);
  return std::make_shared<UInt8Value>(this, data);
}

std::shared_ptr<DataArray> UInt8::readArray(std::ifstream &infile, unsigned int size,
                                            unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size);
  infile.read((char *)data->data(), size);
  return std::make_shared<UInt8Array>(this, data, size);
}

std::shared_ptr<DataArray> UInt8::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size);
  return std::make_shared<UInt8Array>(this, data, size);
}
