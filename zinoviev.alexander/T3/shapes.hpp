#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <vector>

namespace zinoviev
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };
}
#endif
