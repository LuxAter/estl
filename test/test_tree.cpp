// Copyright 2018 Arden Rasmussen

#include "gtest/gtest.h"
#include "tree.hpp"

class TreeTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
  estl::tree::Tree<int> tree;
};

TEST_F(TreeTest, Constructor) {
  int val = 1;
  estl::tree::Tree<int> a;
  EXPECT_EQ(a.str(), "0");
  estl::tree::Tree<int> b(0);
  EXPECT_EQ(b.str(), "0");
  estl::tree::Tree<int> c(val);
  EXPECT_EQ(c.str(), "1");
  estl::tree::Tree<int> d(c);
  EXPECT_EQ(d.str(), "1");
  estl::tree::Tree<int> e(std::move(d));
  EXPECT_EQ(e.str(), "1");
  estl::tree::Tree<int> f({1, 2, 3});
  EXPECT_EQ(f.str(), "1[2,3]");
  estl::tree::Tree<int> g(0, {1, 2, 3});
  EXPECT_EQ(g.str(), "0[1,2,3]");
}

TEST_F(TreeTest, Append) {
  int val = 4;
  estl::tree::Tree<int> a(17);
  tree.append(2);
  tree.append(val);
  tree.append({3, 4, 5});
  tree.append(a);
  EXPECT_EQ(tree.str(), "0[2,4,3[4,5],17]");
}
TEST_F(TreeTest, Prepend) {
  int val = 4;
  estl::tree::Tree<int> a(17);
  tree.prepend(2);
  tree.prepend(val);
  tree.prepend({3, 4, 5});
  tree.prepend(a);
  EXPECT_EQ(tree.str(), "0[17,3[4,5],4,2]");
}
TEST_F(TreeTest, PushPop) {
  int val = 21;
  tree.push_back(17);
  tree.push_back(val);
  EXPECT_EQ(tree.str(), "0[17,21]");
  tree.pop_back();
  EXPECT_EQ(tree.str(), "0[17]");
}

TEST_F(TreeTest, Size) {
  tree.append({1, 2, {3, 4, 5}});
  tree.append({6, 7, {8, 9, 10}});
  EXPECT_EQ(tree.str(), "0[1[2,3[4,5]],6[7,8[9,10]]]");
  EXPECT_EQ(tree.empty(), false);
  EXPECT_EQ(tree.size(), 11);
  EXPECT_EQ(tree.child_size(), 2);
  EXPECT_EQ(tree.leaf_size(), 6);
  tree.clear();
  EXPECT_EQ(tree.str(), "0");
}

TEST_F(TreeTest, InsertErase) {
  int val = 42;
  tree.insert(tree.end(), 15);
  tree.insert(tree.end(), 31);
  tree.insert(tree.begin() + 2, val);
  EXPECT_EQ(tree.str(), "0[15,42,31]");
  tree.erase(tree.begin() + 1);
  EXPECT_EQ(tree.str(), "0[42,31]");
}

TEST_F(TreeTest, DepthFirst) {
  tree.append({1, 2, 3});
  tree.append({4, 5, 6});
  tree.append({7, 8, 9});
  std::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  estl::tree::Tree<int>::depth_iterator it = tree.begin();
  std::vector<int>::iterator vit = vec.begin();
  for (; it != tree.end(); ++it, ++vit) {
    EXPECT_EQ(*vit, *it);
  }
  EXPECT_EQ(tree.at(4).node, 4);
}
TEST_F(TreeTest, Sibling) {
  tree.append({1, 2, 3});
  tree.append({4, 5, 6});
  tree.append({7, 8, 9});
  std::vector<int> vec = {1, 4, 7};
  estl::tree::Tree<int>::sibling_iterator it = tree.child_begin();
  std::vector<int>::iterator vit = vec.begin();
  for (; it != tree.child_end(); ++it, ++vit) {
    EXPECT_EQ(*vit, *it);
  }
  EXPECT_EQ(tree.child_at(2).node, 7);
}
TEST_F(TreeTest, Leaf) {
  tree.append({1, 2, 3});
  tree.append({4, 5, 6});
  tree.append({7, 8, 9});
  std::vector<int> vec = {2, 3, 5, 6, 8, 9};
  estl::tree::Tree<int>::leaf_iterator it = tree.leaf_begin();
  std::vector<int>::iterator vit = vec.begin();
  for (; it != tree.leaf_end(); ++it, ++vit) {
    EXPECT_EQ(*vit, *it);
  }
  EXPECT_EQ(tree.leaf_at(3).node, 6);
}
TEST_F(TreeTest, Reference) {
  tree.append({1, 2, 3});
  tree.append({4, 5, 6});
  tree.append({7, 8, 9});
  EXPECT_EQ(tree.front().node, 1);
  EXPECT_EQ(tree.back().node, 7);
}
TEST_F(TreeTest, Formatting) {
  tree.append({1, 2, 3});
  tree.append({4, 5, 6});
  tree.append({7, 8, 9});
  EXPECT_EQ(estl::tree::pretty(tree),
            "0\n\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80"
            "1\n\xE2\x94\x82  \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80"
            "2\n\xE2\x94\x82  \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80"
            "3\n\xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80"
            "4\n\xE2\x94\x82  \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80"
            "5\n\xE2\x94\x82  \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80"
            "6\n\xE2\x94\x94\xE2\x94\x80\xE2\x94\x80"
            "7\n   \xE2\x94\x9C\xE2\x94\x80\xE2\x94\x80"
            "8\n   \xE2\x94\x94\xE2\x94\x80\xE2\x94\x80"
            "9");
  EXPECT_EQ(estl::tree::dot(tree),
            "graph tree {\n  \"0\" -- \"1\";\n  \"1\" -- \"2\";\n  \"1\" -- "
            "\"3\";\n  \"0\" -- \"4\";\n  \"4\" -- \"5\";\n  \"4\" -- \"6\";\n "
            " \"0\" -- \"7\";\n  \"7\" -- \"8\";\n  \"7\" -- \"9\";\n}");
}
