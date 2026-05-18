#ifndef STRUCTS_IOS_HPP
#define STRUCTS_IOS_HPP

#include <iostream>
#include <string>
#include <vector>
#include "structs_data.hpp"

namespace zinoviev
{
  class IOGuard
  {
  public:
    explicit IOGuard(std::basic_ios<char>& s);
    ~IOGuard();
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::streamsize width_;
    std::basic_ios<char>::fmtflags flags_;
    char fill_;
  };

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
    std::string& value;
  };

  std::istream& operator>>(std::istream& in, const DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, const DoubleLitIO&& dest);
  std::istream& operator>>(std::istream& in, const UllLitIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);

  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);

  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
