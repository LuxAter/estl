#include "basic/vector.hpp"
#include "gtest/gtest.h"

using namespace estl::base;

class BasicVec2Test : public testing::Test {
 protected:
  virtual void SetUp() {
    a = {1, 2};
    b = {3, 4};
  }
  virtual void TearDown() {}
  Vec2f a, b;
};

TEST_F(BasicVec2Test, ElementAccess) {
  EXPECT_EQ(a.x, 1);
  EXPECT_EQ(a[1], 2);
}

TEST_F(BasicVec2Test, Stream) {
  std::stringstream ss;
  ss << a;
  EXPECT_EQ(ss.str(), "<1,2>");
}

TEST_F(BasicVec2Test, BooleanOps) {
  EXPECT_EQ(a == b, false);
  EXPECT_EQ(a != a, false);
  EXPECT_EQ(a < b, true);
  EXPECT_EQ(a > b, false);
  EXPECT_EQ(a <= b, true);
  EXPECT_EQ(a >= b, false);
}

TEST_F(BasicVec2Test, VectorArithmetic) {
  EXPECT_EQ(a + b, Vec2f(4, 6));
  EXPECT_EQ(a - b, Vec2f(-2, -2));
  EXPECT_EQ(a * b, Vec2f(3, 8));
  EXPECT_EQ(b / a, Vec2f(3, 2));
}

TEST_F(BasicVec2Test, ScalarArithmetic) {
  EXPECT_EQ(a + 2.0f, Vec2f(3, 4));
  EXPECT_EQ(a - 3.0f, Vec2f(-2, -1));
  EXPECT_EQ(a * 2.0f, Vec2f(2, 4));
  EXPECT_EQ(b / 2.0f, Vec2f(1.5, 2));
}

TEST_F(BasicVec2Test, Functions) {
  EXPECT_EQ(Cross(a), Vec2f(2, -1));
  EXPECT_EQ(Dot(a, b), 11.0f);
  EXPECT_FLOAT_EQ(Normalize(a).x, 1.0f / sqrt(5.0f));
  EXPECT_FLOAT_EQ(Normalize(a).y, 2.0f / sqrt(5.0f));
  EXPECT_FLOAT_EQ(Length(a), sqrt(5.0f));
  EXPECT_EQ(Sum(a), 3.0f);
  EXPECT_EQ(Pow(a, 2.0), Vec2f(1, 4));
}

class BasicVec3Test : public testing::Test {
 protected:
  virtual void SetUp() {
    a = {1, 2, 3};
    b = {4, 5, 6};
  }
  virtual void TearDown() {}
  Vec3f a, b;
};

TEST_F(BasicVec3Test, ElementAccess) {
  EXPECT_EQ(a.x, 1);
  EXPECT_EQ(a[1], 2);
}

TEST_F(BasicVec3Test, Stream) {
  std::stringstream ss;
  ss << a;
  EXPECT_EQ(ss.str(), "<1,2,3>");
}

TEST_F(BasicVec3Test, BooleanOps) {
  EXPECT_EQ(a == b, false);
  EXPECT_EQ(a != a, false);
  EXPECT_EQ(a < b, true);
  EXPECT_EQ(a > b, false);
  EXPECT_EQ(a <= b, true);
  EXPECT_EQ(a >= b, false);
}

TEST_F(BasicVec3Test, VectorArithmetic) {
  EXPECT_EQ(a + b, Vec3f(5, 7, 9));
  EXPECT_EQ(a - b, Vec3f(-3, -3, -3));
  EXPECT_EQ(a * b, Vec3f(4, 10, 18));
  EXPECT_EQ(b / a, Vec3f(4, 2.5, 2));
}

TEST_F(BasicVec3Test, ScalarArithmetic) {
  EXPECT_EQ(a + 2.0f, Vec3f(3, 4, 5));
  EXPECT_EQ(a - 3.0f, Vec3f(-2, -1, 0));
  EXPECT_EQ(a * 2.0f, Vec3f(2, 4, 6));
  EXPECT_EQ(b / 2.0f, Vec3f(2, 2.5, 3));
}

TEST_F(BasicVec3Test, Functions) {
  EXPECT_EQ(Cross(a, b), Vec3f(-3, 6, -3));
  EXPECT_EQ(Dot(a, b), 32.0f);
  EXPECT_FLOAT_EQ(Normalize(a).x, 1.0f / sqrt(14.0f));
  EXPECT_FLOAT_EQ(Normalize(a).y, 2.0f / sqrt(14.0f));
  EXPECT_FLOAT_EQ(Normalize(a).z, 3.0f / sqrt(14.0f));
  EXPECT_FLOAT_EQ(Length(a), sqrt(14.0f));
  EXPECT_EQ(Sum(a), 6.0f);
  EXPECT_EQ(Pow(a, 2.0), Vec3f(1, 4, 9));
}

class BasicVec4Test : public testing::Test {
 protected:
  virtual void SetUp() {
    a = {1, 2, 3, 4};
    b = {5, 6, 7, 8};
  }
  virtual void TearDown() {}
  Vec4f a, b;
};

TEST_F(BasicVec4Test, ElementAccess) {
  EXPECT_EQ(a.x, 1);
  EXPECT_EQ(a[1], 2);
}

TEST_F(BasicVec4Test, Stream) {
  std::stringstream ss;
  ss << a;
  EXPECT_EQ(ss.str(), "<1,2,3,4>");
}

TEST_F(BasicVec4Test, BooleanOps) {
  EXPECT_EQ(a == b, false);
  EXPECT_EQ(a != a, false);
  EXPECT_EQ(a < b, true);
  EXPECT_EQ(a > b, false);
  EXPECT_EQ(a <= b, true);
  EXPECT_EQ(a >= b, false);
}

TEST_F(BasicVec4Test, VectorArithmetic) {
  EXPECT_EQ(a + b, Vec4f(6, 8, 10, 12));
  EXPECT_EQ(a - b, Vec4f(-4, -4, -4, -4));
  EXPECT_EQ(a * b, Vec4f(5, 12, 21, 32));
  EXPECT_EQ(b / a, Vec4f(5, 3, 7.0f/3.0f, 2));
}

TEST_F(BasicVec4Test, ScalarArithmetic) {
  EXPECT_EQ(a + 2.0f, Vec4f(3, 4, 5, 6));
  EXPECT_EQ(a - 3.0f, Vec4f(-2, -1, 0, 1));
  EXPECT_EQ(a * 2.0f, Vec4f(2, 4, 6, 8));
  EXPECT_EQ(b / 2.0f, Vec4f(2.5, 3, 3.5, 4));
}

TEST_F(BasicVec4Test, Functions) {
  EXPECT_EQ(Cross(Vec4f(1, 0, 0, 0), Vec4f(0, 1, 0, 0), Vec4f(0, 0, 1, 0)), Vec4f(0, 0, 0, 1));
  EXPECT_EQ(Dot(a, b), 70.0f);
  EXPECT_FLOAT_EQ(Normalize(a).x, 1.0f / sqrt(30.0f));
  EXPECT_FLOAT_EQ(Normalize(a).y, 2.0f / sqrt(30.0f));
  EXPECT_FLOAT_EQ(Normalize(a).z, 3.0f / sqrt(30.0f));
  EXPECT_FLOAT_EQ(Normalize(a).w, 4.0f / sqrt(30.0f));
  EXPECT_FLOAT_EQ(Length(a), sqrt(30.0f));
  EXPECT_EQ(Sum(a), 10.0f);
  EXPECT_EQ(Pow(a, 2.0), Vec4f(1, 4, 9, 16));
}
