#include "gtest/gtest.h"

#include <string>

#include "stream.hpp"

TEST(iostream, printf_basic) {
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
}
