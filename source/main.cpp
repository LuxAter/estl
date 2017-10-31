#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"

bool hello(bool tmp) { return !tmp; }

int main(int argc, char const* argv[]) {
  estl::matrix<int, 3, 3> a = {{2, 1, 0}, {4, 5, 3}, {8, 7, 6}};
  estl::matrix<int, 2, 2> b = {0, 1, 2, 3};
  std::cout << std::boolalpha;
  std::cout << a << std::endl;
  std::cout << "det(a) = " << estl::determinate(b) << std::endl;
  return 0;
}
