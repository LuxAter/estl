#include <math.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>

#include <any>
#include <functional>
#include <set>
#include <variant>

// #include "any.hpp"

#include "argparse.hpp"
// #include "argparse/argument.hpp"
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"

int main(int argc, char const* argv[]) {
  // std::any lhs = 15;
  // std::any rhs = 25;
  // std::set<std::any> st(comp);
  // st.insert(lhs);
  // std::cout << (lhs < rhs) << "\n";
  // estl::Argument ag(std::set<std::string>{"-l", "--list"});
  // estl::Argument ag({"-l", "--list"}, estl::ARG_OPT_ACTION, "count");
  // estl::Argument ag({"-l", "--list"}, "Shows list of data",
  //                   estl::ACTION_STORE_TRUE, estl::ARG_OPT_DEFAULT, 3.1415);
  // estl::Argument ag({"-l", "--list"}, estl::ARG_OPT_CHOICES,
  //                   {"breif", "Long", "Slow", "fast"});
  // std::cout << ag;
  // std::any an = estl::ACTION_STORE_TRUE;
  // std::cout << "Types: " << an.type().name() << ":"
  //           << typeid(estl::Action).name() << ":" <<
  //           typeid(estl::NArgs).name()
  //           << "\n";
  // std::any an = std::make_any<std::function<int(double)>>(Hello);
  //
  // std::function<int(double)> func =
  //     std::any_cast<std::function<int(double)>>(an);
  // std::cout << "RES: " << func(3.1415) << "\n";
  estl::ArgumentParser parser("This is an example parser",
                              "This will go after the options");
  parser.AddArgument("Hello", "Help section", 15, estl::ARG_OPT_DEFAULT,
                     3.1415);
  parser.AddArgument({"-l", "--list"}, "Lists all options",
                     estl::ACTION_STORE_TRUE);
  parser.AddArgument("Bye", "Help");
  parser.AddArgument("Only Name");
  // parser.AddArgument("Hello");
  // parser.AddArgument({"hi", "hello"});
  parser.ParseArgs(argc, argv);
  // estl::ArgumentParser::Argument arg(
  //     std::map<std::string, std::any>{{"name", "--list"}});
  // estl::ArgumentParser::Argument arg(std::map<std::string, std::any>{
  //     {"name", std::make_any<std::set<std::string>>(
  //                  std::set<std::string>{"-l", "--list"})}});
  // arg.SetNames({"Hello", "World", "-h", "-w"});
  // arg.SetConst(3.1415);
  // std::cout << arg.names_ << "<\n";
  // std::cout << std::any_cast<double>(arg.const_) << "<<\n";
  return 0;
}
