#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>
#include <iostream>

namespace zinoviev
{
  struct Point
  {
    int x, y;

    bool operator==(const Point& other) const;
  };

  struct Polygon
  {
    std::vector< Point > points;

    bool operator==(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& in, Point& dest);
  std::istream& operator>>(std::istream& in, Polygon& dest);
}
#endif
