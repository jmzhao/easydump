#include "../include/easydump.hpp"

#include <iostream> // cout
#include <map>
#include <utility> // pair
#include <vector>

int main () {
  std::cout << "dump int:" << std::endl;
  int n = 9;
  easydump::dump(n, std::cout);
  std::cout << std::endl;

  std::cout << "dump double:" << std::endl;
  double x = 0.123;
  easydump::dump(x, std::cout);
  std::cout << std::endl;

  std::cout << "dump std::pair:" << std::endl;
  auto p = std::make_pair(n, x);
  easydump::dump(p, std::cout);
  std::cout << std::endl;

  std::cout << "dump std::vector:" << std::endl;
  auto v = std::vector<double>({1, 2, 3, 4, 5});
  easydump::dump(v, std::cout);
  std::cout << std::endl;

  std::cout << "dump std::map:" << std::endl;
  auto m = std::map<int, double>({{1, 2.1}, {3, 4.2}, {5, 6.3}});
  easydump::dump(m, std::cout);
  std::cout << std::endl;

  std::cout << "dump nested type:" << std::endl;
  auto nested = std::map<int, std::vector<int>> {
    {1, {1, 2, 3, 4, 5}},
    {2, {}},
  };
  easydump::dump(nested, std::cout);
  std::cout << std::endl;

  return 0;
}
