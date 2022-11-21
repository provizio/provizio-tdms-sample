#include "types/Float64.h"
#include "types/Float64Value.h"
#include "types/Float64Array.h"

static_assert(sizeof(double) == 8, "Unexpected sizeof(double)");

std::shared_ptr<DataValue> Float64::readValue(std::ifstream &infile) const
{
  double data;
  infile.read((char *)&data, 8);
  return std::make_shared<Float64Value>(this, data);
}

std::shared_ptr<DataArray> Float64::readArray(std::ifstream &infile, unsigned int size,
                                              unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(double));
  infile.read((char *)data->data(), size * sizeof(double));
  return std::make_shared<Float64Array>(this, data, size);
}

std::shared_ptr<DataArray> Float64::newArray(unsigned int size, unsigned int nbytes) const
{
  auto data = std::make_shared<std::vector<std::uint8_t>>(size * sizeof(double));
  return std::make_shared<Float64Array>(this, data, size);
}
