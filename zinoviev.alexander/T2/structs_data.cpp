#include "structs_data.hpp"
#include "structs_ios.hpp"
#include <iomanip>
#include <limits>

namespace zinoviev
{
  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    dest.valid = false;
    std::streampos start_pos = in.tellg();

    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    DataStruct input;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;
    bool ok = true;

    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
    if (!in) ok = false;

    while (ok && in)
    {
      in >> std::ws;

      if (in.peek() == ')')
      {
        in >> DelimiterIO{ ')' };
        break;
      }

      std::string name;
      in >> name;
      if (!in) { ok = false; break; }

      if (name == "key1")
      {
        if (hasKey1) { ok = false; break; }
        in >> DoubleLitIO{ input.key1 };
        hasKey1 = true;
      }
      else if (name == "key2")
      {
        if (hasKey2) { ok = false; break; }
        in >> UllLitIO{ input.key2 };
        hasKey2 = true;
      }
      else if (name == "key3")
      {
        if (hasKey3) { ok = false; break; }
        in >> StringIO{ input.key3 };
        hasKey3 = true;
      }
      else
      {
        ok = false;
        break;
      }

      if (!in) { ok = false; break; }
      in >> DelimiterIO{ ':' };
      if (!in) { ok = false; break; }
    }

    if (ok && hasKey1 && hasKey2 && hasKey3 && in)
    {
      dest = input;
      dest.valid = true;
      return in;
    }

    in.clear();
    in.seekg(start_pos);
    char c;
    while (in.get(c) && c != ')');
    if (in) in.clear();
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
      return out;

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
