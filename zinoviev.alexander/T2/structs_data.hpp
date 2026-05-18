#ifndef STRUCTS_DATA_HPP
#define STRUCTS_DATA_HPP

#include <string>

namespace zinoviev
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
    bool valid;

    DataStruct() : key1(0.0), key2(0), key3(), valid(false) {}
  };
}

#endif
