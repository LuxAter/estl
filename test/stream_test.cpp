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

TEST(iostream, print_uppercase) {
  EXPECT_EQ(estl::sprint("%I", 12345), "12345");
  EXPECT_EQ(estl::sprint("%D", 12345), "12345");
  EXPECT_EQ(estl::sprint("%U", unsigned(12345)), "12345");
  EXPECT_EQ(estl::sprint("%O", unsigned(123456)), "361100");
  EXPECT_EQ(estl::sprint("%X", unsigned(123456)), "1E240");
  EXPECT_EQ(estl::sprint("%F", 123.456), "123.456000");
  EXPECT_EQ(estl::sprint("%E", 123.456), "1.234560E+02");
  EXPECT_EQ(estl::sprint("%G", 123.456), "123.456");
  EXPECT_EQ(estl::sprint("%A", 123.456), "0X1.EDD2F1A9FBE77P+6");
  EXPECT_EQ(estl::sprint("%C", 'a'), "a");
  EXPECT_EQ(estl::sprint("%S", "stream_test"), "stream_test");
  EXPECT_EQ(estl::sprint("%N", "abcde"), "abcde");
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
  EXPECT_EQ(estl::sprint("Hello World!!%"), "Hello World!!%");
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

TEST(iostream, print_precision) {
  EXPECT_EQ(estl::sprint("%.3i", 1234567), "1234567");
  EXPECT_EQ(estl::sprint("%.3i", -1234567), "-1234567");
  EXPECT_EQ(estl::sprint("%.3f", 123.456), "123.456");
  EXPECT_EQ(estl::sprint("%.3f", -123.456), "-123.456");
  EXPECT_EQ(estl::sprint("%.3s", "abcdefghi"), "abcdefghi");
}

TEST(iostream, print_justification) {
  EXPECT_EQ(estl::sprint("%-12i", 1234567), "1234567     ");
  EXPECT_EQ(estl::sprint("%-12i", -1234567), "-1234567    ");
  EXPECT_EQ(estl::sprint("%-12f", 123.456), "123.456000  ");
  EXPECT_EQ(estl::sprint("%-12f", -123.456), "-123.456000 ");
  EXPECT_EQ(estl::sprint("%-12s", "abcdefghi"), "abcdefghi   ");
}

TEST(iostream, print_padding) {
  EXPECT_EQ(estl::sprint("%012i", 1234567), "000001234567");
  EXPECT_EQ(estl::sprint("%012i", -1234567), "-00001234567");
  EXPECT_EQ(estl::sprint("%012f", 123.456), "00123.456000");
  EXPECT_EQ(estl::sprint("%012f", -123.456), "-0123.456000");
  EXPECT_EQ(estl::sprint("%012s", "abcdefghi"), "   abcdefghi");
}
