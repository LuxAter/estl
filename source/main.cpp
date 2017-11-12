#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"

int main(int argc, char const* argv[]) {
  // estl::matrix<double, 3, 3> a = {2, 2, 3, 4, 5, 6, 7, 8, 9};
  estl::matrix<double, 4, 3> b = {
      {2, 1, -1}, {8, -3, -1}, {2, -11, -2}, {1, 2, -3}};
  estl::matrix<double, 2, 3> a = {1, 2, 3, 4, 5, 6};
  // estl::matrix<double, 3, 2> b = {{7, 8, 9}, {10, 11, 12}};
  std::cout << std::boolalpha;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  // std::cout << multiplication(a, b) << std::endl;
  // std::cout << echelon_form(b) << std::endl;
  // std::array<double, 9> data = a.data_array();
  // data[0] = 3.1415;
  // std::cout << a << std::endl;
  // std::cout << "trace(a)=" << estl::trace(a) << std::endl;
  // std::cout << "det(a) = " << estl::determinant(a) << std::endl;
  // std::cout << "Inv(a) = " << estl::inverse(a) << std::endl;
  return 0;
}
