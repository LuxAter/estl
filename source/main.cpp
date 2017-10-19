#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "stream.hpp"

int main(int argc, char const* argv[]) {
  float a = 0;
  // std::cin >> a;
  estl::cscan("%f", a);
  estl::cprint("HEX FLOAT: %a\n", a);
  estl::cscan("%a", a);
  estl::cprint("FLOAT: %f\n", a);
}
