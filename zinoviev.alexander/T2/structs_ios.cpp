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

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    dest.valid = false;
    DataStruct tmp;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    bool ok = true;

    std::streampos start_pos = in.tellg();

    in >> DelimiterIO{'('} >> DelimiterIO{':'};
    if (!in) { ok = false; }

    while (ok && in)
    {
      in >> std::ws;

      if (in.peek() == ')')
      {
        in >> DelimiterIO{')'};
        break;
      }

      std::string name;
      in >> name;
      if (!in) { ok = false; break; }

      if (name == "key1")
      {
        if (hasKey1) { ok = false; break; }
        in >> DoubleLitIO{ tmp.key1 };
        hasKey1 = true;
      }
      else if (name == "key2")
      {
        if (hasKey2) { ok = false; break; }
        in >> UllLitIO{ tmp.key2 };
        hasKey2 = true;
      }
      else if (name == "key3")
      {
        if (hasKey3) { ok = false; break; }
        in >> StringIO{ tmp.key3 };
        hasKey3 = true;
      }
      else
      {
        ok = false;
        break;
      }

      if (!in) { ok = false; break; }

      in >> DelimiterIO{':'};
      if (!in) { ok = false; break; }
    }

    if (ok && hasKey1 && hasKey2 && hasKey3 && in)
    {
      dest = tmp;
      dest.valid = true;
      return in;
    }

    in.clear();
    in.seekg(start_pos);
    char c;
    while (in.get(c) && c != ')');
    if (in) {
      in.clear();
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    IOGuard guard(out);
    out << "(:key1 "
        << std::fixed << std::setprecision(1) << src.key1 << "d"
        << ":key2 " << src.key2 << "ull"
        << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
      return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2)
      return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
  }
}
