#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "matrix.hpp"
#include "stream.hpp"

int main(int argc, char const* argv[]) {
  estl::matrix<double, 4, 4> mat;
  std::array<int, 16> arr;
  mat.fill(3.1415);
  std::cout << std::boolalpha;
  std::cout << arr.size() << ":" << mat.size() << "\n";
  std::cout << arr.max_size() << ":" << mat.max_size() << "\n";
  std::cout << arr.empty() << ":" << mat.empty() << "\n";
  std::cout << arr.at(8) << ":" << mat.at(8) << "\n";
  std::cout << mat << "\n";
  return 0;
}
