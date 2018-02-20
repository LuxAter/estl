#include <iostream>

// #include "argparse/variable.hpp"
#include "argparse.hpp"
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"

int main(int argc, char const* argv[]) {
  // estl::argparse::Variable var(3.1415);
  // std::cout << "A:" << var << std::endl;
  // var = {"HI", "HEllo", "Bye"};
  // std::cout << "B:" << var << std::endl;
  estl::argparse::ArgumentParser parser;
  parser.SetAddHelp(false);
  parser.SetAddVersion(false);
  parser.SetVersion("v0.4");
  parser.SetProlog(
      "This is an example of the ability of the argument parser class "
      "implemented in estl. It allows for practicaly anything that the python"
      "insperation has the ability for, although it is limited to only base "
      "types, and vectors of the base types.");
  parser.AddArgument({"-?", "--help"}, estl::argparse::HELP,
                     "show list of command-line options");
  parser.AddArgument({"-v", "--version"}, estl::argparse::VERSION,
                     "show version");
  parser.Group("display options");
  parser.AddArgument({"-1", "--oneline"}, estl::argparse::STORE_TRUE,
                     "display one entry per line");
  parser.AddArgument({"-l", "--long"}, estl::argparse::STORE_TRUE,
                     "display extneded file metadata as a table");
  parser.AddArgument({"-G", "--grid"}, estl::argparse::STORE_TRUE,
                     "display entries as a grid (default)");
  parser.AddArgument({"-x", "--across"}, estl::argparse::STORE_TRUE,
                     "sort the grid across, rather than downwards");
  parser.AddArgument({"-R", "--recurse"}, estl::argparse::STORE_TRUE,
                     "recurse into directories");
  parser.AddArgument({"-T", "--tree"}, estl::argparse::STORE_TRUE,
                     "recurse into directories as a tree");
  parser.AddArgument({"-F", "--classify"}, estl::argparse::STORE_TRUE,
                     "display type indicator by file names");
  parser.AddArgument({"--color", "--colour"}, {"always", "auto", "never"},
                     "when to use terminal colors", "color", "WHEN", "auto");
  parser.AddArgument({"--color-scale", "--colour-scale"},
                     estl::argparse::STORE_TRUE,
                     "highlights levels of file sizes distinctly");
  parser.Group("testing options");
  parser.AddArgument({"-t", "--test"}, estl::argparse::N,
                     estl::argparse::ARG_N_ARGS, "3",
                     "this argument requires three entries, and it has an "
                     "obsurdly long help string. This help string will have to"
                     "be wraped over multiple lines. Lets hope that it worked"
                     "properly.");
  parser.AddArgument({"--name", "--names"}, estl::argparse::KLEENE_PLUS,
                     "this requires at least one argument");
  parser.AddArgument("ints", estl::argparse::KLEENE_PLUS, estl::argparse::INT,
                     "list of numbers", {2, 4, 6, 8, 10, 12, 14, 16, 18, 20},
                     false);
  std::map<std::string, estl::argparse::Variable> data =
      parser.ParseArgs(argc, argv);
  for (auto& it : data) {
    std::cout << it.first << ":" << it.second << "\n";
  }
  return 0;
}
