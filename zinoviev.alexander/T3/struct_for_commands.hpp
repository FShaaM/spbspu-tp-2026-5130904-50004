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
}

#endif
