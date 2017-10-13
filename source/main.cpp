#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "stream.hpp"

int main(int argc, char const* argv[]) {
  int i = 0, b = 0;
  // scanf("hello %3i, %i", &i, &b);
  estl::scan(std::cin, "hello %3i, %i", i, b);
  std::cout << i << "," << b << "\n";
}
