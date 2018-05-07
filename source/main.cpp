#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"

#include <climits>
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"
#include "tree.hpp"

int main(int argc, char const* argv[]) {
  estl::tree::Tree<int> t(17);
  t.append(5);
  t.append(6);
  // t.child_back().append(100);
  // t.append(7);
  // t.prepend(2);
  std::cout << t << "\n";
  std::cout << estl::tree::pretty(t) << "\n";
  for(auto& it : t){
    std::cout << it << "<<\n";
  }
  for(auto it = t.begin(); it != t.end(); ++it){
    std::cout << "It: " << it.node_ << ":" << (*it) << "\n";
  }
  std::cout << t.at(0).get_next_ptr() << "\n";
  std::cout << t.begin().node_ << "->" << t.end().node_ << "\n";
  
  // t.append_child(t.begin(), 2018);
  // t.append_child(t.begin(), 2017);
  // std::cout << t << "\n";
  return 0;
}
