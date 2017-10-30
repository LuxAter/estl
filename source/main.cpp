#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"

int main(int argc, char const* argv[]) {
  estl::matrix<int, 4, 4> a = {0, 1, 2,  3,  4,  5,  6,  7,
                               8, 9, 10, 11, 12, 13, 14, 15};
  estl::matrix<int, 4, 4> b = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}};
  std::cout << std::boolalpha;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  a = a + 3;
  std::cout << a << std::endl;
  a = a - 3;
  std::cout << a << std::endl;
  return 0;
}
