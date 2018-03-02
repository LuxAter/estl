// Copyright 2018 Arden Rasmussen

#include "argparse/argument.hpp"
#include "gtest/gtest.h"

class ArgParseArgumentTest : public testing::Test {
  protected:
    virtual void SetUp(){
      arg1.SetName({"1"});
      arg2.SetName({"2"});
      arg3.SetName({"3"});
    }
    virtual void TearDown(){}
    estl::argparse::Argument arg1, arg2, arg3;
};

TEST_F(ArgParseArgumentTest, Constructor){
  estl::argparse::Argument arg_({"name-a", "name-b"}, {});
  EXPECT_EQ(arg_.GetHelp(), "  name-b, name-a              ");
}

TEST_F(ArgParseArgumentTest, SetHelp){
  arg1.SetHelp("This is the help string");
  arg2.SetVariable("This is the help", estl::argparse::ARG_NONE);
  arg3.SetVariable("Help String", estl::argparse::ARG_HELP);
  EXPECT_EQ(arg1.GetHelp(), "  1                           This is the help string");
  EXPECT_EQ(arg2.GetHelp(), "  2                           This is the help");
  EXPECT_EQ(arg3.GetHelp(), "  3                           Help String");
}

TEST_F(ArgParseArgumentTest, SetDest){
  arg1.SetDest("DEST");
  arg2.SetVariable("This is the help", estl::argparse::ARG_NONE);
  arg2.SetVariable("DESTIN", estl::argparse::ARG_NONE);
  arg3.SetVariable("DESTINATION", estl::argparse::ARG_DEST);
  EXPECT_EQ(arg1.GetDest(), "DEST");
  EXPECT_EQ(arg2.GetDest(), "DESTIN");
  EXPECT_EQ(arg3.GetDest(), "DESTINATION");
}

TEST_F(ArgParseArgumentTest, SetMetavar){
  arg1.SetMetavar("META");
  arg2.SetVariable("This is the help", estl::argparse::ARG_NONE);
  arg2.SetVariable("Dest", estl::argparse::ARG_NONE);
  arg2.SetVariable("METAV", estl::argparse::ARG_NONE);
  arg3.SetVariable("METAVAR", estl::argparse::ARG_METAVAR);
  EXPECT_EQ(arg1.GetUsage(), "[META]");
  EXPECT_EQ(arg2.GetUsage(), "[METAV]");
  EXPECT_EQ(arg3.GetUsage(), "[METAVAR]");
}

TEST_F(ArgParseArgumentTest, SetNArgs){
  arg1.SetNArgs(estl::argparse::KLEENE_STAR);
  EXPECT_EQ(arg1.GetUsage(), "[1 [1 ...]]");
  arg1.SetNArgs(1);
  EXPECT_EQ(arg1.GetUsage(), "1");
  arg1.SetNArgs(5);
  EXPECT_EQ(arg1.GetUsage(), "1 1 1 1 1");
  arg1.SetNArgs("one");
  EXPECT_EQ(arg1.GetUsage(), "1");
  arg1.SetNArgs("n");
  EXPECT_EQ(arg1.GetUsage(), "1");
  arg1.SetNArgs("?");
  EXPECT_EQ(arg1.GetUsage(), "[1]");
  arg1.SetNArgs("*");
  EXPECT_EQ(arg1.GetUsage(), "[1 [1 ...]]");
  arg1.SetNArgs("+");
  EXPECT_EQ(arg1.GetUsage(), "1 [1 ...]");
  arg1.SetNArgs("1");
  EXPECT_EQ(arg1.GetUsage(), "1");
  arg1.SetNArgs("3");
  EXPECT_EQ(arg1.GetUsage(), "1 1 1");
  arg3.SetVariable("+", estl::argparse::ARG_N_ARGS);
  EXPECT_EQ(arg3.GetUsage(), "3 [3 ...]");
}

TEST_F(ArgParseArgumentTest, SetAction){
  arg1.SetAction(estl::argparse::STORE_TRUE);
  EXPECT_EQ(arg1.GetAction(), estl::argparse::STORE_TRUE);
  arg1.SetAction(estl::argparse::STORE_FALSE);
  EXPECT_EQ(arg1.GetAction(), estl::argparse::STORE_FALSE);
  arg1.SetAction("store");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::STORE);
  arg1.SetAction("store_const");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::STORE_CONST);
  arg1.SetAction("store_true");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::STORE_TRUE);
  arg1.SetAction("store_false");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::STORE_FALSE);
  arg1.SetAction("append");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::APPEND);
  arg1.SetAction("append_const");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::APPEND_CONST);
  arg1.SetAction("count");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::COUNT);
  arg1.SetAction("help");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::HELP);
  arg1.SetAction("version");
  EXPECT_EQ(arg1.GetAction(), estl::argparse::VERSION);
  arg3.SetVariable("count", estl::argparse::ARG_ACTION);
  EXPECT_EQ(arg3.GetAction(), estl::argparse::COUNT);
}

TEST_F(ArgParseArgumentTest, SetType){
  arg1.SetType(estl::argparse::BOOL);
  EXPECT_EQ(arg1.GetType(), estl::argparse::BOOL);
  arg1.SetType("none");
  EXPECT_EQ(arg1.GetType(), estl::argparse::NONE);
  arg1.SetType("bool");
  EXPECT_EQ(arg1.GetType(), estl::argparse::BOOL);
  arg1.SetType("int");
  EXPECT_EQ(arg1.GetType(), estl::argparse::INT);
  arg1.SetType("double");
  EXPECT_EQ(arg1.GetType(), estl::argparse::DOUBLE);
  arg1.SetType("string");
  EXPECT_EQ(arg1.GetType(), estl::argparse::STRING);
  arg1.SetType("bool_vector");
  EXPECT_EQ(arg1.GetType(), estl::argparse::BOOL_VECTOR);
  arg1.SetType("int_vector");
  EXPECT_EQ(arg1.GetType(), estl::argparse::INT_VECTOR);
  arg1.SetType("double_vector");
  EXPECT_EQ(arg1.GetType(), estl::argparse::DOUBLE_VECTOR);
  arg1.SetType("string_vector");
  EXPECT_EQ(arg1.GetType(), estl::argparse::STRING_VECTOR);
  arg2.SetVariable(estl::argparse::INT, estl::argparse::ARG_TYPE);
  EXPECT_EQ(arg2.GetType(), estl::argparse::INT);

}

TEST_F(ArgParseArgumentTest, SetRequired){
  arg1.SetRequired(true);
  EXPECT_EQ(arg1.GetUsage(), "1");
  arg2.SetVariable(true, estl::argparse::ARG_NONE);
  EXPECT_EQ(arg2.GetUsage(), "2");
  arg3.SetVariable(true, estl::argparse::ARG_REQUIRED);
  EXPECT_EQ(arg3.GetUsage(), "3");
}

TEST_F(ArgParseArgumentTest, SetChoices){
  arg1.SetChoices({"a", "b"});
  EXPECT_EQ(arg1.GetChoicesStr(), "{a, b}");
  arg2.SetVariable({1, 2, 3}, estl::argparse::ARG_NONE);
  EXPECT_EQ(arg2.GetChoicesStr(), "{1, 2, 3}");
  arg3.SetVariable({'a', 'b', 'c'}, estl::argparse::ARG_CHOICES);
  EXPECT_EQ(arg3.GetChoicesStr(), "{a, b, c}");
}

TEST_F(ArgParseArgumentTest, SetDefault){
  arg1.SetDefault(17);
  EXPECT_EQ(arg1.GetValue(), 17);
}
