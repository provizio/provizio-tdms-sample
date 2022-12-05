#include "types/Float32.h"
#include "types/Float32Array.h"
#include "types/Float32Value.h"

static_assert(sizeof(float) == 4, "Unexpected sizeof(float)");

std::shared_ptr<DataValue> Float32::readValue(std::ifstream &infile) const
{
  float data;
  infile.read((char *)&data, 4);
  return std::make_shared<Float32Value>(this, data);
}

std::shared_ptr<DataArray> Float32::readArray(std::ifstream &infile, unsigned int size,
                                              unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(float));
  infile.read((char *)data->data(), size * sizeof(float));
  return std::make_shared<Float32Array>(this, data, size);
}

std::shared_ptr<DataArray> Float32::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(float));
  return std::make_shared<Float32Array>(this, data, size);
}
