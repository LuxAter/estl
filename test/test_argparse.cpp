// Copyright 2018 Arden Rasmussen

#include "argparse.hpp"
#include "gtest/gtest.h"

class ArgParseTest : public testing::Test {
 protected:
  virtual void SetUp() {
    parser.AddArgument("-a");
    parser.AddArgument({"-b", "--test_b"}, "Argument with help");
    parser.AddArgument("pos", estl::Variable::CHAR);
  }
  virtual void TearDown() {}
  estl::ArgumentParser parser;
};

TEST_F(ArgParseTest, Constructor) {}
