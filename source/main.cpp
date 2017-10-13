#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "stream.hpp"

int main(int argc, char const* argv[]) {
  float a = 0;
  unsigned int b = 0;
  estl::scan(std::cin, "%f", a);
  estl::print(std::cout, "HEX: %a\n", a);
  estl::scan(std::cin, "%x", b);
  estl::print(std::cout, "FLOAT: %u\n", b);
  // estl::scan(std::cin, "%f", a);
  // estl::print(std::cout, "%a\n", a);
  // estl::scan(std::cin, "%a", a);
  // estl::print(std::cout, "HEX: %a\nInt: %f\n", a, a);
  // estl::scan(std::cin, "%x", b);
  // estl::print(std::cout, "HEX: %x\n", b);
}
