#ifndef ESTL_BASIC_VECTOR_HPP_
#define ESTL_BASIC_VECTOR_HPP_

#include <array>
#include <cmath>
#include <iostream>

namespace estl {
namespace base {

  template <typename T>
  class Vec2 {
   public:
    Vec2() : x(T()), y(T()) {}
    Vec2(const T& a) : x(a), y(a) {}
    Vec2(const T& a, const T& b, const T& c) : x(a), y(b) {}
    explicit Vec2(const std::array<T, 2>& vec) : x(vec[0]), y(vec[1]) {}
    explicit Vec2(const Vec2<T>& vec) : x(vec.x), y(vec.y) {}
    ~Vec2() {}

    inline Vec2<T>& operator=(const Vec2<T>& vec) {
      x = vec.x;
      y = vec.y;
      return *this;
    }
    inline Vec2<T>& operator=(const T& val) {
      x = val;
      y = val;
      return *this;
    }

    inline T operator[](unsigned val) {
      if (val == 0) {
        return x;
      } else if (val == 1) {
        return y;
      } else {
        throw std::out_of_range("subscript (which is " + std::to_string(val) +
                                ") is >= 2");
      }
    }

    template <typename U>
    inline Vec2<T>& operator+=(const U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename U>
    inline Vec2<T>& operator-=(const U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename U>
    inline Vec2<T>& operator*=(const U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename U>
    inline Vec2<T>& operator/=(const U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    T x, y;
  };
  template <typename T>
  class Vec3 {
   public:
    Vec3() : x(T()), y(T()), z(T()) {}
    Vec3(const T& a) : x(a), y(a), z(a) {}
    Vec3(const T& a, const T& b, const T& c) : x(a), y(b), z(c) {}
    Vec3(const std::array<T, 3>& vec) : x(vec[0]), y(vec[1]), z(vec[2]) {}
    Vec3(const Vec3<T>& vec) : x(vec.x), y(vec.y), z(vec.z) {}
    ~Vec3() {}

    inline Vec3<T>& operator=(const Vec3<T>& vec) {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      return *this;
    }
    inline Vec3<T>& operator=(const T& val) {
      x = val;
      y = val;
      z = val;
      return *this;
    }
    inline T operator[](unsigned val) {
      if (val == 0) {
        return x;
      } else if (val == 1) {
        return y;
      } else if (val == 2) {
        return z;
      } else {
        throw std::out_of_range("subscript (which is " + std::to_string(val) +
                                ") is >= 3");
      }
    }

    template <typename U>
    inline Vec3<T>& operator+=(const U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename U>
    inline Vec3<T>& operator-=(const U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename U>
    inline Vec3<T>& operator*=(const U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename U>
    inline Vec3<T>& operator/=(const U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    T x, y, z;
  };
  template <typename T>
  class Vec4 {
   public:
    Vec4() : x(T()), y(T()), z(T()), w(T()) {}
    Vec4(const T& a) : x(a), y(a), z(a), w(a) {}
    Vec4(const T& a, const T& b, const T& c, const T& d)
        : x(a), y(b), z(c), w(d) {}
    Vec4(const std::array<T, 4>& vec)
        : x(vec[0]), y(vec[1]), z(vec[2]), w(vec[3]) {}
    Vec4(const Vec4<T>& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
    ~Vec4() {}

    inline Vec4<T>& operator=(const Vec4<T>& vec) {
      x = vec.x;
      y = vec.y;
      z = vec.z;
      w = vec.w;
      return *this;
    }
    inline Vec4<T>& operator=(const T& val) {
      x = val;
      y = val;
      z = val;
      w = val;
      return *this;
    }

    inline T operator[](unsigned val) {
      if (val == 0) {
        return x;
      } else if (val == 1) {
        return y;
      } else if (val == 2) {
        return z;
      } else if (val == 3) {
        return w;
      } else {
        throw std::out_of_range("subscript (which is " + std::to_string(val) +
                                ") is >= 4");
      }
    }

    template <typename U>
    inline Vec4<T>& operator+=(const U& rhs) {
      *this = *this + rhs;
      return *this;
    }
    template <typename U>
    inline Vec4<T>& operator-=(const U& rhs) {
      *this = *this - rhs;
      return *this;
    }
    template <typename U>
    inline Vec4<T>& operator*=(const U& rhs) {
      *this = *this * rhs;
      return *this;
    }
    template <typename U>
    inline Vec4<T>& operator/=(const U& rhs) {
      *this = *this / rhs;
      return *this;
    }

    T x, y, z, w;
  };

  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Vec2<T>& vec) {
    out << '<' << vec.x << ',' << vec.y << '>';
    return out;
  }
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Vec3<T>& vec) {
    out << '<' << vec.x << ',' << vec.y << ',' << vec.z << '>';
    return out;
  }
  template <typename T>
  inline std::ostream& operator<<(std::ostream& out, const Vec4<T>& vec) {
    out << '<' << vec.x << ',' << vec.y << ',' << vec.z << ',' << vec.w << '>';
    return out;
  }

  template <typename T>
  inline bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y));
  }
  template <typename T>
  inline bool operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T>
  inline bool operator<(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    if (lhs.x < rhs.x) {
      return true;
    } else if (rhs.x < lhs.x) {
      return false;
    } else if (lhs.y < rhs.y) {
      return true;
    } else if (rhs.y < lhs.y) {
      return false;
    } else {
      return false;
    }
  }
  template <typename T>
  inline bool operator>(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return rhs < lhs;
  }
  template <typename T>
  inline bool operator<=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(rhs > lhs);
  }
  template <typename T>
  inline bool operator>=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(rhs < lhs);
  }
  template <typename T>
  inline bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
  }
  template <typename T>
  inline bool operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T>
  inline bool operator<(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    if (lhs.x < rhs.x) {
      return true;
    } else if (rhs.x < lhs.x) {
      return false;
    } else if (lhs.y < rhs.y) {
      return true;
    } else if (rhs.y < lhs.y) {
      return false;
    } else if (lhs.z < rhs.z) {
      return true;
    } else if (rhs.z < lhs.z) {
      return false;
    } else {
      return false;
    }
  }
  template <typename T>
  inline bool operator>(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return rhs < lhs;
  }
  template <typename T>
  inline bool operator<=(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return !(rhs > lhs);
  }
  template <typename T>
  inline bool operator>=(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return !(rhs < lhs);
  }
  template <typename T>
  inline bool operator==(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) &&
            (lhs.w == rhs.w));
  }
  template <typename T>
  inline bool operator!=(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return !(lhs == rhs);
  }
  template <typename T>
  inline bool operator<(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    if (lhs.x < rhs.x) {
      return true;
    } else if (rhs.x < lhs.x) {
      return false;
    } else if (lhs.y < rhs.y) {
      return true;
    } else if (rhs.y < lhs.y) {
      return false;
    } else if (lhs.z < rhs.z) {
      return true;
    } else if (rhs.z < lhs.z) {
      return false;
    } else if (lhs.w < rhs.w) {
      return true;
    } else if (rhs.w < lhs.w) {
      return false;
    } else {
      return false;
    }
  }
  template <typename T>
  inline bool operator>(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return rhs < lhs;
  }
  template <typename T>
  inline bool operator<=(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return !(rhs > lhs);
  }
  template <typename T>
  inline bool operator>=(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return !(rhs < lhs);
  }

  template <typename T>
  inline Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
  }
  template <typename T>
  inline Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
  }
  template <typename T>
  inline Vec2<T> operator*(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
  }
  template <typename T>
  inline Vec2<T> operator/(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
  }
  template <typename T>
  inline Vec2<T> operator+(const Vec2<T>& lhs, const T& rhs) {
    return Vec2<T>(lhs.x + rhs, lhs.y + rhs);
  }
  template <typename T>
  inline Vec2<T> operator-(const Vec2<T>& lhs, const T& rhs) {
    return Vec2<T>(lhs.x - rhs, lhs.y - rhs);
  }
  template <typename T>
  inline Vec2<T> operator*(const Vec2<T>& lhs, const T& rhs) {
    return Vec2<T>(lhs.x * rhs, lhs.y * rhs);
  }
  template <typename T>
  inline Vec2<T> operator/(const Vec2<T>& lhs, const T& rhs) {
    return Vec2<T>(lhs.x / rhs, lhs.y / rhs);
  }
  template <typename T>
  inline Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  }
  template <typename T>
  inline Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }
  template <typename T>
  inline Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
  }
  template <typename T>
  inline Vec3<T> operator/(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
  }
  template <typename T>
  inline Vec3<T> operator+(const Vec3<T>& lhs, const T& rhs) {
    return Vec3<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
  }
  template <typename T>
  inline Vec3<T> operator-(const Vec3<T>& lhs, const T& rhs) {
    return Vec3<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
  }
  template <typename T>
  inline Vec3<T> operator*(const Vec3<T>& lhs, const T& rhs) {
    return Vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
  }
  template <typename T>
  inline Vec3<T> operator/(const Vec3<T>& lhs, const T& rhs) {
    return Vec3<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
  }
  template <typename T>
  inline Vec4<T> operator+(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
  }
  template <typename T>
  inline Vec4<T> operator-(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
  }
  template <typename T>
  inline Vec4<T> operator*(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
  }
  template <typename T>
  inline Vec4<T> operator/(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return Vec4<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
  }
  template <typename T>
  inline Vec4<T> operator+(const Vec4<T>& lhs, const T& rhs) {
    return Vec4<T>(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
  }
  template <typename T>
  inline Vec4<T> operator-(const Vec4<T>& lhs, const T& rhs) {
    return Vec4<T>(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs, lhs.w - rhs);
  }
  template <typename T>
  inline Vec4<T> operator*(const Vec4<T>& lhs, const T& rhs) {
    return Vec4<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
  }
  template <typename T>
  inline Vec4<T> operator/(const Vec4<T>& lhs, const T& rhs) {
    return Vec4<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
  }

  template <typename T>
  inline Vec2<T> Cross(const Vec2<T>& lhs) {
    return Vec2<T>(lhs.y, -lhs.x);
  }
  template <typename T>
  inline T Dot(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  template <typename T>
  inline Vec2<T> Normalize(const Vec2<T>& lhs) {
    return lhs / Length(lhs);
  }
  template <typename T>
  inline T Length(const Vec2<T>& lhs) {
    return sqrt(Dot(lhs, lhs));
  }
  template <typename T>
  inline T Sum(const Vec2<T>& lhs) {
    return lhs.x + lhs.y;
  }
  template <typename T>
  inline Vec3<T> Cross(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return Vec3<T>(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                   lhs.x * rhs.y - lhs.y * rhs.x);
  }
  template <typename T>
  inline T Dot(const Vec3<T>& lhs, const Vec3<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
  }
  template <typename T>
  inline Vec3<T> Normalize(const Vec3<T>& lhs) {
    return lhs / Length(lhs);
  }
  template <typename T>
  inline T Length(const Vec3<T>& lhs) {
    return sqrt(Dot(lhs, lhs));
  }
  template <typename T>
  inline T Sum(const Vec3<T>& lhs) {
    return lhs.x + lhs.y + lhs.z;
  }
  template <typename T>
  inline Vec4<T> Cross(const Vec4<T>& v0, const Vec4<T>& v1,
                       const Vec4<T>& v2) {
    T a = v1.z * v2.w - v1.w * v2.z;
    T b = v1.y * v2.w - v1.w * v2.y;
    T c = v1.y * v2.z - v1.z * v2.y;
    T d = v1.x * v2.w - v1.w * v2.x;
    T e = v1.x * v2.z - v1.z * v2.x;
    T f = v1.x * v2.y - v1.y * v2.x;
    return Vec4<T>(
        v0.y * a - v0.z * b + v0.w * c, v0.x * a - v0.z * d + v0.w * e,
        v0.x * b - v0.y * d + v0.w * f, v0.x * c - v0.y * e + v0.z * f);
  }
  template <typename T>
  inline T Dot(const Vec4<T>& lhs, const Vec4<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
  }
  template <typename T>
  inline Vec4<T> Normalize(const Vec4<T>& lhs) {
    return lhs / Length(lhs);
  }
  template <typename T>
  inline T Length(const Vec4<T>& lhs) {
    return std::sqrt(Dot(lhs, lhs));
  }
  template <typename T>
  inline T Sum(const Vec4<T>& lhs) {
    return lhs.x + lhs.y + lhs.z + lhs.w;
  }

  typedef Vec2<bool> Vec2b;
  typedef Vec2<int> Vec2i;
  typedef Vec2<float> Vec2f;
  typedef Vec2<double> Vec2d;
  typedef Vec3<bool> Vec3b;
  typedef Vec3<int> Vec3i;
  typedef Vec3<float> Vec3f;
  typedef Vec3<double> Vec3d;
  typedef Vec4<bool> Vec4b;
  typedef Vec4<int> Vec4i;
  typedef Vec4<float> Vec4f;
  typedef Vec4<double> Vec4d;

}  // namespace base
}  // namespace estl

#endif  // ESTL_BASIC_VECTOR_HPP_
