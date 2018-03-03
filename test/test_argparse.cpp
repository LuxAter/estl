// Copyright 2018 Arden Rasmussen

#include "argparse.hpp"
#include "gtest/gtest.h"

class ArgParseTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
  estl::argparse::ArgumentParser parser;
};

TEST_F(ArgParseTest, Constructor) {
  estl::argparse::ArgumentParser prog_parser("prog"),
      proep_parser("This is the prolog", "This is the epilog"),
      all_parser("prog", "this is the pro", "this is the epi");
  EXPECT_EQ("usage: prog \n\n", prog_parser.GetHelp());
  EXPECT_EQ("usage: \n\nThis is the prolog\n\nThis is the epilog\n",
            proep_parser.GetHelp());
  EXPECT_EQ("usage: prog \n\nthis is the pro\n\nthis is the epi\n",
            all_parser.GetHelp());
}

TEST_F(ArgParseTest, AddArgument) {
  parser.AddArgument("a");
  parser.AddArgument({"-b", "--test-b"});
  parser.AddArgument("--longargumentnamea");
  parser.AddArgument("--longargumentnameb");
  parser.Group("test_group");
  parser.AddArgument(std::set<std::string>{"-c", "--test-c"});
  EXPECT_EQ(
      "usage: [--longargumentnamea LONGARGUMENTNAMEA] \n       "
      "[--longargumentnameb LONGARGUMENTNAMEB] [--test-b TESTB] \n       "
      "[--test-c TESTC] A \n\noptional arguments:\n  --longargumentnamea       "
      "  \n  --longargumentnameb         \n  -b, --test-b                "
      "\npositional arguments:\n  a                           \ntest_group:\n  "
      "-c, --test-c                \n\n",
      parser.GetHelp());
}

TEST_F(ArgParseTest, Options) {
  parser.SetProg("prog");
  parser.SetProlog("prolog text");
  parser.SetEpilog(
      "this is a very long test string, it is still going. will it ever end??? "
      "lets find out!");
  parser.SetUsage("[options]");
  parser.SetVersion("1.0");
  parser.SetAddHelp(true);
  parser.SetAddVersion(true);
  parser.ParseArgs(0, NULL);
  EXPECT_EQ(
      "usage: prog [options]\nprog 1.0\n\nprolog text\n\noptional arguments:\n "
      " -h, --help                  show this help message and exit\n  "
      "--version                   show program's version number and "
      "exit\n\nthis is a very long test string, it is still going. will it "
      "ever end??? lets \nfind out! \n",
      parser.GetHelp());
}

TEST_F(ArgParseTest, ParseArgs) {
  std::vector<const char*> in_args = {
      "unit-tests", "--test-a", "hello", "-gbc", "-gd", "7",  "-gd", "8",
      "-eff",       "-h",       "2.0",   "1.5",  "1.0", "-i", "a",   "c",
      "-j",         "false",    "-k",     "2",    "-l",   "Bye"};
  int argc = in_args.size();
  const char** argv = &in_args[0];
  parser.SetAddHelp(false);
  parser.SetAddVersion(false);
  parser.AddArgument({"-a", "--test-a"}, estl::argparse::STORE);
  parser.AddArgument({"-b", "--test-b"}, estl::argparse::STORE_TRUE);
  parser.AddArgument({"-c", "--test-c"}, estl::argparse::STORE_CONST,
                     estl::argparse::ARG_CONST, 2018);
  parser.AddArgument({"-d", "--test-d"}, estl::argparse::APPEND,
                     estl::argparse::INT);
  parser.AddArgument({"-e", "--test-e"}, estl::argparse::STORE_FALSE);
  parser.AddArgument({"-f", "--test-f"}, estl::argparse::APPEND_CONST,
                     estl::argparse::ARG_CONST, 3.14);
  parser.AddArgument({"-g", "--test-g"}, estl::argparse::COUNT);
  parser.AddArgument({"-h", "--test-h"}, estl::argparse::KLEENE_PLUS,
                     estl::argparse::DOUBLE, {1.0, 1.5, 2.0, 2.5});
  parser.AddArgument({"-i", "--test-i"}, estl::argparse::KLEENE_STAR,
                     estl::argparse::CHAR, {'a', 'b', 'c'});
  parser.AddArgument({"-j", "--test-j"}, estl::argparse::BOOL, {true, false});
  parser.AddArgument({"-k", "--test-k"}, estl::argparse::INT, {2, 4, 6, 8});
  parser.AddArgument({"-l", "--test-l"}, estl::argparse::STRING,
                     {"Hello", "Bye"});
  std::map<std::string, estl::argparse::Variable> args =
      parser.ParseArgs(argc, argv);
  EXPECT_EQ(args["test-a"], "hello");
  EXPECT_EQ(args["test-b"], true);
  EXPECT_EQ(args["test-c"], 2018);
  EXPECT_EQ(args["test-d"], std::vector<int>({7, 8}));
  EXPECT_EQ(args["test-e"], false);
  EXPECT_EQ(args["test-f"], std::vector<double>({3.14, 3.14}));
  EXPECT_EQ(args["test-g"], 3);
  EXPECT_EQ(args["test-h"], std::vector<double>({2.0, 1.5, 1.0}));
  EXPECT_EQ(args["test-i"], std::vector<char>({'a', 'c'}));
  EXPECT_EQ(args["test-j"], false);
  EXPECT_EQ(args["test-k"], 2);
  EXPECT_EQ(args["test-l"], "Bye");
}
