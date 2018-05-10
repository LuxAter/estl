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
  estl::tree::Tree<int> t(42);
  t.append(0);
  t.back().append(3);
  t.back().append(4);
  t.append(1);
  t.back().append(5);
  t.back().append(6);
  t.append(2);
  t.back().append(7);
  t.back().append(8);
  estl::tree::Tree<int> a(t);
  std::cout << t << "\n";
  std::cout << a << "\n";
  a.back().clear();
  a.erase(a.begin() + 5);
  std::cout << t << "\n";
  std::cout << a << "\n";
  // t.back().append(100);
  // estl::tree::Tree<int> ref = t.subtree(++t.begin());
  // t.append(7);
  // t.prepend(2);
  // std::cout << t << "\n";
  // estl::tree::Tree<int>::iterator it = t.begin();
  // // std::cout << t.end().node_ << "\n";
  // std::cout << it.node_ << std::flush << "::" << *it << "\n";
  // ++it;
  // std::cout << it.node_ << std::flush<< "::" << *it << "\n";
  // ++it;
  // std::cout << it.node_ << std::flush << "::" << *it << "\n";
  // ++it;
  // std::cout << it.node_ << std::flush << "::" << *it << "\n";
  // std::cout << estl::tree::pretty(t) << "\n";
  // std::cout << estl::tree::pretty(ref) << "\n";
  // for(auto& it : t){
  //   std::cout << it << "<<\n";
  // }
  // for(auto it = t.begin(); it != t.end(); ++it){
  //   std::cout << "It: " << it.node_ << ":" << (*it) << "\n";
  // }
  // for(auto it = --t.end(); it != t.begin(); --it){
  //   std::cout << "It: " << it.node_ << ":" << (*it) << "\n";
  // }
  // std::cout << t.at(0).get_next_ptr() << "\n";
  // std::cout << t.begin().node_ << "->" << t.end().node_ << "\n";
  
  // t.append_child(t.begin(), 2018);
  // t.append_child(t.begin(), 2017);
  // std::cout << t << "\n";
  return 0;
}
