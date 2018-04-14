#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"

// #include <climits>
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
#include "vector.hpp"

#include "basic/vector.hpp"
#include "basic/matrix.hpp"

using namespace estl::base;

int main(int argc, char const* argv[]) {
  Vec3f a(1), b(1.5), c;
  Mat3f ma(2), mb(3.1415), mc;
  std::cout << a << b << c << std::endl;
  std::cout << ma <<"\n"<< mb << "\n"<<mc << std::endl;
  std::cout << Dot(ma, b) << "\n";
}
