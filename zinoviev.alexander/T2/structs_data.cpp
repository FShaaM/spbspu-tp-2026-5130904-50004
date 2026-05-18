#include "structs_data.hpp"
#include "structs_ios.hpp"
#include <iomanip>

std::istream& zinoviev::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  DataStruct input;
  bool hasKey1 = false;
  bool hasKey2 = false;
  bool hasKey3 = false;

  in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' };
  while (in)
  {
    in >> std::ws;

    if (in.peek() == ')')
    {
      in >> DelimiterIO{ ')' };
      break;
    }

    std::string name;
    in >> name;

    if (name == "key1")
    {
      in >> DoubleLitIO{ input.key1 };
      hasKey1 = true;
    }
    else if (name == "key2")
    {
      in >> UllLitIO{ input.key2 };
      hasKey2 = true;
    }
    else if (name == "key3")
    {
      in >> StringIO{ input.key3 };
      hasKey3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> DelimiterIO{ ':' };
  }

  if (hasKey1 && hasKey2 && hasKey3)
    dest = input;
  else
    in.setstate(std::ios::failbit);

  return in;
}

std::ostream& zinoviev::operator<<(std::ostream& out, const DataStruct& src)
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
