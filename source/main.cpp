#include <iostream>

// #include "argparse/variable.hpp"
#include "argparse.hpp"
#include "format.hpp"
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
    return "Tester: (" + std::string(1,fill) + "," + std::to_string(align) + "," +
           std::to_string(sign) + "," + std::to_string(width) + "," +
           std::to_string(percision) + ")";
  }
};

int main(int argc, char const* argv[]) {
  Tester t;
  t.value = 17;
  // std::string fmt = estl::format::Format("Hello}{2:17}! This is a {}",
  // "World", "Test", 3.1415);
  std::string fmt = estl::format::Format(
      "Hello {^+10.5} This is more text |{0[2]:^ 020.5}| after each "
      "replacement");
  std::cout << "RES \"" << fmt << "\"\n";
  return 0;
}
