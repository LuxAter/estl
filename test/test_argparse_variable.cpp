// Copyright 2018 Arden Rasmussen

#include "argparse/variable.hpp"
#include "gtest/gtest.h"

class ArgParseVariableTest : public testing::Test {
 protected:
  virtual void SetUp() {
    b_ = true;
    c_ = 'a';
    i_ = 1;
    d_ = 1.5;
    a_ = "Hello";
    s_ = std::string("World");
    vb_ = std::vector<bool>{true, false};
    vc_ = std::vector<char>{'a', 'b'};
    vi_ = std::vector<int>{1, 2};
    vd_ = std::vector<double>{1.5, 2.0};
    vs_ = std::vector<std::string>{"Hello", "World"};
    ib_ = {false, true};
    ic_ = {'c', 'd'};
    ii_ = {3, 4};
    id_ = {2.5, 3.0};
    ia_ = {"Hello", "World"};
    is_ = {std::string("World"), std::string("Hello")};
  }
  virtual void TearDown() {}
  estl::argparse::Variable b_, c_, i_, d_, a_, s_, vb_, vc_, vi_, vd_, vs_, ib_,
      ic_, ii_, id_, ia_, is_, inv_;
};

TEST_F(ArgParseVariableTest, Constructor) {
  estl::argparse::Variable b(true), c('a'), i(15), d(3.1415),
      ca("Hello World!"), s(std::string("Bye!")),
      vb(std::vector<bool>{true, false}), vc(std::vector<char>{'a', 'b'}),
      vi(std::vector<int>{15, 20}), vd(std::vector<double>{3.14, .15}),
      vs(std::vector<std::string>{"Hello", "World"}), ib({false, true}),
      ic({'c', 'd'}), ii({25, 30}), id({20.17, 20.18}),
      ica({"Hello", "World!"}), is({std::string("Bye"), std::string("!")}), inv;
  EXPECT_EQ(b.IsValid(), true);
  EXPECT_EQ(c.IsValid(), true);
  EXPECT_EQ(i.IsValid(), true);
  EXPECT_EQ(d.IsValid(), true);
  EXPECT_EQ(ca.IsValid(), true);
  EXPECT_EQ(s.IsValid(), true);
  EXPECT_EQ(vb.IsValid(), true);
  EXPECT_EQ(vc.IsValid(), true);
  EXPECT_EQ(vi.IsValid(), true);
  EXPECT_EQ(vd.IsValid(), true);
  EXPECT_EQ(vs.IsValid(), true);
  EXPECT_EQ(ib.IsValid(), true);
  EXPECT_EQ(ic.IsValid(), true);
  EXPECT_EQ(ii.IsValid(), true);
  EXPECT_EQ(id.IsValid(), true);
  EXPECT_EQ(ica.IsValid(), true);
  EXPECT_EQ(is.IsValid(), true);
  EXPECT_EQ(inv.IsValid(), false);
}

TEST_F(ArgParseVariableTest, IsValid) {
  EXPECT_EQ(b_.IsValid(), true);
  EXPECT_EQ(c_.IsValid(), true);
  EXPECT_EQ(i_.IsValid(), true);
  EXPECT_EQ(d_.IsValid(), true);
  EXPECT_EQ(a_.IsValid(), true);
  EXPECT_EQ(s_.IsValid(), true);
  EXPECT_EQ(vb_.IsValid(), true);
  EXPECT_EQ(vc_.IsValid(), true);
  EXPECT_EQ(vi_.IsValid(), true);
  EXPECT_EQ(vd_.IsValid(), true);
  EXPECT_EQ(vs_.IsValid(), true);
  EXPECT_EQ(ib_.IsValid(), true);
  EXPECT_EQ(ic_.IsValid(), true);
  EXPECT_EQ(ii_.IsValid(), true);
  EXPECT_EQ(id_.IsValid(), true);
  EXPECT_EQ(ia_.IsValid(), true);
  EXPECT_EQ(is_.IsValid(), true);
  EXPECT_EQ(inv_.IsValid(), false);
}

TEST_F(ArgParseVariableTest, IsVector) {
  EXPECT_EQ(b_.IsVector(), false);
  EXPECT_EQ(c_.IsVector(), false);
  EXPECT_EQ(i_.IsVector(), false);
  EXPECT_EQ(d_.IsVector(), false);
  EXPECT_EQ(a_.IsVector(), false);
  EXPECT_EQ(s_.IsVector(), false);
  EXPECT_EQ(vb_.IsVector(), true);
  EXPECT_EQ(vc_.IsVector(), true);
  EXPECT_EQ(vi_.IsVector(), true);
  EXPECT_EQ(vd_.IsVector(), true);
  EXPECT_EQ(vs_.IsVector(), true);
  EXPECT_EQ(ib_.IsVector(), true);
  EXPECT_EQ(ic_.IsVector(), true);
  EXPECT_EQ(ii_.IsVector(), true);
  EXPECT_EQ(id_.IsVector(), true);
  EXPECT_EQ(ia_.IsVector(), true);
  EXPECT_EQ(is_.IsVector(), true);
  EXPECT_EQ(inv_.IsVector(), false);
}

TEST_F(ArgParseVariableTest, Type) {
  EXPECT_EQ(b_.Type(), estl::argparse::BOOL);
  EXPECT_EQ(c_.Type(), estl::argparse::CHAR);
  EXPECT_EQ(i_.Type(), estl::argparse::INT);
  EXPECT_EQ(d_.Type(), estl::argparse::DOUBLE);
  EXPECT_EQ(a_.Type(), estl::argparse::STRING);
  EXPECT_EQ(s_.Type(), estl::argparse::STRING);
  EXPECT_EQ(vb_.Type(), estl::argparse::BOOL_VECTOR);
  EXPECT_EQ(vc_.Type(), estl::argparse::CHAR_VECTOR);
  EXPECT_EQ(vi_.Type(), estl::argparse::INT_VECTOR);
  EXPECT_EQ(vd_.Type(), estl::argparse::DOUBLE_VECTOR);
  EXPECT_EQ(vs_.Type(), estl::argparse::STRING_VECTOR);
  EXPECT_EQ(ib_.Type(), estl::argparse::BOOL_VECTOR);
  EXPECT_EQ(ic_.Type(), estl::argparse::CHAR_VECTOR);
  EXPECT_EQ(ii_.Type(), estl::argparse::INT_VECTOR);
  EXPECT_EQ(id_.Type(), estl::argparse::DOUBLE_VECTOR);
  EXPECT_EQ(ia_.Type(), estl::argparse::STRING_VECTOR);
  EXPECT_EQ(is_.Type(), estl::argparse::STRING_VECTOR);
  EXPECT_EQ(inv_.Type(), estl::argparse::NONE);
}

TEST_F(ArgParseVariableTest, PushBack) {
  b_.PushBack(true);
  c_.PushBack('c');
  i_.PushBack(3);
  d_.PushBack(2.5);
  a_.PushBack("Hello");
  s_.PushBack(std::string("Bye"));
  vb_.PushBack(true);
  vc_.PushBack('c');
  vi_.PushBack(3);
  vd_.PushBack(2.5);
  vs_.PushBack("Hello");
  vs_.PushBack(std::string("Bye"));
  EXPECT_EQ(b_, std::vector<bool>({true}));
  EXPECT_EQ(c_, std::vector<char>({'c'}));
  EXPECT_EQ(i_, std::vector<int>({3}));
  EXPECT_EQ(d_, std::vector<double>({2.5}));
  EXPECT_EQ(a_, std::vector<std::string>({"Hello"}));
  EXPECT_EQ(s_, std::vector<std::string>({"Bye"}));
  EXPECT_EQ(vb_, std::vector<bool>({true, false, true}));
  EXPECT_EQ(vc_, std::vector<char>({'a', 'b', 'c'}));
  EXPECT_EQ(vi_, std::vector<int>({1, 2, 3}));
  EXPECT_EQ(vd_, std::vector<double>({1.5, 2.0, 2.5}));
  EXPECT_EQ(vs_, std::vector<std::string>({"Hello", "World", "Hello", "Bye"}));
}

TEST_F(ArgParseVariableTest, Conversion){
  bool b(b_);
  char c( c_);
  int i ( i_);
  double d ( d_);
  std::string s ( s_);
  std::vector<bool> vb( vb_);
  std::vector<char> vc( vc_);
  std::vector<int> vi( vi_);
  std::vector<double> vd( vd_);
  std::vector<std::string> vs( vs_);
  EXPECT_EQ(b, true);
  EXPECT_EQ(c, 'a');
  EXPECT_EQ(i, 1);
  EXPECT_EQ(d, 1.5);
  EXPECT_EQ(s, "World");
  EXPECT_EQ(vb, std::vector<bool>({true, false}));
  EXPECT_EQ(vc, std::vector<char>({'a', 'b'}));
  EXPECT_EQ(vi, std::vector<int>({1, 2}));
  EXPECT_EQ(vd, std::vector<double>({1.5, 2.0}));
  EXPECT_EQ(vs, std::vector<std::string>({"Hello", "World"}));
}

TEST_F(ArgParseVariableTest, Operator){
  estl::argparse::Variable var = true;
  EXPECT_EQ(b_ == var, true);
  EXPECT_EQ(b_ != var, false);
  EXPECT_EQ(b_ < var, false);
  EXPECT_EQ(b_ > var, false);
  EXPECT_EQ(b_ <= var, true);
  EXPECT_EQ(b_ >= var, true);
  EXPECT_EQ(c_ == var, false);
  EXPECT_EQ(c_ < var, false);
  var = 'a';
  EXPECT_EQ(c_ == var, true);
  var = 'd';
  EXPECT_EQ(c_ < var, true);
  var = 1;
  EXPECT_EQ(i_ == var, true);
  var = 17;
  EXPECT_EQ(i_ < var, true);
  var = 1.5;
  EXPECT_EQ(d_ == var, true);
  var = 20.18;
  EXPECT_EQ(d_ < var, true);
  var = "World";
  EXPECT_EQ(s_ == var, true);
  EXPECT_EQ(s_ < var, false);
  var = {false, false, true};
  EXPECT_EQ(vb_ < var, false);
  var = {'c', 'd'};
  EXPECT_EQ(vc_ < var, true);
  var = {-1, -2};
  EXPECT_EQ(vi_ < var, false);
  var = {3.1415, 2.1415};
  EXPECT_EQ(vd_ < var, true);
  var = {"HI", "Bye"};
  EXPECT_EQ(vs_ < var, false);
}

TEST_F(ArgParseVariableTest, StreamOperator){
  std::stringstream out;
  out << b_;
  EXPECT_EQ(out.str(), "1");
  out.str("");
  out << c_;
  EXPECT_EQ(out.str(), "a");
  out.str("");
  out << i_;
  EXPECT_EQ(out.str(), "1");
  out.str("");
  out << d_;
  EXPECT_EQ(out.str(), "1.5");
  out.str("");
  out << s_;
  EXPECT_EQ(out.str(), "World");
  out.str("");
  out << vb_;
  EXPECT_EQ(out.str(), "1, 0");
  out.str("");
  out << vc_;
  EXPECT_EQ(out.str(), "a, b");
  out.str("");
  out << vi_;
  EXPECT_EQ(out.str(), "1, 2");
  out.str("");
  out << vd_;
  EXPECT_EQ(out.str(), "1.5, 2");
  out.str("");
  out << vs_;
  EXPECT_EQ(out.str(), "Hello, World");
  out.str("");
  out << inv_;
  EXPECT_EQ(out.str(), "(null)");
}
