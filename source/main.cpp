#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"
#include "tree.hpp"

using namespace estl::tree;

int main(int argc, char const* argv[]) {
  Tree<int> a({{1, 2, 3},{4,5,6},{7,8,9}});
  // a.append(2);
  // a.append(3);
  Tree<int> b(4);
  b.append(5);
  b.append(6);
  a.append(b);
  std::cout << a.size() << "\n";
  std::cout << a.child_size() << "\n";
  std::cout << a.leaf_size() << "\n";
  std::cout << pretty(a) << "\n";
  return 0;
}
