#include <iostream>

// #include "any.hpp"

// #include "variable.hpp"

#include "argparse.hpp"
// #include "argparse/argument.hpp"
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"

// void tmp(std::string tmp) { std::cout << "a\n"; }

int main(int argc, char const* argv[]) {
  estl::ArgumentParser parser(
      "A general C++ utility libraries all implemented as header only files.",
      "Everything is split betwen the header files, so that anything not used "
      "is not compiled into the program unneccesarily.");
  parser.SetVersion("v0.4");
  // parser.SetProg("estl");
  parser.SetAddVersion(true);
  parser.AddArgument("-t", "This is a test function",
                     estl::ArgumentParser::STORE_TRUE);
  parser.AddArgument({"-a", "--all"}, "This will show all options",
                     {1, 2, 3, 4, 5}, estl::Variable::SIGNED_INT);
  std::map<std::string, estl::Variable> data = parser.ParseArgs(argc, argv);
  for (auto& it : data) {
    std::cout << it.first << ":" << it.second << "\n";
  }
  // std::cout << parser.GetHelp();
  // estl::Variable var(3.1415);
  // std::cout << var;
  // var = "Hello World!";
  // std::cout << var;
  //     estl::ArgumentParser parser("This is an example parser",
  //                                 "This will go after the options");
  // parser.SetVersion("v0.3.5");
  // // parser.AddArgument({"-a", "--args"}, "Many more arguments",
  // //                    estl::Argument::KLEENE_PLUS);
  // parser.AddArgument({"-i", "--int"}, "Add any even integers <=10",
  //                    estl::Argument::INT, estl::Argument::KLEENE_STAR,
  //                    {0, 2, 4, 6, 8, 10});
  // // parser.AddArgument("-a", "Setting A", estl::Argument::STORE_TRUE);
  // // parser.AddArgument("-b", "Setting B", estl::Argument::STORE_TRUE);
  // // parser.AddArgument("-c", "Setting C", estl::Argument::STORE_TRUE);
  // // parser.AddArgument({"-a", "--all"}, "This is the help text!",
  // //                    estl::Argument::STORE_TRUE);
  // // parser.Group("ALPHA");
  // // parser.AddArgument({"-abc", "--alpha"}, "Alphabet");
  // // parser.AddArgument("--hello", estl::Argument::STORE_TRUE, true);
  // std::map<std::string, std::any> args = parser.ParseArgs(argc, argv);
  // for (std::map<std::string, std::any>::iterator it = args.begin();
  //      it != args.end(); ++it) {
  //   std::cout << (*it).first << ": " << (*it).second << "\n";
  // }
  // std::vector<std::any> res =
  // std::any_cast<std::vector<std::any>>(args["int"]);
  // for (int i = 0; i < res.size(); i++) {
  //   std::cout << res[i] << ", ";
  // }
  // std::cout << parser.GetHelp();
  return 0;
}
