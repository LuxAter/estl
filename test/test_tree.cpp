//Copyright 2018 Arden Rasmussen

#include "gtest/gtest.h"
#include "tree.hpp"

class TreeTest : public testing::Test {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
    estl::tree::Tree<int> a, b, c;
};

TEST_F(TreeTest, Constructor){
  estl::tree::Tree<int> tree(0);
  tree.append(1);
  tree.prepend(2);
}
