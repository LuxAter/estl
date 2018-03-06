#include <iostream>

// #include "argparse/variable.hpp"
#include "argparse.hpp"
#include "format.hpp"
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"

class Tester{
  public:
    int value;
    std::string Format(){
      return "Tester: " + std::to_string(value);
    }
};

int main(int argc, char const* argv[]) {
  Tester t;
  t.value = 17;
  // std::string fmt = estl::format::Format("Hello}{2:17}! This is a {}", "World", "Test", 3.1415);
  std::string fmt = estl::format::Format("Hello {:-^10} This is more text |{:^ 020.5}| after each replacement", "HI", 3.1415);
  std::cout << "RES \"" << fmt << "\"\n";
  return 0;
}
