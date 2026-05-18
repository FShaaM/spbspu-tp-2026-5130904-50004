#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include "structs_data.hpp"
#include "structs_ios.hpp"

int main()
{
  using namespace zinoviev;

  std::vector<DataStruct> raw;
  std::copy(std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(raw));

  std::vector<DataStruct> data;
  std::copy_if(raw.begin(), raw.end(),
         std::back_inserter(data),
         [](const DataStruct& ds) { return ds.valid; });

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n"));
}
