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
  t.append(10);
  t.back().append(0);
  t.back().back().append(3);
  t.back().back().append(4);
  t.back().append(1);
  t.back().back().append(5);
  t.back().back().append(6);
  t.back().append(2);
  t.back().back().append(7);
  t.back().back().append(8);
  t.append(26);
  t.back().append(7);
  t.front().prepend(32);
  t.append(18);
  t.prepend(99);
  auto it = t.begin();
  t.insert(t.child_begin() + 2, 42);
  std::cout << t << "\n";
  std::cout << estl::tree::pretty(t) << "\n";
  std::cout << "depth_first:\n";
  for(auto it = t.begin(); it != t.end(); ++it){
    std::cout << *it << ",";
  }
  std::cout << "\n";
  std::cout << "sibling:\n";
  for(auto it = t.child_begin(); it != t.child_end(); ++it){
    std::cout << *it << ",";
  }
  std::cout << "\n";
  std::cout << "leaf:\n";
  for(auto it = t.leaf_begin(); it != t.leaf_end(); ++it){
    std::cout << *it << ",";
  }
  std::cout << "\n";
  std::cout << t.leaf_at(4) << "\n";
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
