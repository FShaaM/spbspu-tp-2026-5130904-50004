#include "struct_for_reading.hpp"
#include <limits>

namespace zinoviev
{
  IOGuard::IOGuard(std::basic_ios<char>& s)
    : s_(s),
    precision_(s.precision()),
    width_(s.width()),
    flags_(s.flags()),
    fill_(s.fill())
  {}

  IOGuard::~IOGuard()
  {
    s_.precision(precision_);
    s_.width(width_);
    s_.flags(flags_);
    s_.fill(fill_);
  }

  bool isSpace(char c)
  {
    return c == ' ';
  }

  std::istream& operator>>(std::istream& in, const ExpRead&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    char c;
    in >> c;

    if (in && c != dest.expected)
      in.setstate(std::ios::failbit);

    return in;
  }

  void readAll(std::istream& in, std::vector<Polygon>& polygons)
  {
    Polygon p;
    if (in >> p)
    {
      polygons.push_back(p);
      readAll(in, polygons);
    }
    else if (!in.eof())
    {
      in.clear();
      std::string trash;
      std::getline(in, trash);
      readAll(in, polygons);
    }
    return;
  }
}
