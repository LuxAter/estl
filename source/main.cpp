#include <stdio.h>
#include <iostream>

#include "stream.hpp"
#include "time.hpp"

int main(int argc, char const* argv[]) {
  double a = 19011.998;
  estl::print(std::cout, "%f\n", double(a));
  printf("\n%f\n", a);
  // printf("%i, %+i, %i\n", a, b, c);
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
