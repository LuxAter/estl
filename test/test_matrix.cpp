// Copyright 2017 Arden Rasmussen

#include "gtest/gtest.h"
#include "matrix.hpp"

#include <math.h>

class MatrixTest : public testing::Test {
 protected:
  virtual void SetUp() { b = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}; }
  virtual void TearDown() {}
  estl::matrix<double, 3, 3> a, b, c;
  estl::matrix<double, 0, 0> d;
};

template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
::testing::AssertionResult MatrixMatch(estl::matrix<_Tp, _Nr, _Nc> lhs,
                                       estl::matrix<_Tp, _Nr, _Nc> rhs) {
  for (size_t r = 0; r < _Nr; r++) {
    for (size_t c = 0; c < _Nc; c++) {
      EXPECT_FLOAT_EQ(lhs.at(r, c), rhs.at(r, c));
    }
  }
  return ::testing::AssertionSuccess();
}

TEST_F(MatrixTest, Constructor) {
  EXPECT_TRUE(MatrixMatch(a, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}));
  EXPECT_TRUE(MatrixMatch(b, {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}));
  estl::matrix<double, 3, 3> mat(b);
  EXPECT_TRUE(MatrixMatch(b, mat));
}

TEST_F(MatrixTest, ElementAccess) {
  EXPECT_FLOAT_EQ(b.at(5), 5.0);
  EXPECT_FLOAT_EQ(b.at(1, 2), 5.0);
  EXPECT_FLOAT_EQ(b[5], 5.0);
  EXPECT_FLOAT_EQ(b(1, 2), 5.0);
  EXPECT_FLOAT_EQ(b.front(), 0.0);
  EXPECT_FLOAT_EQ(b.back(), 8.0);
  EXPECT_FLOAT_EQ(*(b.data() + 1), 1.0);
  EXPECT_FLOAT_EQ(b.data_array()[4], 4.0);
  EXPECT_FLOAT_EQ(b.data_2darray()[1][1], 4.0);
  EXPECT_FLOAT_EQ(b.data_vector()[6], 6.0);
}

TEST_F(MatrixTest, Iterator) {
  EXPECT_FLOAT_EQ(*b.begin(), 0.0);
  EXPECT_FLOAT_EQ(*b.cbegin(), 0.0);
  EXPECT_FLOAT_EQ(*(b.end() - 1), 8.0);
  EXPECT_FLOAT_EQ(*(b.cend() - 1), 8.0);
  EXPECT_FLOAT_EQ(*(b.rbegin() - 2), 1.0);
  EXPECT_FLOAT_EQ(*(b.rend() + 2), 6.0);
  EXPECT_FLOAT_EQ(*(b.crbegin() - 2), 1.0);
  EXPECT_FLOAT_EQ(*(b.crend() + 2), 6.0);
  EXPECT_FLOAT_EQ(*b.element(2, 2), 8.0);
  EXPECT_FLOAT_EQ(*b.celement(1, 2), 5.0);
}

TEST_F(MatrixTest, Capacity) {
  EXPECT_EQ(a.empty(), false);
  EXPECT_EQ(d.empty(), true);
  EXPECT_EQ(b.size(), 9);
  EXPECT_EQ(b.rows(), 3);
  EXPECT_EQ(b.columns(), 3);
  EXPECT_EQ(b.max_size(), 9);
}

TEST_F(MatrixTest, Operations) {
  estl::matrix<double, 3, 3> mat;
  a.fill(3.14);
  mat = {3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14, 3.14};
  EXPECT_EQ(a, mat);
  a.fill(0);
  a.fill_diagonal(-5.0);
  mat = {-5.0, 0, 0, 0, -5.0, 0, 0, 0, -5.0};
  EXPECT_EQ(a, mat);
  a(fabs);
  mat = {5.0, 0, 0, 0, 5.0, 0, 0, 0, 5.0};
  EXPECT_EQ(a, mat);
  a.swap_row(0, 2);
  mat = {0, 0, 5.0, 0, 5, 0, 5, 0, 0};
  EXPECT_EQ(a, mat);
  a.swap_column(0, 2);
  mat = {5.0, 0, 0, 0, 5, 0, 0, 0, 5.0};
  EXPECT_EQ(a, mat);
}
