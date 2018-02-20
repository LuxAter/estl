// Copyright 2018 Arden Rasmussen

#include "argparse.hpp"
#include "gtest/gtest.h"

class ArgParseTest : public testing::Test {
 protected:
  virtual void SetUp() {
    parser.AddArgument("-a");
    parser.AddArgument({"-b", "--test_b"}, "Argument with help");
    parser.AddArgument("pos", estl::argparse::CHAR);
  }
  virtual void TearDown() {}
  estl::argparse::ArgumentParser parser;
};

TEST_F(ArgParseTest, Constructor) {}
