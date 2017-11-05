// Copyright 2017 Arden Rasmussen

#include "gtest/gtest.h"
#include "matrix.hpp"

class MatrixTest : public testing::Test {
 protected:
  virtual void SetUp() { b = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0}; }
  virtual void TearDown() {}
  estl::matrix<double, 3, 3> a, b, c;
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
  std::cout << b << "\n";
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
}
