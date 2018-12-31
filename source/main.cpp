#include <iostream>

#include "lua.hpp"

#include <vector>
#include <fstream>

int main(int argc, char const* argv[]) {
  estl::lua::Script lua("test.lua");
  std::cout << lua.get<float>("height") << '\n';
  std::cout << lua.get<float>("width") << '\n';
  std::vector<int> vec = lua.lua_get_vector<int>("test");
  std::cout << vec.size() << '\n';
  for(auto& it: vec){
    std::cout << it << ',';
  }
  std::cout << '\n';
  for(uint32_t i = 1; i < 10; ++i){
    std::cout << lua.fib(i) << "\n";
  }
  return 0;
}
