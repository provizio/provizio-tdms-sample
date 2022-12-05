#include "types/DataTypeFactory.h"
#include "libtdms/Error.h"
#include "types/Int8.h"
#include "types/Int16.h"
#include "types/Int32.h"
#include "types/Int64.h"
#include "types/UInt8.h"
#include "types/UInt16.h"
#include "types/UInt32.h"
#include "types/UInt64.h"
#include "types/Float32.h"
#include "types/Float64.h"
#include "types/Float128.h"
#include "types/String.h"
#include "types/Bool.h"

std::map<int, std::shared_ptr<DataType>> DataTypeFactory::singletonObjects;

const DataType *DataTypeFactory::instanceFromIndex(unsigned int itype)
{
  if (singletonObjects.size() == 0)
  {
    // std::cout << "initializing objects" << std::endl;
    singletonObjects[INT8] = std::make_shared<Int8>();
    singletonObjects[INT16] = std::make_shared<Int16>();
    singletonObjects[INT32] = std::make_shared<Int32>();
    singletonObjects[INT64] = std::make_shared<Int64>();
    singletonObjects[UINT8] = std::make_shared<UInt8>();
    singletonObjects[UINT16] = std::make_shared<UInt16>();
    singletonObjects[UINT32] = std::make_shared<UInt32>();
    singletonObjects[UINT64] = std::make_shared<UInt64>();
    singletonObjects[FLOAT32] = std::make_shared<Float32>();
    singletonObjects[FLOAT64] = std::make_shared<Float64>();
    singletonObjects[FLOAT128] = std::make_shared<Float128>();
    singletonObjects[STRING] = std::make_shared<String>();
    singletonObjects[BOOL] = std::make_shared<Bool>();
  }
  if (singletonObjects.count(itype) == 0)
  {
    throw IOError("Unimplented data type");
  }
  return singletonObjects[itype].get();
}

const int DataTypeFactory::INT8 = 1;
const int DataTypeFactory::INT16 = 2;
const int DataTypeFactory::INT32 = 3;
const int DataTypeFactory::INT64 = 4;
const int DataTypeFactory::UINT8 = 5;
const int DataTypeFactory::UINT16 = 6;
const int DataTypeFactory::UINT32 = 7;
const int DataTypeFactory::UINT64 = 8;
const int DataTypeFactory::FLOAT32 = 9;
const int DataTypeFactory::FLOAT64 = 10;
const int DataTypeFactory::FLOAT128 = 11;
const int DataTypeFactory::STRING = 32;
const int DataTypeFactory::BOOL = 33;
