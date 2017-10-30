#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"

int main(int argc, char const* argv[]) {
  estl::matrix<int, 2, 2> a = {{0, 1}, {2, 3}};
  std::cout << std::boolalpha;
  std::cout << a << std::endl;
  a += 5;
  std::cout << a << std::endl;
  return 0;
}
