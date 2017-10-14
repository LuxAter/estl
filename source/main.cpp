#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "stream.hpp"

int main(int argc, char const* argv[]) {
  int a = 0;
  estl::cscan("%i17", a);
  estl::cprint("INTEGER: %i", a);
}
