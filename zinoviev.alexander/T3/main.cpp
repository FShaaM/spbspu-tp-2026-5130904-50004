#include <fstream>
#include <iostream>
#include <vector>
#include "shapes.hpp"
#include "struct_for_reading.hpp"

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
}
