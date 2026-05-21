#include <string>
#include <numeric>
#include <algorithm>
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
      double sum = std::accumulate(p.begin(), p.end(), 0.0, EvenAdder());
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (cmd == "ODD")
    {
      double sum = std::accumulate(p.begin(), p.end(), 0.0, OddAdder());
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    else if (cmd == "MEAN")
    {
      if (p.empty())
      {
        out << "<INVALID COMMAND>\n";
        return;
      }

      double sum = std::accumulate(p.begin(), p.end(), 0.0, AllAdder());
      double mean = sum / p.size();
      out << std::fixed << std::setprecision(1) << mean << '\n';
    }
    else
    {
      size_t tops = 0;
      try
      {
        tops = std::stoull(cmd);
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }

      if (tops < 3)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }

      FixedAdder adder(tops);
      double sum = std::accumulate(p.begin(), p.end(), 0.0, adder);
      out << std::fixed << std::setprecision(1) << sum << '\n';
    }

  }

  void min(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g(in);

    std::string cmd;
    if (!(in >> cmd) || p.empty())
    {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (cmd == "AREA")
    {
      auto it = std::min_element(p.begin(), p.end(), AreaLess());
      double minArea = getArea(*it);
      out << std::fixed << std::setprecision(1) << minArea << '\n';
    }
    else if (cmd == "VERTEXES")
    {
      auto it = std::min_element(p.begin(), p.end(), VertexesLess());
      size_t minVert = it->points.size();
      out << minVert << '\n';
    }
    else
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
  }

  void max(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g(in);

    std::string cmd;
    if (!(in >> cmd) || p.empty())
    {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (cmd == "AREA")
    {
      auto it = std::max_element(p.begin(), p.end(), AreaLess());
      double maxArea = getArea(*it);
      out << std::fixed << std::setprecision(1) << maxArea << '\n';
    }
    else if (cmd == "VERTEXES")
    {
      auto it = std::max_element(p.begin(), p.end(), VertexesLess());
      size_t maxVert = it->points.size();
      out << maxVert << '\n';
    }
    else
    {
      out << "<INVALID COMMAND>\n";
      return;
    }
  }

  void count(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g(in);

    std::string cmd;
    if (!(in >> cmd) || p.empty())
    {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (cmd == "EVEN")
    {
      size_t cnt = std::count_if(p.begin(), p.end(), EvenCount());
      out << cnt << '\n';
    }
    else if (cmd == "ODD")
    {
      size_t cnt = std::count_if(p.begin(), p.end(), OddCount());
      out << cnt << '\n';
    }
    else
    {
      size_t tops = 0;
      try
      {
        tops = std::stoull(cmd);
      }
      catch (...)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }

      if (tops < 3)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }

      FixedCount adder(tops);
      size_t cnt = std::count_if(p.begin(), p.end(), adder);
      out << cnt << '\n';
    }

  }
}
