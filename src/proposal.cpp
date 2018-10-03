#include "./include/qstore.hpp"

typedef unsigned int id_type;
typedef qstore::uint id_type; // alt

int main() {
  using qstore::list, qstore::pair, qstore::load;

  std::vector<std::pair<int, std::vector<int>>> tree_children_internal;

  // dump
  {
    // option A
    qstore::list<pair<id_type, list<id_type>>> tree_children;
    tree_children.from(tree_children_internal);
    tree_children.dump("tree_children.bin");
  }
  {
    // option B
    qstore::list<pair<id_type, list<id_type>>> /*auto*/ tree_children = from(tree_children_internal);
    tree_children.dump("tree_children.bin");
  }
  {
    // option B
    qstore::dump(tree_children_internal);
  }


  // load, option 1
  auto tree_children2 = qstore::list<pair<id_type, list<id_type>>>();
  tree_children2.load("tree_children.bin");
  // load, option 2
  auto tree_children2 = qstore::load<qstore::list<pair<id_type, list<id_type>>>>("tree_children.bin");

  tree_children_internal = tree_children2.to<decltype(tree_children_internal)>();

  return 0;
}
