#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"

#include <climits>
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"
#include "tree.hpp"

int main(int argc, char const* argv[]) {
  estl::tree::Tree<int> t(17);
  t.append_child(t.begin(), 2018);
  t.append_child(t.begin(), 2017);
  std::cout << t << "\n";
  return 0;
}
