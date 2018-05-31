#include "basic/matrix.hpp"
#include "basic/vector.hpp"
#include "gtest/gtest.h"

using namespace estl::base;

class BasicMatrixTest : public testing::Test {
 protected:
  virtual void SetUp() {
    a = {1, 2, 3, 4};
    b = {5, 6, 7, 8};
    c = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    d = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  }
  virtual void TearDown() {}
  Mat2f a, b;
  Mat3f c;
  Mat4f d;
};

TEST_F(BasicMatrixTest, ElementAccess) {
  EXPECT_EQ(a[3], 4);
  EXPECT_EQ(d(2, 1), 10);
  a.Fill(1);
  a.Diagonal(3);
  EXPECT_EQ(a, Mat2f({3, 1, 1, 3}));
}

TEST_F(BasicMatrixTest, Stream) {
  std::stringstream ss;
  ss << a;
  EXPECT_EQ(ss.str(), "[[1,2],[3,4]]");
}

TEST_F(BasicMatrixTest, BooleanOps) {
  EXPECT_EQ(a == b, false);
  EXPECT_EQ(a != a, false);
  EXPECT_EQ(a < b, true);
  EXPECT_EQ(a > b, false);
  EXPECT_EQ(a <= b, true);
  EXPECT_EQ(a >= b, false);
}

TEST_F(BasicMatrixTest, MatrixArithmetic) {
  EXPECT_EQ(a + b, Mat2f({6, 8, 10, 12}));
  EXPECT_EQ(a - b, Mat2f({-4, -4, -4, -4}));
  EXPECT_EQ(a * b, Mat2f({5, 12, 21, 32}));
  EXPECT_EQ(a / b, Mat2f({0.2, 1.0 / 3.0, 3.0 / 7.0, 0.5}));
}

TEST_F(BasicMatrixTest, ScalarArithmetic) {
  EXPECT_EQ(a + 2.0f, Mat2f({3, 4, 5, 6}));
  EXPECT_EQ(a - 3.0f, Mat2f({-2, -1, 0, 1}));
  EXPECT_EQ(a * 2.0f, Mat2f({2, 4, 6, 8}));
  EXPECT_EQ(a / 3.0f, Mat2f({1.0 / 3.0, 2.0 / 3.0, 1, 4.0 / 3.0}));
}

TEST_F(BasicMatrixTest, Multiplication){
  Vec2f v2(1.0, 2.0);
  Vec3f v3(1.0, 2.0, 3.0);
  Vec4f v4(1.0, 2.0, 3.0, 4.0);
  EXPECT_EQ(Dot(a,b), Mat2f({19, 22, 43, 50}));
  EXPECT_EQ(Dot(a,v2), Vec2f(5, 14));
  EXPECT_EQ(Dot(a,v3), Vec3f(5, 14, 0));
  EXPECT_EQ(Dot(a,v4), Vec4f(5, 14, 0, 0));
  EXPECT_EQ(Dot(c,v2), Vec2f(14, 20));
  EXPECT_EQ(Dot(c,v3), Vec3f(14, 32, 50));
  EXPECT_EQ(Dot(c,v4), Vec4f(14, 32, 50, 0));
  EXPECT_EQ(Dot(d,v2), Vec2f(12, 32));
  EXPECT_EQ(Dot(d,v3), Vec3f(18, 46, 74));
  EXPECT_EQ(Dot(d,v4), Vec4f(30, 70, 110, 150));
}

