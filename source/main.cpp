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
  estl::matrix::Matrix<double, 3, 3> mat{1, 2, 3, 4, 5, 6, 7, 8, 9};
  estl::vector::Vector<double, 3> vec{2, 1, 3};
  estl::vector::Vector<double, 3> res = mat * vec;
  std::cout << mat << "*" << vec << "=" << res << '\n';
  return 0;
}
