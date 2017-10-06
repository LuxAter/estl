#include <stdio.h>
#include <iostream>

#include "time.hpp"

int main(int argc, char const* argv[]) {
  estl::Time t;
  t.SetTimeD(50271.03714607);
  std::cout << t.Format("%h:%m:%s:%ms:%us:%ns") << "\n";
  std::string str;
  std::cin >> str;
  t.ReadFormat("%h:", str);
  std::cout << t.Format("%h:%m:%s:%ms:%us:%ns") << "\n";
  /* code */
  return 0;
}
