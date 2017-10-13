#include <string>

#include "gtest/gtest.h"
#include "stream.hpp"

TEST(iostream, print_basic) {
  EXPECT_EQ(estl::sprint("%i", 12345), "12345");
  EXPECT_EQ(estl::sprint("%d", 12345), "12345");
  EXPECT_EQ(estl::sprint("%u", unsigned(12345)), "12345");
  EXPECT_EQ(estl::sprint("%o", unsigned(123456)), "361100");
  EXPECT_EQ(estl::sprint("%x", unsigned(123456)), "1e240");
  EXPECT_EQ(estl::sprint("%f", 123.456), "123.456000");
  EXPECT_EQ(estl::sprint("%e", 123.456), "1.234560e+02");
  EXPECT_EQ(estl::sprint("%g", 123.456), "123.456");
  EXPECT_EQ(estl::sprint("%a", 123.456), "0x1.edd2f1a9fbe77p+6");
  EXPECT_EQ(estl::sprint("%c", 'a'), "a");
  EXPECT_EQ(estl::sprint("%s", "stream_test"), "stream_test");
  EXPECT_EQ(estl::sprint("%n", "abcde"), "abcde");
}

TEST(iostream, print_type_safe) {
  std::string test = "";
  test += '\0';
  EXPECT_EQ(estl::sprint("%i", 'a'), "0");
  EXPECT_EQ(estl::sprint("%d", 'a'), "0");
  EXPECT_EQ(estl::sprint("%u", 'b'), "0");
  EXPECT_EQ(estl::sprint("%o", 'b'), "0");
  EXPECT_EQ(estl::sprint("%x", 'b'), "0");
  EXPECT_EQ(estl::sprint("%f", 12345), "0");
  EXPECT_EQ(estl::sprint("%e", 12345), "0");
  EXPECT_EQ(estl::sprint("%g", 12345), "0");
  EXPECT_EQ(estl::sprint("%a", 12345), "0");
  EXPECT_EQ(estl::sprint("%c", 12345), test);
  EXPECT_EQ(estl::sprint("%s", 12345), "");
  EXPECT_EQ(estl::sprint("%n", "abcde"), "abcde");
}

TEST(iostream, print_text) {
  EXPECT_EQ(estl::sprint("Hello World!!"), "Hello World!!");
  EXPECT_EQ(estl::sprint("Hello %s!!", "World"), "Hello World!!");
  EXPECT_EQ(estl::sprint("Hello Year %i!!", 2017), "Hello Year 2017!!");
  EXPECT_EQ(estl::sprint("Hello Year %%%i!!", 2017), "Hello Year %2017!!");
}

TEST(iostream, print_flags) {
  EXPECT_EQ(estl::sprint("%+i", 1234), "+1234");
  EXPECT_EQ(estl::sprint("%+i", -1234), "-1234");
  EXPECT_EQ(estl::sprint("%+f", 123.456), "+123.456000");
  EXPECT_EQ(estl::sprint("%+f", -123.456), "-123.456000");
  EXPECT_EQ(estl::sprint("%+s", "abcd"), "abcd");
  EXPECT_EQ(estl::sprint("% i", 1234), " 1234");
  EXPECT_EQ(estl::sprint("% i", -1234), "-1234");
  EXPECT_EQ(estl::sprint("% f", 123.456), " 123.456000");
  EXPECT_EQ(estl::sprint("% f", -123.456), "-123.456000");
  EXPECT_EQ(estl::sprint("% s", "abcd"), "abcd");
}

TEST(iostream, print_over_width) {
  EXPECT_EQ(estl::sprint("%5i", 1234567), "1234567");
  EXPECT_EQ(estl::sprint("%5i", -1234567), "-1234567");
  EXPECT_EQ(estl::sprint("%5f", 123.456), "123.456000");
  EXPECT_EQ(estl::sprint("%5f", -123.456), "-123.456000");
  EXPECT_EQ(estl::sprint("%5s", "abcdefghi"), "abcdefghi");
}

TEST(iostream, print_width) {
  EXPECT_EQ(estl::sprint("%12i", 1234567), "     1234567");
  EXPECT_EQ(estl::sprint("%12i", -1234567), "    -1234567");
  EXPECT_EQ(estl::sprint("%12f", 123.456), "  123.456000");
  EXPECT_EQ(estl::sprint("%12f", -123.456), " -123.456000");
  EXPECT_EQ(estl::sprint("%12s", "abcdefghi"), "   abcdefghi");
}
