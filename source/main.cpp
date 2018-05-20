#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"

// #include <climits>
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"
#include "logger.hpp"
using namespace estl::logger;

void test();

int main(int argc, char const* argv[]) {
  Fatal("HELP!");
  Error("Hello");
  return 0;
}
