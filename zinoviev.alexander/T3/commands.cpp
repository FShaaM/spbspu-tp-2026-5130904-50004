#include <string>
#include "commands.hpp"
#include "struct_for_reading.hpp"

namespace zinoviev
{
  double getArea(const Polygon& p, size_t i, double acc)
  {
    if (i == p.points.size())
    {
      return std::abs(acc) / 2.0;
    }
    size_t j = (i + 1) % p.points.size();
    double term = p.points[i].x * p.points[j].y - p.points[j].x * p.points[i].y;
    return getArea(p, i + 1, acc + term);
  }

  void area(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g;

    std::string cmd;
    if (!(in >> cmd))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (cmd == "EVEN")
    {

    }
    else if (cmd == "ODD")
    {

    }
    else if (cmd == "MEAN")
    {

    }
    else
    {
      int top;
      try
      {
        top = std::stoi(cmd);
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
    }

  }
}
