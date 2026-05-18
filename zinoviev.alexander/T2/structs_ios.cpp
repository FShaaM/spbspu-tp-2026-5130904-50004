#include "structs_ios.hpp"
#include <string>

std::istream& zinoviev::operator>>(std::istream& in, const DelimiterIO&& dest)
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

std::istream& zinoviev::operator>>(std::istream& in, const DoubleLitIO&& dest)
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

std::istream& zinoviev::operator>>(std::istream& in, const UllLitIO&& dest)
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

std::istream& zinoviev::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  return std::getline(in >> DelimiterIO{ '"' }, dest.line, '"');
}

std::istream& zinoviev::operator>>(std::istream& in, const LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  std::string word;
  if (!(in >> word))
    return in;

  if (word != dest.expected)
    in.setstate(std::ios::failbit);

  return in;
}
