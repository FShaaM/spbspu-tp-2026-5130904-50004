#ifndef STRUCTS_IOS_HPP
#define STRUCTS_IOS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

namespace zinoviev
{
  struct DelimiterIO
  {
    char expected;
  };

  struct DoubleLitIO
  {
    double& value;
  };

  struct UllLitIO
  {
    unsigned long long& value;
  };

  struct StringIO
  {
    std::string line;
  };

  struct LabelIO
  {
    std::string expected;
  };

  std::istream& operator>>(std::istream& in, const DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, const DoubleLitIO&& dest);
  std::istream& operator>>(std::istream& in, const UllLitIO&& dest);
  std::istream& operator>>(std::istream& in, const StringIO&& dest);
  std::istream& operator>>(std::istream& in, const LabelIO&& dest);

}
#endif
