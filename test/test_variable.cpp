// Copyright 2017 Arden Rasmussen

#include "gtest/gtest.h"
#include "variable.hpp"

TEST(VariableTest, Bool) {
  estl::Variable var(false);
  EXPECT_EQ(false, var.GetBool());
  bool val = var;
  EXPECT_EQ(false, val);
  EXPECT_EQ(estl::Variable::BOOL, var.Type());
}
TEST(VariableTest, Char) {
  estl::Variable var(char('a'));
  EXPECT_EQ('a', var.GetChar());
  char val = var;
  EXPECT_EQ(char('a'), val);
  EXPECT_EQ(estl::Variable::CHAR, var.Type());
}

TEST(VariableTest, Integer) {
  estl::Variable var(2018);
  EXPECT_EQ(2018, var.GetSignedInt());
  int val = var;
  EXPECT_EQ(2018, val);
  EXPECT_EQ(estl::Variable::SIGNED_INT, var.Type());
}

TEST(VariableTest, Double) {
  estl::Variable var(3.1415);
  EXPECT_EQ(3.1415, var.GetDouble());
  double val = var;
  EXPECT_EQ(3.1415, val);
  EXPECT_EQ(estl::Variable::DOUBLE, var.Type());
}

TEST(VariableTest, String) {
  estl::Variable var(std::string("Hello World!"));
  EXPECT_EQ(std::string("Hello World!"), var.GetString());
  std::string val = var;
  EXPECT_EQ(std::string("Hello World!"), val);
  EXPECT_EQ(estl::Variable::STRING, var.Type());
}

TEST(VariableTest, BoolVector) {
  estl::Variable var({true, false, true});
  EXPECT_EQ(std::vector<bool>({true, false, true}), var.GetBoolVector());
  std::vector<bool> val = var;
  EXPECT_EQ(std::vector<bool>({true, false, true}), val);
  EXPECT_EQ(estl::Variable::BOOL_VECTOR, var.Type());
  var.PushBack(false);
  EXPECT_EQ(std::vector<bool>({true, false, true, false}), var.GetBoolVector());
}

TEST(VariableTest, IntegerVector) {
  estl::Variable var({2, 4, 6, 8});
  EXPECT_EQ(std::vector<int>({2, 4, 6, 8}), var.GetSignedIntVector());
  std::vector<int> val = var;
  EXPECT_EQ(std::vector<int>({2, 4, 6, 8}), val);
  EXPECT_EQ(estl::Variable::SIGNED_INT_VECTOR, var.Type());
  var.PushBack(10);
  EXPECT_EQ(std::vector<int>({2, 4, 6, 8, 10}), var.GetSignedIntVector());
}

TEST(VariableTest, DoubleVector) {
  estl::Variable var({1.5, 3.1415, 2.45});
  EXPECT_EQ(std::vector<double>({1.5, 3.1415, 2.45}), var.GetDoubleVector());
  std::vector<double> val = var;
  EXPECT_EQ(std::vector<double>({1.5, 3.1415, 2.45}), val);
  EXPECT_EQ(estl::Variable::DOUBLE_VECTOR, var.Type());
  var.PushBack(10.25);
  EXPECT_EQ(std::vector<double>({1.5, 3.1415, 2.45, 10.25}),
            var.GetDoubleVector());
}

TEST(VariableTest, StringVector) {
  estl::Variable var({std::string("Hello"), std::string("World!")});
  EXPECT_EQ(std::vector<std::string>({"Hello", "World!"}),
            var.GetStringVector());
  std::vector<std::string> val = var;
  EXPECT_EQ(std::vector<std::string>({"Hello", "World!"}), val);
  EXPECT_EQ(estl::Variable::STRING_VECTOR, var.Type());
  var.PushBack(std::string("test"));
  EXPECT_EQ(std::vector<std::string>({"Hello", "World!", "test"}),
            var.GetStringVector());
}
