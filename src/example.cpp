#include "../include/easydump.hpp"

#include <cassert>
#include <iostream> // cout
#include <map>
#include <sstream>
#include <utility> // pair
#include <vector>

int main () {
  std::ostringstream out;
  std::istringstream in;

  out = std::ostringstream();
  std::cout << "dump int:" << std::endl;
  int n = 9;
  easydump::dump(n, out);
  std::cout << out.str() << std::endl;

  in = std::istringstream(out.str());
  std::cout << "load int:...";
  decltype(n) n2;
  easydump::load(n2, in);
  assert(n == n2);
  std::cout << "success!" << std::endl;

  out = std::ostringstream();
  std::cout << "dump double:" << std::endl;
  double x = 0.123;
  easydump::dump(x, out);
  std::cout << out.str() << std::endl;

  in = std::istringstream(out.str());
  std::cout << "load double:...";
  decltype(x) x2;
  easydump::load(x2, in);
  assert(x == x2);
  std::cout << "success!" << std::endl;


  out = std::ostringstream();
  std::cout << "dump std::pair:" << std::endl;
  auto p = std::make_pair(n, x);
  easydump::dump(p, out);
  std::cout << out.str() << std::endl;

  in = std::istringstream(out.str());
  std::cout << "load std::pair:...";
  decltype(p) p2;
  easydump::load(p2, in);
  assert(p == p2);
  std::cout << "success!" << std::endl;


  out = std::ostringstream();
  std::cout << "dump std::vector:" << std::endl;
  auto v = std::vector<double>({1, 2, 3, 4, 5});
  easydump::dump(v, out);
  std::cout << out.str() << std::endl;

  in = std::istringstream(out.str());
  std::cout << "load std::vector:...";
  decltype(v) v2;
  easydump::load(v2, in);
  assert(*v.rbegin() == *v2.rbegin());
  std::cout << "success!" << std::endl;


  out = std::ostringstream();
  std::cout << "dump std::map:" << std::endl;
  auto m = std::map<int, double>({{1, 2.1}, {3, 4.2}, {5, 6.3}});
  easydump::dump(m, out);
  std::cout << out.str() << std::endl;

  in = std::istringstream(out.str());
  std::cout << "load std::map:...";
  decltype(m) m2;
  easydump::load(m2, in);
  assert(*m.rbegin() == *m2.rbegin());
  std::cout << "success!" << std::endl;

  out = std::ostringstream();
  std::cout << "dump nested type:" << std::endl;
  auto nested = std::map<int, std::vector<int>> {
    {1, {1, 2, 3, 4, 5}},
    {2, {}},
  };
  easydump::dump(nested, out);
  std::cout << out.str() << std::endl;

  in = std::istringstream(out.str());
  std::cout << "load nested type:...";
  decltype(nested) nested2;
  easydump::load(nested2, in);
  assert(*nested.rbegin() == *nested2.rbegin());
  std::cout << "success!" << std::endl;


  return 0;
}
