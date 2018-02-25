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
