#include "format.hpp"
#include "gtest/gtest.h"

using namespace estl::format;

TEST(FormatTest, BaseString) {
  EXPECT_EQ(Format("Hello, World!"), "Hello, World!");
}

TEST(FormatTest, BaseType) {
  EXPECT_EQ(Format("Hello, {}!", "World"), "Hello, World!");
  EXPECT_EQ(Format("Hello, {}!", false), "Hello, false!");
  EXPECT_EQ(Format("Hello, {}!", 'a'), "Hello, a!");
  EXPECT_EQ(Format("Hello, {}!", 2018), "Hello, 2018!");
  EXPECT_EQ(Format("Hello, {}!", 3.1415), "Hello, 3.141500!");
}

TEST(FormatTest, ArgumentIndex) {
  EXPECT_EQ(Format("{1}, {0}!", "World", "Hello"), "Hello, World!");
}

TEST(FormatTest, ArgumentSubscript) {
  EXPECT_EQ(Format("{[0]}, {0[3]}", "abcdefg"), "a, d");
  EXPECT_EQ(Format("{[2]:}, {0[4]:}", "abcdefg"), "c, e");
}

TEST(FormatTest, IntegerFormat) {
  EXPECT_EQ(Format("Value: {: 010.5}", 15.0), "Value:  015.00000");
}

TEST(FormatTest, StringFormat) {
  EXPECT_EQ(Format("Value: {:<10}", "Hello"), "Value: Hello     ");
  EXPECT_EQ(Format("Value: {:>10}", "Hello"), "Value:      Hello");
  EXPECT_EQ(Format("Value: {:^10}", "Hello"), "Value:   Hello   ");
  EXPECT_EQ(Format("Value: {:==10}", "-Hello"), "Value: -====Hello");
}

TEST(FormatTest, InvalidFmt) {
  try {
    Format("Value: {:a}", "HI");
    FAIL() << "\"{:a}\" should be an invalid format\n";
  } catch (std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "Format string specifier (which is "
              "\":a\") is of an invalid format");
  }
}

TEST(FormatTest, InvalidIndex) {
  try {
    Format("Value: {5}", "hello");
    FAIL() << "\"5\" should be out of range\n";
  } catch (std::out_of_range& e) {
    EXPECT_EQ(std::string(e.what()),
              "argument index (which is 4) >= argument count (which is 1)");
  }
}

TEST(FormatTest, InvalidSubscript) {
  try {
    Format("{[2]}", 3.1415);
    FAIL() << "\"3.1415\" should not be subscriptable\n";
  } catch (std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "argument index (which is 0) of type double is not "
              "subscriptable, but format string requested subscript");
  }
}
