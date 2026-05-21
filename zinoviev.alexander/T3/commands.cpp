#include <string>
#include <numeric>
#include <iomanip>
#include "commands.hpp"
#include "struct_for_reading.hpp"
#include "structs_for_commands.hpp"

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

  double getArea(const Polygon& p)
  {
    return getArea(p, 0, 0.0);
  }

  void area(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g(in);

    std::string cmd;
    if (!(in >> cmd))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (cmd == "EVEN")
    {
      if (p.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }

      double sum = std::accumulate(p.begin(), p.end(), 0.0, EvenAdder());
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (cmd == "ODD")
    {
      if (p.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }

      double sum = std::accumulate(p.begin(), p.end(), 0.0, OddAdder());
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (cmd == "MEAN")
    {
      if (p.empty()) {
        out << "<INVALID COMMAND>\n";
        return;
      }
      double sum = std::accumulate(p.begin(), p.end(), 0.0, AllAdder());
      double mean = sum / p.size();
      out << std::fixed << std::setprecision(1) << mean << '\n';
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

      if (top < 3)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }

      FixedAdder adder(static_cast<size_t>(top));
      double sum = std::accumulate(p.begin(), p.end(), 0.0, adder);
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }

  }
}
