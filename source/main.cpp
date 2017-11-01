#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"

int main(int argc, char const* argv[]) {
  estl::matrix<double, 3, 3> a = {2, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << std::boolalpha;
  std::cout << a << std::endl;
  std::cout << "trace(a)=" << estl::trace(a) << std::endl;
  std::cout << "det(a) = " << estl::det(a) << std::endl;
  std::cout << "Inv(a) = " << estl::inverse(a) << std::endl;
  return 0;
}
