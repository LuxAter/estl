#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "stream.hpp"

int main(int argc, char const* argv[]) {
  std::cout << "Hello" << estl::sprint("%i %i %i", 5, 4, 3) << "\n";
}
