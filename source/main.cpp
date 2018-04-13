#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"

#include <climits>
#include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
#include "vector.hpp"

int main(int argc, char const* argv[]) {
  estl::vector::Vector<double, 3> vec{2, 1, 3};
  std::cout << 2 * vec << "\n";
  return 0;
}
