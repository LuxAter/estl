// Copyright 2017 Arden Rasmussen
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

TEST(iostream, scan_basic) {
  int a = int();
  unsigned int b = unsigned();
  double c = double();
  char d = char();
  std::string e = std::string();
  estl::sscan("12345", "%i", a);
  EXPECT_EQ(a, 12345);
  estl::sscan("12345", "%d", a);
  EXPECT_EQ(a, 12345);
  estl::sscan("123456", "%u", b);
  EXPECT_EQ(b, 123456);
  estl::sscan("361100", "%o", b);
  EXPECT_EQ(b, 123456);
  estl::sscan("1e240", "%x", b);
  EXPECT_EQ(b, 123456);
  estl::sscan("123.456000", "%f", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("1.234560e+02", "%e", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("123.456", "%g", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("0x1.edd2f1a9fbe77p+6", "%a", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("a", "%c", d);
  EXPECT_EQ(d, 'a');
  estl::sscan("stream_test", "%s", e);
  EXPECT_EQ(e, "stream_test");
  estl::sscan("abcde", "%n", e);
  EXPECT_EQ(e, "abcde");
}

TEST(iostream, scan_uppercase) {
  int a = int();
  unsigned int b = unsigned();
  double c = double();
  char d = char();
  std::string e = std::string();
  estl::sscan("12345", "%I", a);
  EXPECT_EQ(a, 12345);
  estl::sscan("12345", "%D", a);
  EXPECT_EQ(a, 12345);
  estl::sscan("123456", "%U", b);
  EXPECT_EQ(b, 123456);
  estl::sscan("361100", "%O", b);
  EXPECT_EQ(b, 123456);
  estl::sscan("1E240", "%X", b);
  EXPECT_EQ(b, 123456);
  estl::sscan("123.456000", "%F", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("1.234560E+02", "%E", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("123.456", "%G", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("0x1.EDD2F1A9FBE77P+6", "%A", c);
  EXPECT_EQ(c, 123.456);
  estl::sscan("a", "%C", d);
  EXPECT_EQ(d, 'a');
  estl::sscan("stream_test", "%S", e);
  EXPECT_EQ(e, "stream_test");
  estl::sscan("abcde", "%N", e);
  EXPECT_EQ(e, "abcde");
}

TEST(iostream, scan_type_safe) {
  int a = int();
  unsigned int b = unsigned();
  double c = double();
  char d = char();
  std::string e = std::string();
  estl::sscan("z", "%i", a);
  EXPECT_EQ(a, 0);
  estl::sscan("z", "%d", a);
  EXPECT_EQ(a, 0);
  estl::sscan("y", "%u", b);
  EXPECT_EQ(b, 0);
  estl::sscan("y", "%o", b);
  EXPECT_EQ(b, 0);
  estl::sscan("y", "%x", b);
  EXPECT_EQ(b, 0);
  estl::sscan("x", "%f", c);
  EXPECT_EQ(c, 0.0);
  estl::sscan("x", "%e", c);
  EXPECT_EQ(c, 0.0);
  estl::sscan("x", "%g", c);
  EXPECT_EQ(c, 0.0);
  estl::sscan("x", "%a", c);
  EXPECT_EQ(c, 0.0);
  estl::sscan("12345", "%c", d);
  EXPECT_EQ(d, '1');
  estl::sscan("12345", "%s", e);
  EXPECT_EQ(e, "12345");
  estl::sscan("abcde", "%n", e);
  EXPECT_EQ(e, "abcde");
}

TEST(iostream, scan_text) {
  std::string a = std::string();
  int b = int();
  estl::sscan("Hello World!!", "Hello World!!", a);
  EXPECT_EQ(a, std::string());
  estl::sscan("Hello World!!%", "Hello World!!%", a);
  EXPECT_EQ(a, std::string());
  estl::sscan("Hello World!!", "Hello %s!!", a);
  EXPECT_EQ(a, "World");
  estl::sscan("Hello Year 2017!!", "Hello Year %i!!", b);
  EXPECT_EQ(b, 2017);
  estl::sscan("Hello Year %2018!!", "Hello Year %%%i!!", b);
  EXPECT_EQ(b, 2018);
}

TEST(iostream, scan_over_width) {
  int a = int();
  double b = double();
  std::string c = std::string();
  estl::sscan("1234567", "%5i", a);
  EXPECT_EQ(a, 12345);
  estl::sscan("-1234567", "%5i", a);
  EXPECT_EQ(a, -1234);
  estl::sscan("123.456000", "%5f", b);
  EXPECT_EQ(b, 123.4);
  estl::sscan("-123.456000", "%5f", b);
  EXPECT_EQ(b, -123.0);
  estl::sscan("abcdefghi", "%5s", c);
  EXPECT_EQ(c, "abcde");
}

TEST(iostream, scan_width) {
  int a = int();
  double b = double();
  std::string c = std::string();
  estl::sscan("123 45", "%5i", a);
  EXPECT_EQ(a, 123);
  estl::sscan("-123 45", "%5i", a);
  EXPECT_EQ(a, -123);
  estl::sscan("12.23 45", "%5f", b);
  EXPECT_EQ(b, 12.23);
  estl::sscan("-1.23 45", "%5f", b);
  EXPECT_EQ(b, -1.23);
  estl::sscan("abcd efgh", "%5s", c);
  EXPECT_EQ(c, "abcd");
}

TEST(iostream, scan_delimiter) {
  int a = int();
  estl::sscan("1234567890", "%i67890", a);
  EXPECT_EQ(a, 12345);
}
