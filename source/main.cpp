#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>

#include "argparse.hpp"
#include "matrix.hpp"
#include "stream.hpp"
#include "variadic.hpp"
#include "vector.hpp"

int main(int argc, char const* argv[]) {
  estl::ArgumentParser parser("This is an example parser",
                              "This will go after the options");
  parser.AddArgument("Hello");
  parser.ParseArgs(argc, argv);
  return 0;
}
