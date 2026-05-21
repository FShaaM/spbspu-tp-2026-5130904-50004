#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>

struct Point
{
  int x, y;
};

struct Polygon
{
  std::vector< Point > points;
};

#endif
