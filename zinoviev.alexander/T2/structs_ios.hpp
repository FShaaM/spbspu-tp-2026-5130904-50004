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

  class IOguard
  {
    std::basic_ios<char>& s_;
    std::streamsize width_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
    char fill_;

  public:
    explicit IOguard(std::basic_ios<char>& s);
    ~IOguard();
  };

  std::istream& operator>>(std::istream& in, const DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, const DoubleLitIO&& dest);
  std::istream& operator>>(std::istream& in, const UllLitIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, const LabelIO&& dest);

}
#endif
