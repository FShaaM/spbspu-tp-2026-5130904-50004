#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "shapes.hpp"

namespace zinoviev
{
  double getArea(const Polygon& p);
  void area(const std::vector<Polygon>& p, std::istream& in, std::ostream& out);
  void min(const std::vector<Polygon>& p, std::istream& in, std::ostream& out);
  void max(const std::vector<Polygon>& p, std::istream& in, std::ostream& out);
  void count(const std::vector<Polygon>& p, std::istream& in, std::ostream& out);
  void maxseq(const std::vector<Polygon>& p, std::istream& in, std::ostream& out);
}
#endif
