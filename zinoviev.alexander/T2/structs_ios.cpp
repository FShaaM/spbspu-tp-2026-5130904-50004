#include "structs_ios.hpp"
#include "structs_data.hpp"
#include <iomanip>
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

  std::istream& operator>>(std::istream& in, const DelimiterIO&& dest)
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

  std::istream& operator>>(std::istream& in, const DoubleLitIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    if (!(in >> dest.value))
      return in;

    char c;
    in >> c;
    if (in && c != 'd' && c != 'D')
      in.setstate(std::ios::failbit);
    return in;
  }

  std::istream& operator>>(std::istream& in, const UllLitIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    if (!(in >> dest.value))
      return in;

    char c1, c2, c3;
    in >> c1 >> c2 >> c3;
    if (in)
    {
      bool ok = (c1 == 'u' || c1 == 'U')
             && (c2 == 'l' || c2 == 'L')
             && (c3 == 'l' || c3 == 'L');
      if (!ok)
        in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    in >> DelimiterIO{'"'};
    if (!in)
      return in;

    dest.value.clear();
    char c;
    while (in.get(c) && c != '"')
      dest.value.push_back(c);

    if (!in || c != '"')
      in.setstate(std::ios::failbit);
    return in;
  }
}
