#ifndef STRUCT_FOR_READING_HPP
#define STRUCT_FOR_READING_HPP

#include <iostream>
#include "shapes.hpp"

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

  struct ExpRead
  {
    char expected;
  };

  bool isSpace(char c);
  std::istream& operator>>(std::istream& in, const ExpRead&& dest);
  void readAll(std::istream& in, std::vector<Polygon>& polygons);
}

#endif
