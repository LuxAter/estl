#include <stdio.h>
#include <iostream>

#include "stream.hpp"
#include "time.hpp"

int main(int argc, char const* argv[]) {
  int a = 7;
  double b = 31415926535897.9323846264;
  std::string c = "Hello World";
  estl::print(std::cout, "%i, %f, %e, %g \n", a, b, b, b);
  printf("%i, %f, %e, %g", a, b, b, b);
  // estl::Time t;
  // t.SetTimeUI(18135);
  // std::cout << t.Format("%H:%M:%S") << "\n";
  // t.ReadFormat("%H:%M:%S", "10:43:29");
  // std::cout << t.Format("%H:%M:%S") << "\n";
  // std::string str;
  // std::cin >> str;
  // t.ReadFormat("%h:", str);
  // std::cout << t.Format("%h:%m:%s:%ms:%us:%ns") << "\n";
  /* code */
  return 0;
}
