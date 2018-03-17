#include <iostream>

// #include "argparse/variable.hpp"
#include "argparse.hpp"
#include "format.hpp"

#include <climits>
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"

class Tester {
 public:
  int value;
  std::string Format(char fill, unsigned align, unsigned sign, int width,
                     int percision) {
    return "Tester: (" + std::string(1, fill) + "," + std::to_string(align) +
           "," + std::to_string(sign) + "," + std::to_string(width) + "," +
           std::to_string(percision) + ")";
  }
};

int main(int argc, char const* argv[]) {
  Tester t;
  t.value = 17;
  std::string fmt = estl::format::Format("MAX: {:100b} MIN: {:b} UINT: {} UINT: {}", ULLONG_MAX);
  std::cout << "RES \"" << fmt << "\"\n";
  return 0;
}
