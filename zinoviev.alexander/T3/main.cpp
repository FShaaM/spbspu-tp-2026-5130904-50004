#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "shapes.hpp"
#include "struct_for_reading.hpp"
#include "commands.hpp"

int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: ./lab filename\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "Bad filename\n";
    return 1;
  }

  std::vector<zinoviev::Polygon> polygons;
  zinoviev::readAll(file, polygons);

  std::map< std::string, std::function< void() > > cmd;
  cmd["AREA"] = std::bind(zinoviev::area, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
  cmd["MAX"] = std::bind(zinoviev::max, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
  cmd["MIN"] = std::bind(zinoviev::min, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
  cmd["COUNT"] = std::bind(zinoviev::count, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
  cmd["MAXSEQ"] = std::bind(zinoviev::maxseq, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));
  cmd["INFRAME"] = std::bind(zinoviev::inframe, std::cref(polygons), std::ref(std::cin), std::ref(std::cout));

  zinoviev::processCommands(std::cin, std::cout, cmd);
}
