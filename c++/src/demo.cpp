#include "../include/easydump.hpp"

#include <iostream> // cout
#include <map>
#include <fstream>
#include <vector>

int main (int argc, char *argv[]) {
  auto x = std::map<int, std::vector<double>>();
  // auto x = std::vector<int>();

  auto fin = std::ifstream(argv[1], std::ios::binary);
  easydump::bin::load(x, fin);
  fin.close();

  easydump::txt::dump(x, std::cout);

  return 0;
}
