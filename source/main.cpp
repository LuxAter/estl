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
  Mat4f ma({1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 8, 0, 0, 0, 1}), mb, mc;
  mb.Diagonal(1);
  // ma.Diagonal(5);
  std::cout << ma << "," << mb << "\n";
  mc = Dot(ma, mb);
  std::cout << mc;
}
