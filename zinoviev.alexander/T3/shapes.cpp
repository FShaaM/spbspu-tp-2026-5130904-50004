#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "shapes.hpp"
#include "struct_for_reading.hpp"

namespace zinoviev
{
  bool Point::operator==(const Point& other) const
  {
    return x == other.x && y == other.y;
  }

  bool Polygon::operator==(const Polygon& other) const
  {
    if (other.points.size() != points.size())
      return false;
    return std::equal(points.cbegin(), points.cend(), other.points.cbegin());
  }

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

    int n = 0;
    in >> n;
    if (!in || n < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }


    std::vector<Point> v;
    v.reserve(n);
    std::copy_n(std::istream_iterator<Point>(in), n, std::back_inserter(v));

    if (in && v.size() == static_cast<size_t>(n))
      std::swap(dest.points, v);
    else
      in.setstate(std::ios::failbit);

    return in;
  }
}
