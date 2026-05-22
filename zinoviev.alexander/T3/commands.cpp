#include <string>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iterator>
#include <map>
#include <limits>
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
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
      }

      if (tops < 3)
      {
        out << "<INVALID COMMAND>\n";
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    if (!(in >> cmd))
    {
      out << "<INVALID COMMAND>\n";
      return;
    }

    if (p.empty())
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return;
    }
  }

  void max(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
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

    if (p.empty())
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return;
    }
  }

  void count(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
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
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
      }

      if (tops < 3)
      {
        out << "<INVALID COMMAND>\n";
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
      }

      FixedCount adder(tops);
      size_t cnt = std::count_if(p.begin(), p.end(), adder);
      out << cnt << '\n';
    }

  }

  size_t findMaxSeq(std::vector<Polygon>::const_iterator begin,
    std::vector<Polygon>::const_iterator end, const Polygon& p)
  {
    if (begin == end)
      return 0;

    auto it = std::find_if(begin, end,
      std::bind(std::equal_to<Polygon>(), p, std::placeholders::_1));

    if (it == end)
      return 0;

    auto next = std::find_if_not(it, end,
      std::bind(std::equal_to<Polygon>(), p, std::placeholders::_1));

    size_t len = next - it;
    size_t nextlen = findMaxSeq(next, end, p);

    return std::max(len, nextlen);
  }

  void maxseq(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g(in);

    Polygon target;
    if (!(in >> target))
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return;
    }

    size_t seq = findMaxSeq(p.cbegin(), p.cend(), target);
    out << seq << "\n";
  }

  void findFrame(const std::vector<Polygon>& p, size_t id_polydon, size_t id_point,
    int& x_min, int& x_max, int& y_min, int& y_max)
  {
    if (id_polydon == p.size())
      return;
    if (id_point == p[id_polydon].points.size())
    {
      findFrame(p, id_polydon + 1, 0, x_min, x_max, y_min, y_max);
      return;
    }

    int p_x = p[id_polydon].points[id_point].x;
    int p_y = p[id_polydon].points[id_point].y;

    x_min = std::min(x_min, p_x);
    x_max = std::max(x_max, p_x);
    y_min = std::min(y_min, p_y);
    y_max = std::max(y_max, p_y);

    findFrame(p, id_polydon, id_point + 1, x_min, x_max, y_min, y_max);
  }

  void inframe(const std::vector<Polygon>& p, std::istream& in, std::ostream& out)
  {
    if (!in)
      return;

    IOGuard g(in);

    Polygon target;
    if (!(in >> target))
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return;
    }

    if (p.empty())
    {
      out << "<FALSE>\n";
      return;
    }

    int x_min = p[0].points[0].x;
    int x_max = p[0].points[0].x;
    int y_min = p[0].points[0].y;
    int y_max = p[0].points[0].y;
    findFrame(p, 0, 0, x_min, x_max, y_min, y_max);

    PointInFrame frame(x_min, x_max, y_min, y_max);
    bool res = std::all_of(target.points.cbegin(), target.points.cend(), frame);

    if (res)
      out << "<TRUE>\n";
    else
      out << "<FALSE>\n";

    return;
  }

  void processCommands(std::istream& in, std::ostream& out,
    const std::map<std::string, std::function<void()>>& cmdMap)
  {
    std::string cmd;
    if (!(in >> cmd))
    {
      if (in.eof())
        return;

      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      processCommands(in, out, cmdMap);
      return;
    }

    auto it = cmdMap.find(cmd);
    if (it == cmdMap.end())
    {
      out << "<INVALID COMMAND>\n";
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      processCommands(in, out, cmdMap);
      return;
    }

    it->second();
    processCommands(in, out, cmdMap);
  }
}
