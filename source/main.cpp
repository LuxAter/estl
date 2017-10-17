#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "stream.hpp"

int main(int argc, char const* argv[]) {
  int a = 0;
  estl::sscan("2017", "%i", a);
  // scanf("%i17", &a);
  estl::cprint("INTEGER: %i", a);
}
