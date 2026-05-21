#include "shapes.hpp"
#include "struct_for_reading.hpp"

namespace zinoviev
{
  std::istream& operator>>(std::istream& in, Point& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    Point p{ 0,0 };
    in >> ExpRead{ '(' } >> p.x >> ExpRead{ ';' } >> p.y >> ExpRead{ ')' };

    if (in)
      dest = p;

    return in;
  }

  std::istream& operator>>(std::istream& in, Polygon& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
      return in;

    IOGuard guard(in);
    int n = 0;
    if (!in >> n || n < 3)
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    std::vector<Point> v;
    v.reserve(n);
    std::copy_n(std::istream_iterator<Point>(in), n, std::back_inserter(v));

    if (in && v.size() == n)
      std::swap(dest.points, v);
    else
      in.setstate(std::ios::failbit);

    return in;
  }
}
