#include "types/String.h"
#include "types/StringArray.h"
#include "types/StringValue.h"

std::shared_ptr<DataValue> String::readValue(std::ifstream &infile) const
{
  unsigned int strlen;
  infile.read((char *)&strlen, 4);
  std::string str(strlen, '\0');
  infile.read(str.data(), strlen);
  return std::make_shared<StringValue>(this, str);
}

std::shared_ptr<DataArray> String::readArray(std::ifstream &infile, unsigned int size,
                                             unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(nbytes);
  infile.read((char *)data->data(), nbytes);
  return std::make_shared<StringArray>(this, data, size, nbytes);
}

std::shared_ptr<DataArray> String::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(nbytes);
  return std::make_shared<StringArray>(this, data, size, nbytes);
}
