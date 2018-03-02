// Copyright 2018 Arden Rasmussen

#include "argparse/argument.hpp"
#include "gtest/gtest.h"

TEST(ArgumentTest, Constructor){
  estl::argparse::Argument arg({"name-a", "name-b"}, {});
}
