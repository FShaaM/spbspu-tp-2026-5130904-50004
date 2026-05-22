#ifndef STRUCTS_FOR_COMMANDS_HPP
#define STRUCTS_FOR_COMMANDS_HPP

#include "shapes.hpp"
#include "commands.hpp"

namespace zinoviev
{
  struct EvenAdder
  {
    double operator()(double acc, const Polygon& p) const
    {
      return acc + ((p.points.size() % 2 == 0) ? getArea(p) : 0.0);
    }
  };

  struct OddAdder
  {
    double operator()(double acc, const Polygon& p) const
    {
      return acc + ((p.points.size() % 2 == 1) ? getArea(p) : 0.0);
    }
  };

  struct AllAdder {
    double operator()(double acc, const Polygon& p) const
    {
      return acc + getArea(p);
    }
  };

  struct FixedAdder
  {
    size_t target;

    explicit FixedAdder(size_t t) :
      target(t)
    {}

    double operator()(double acc, const Polygon& p) const
    {
      return acc + ((p.points.size() == target) ? getArea(p) : 0.0);
    }
  };

  struct AreaLess
  {
    bool operator()(const Polygon& a, const Polygon& b) const
    {
      return getArea(a) < getArea(b);
    }
  };

  struct VertexesLess
  {
    bool operator()(const Polygon& a, const Polygon& b) const
    {
      return a.points.size() < b.points.size();
    }
  };

  struct EvenCount
  {
    int operator()(const Polygon& p) const
    {
      return p.points.size() % 2 == 0;
    }
  };

  struct OddCount
  {
    int operator()(const Polygon& p) const
    {
      return p.points.size() % 2 == 1;
    }
  };

  struct FixedCount
  {
    size_t target;

    explicit FixedCount(size_t t) :
      target(t)
    {
    }

    int operator()(const Polygon& p) const
    {
      return p.points.size() == target;
    }
  };

  struct PointInFrame
  {
    int x_min;
    int x_max;
    int y_min;
    int y_max;

    PointInFrame(int min_x, int max_x, int min_y, int max_y) :
      x_min(min_x),
      x_max(max_x),
      y_min(min_y),
      y_max(max_y)
    {}

    bool operator()(const Point& pt) const
    {
      return pt.x >= x_min && pt.x <= x_max && pt.y >= y_min && pt.y <= y_max;
    }
  };
}

#endif
