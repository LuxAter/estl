#ifndef ESTL_BASIC_MATRIX_HPP_
#define ESTL_BASIC_MATRIX_HPP_

#include <array>
#include <iostream>

#include "vector.hpp"

namespace estl {
namespace base {
  template <typename T, std::size_t N>
  class Mat {
   public:
    Mat() { data_.fill(T()); }
    Mat(const T& val) { data_.fill(val); }
    Mat(std::initializer_list<T> vals) {
      std::copy(vals.begin(), vals.end(), data_.data());
    }
    Mat(const Mat<T, N>& mat) {
      std::copy(mat.data_.begin(), mat.data_.end(), data_.data());
    }
    ~Mat() {}

    inline void Fill(const T& val) { data_.fill(val); }
    inline void Diagonal(const T& val) {
      for (std::size_t i = 0; i < N * N; i += N + 1) {
        data_[i] = val;
      }
    }

    inline Mat<T, N> operator=(const Mat<T, N>& mat) {
      std::copy(mat.data_.begin(), mat.data_.end(), data_.data());
      return *this;
    }
    inline Mat<T, N> operator=(const T& val) {
      data_.fill(val);
      return *this;
    }

    inline std::array<T, N>& operator[](unsigned val) {
      std::array<T, N> arr;
      for (std::size_t i = val; i < N; ++i) {
        arr[i] = data_[i];
      }
      return arr;
    }
    inline T& operator()(unsigned row, unsigned col) {
      return data_[col + (row * N)];
    }

    template <typename U>
    inline Mat<T, N> operator+=(const U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename U>
    inline Mat<T, N> operator-=(const U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename U>
    inline Mat<T, N> operator*=(const U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename U>
    inline Mat<T, N> operator/=(const U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    std::array<T, N * N> data_;
  };
  template <typename T, std::size_t N>
  inline std::ostream& operator<<(std::ostream& out, const Mat<T, N>& mat) {
    out << '[';
    for (std::size_t row = 0; row < N; ++row) {
      out << '[';
      for (std::size_t col = 0; col < N; ++col) {
        out << mat.data_[col + (row * N)];
        if (col != N - 1) {
          out << ',';
        }
      }
      out << ']';
      if (row != N - 1) {
        out << ',';
      }
    }
    out << ']';
    return out;
  }
  template <typename T, std::size_t N>
  inline bool operator==(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    return lhs.data_ == rhs.data_;
  }
  template <typename T, std::size_t N>
  inline bool operator!=(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    return lhs.data_ != rhs.data_;
  }
  template <typename T, std::size_t N>
  inline bool operator<(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    return lhs.data_ < rhs.data_;
  }
  template <typename T, std::size_t N>
  inline bool operator>(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    return lhs.data_ > rhs.data_;
  }
  template <typename T, std::size_t N>
  inline bool operator<=(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    return lhs.data_ <= rhs.data_;
  }
  template <typename T, std::size_t N>
  inline bool operator>=(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    return lhs.data_ >= rhs.data_;
  }

  template <typename T, std::size_t N>
  inline Mat<T, N> operator+(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] + rhs.data_[i];
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator-(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] - rhs.data_[i];
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator*(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] * rhs.data_[i];
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator/(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] / rhs.data_[i];
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator+(const Mat<T, N>& lhs, const T& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] + rhs;
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator-(const Mat<T, N>& lhs, const T& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] - rhs;
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator*(const Mat<T, N>& lhs, const T& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] * rhs;
    }
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> operator/(const Mat<T, N>& lhs, const T& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N * N; ++i) {
      mat.data_[i] = lhs.data_[i] / rhs;
    }
  }

  template <typename T>
  inline Vec2<T> Dot(const Mat<T, 2>& mat, const Vec2<T>& vec) {
    return Vec2<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y,
                   mat.data_[3] * vec.x + mat.data_[4] * vec.y);
  }
  template <typename T>
  inline Vec3<T> Dot(const Mat<T, 2>& mat, const Vec3<T>& vec) {
    return Vec3<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y,
                   mat.data_[3] * vec.x + mat.data_[4] * vec.y, T());
  }
  template <typename T>
  inline Vec4<T> Dot(const Mat<T, 2>& mat, const Vec4<T>& vec) {
    return Vec4<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y,
                   mat.data_[3] * vec.x + mat.data_[4] * vec.y, T(), T());
  }
  template <typename T>
  inline Vec2<T> Dot(const Mat<T, 3>& mat, const Vec2<T>& vec) {
    return Vec2<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y + mat.data_[2],
                   mat.data_[3] * vec.x + mat.data_[4] * vec.y) +
           mat.data_[5];
  }
  template <typename T>
  inline Vec3<T> Dot(const Mat<T, 3>& mat, const Vec3<T>& vec) {
    return Vec3<T>(
        mat.data_[0] * vec.x + mat.data_[1] * vec.y + mat.data_[2] * vec.z,
        mat.data_[3] * vec.x + mat.data_[4] * vec.y + mat.data_[5] * vec.z,
        mat.data_[6] * vec.x + mat.data_[7] * vec.y + mat.data_[8] * vec.z);
  }
  template <typename T>
  inline Vec4<T> Dot(const Mat<T, 3>& mat, const Vec4<T>& vec) {
    return Vec4<T>(
        mat.data_[0] * vec.x + mat.data_[1] * vec.y + mat.data_[2] * vec.z,
        mat.data_[3] * vec.x + mat.data_[4] * vec.y + mat.data_[5] * vec.z,
        mat.data_[6] * vec.x + mat.data_[7] * vec.y + mat.data_[8] * vec.z,
        T());
  }
  template <typename T>
  inline Vec2<T> Dot(const Mat<T, 4>& mat, const Vec2<T>& vec) {
    return Vec2<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y + mat.data_[2] +
                       mat.data[3],
                   mat.data_[4] * vec.x + mat.data_[5] * vec.y + mat.data_[6] +
                       mat.data[7]);
  }
  template <typename T>
  inline Vec3<T> Dot(const Mat<T, 4>& mat, const Vec3<T>& vec) {
    return Vec3<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y +
                       mat.data_[2] * vec.z + mat.data_[3],
                   mat.data_[4] * vec.x + mat.data_[5] * vec.y +
                       mat.data_[6] * vec.z + mat.data_[7],
                   mat.data_[8] * vec.x + mat.data_[9] * vec.y +
                       mat.data_[10] * vec.z + mat.data_[11]);
  }
  template <typename T>
  inline Vec4<T> Dot(const Mat<T, 4>& mat, const Vec4<T>& vec) {
    return Vec4<T>(mat.data_[0] * vec.x + mat.data_[1] * vec.y +
                       mat.data_[2] * vec.z + mat.data_[3] * vec.w,
                   mat.data_[4] * vec.x + mat.data_[5] * vec.y +
                       mat.data_[6] * vec.z + mat.data_[7] * vec.w,
                   mat.data_[8] * vec.x + mat.data_[9] * vec.y +
                       mat.data_[10] * vec.z + mat.data_[11] * vec.w,
                   mat.data_[12] * vec.x + mat.data_[13] * vec.y +
                       mat.data[14] * vec.z + mat.data[15] * vec.w);
  }
  template <typename T, std::size_t N>
  inline Mat<T, N> Dot(const Mat<T, N>& lhs, const Mat<T, N>& rhs) {
    Mat<T, N> mat;
    for (std::size_t i = 0; i < N; ++i) {
      for (std::size_t j = 0; j < N; ++j) {
        T sum = T();
        for (std::size_t k = 0; k < N; ++k) {
          sum += lhs.data_[(i * N) + k] * rhs.data_[(k * N) + j];
        }
        mat.data_[(i * N) + j] = sum;
      }
    }
    return mat;
  }

  typedef Mat<bool, 2> Mat2b;
  typedef Mat<int, 2> Mat2i;
  typedef Mat<float, 2> Mat2f;
  typedef Mat<double, 2> Mat2d;
  typedef Mat<bool, 3> Mat3b;
  typedef Mat<int, 3> Mat3i;
  typedef Mat<float, 3> Mat3f;
  typedef Mat<double, 3> Mat3d;
  typedef Mat<bool, 4> Mat4b;
  typedef Mat<int, 4> Mat4i;
  typedef Mat<float, 4> Mat4f;
  typedef Mat<double, 4> Mat4d;

}  // namespace base
}  // namespace estl

#endif  // ESTL_BASIC_MATRIX_HPP_
