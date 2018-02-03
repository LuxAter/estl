// Copyright 2018 Arden Rasmussen

#include "gtest/gtest.h"
#include "vector.hpp"

#include <math.h>

class VectorTest : public testing::Test {
 protected:
  virtual void SetUp() { b = {1.0, 2.0, 3.0}; }
  virtual void TearDown() {}
  estl::vector<double, 3> a, b;
  estl::vector<double, 0> c;
};

template<typename _Tp, std::size_t _N>
::testing::AssertionResult VectorMatch(estl::vector<_Tp, _N> lhs, estl::vector<_Tp, _N> rhs){
  for(size_t i = 0; i < _N; i++){
    EXPECT_FLOAT_EQ(lhs.at(i), rhs.at(i));
  }
  return ::testing::AssertionSuccess();
}

TEST_F(VectorTest, Constructor) {
  estl::vector<double, 3> vec({0.0, 0.0, 0.0});
  EXPECT_EQ(a, vec);
  vec = {1.0, 2.0, 3.0};
  EXPECT_EQ(b, vec);
}

TEST_F(VectorTest, ElementAccess) {
  EXPECT_FLOAT_EQ(b.at(1), 2.0);
  EXPECT_FLOAT_EQ(b[2], 3.0);
  EXPECT_FLOAT_EQ(b.front(), 1.0);
  EXPECT_FLOAT_EQ(b.back(), 3.0);
  EXPECT_FLOAT_EQ(*(b.data() + 1), 2.0);
}

TEST_F(VectorTest, Iterator) {
  EXPECT_FLOAT_EQ(*b.begin(), 1.0);
  EXPECT_FLOAT_EQ(*b.cbegin(), 1.0);
  EXPECT_FLOAT_EQ(*(b.end() - 1), 3.0);
  EXPECT_FLOAT_EQ(*(b.cend() - 1), 3.0);
  EXPECT_FLOAT_EQ(*(b.rbegin() - 2), 2.0);
  EXPECT_FLOAT_EQ(*(b.rend() + 2), 1.0);
  EXPECT_FLOAT_EQ(*(b.crbegin() - 2), 2.0);
  EXPECT_FLOAT_EQ(*(b.crend() + 2), 1.0);
  EXPECT_FLOAT_EQ(*b.element(2), 3.0);
}

TEST_F(VectorTest, Capacity) {
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(c.empty(), true);
  EXPECT_EQ(b.size(), 3);
}

TEST_F(VectorTest, Operations) {
  estl::vector<double, 3> vec;
  a.fill(3.14);
  vec = {3.14, 3.14, 3.14};
  EXPECT_EQ(a, vec);
  a.fill(-2.718);
  a(fabs);
  vec = {2.718, 2.718, 2.718};
  EXPECT_EQ(a, vec);
}

TEST_F(VectorTest, Operators) {
  estl::vector<double, 3> vec;
  vec = {2.0, 3.0, 4.0};
  b += 1;
  EXPECT_EQ(b, vec);
  vec = {-1.0, 0.0, 1.0};
  b -= 3;
  EXPECT_EQ(b, vec);
  vec = {-2.0, 0.0, 2.0};
  b *= 2;
  EXPECT_EQ(b, vec);
  vec = {-0.5, 0.0, 0.5};
  b /= 4;
  EXPECT_EQ(b, vec);
  std::stringstream ss;
  ss << b;
  std::string str = ss.str();
  EXPECT_EQ(str, "<-0.5, 0, 0.5>");
}

TEST_F(VectorTest, Boolian) {
  EXPECT_EQ(b == a, false);
  EXPECT_EQ(b != a, true);
  EXPECT_EQ(b > a, true);
  EXPECT_EQ(b < a, false);
  EXPECT_EQ(b >= b, true);
  EXPECT_EQ(b >= a, false);
  EXPECT_EQ(b <= b, true);
  EXPECT_EQ(b <= a, true);
}

TEST_F(VectorTest, Functions){
  estl::vector<double, 3> vec = {-3.0, 6.0, -3.0};
  a = {4.0, 5.0, 6.0};
  EXPECT_EQ(estl::sum(b), 6.0);
  EXPECT_EQ(estl::dot(b, a), 32);
  EXPECT_EQ(estl::cross(b, a), vec);
  EXPECT_FLOAT_EQ(estl::length(b), 3.7416575);
  vec = {1.0/sqrt(14.0), sqrt(2.0/7.0), 3.0/sqrt(14.0)};
  EXPECT_EQ(estl::normalize(b), vec);
  vec = {sqrt(14.0), asin(sqrt(5.0/14.0)), atan(2.0)};
  EXPECT_EQ(estl::SphericalCoordinates(b), vec);
  EXPECT_TRUE(VectorMatch(estl::CartesianCoordinates(estl::SphericalCoordinates(b)), b));
}
