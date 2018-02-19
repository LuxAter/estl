// Copyright 2017 Arden Rasmussen
#include <string>

#include "gtest/gtest.h"
#include "stream.hpp"

TEST(iostream, print_basic) {
  EXPECT_EQ(estl::stream::sprint("%i", 12345), "12345");
  EXPECT_EQ(estl::stream::sprint("%d", 12345), "12345");
  EXPECT_EQ(estl::stream::sprint("%u", unsigned(12345)), "12345");
  EXPECT_EQ(estl::stream::sprint("%o", unsigned(123456)), "361100");
  EXPECT_EQ(estl::stream::sprint("%x", unsigned(123456)), "1e240");
  EXPECT_EQ(estl::stream::sprint("%f", 123.456), "123.456000");
  EXPECT_EQ(estl::stream::sprint("%e", 123.456), "1.234560e+02");
  EXPECT_EQ(estl::stream::sprint("%g", 123.456), "123.456");
  EXPECT_EQ(estl::stream::sprint("%a", 123.456), "0x1.edd2f1a9fbe77p+6");
  EXPECT_EQ(estl::stream::sprint("%c", 'a'), "a");
  EXPECT_EQ(estl::stream::sprint("%s", "stream_test"), "stream_test");
  EXPECT_EQ(estl::stream::sprint("%n", "abcde"), "abcde");
}

TEST(iostream, print_uppercase) {
  EXPECT_EQ(estl::stream::sprint("%I", 12345), "12345");
  EXPECT_EQ(estl::stream::sprint("%D", 12345), "12345");
  EXPECT_EQ(estl::stream::sprint("%U", unsigned(12345)), "12345");
  EXPECT_EQ(estl::stream::sprint("%O", unsigned(123456)), "361100");
  EXPECT_EQ(estl::stream::sprint("%X", unsigned(123456)), "1E240");
  EXPECT_EQ(estl::stream::sprint("%F", 123.456), "123.456000");
  EXPECT_EQ(estl::stream::sprint("%E", 123.456), "1.234560E+02");
  EXPECT_EQ(estl::stream::sprint("%G", 123.456), "123.456");
  EXPECT_EQ(estl::stream::sprint("%A", 123.456), "0X1.EDD2F1A9FBE77P+6");
  EXPECT_EQ(estl::stream::sprint("%C", 'a'), "a");
  EXPECT_EQ(estl::stream::sprint("%S", "stream_test"), "stream_test");
  EXPECT_EQ(estl::stream::sprint("%N", "abcde"), "abcde");
}

TEST(iostream, print_type_safe) {
  std::string test = "";
  test += '\0';
  EXPECT_EQ(estl::stream::sprint("%i", 'a'), "0");
  EXPECT_EQ(estl::stream::sprint("%d", 'a'), "0");
  EXPECT_EQ(estl::stream::sprint("%u", 'b'), "0");
  EXPECT_EQ(estl::stream::sprint("%o", 'b'), "0");
  EXPECT_EQ(estl::stream::sprint("%x", 'b'), "0");
  EXPECT_EQ(estl::stream::sprint("%f", 12345), "0");
  EXPECT_EQ(estl::stream::sprint("%e", 12345), "0");
  EXPECT_EQ(estl::stream::sprint("%g", 12345), "0");
  EXPECT_EQ(estl::stream::sprint("%a", 12345), "0");
  EXPECT_EQ(estl::stream::sprint("%c", 12345), test);
  EXPECT_EQ(estl::stream::sprint("%s", 12345), "");
  EXPECT_EQ(estl::stream::sprint("%n", "abcde"), "abcde");
}

TEST(iostream, print_text) {
  EXPECT_EQ(estl::stream::sprint("Hello World!!"), "Hello World!!");
  EXPECT_EQ(estl::stream::sprint("Hello World!!%"), "Hello World!!%");
  EXPECT_EQ(estl::stream::sprint("Hello %s!!", "World"), "Hello World!!");
  EXPECT_EQ(estl::stream::sprint("Hello Year %i!!", 2017), "Hello Year 2017!!");
  EXPECT_EQ(estl::stream::sprint("Hello Year %%%i!!", 2017),
            "Hello Year %2017!!");
}

TEST(iostream, print_flags) {
  EXPECT_EQ(estl::stream::sprint("%+i", 1234), "+1234");
  EXPECT_EQ(estl::stream::sprint("%+i", -1234), "-1234");
  EXPECT_EQ(estl::stream::sprint("%+f", 123.456), "+123.456000");
  EXPECT_EQ(estl::stream::sprint("%+f", -123.456), "-123.456000");
  EXPECT_EQ(estl::stream::sprint("%+s", "abcd"), "abcd");
  EXPECT_EQ(estl::stream::sprint("% i", 1234), " 1234");
  EXPECT_EQ(estl::stream::sprint("% i", -1234), "-1234");
  EXPECT_EQ(estl::stream::sprint("% f", 123.456), " 123.456000");
  EXPECT_EQ(estl::stream::sprint("% f", -123.456), "-123.456000");
  EXPECT_EQ(estl::stream::sprint("% s", "abcd"), "abcd");
}

TEST(iostream, print_over_width) {
  EXPECT_EQ(estl::stream::sprint("%5i", 1234567), "1234567");
  EXPECT_EQ(estl::stream::sprint("%5i", -1234567), "-1234567");
  EXPECT_EQ(estl::stream::sprint("%5f", 123.456), "123.456000");
  EXPECT_EQ(estl::stream::sprint("%5f", -123.456), "-123.456000");
  EXPECT_EQ(estl::stream::sprint("%5s", "abcdefghi"), "abcdefghi");
}

TEST(iostream, print_width) {
  EXPECT_EQ(estl::stream::sprint("%12i", 1234567), "     1234567");
  EXPECT_EQ(estl::stream::sprint("%12i", -1234567), "    -1234567");
  EXPECT_EQ(estl::stream::sprint("%12f", 123.456), "  123.456000");
  EXPECT_EQ(estl::stream::sprint("%12f", -123.456), " -123.456000");
  EXPECT_EQ(estl::stream::sprint("%12s", "abcdefghi"), "   abcdefghi");
}

TEST(iostream, print_precision) {
  EXPECT_EQ(estl::stream::sprint("%.3i", 1234567), "1234567");
  EXPECT_EQ(estl::stream::sprint("%.3i", -1234567), "-1234567");
  EXPECT_EQ(estl::stream::sprint("%.3f", 123.456), "123.456");
  EXPECT_EQ(estl::stream::sprint("%.3f", -123.456), "-123.456");
  EXPECT_EQ(estl::stream::sprint("%.3s", "abcdefghi"), "abcdefghi");
}

TEST(iostream, print_justification) {
  EXPECT_EQ(estl::stream::sprint("%-12i", 1234567), "1234567     ");
  EXPECT_EQ(estl::stream::sprint("%-12i", -1234567), "-1234567    ");
  EXPECT_EQ(estl::stream::sprint("%-12f", 123.456), "123.456000  ");
  EXPECT_EQ(estl::stream::sprint("%-12f", -123.456), "-123.456000 ");
  EXPECT_EQ(estl::stream::sprint("%-12s", "abcdefghi"), "abcdefghi   ");
}

TEST(iostream, print_padding) {
  EXPECT_EQ(estl::stream::sprint("%012i", 1234567), "000001234567");
  EXPECT_EQ(estl::stream::sprint("%012i", -1234567), "-00001234567");
  EXPECT_EQ(estl::stream::sprint("%012f", 123.456), "00123.456000");
  EXPECT_EQ(estl::stream::sprint("%012f", -123.456), "-0123.456000");
  EXPECT_EQ(estl::stream::sprint("%012s", "abcdefghi"), "   abcdefghi");
}

TEST(iostream, scan_basic) {
  int a = int();
  unsigned int b = unsigned();
  double c = double();
  char d = char();
  std::string e = std::string();
  estl::stream::sscan("12345", "%i", a);
  EXPECT_EQ(a, 12345);
  estl::stream::sscan("12345", "%d", a);
  EXPECT_EQ(a, 12345);
  estl::stream::sscan("123456", "%u", b);
  EXPECT_EQ(b, 123456);
  estl::stream::sscan("361100", "%o", b);
  EXPECT_EQ(b, 123456);
  estl::stream::sscan("1e240", "%x", b);
  EXPECT_EQ(b, 123456);
  estl::stream::sscan("123.456000", "%f", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("1.234560e+02", "%e", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("123.456", "%g", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("0x1.edd2f1a9fbe77p+6", "%a", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("a", "%c", d);
  EXPECT_EQ(d, 'a');
  estl::stream::sscan("stream_test", "%s", e);
  EXPECT_EQ(e, "stream_test");
  estl::stream::sscan("abcde", "%n", e);
  EXPECT_EQ(e, "abcde");
}

TEST(iostream, scan_uppercase) {
  int a = int();
  unsigned int b = unsigned();
  double c = double();
  char d = char();
  std::string e = std::string();
  estl::stream::sscan("12345", "%I", a);
  EXPECT_EQ(a, 12345);
  estl::stream::sscan("12345", "%D", a);
  EXPECT_EQ(a, 12345);
  estl::stream::sscan("123456", "%U", b);
  EXPECT_EQ(b, 123456);
  estl::stream::sscan("361100", "%O", b);
  EXPECT_EQ(b, 123456);
  estl::stream::sscan("1E240", "%X", b);
  EXPECT_EQ(b, 123456);
  estl::stream::sscan("123.456000", "%F", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("1.234560E+02", "%E", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("123.456", "%G", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("0x1.EDD2F1A9FBE77P+6", "%A", c);
  EXPECT_EQ(c, 123.456);
  estl::stream::sscan("a", "%C", d);
  EXPECT_EQ(d, 'a');
  estl::stream::sscan("stream_test", "%S", e);
  EXPECT_EQ(e, "stream_test");
  estl::stream::sscan("abcde", "%N", e);
  EXPECT_EQ(e, "abcde");
}

TEST(iostream, scan_type_safe) {
  int a = int();
  unsigned int b = unsigned();
  double c = double();
  char d = char();
  std::string e = std::string();
  estl::stream::sscan("z", "%i", a);
  EXPECT_EQ(a, 0);
  estl::stream::sscan("z", "%d", a);
  EXPECT_EQ(a, 0);
  estl::stream::sscan("y", "%u", b);
  EXPECT_EQ(b, 0);
  estl::stream::sscan("y", "%o", b);
  EXPECT_EQ(b, 0);
  estl::stream::sscan("y", "%x", b);
  EXPECT_EQ(b, 0);
  estl::stream::sscan("x", "%f", c);
  EXPECT_EQ(c, 0.0);
  estl::stream::sscan("x", "%e", c);
  EXPECT_EQ(c, 0.0);
  estl::stream::sscan("x", "%g", c);
  EXPECT_EQ(c, 0.0);
  estl::stream::sscan("x", "%a", c);
  EXPECT_EQ(c, 0.0);
  estl::stream::sscan("12345", "%c", d);
  EXPECT_EQ(d, '1');
  estl::stream::sscan("12345", "%s", e);
  EXPECT_EQ(e, "12345");
  estl::stream::sscan("abcde", "%n", e);
  EXPECT_EQ(e, "abcde");
}

TEST(iostream, scan_text) {
  std::string a = std::string();
  int b = int();
  estl::stream::sscan("Hello World!!", "Hello World!!", a);
  EXPECT_EQ(a, std::string());
  estl::stream::sscan("Hello World!!%", "Hello World!!%", a);
  EXPECT_EQ(a, std::string());
  estl::stream::sscan("Hello World!!", "Hello %s!!", a);
  EXPECT_EQ(a, "World");
  estl::stream::sscan("Hello Year 2017!!", "Hello Year %i!!", b);
  EXPECT_EQ(b, 2017);
  estl::stream::sscan("Hello Year %2018!!", "Hello Year %%%i!!", b);
  EXPECT_EQ(b, 2018);
}

TEST(iostream, scan_over_width) {
  int a = int();
  double b = double();
  std::string c = std::string();
  estl::stream::sscan("1234567", "%5i", a);
  EXPECT_EQ(a, 12345);
  estl::stream::sscan("-1234567", "%5i", a);
  EXPECT_EQ(a, -1234);
  estl::stream::sscan("123.456000", "%5f", b);
  EXPECT_EQ(b, 123.4);
  estl::stream::sscan("-123.456000", "%5f", b);
  EXPECT_EQ(b, -123.0);
  estl::stream::sscan("abcdefghi", "%5s", c);
  EXPECT_EQ(c, "abcde");
}

TEST(iostream, scan_width) {
  int a = int();
  double b = double();
  std::string c = std::string();
  estl::stream::sscan("123 45", "%5i", a);
  EXPECT_EQ(a, 123);
  estl::stream::sscan("-123 45", "%5i", a);
  EXPECT_EQ(a, -123);
  estl::stream::sscan("12.23 45", "%5f", b);
  EXPECT_EQ(b, 12.23);
  estl::stream::sscan("-1.23 45", "%5f", b);
  EXPECT_EQ(b, -1.23);
  estl::stream::sscan("abcd efgh", "%5s", c);
  EXPECT_EQ(c, "abcd");
}

TEST(iostream, scan_delimiter) {
  int a = int();
  estl::stream::sscan("1234567890", "%i67890", a);
  EXPECT_EQ(a, 12345);
}
