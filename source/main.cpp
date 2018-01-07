#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"
#include "variadic.hpp"
#include "vector.hpp"

int main(int argc, char const* argv[]) {
  estl::vector<double, 3> a = {1, 2, 3}, b = {4, 5, 6};
  std::cout << a << "*" << b << "=" << estl::dot(a, b) << "\n";
  std::cout << a << "X" << b << "=" << estl::cross(a, b) << "\n";
  estl::vector<double, 4> c = {1, 0, 0, 0}, d = {0, 1, 0, 0}, e = {0, 0, 1, 0};
  std::cout << c << d << e << "=" << estl::cross(c, d, e) << '\n';

  estl::matrix<double, 3, 3> mat = {{2, 3, 4}, {6, 7, 8}, {10, 11, 12}};
  std::cout << mat << "->" << estl::determinant(mat) << "\n";
  return 0;
}
