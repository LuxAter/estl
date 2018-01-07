/* Copyright (C)
 * 2018 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

/**
 * @file vector.hpp
 * @brief Mathematical vector template class.
 * @author Arden Rasmussen
 * @version 0.0
 * @date 2018-01-05
 * @copyright GNU General Public License
 *
 * This provides a vector class that is a vector in the mathematical sense,
 * along with some vector operations.
 */

#ifndef ESTL_VECTOR_HPP_
#define ESTL_VECTOR_HPP_

#include <initializer_list>
#include <iostream>

#include "matrix.hpp"
#include "variadic.hpp"

namespace estl {
template <typename _Tp, std::size_t _N, typename _Al = std::allocator<_Tp>>
class vector {
 public:
  typedef _Al allocator_type;
  typedef typename _Al::value_type value_type;
  typedef typename _Al::reference reference;
  typedef typename _Al::const_reference const_reference;
  typedef typename _Al::difference_type difference_type;
  typedef typename _Al::size_type size_type;
  typedef typename _Al::pointer pointer;
  typedef typename _Al::const_pointer const_pointer;
  typedef typename _Al::pointer iterator;
  typedef typename _Al::const_pointer const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  vector() {
    _Al al;
    data_ = al.allocate(size());
    fill(_Tp());
  }
  vector(_Tp val) {
    _Al al;
    data_ = al.allocate(size());
    fill(val);
  }
  vector(const std::initializer_list<_Tp>& vec) {
    _Al al;
    data_ = al.allocate(size());
    if (vec.size() > size()) {
      std::__throw_out_of_range_fmt(
          __N("initializer_list.size() (which is %zu) > _N (which is %zu)"),
          vec.size(), size());
    }
    std::copy(vec.begin(), vec.end(), data_);
  }
  template <class _InputIt>
  vector(_InputIt first, _InputIt last) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(first, last, data_);
  }
  vector(const vector& vec) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(vec.begin(), vec.end(), data_);
  }

  ~vector() {
    _Al al;
    al.deallocate(data_, size());
  }

  vector& operator=(const vector& vec) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(vec.begin(), vec.end(), data_);
  }
  vector& operator=(const std::initializer_list<_Tp>& vec) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(vec.begin(), vec.end(), data_);
  }

  reference at(size_type i) {
    if (i >= size()) {
      std::__throw_out_of_range_fmt(
          __N("vector::at:i (which is %zu) >= _N (which is %zu)"), i, size());
    } else {
      return reference(data_[i]);
    }
  }

  constexpr const_reference at(size_type i) const {
    if (i >= size()) {
      std::__throw_out_of_range_fmt(
          __N("vector::at:i (which is %zu) >= _N (which is %zu)"), i, size());
    } else {
      return const_reference(data_[i]);
    }
  }
  reference operator[](size_type i) noexcept { return reference(data_[i]); }
  constexpr const_reference operator[](size_type i) const noexcept {
    return const_reference(data_[i]);
  }
  reference front() { return reference(data_[0]); }
  constexpr const_reference font() const { return const_reference(data_[0]); }
  reference back() { return reference(data_[size() - 1]); }
  constexpr const_reference back() const {
    return const_reference(data_[size() - 1]);
  }
  pointer data() { return data_; }
  const_pointer data() const { return data_; }

  iterator begin() { return iterator(data_); }
  const_iterator begin() const { return const_iterator(data_); }
  const_iterator cbegin() const { return const_iterator(data_); }
  iterator end() { return iterator(data_ + size()); }
  const_iterator end() const { return const_iterator(data_ + size()); }
  const_iterator cend() const { return const_iterator(data_ + size()); }
  reverse_iterator rbegin() { return reverse_iterator(data_); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(data_);
  }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(data_);
  }
  reverse_iterator rend() { return reverse_iterator(data_ + size()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(data_ + size());
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(data_ + size());
  }
  iterator element(size_type i) { return iterator(data_ + i); }
  const_iterator element(size_type i) const {
    return const_iterator(data_ + i);
  }
  const_iterator celement(size_type i) const {
    return const_iterator(data_ + i);
  }
  reverse_iterator relement(size_type i) { return reverse_iterator(data_ + i); }
  const_reverse_iterator relement(size_type i) const {
    return const_reverse_iterator(data_ + i);
  }
  const_reverse_iterator crelement(size_type i) const {
    return const_reverse_iterator(data_ + i);
  }

  bool empty() const noexcept { return size() == 0; }
  constexpr inline size_type size() const noexcept { return _N; }
  constexpr size_type max_size() const noexcept { return _N; }

  void fill(const value_type& val) { std::fill_n(begin(), size(), val); }
  void swap(vector& other) { std::swap_ranges(begin(), end(), other.begin()); }
  inline void operator()(_Tp (*func)(_Tp)) {
    for (iterator it = begin(); it != end(); ++it) {
      *it = func(*it);
    }
  }

  template <typename _T>
  inline estl::vector<_Tp, _N>& operator+=(const _T& rhs) {
    *this = *this + rhs;
    return *this;
  }
  template <typename _T>
  inline estl::vector<_Tp, _N>& operator-=(const _T& rhs) {
    *this = *this - rhs;
    return *this;
  }
  template <typename _T>
  inline estl::vector<_Tp, _N>& operator*=(const _T& rhs) {
    *this = *this * rhs;
    return *this;
  }
  template <typename _T>
  inline estl::vector<_Tp, _N>& operator/=(const _T& rhs) {
    *this = *this / rhs;
    return *this;
  }

 private:
  pointer data_ = nullptr;
};

template <typename _Tp, std::size_t _N>
std::ostream& operator<<(std::ostream& out, const estl::vector<_Tp, _N> vec) {
  out << '<';
  for (std::size_t i = 0; i < _N; i++) {
    out << vec[i];
    if (i != _N - 1) {
      out << ',';
    }
  }
  out << '>';
  return out;
}

template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline bool operator==(const estl::vector<_TpA, _NA>& lhs,
                       const estl::vector<_TpB, _NB>& rhs) {
  if (_NA != _NB) {
    return false;
  } else {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline bool operator!=(const estl::vector<_TpA, _NA>& lhs,
                       const estl::vector<_TpB, _NB>& rhs) {
  return !(lhs == rhs);
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline bool operator<(const estl::vector<_TpA, _NA>& lhs,
                      const estl::vector<_TpB, _NB>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline bool operator>(const estl::vector<_TpA, _NA>& lhs,
                      const estl::vector<_TpB, _NB>& rhs) {
  return rhs < lhs;
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline bool operator<=(const estl::vector<_TpA, _NA>& lhs,
                       const estl::vector<_TpB, _NB>& rhs) {
  return !(rhs > lhs);
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline bool operator>=(const estl::vector<_TpA, _NA>& lhs,
                       const estl::vector<_TpB, _NB>& rhs) {
  return !(rhs < lhs);
}

template <typename _Tp, std::size_t _N, typename _T>
inline estl::vector<_Tp, _N> operator+(const estl::vector<_Tp, _N>& lhs,
                                       const _T& rhs) {
  estl::vector<_Tp, _N> vec(lhs);
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin();
       it != vec.end(); ++it) {
    *it = *it + rhs;
  }
  return vec;
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline estl::vector<_TpA, _NA> operator+(const estl::vector<_TpA, _NA>& lhs,
                                         const estl::vector<_TpB, _NB>& rhs) {
  estl::vector<_TpA, _NA> vec(lhs);
  typename estl::vector<_TpA, _NA>::iterator it;
  typename estl::vector<_TpB, _NB>::const_iterator rhs_it;
  for (it = vec.begin(), rhs_it = rhs.begin();
       it != vec.end() && rhs_it != rhs.end(); ++it, ++rhs_it) {
    *it = *it + *rhs_it;
  }
  return vec;
}
template <typename _Tp, std::size_t _N, typename _T>
inline estl::vector<_Tp, _N> operator-(const estl::vector<_Tp, _N>& lhs,
                                       const _T& rhs) {
  estl::vector<_Tp, _N> vec(lhs);
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin();
       it != vec.end(); ++it) {
    *it = *it - rhs;
  }
  return vec;
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline estl::vector<_TpA, _NA> operator-(const estl::vector<_TpA, _NA>& lhs,
                                         const estl::vector<_TpB, _NB>& rhs) {
  estl::vector<_TpA, _NA> vec(lhs);
  typename estl::vector<_TpA, _NA>::iterator it;
  typename estl::vector<_TpB, _NB>::const_iterator rhs_it;
  for (it = vec.begin(), rhs_it = rhs.begin();
       it != vec.end() && rhs_it != rhs.end(); ++it, ++rhs_it) {
    *it = *it - *rhs_it;
  }
  return vec;
}
template <typename _Tp, std::size_t _N, typename _T>
inline estl::vector<_Tp, _N> operator*(const estl::vector<_Tp, _N>& lhs,
                                       const _T& rhs) {
  estl::vector<_Tp, _N> vec(lhs);
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin();
       it != vec.end(); ++it) {
    *it = *it * rhs;
  }
  return vec;
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline estl::vector<_TpA, _NA> operator*(const estl::vector<_TpA, _NA>& lhs,
                                         const estl::vector<_TpB, _NB>& rhs) {
  estl::vector<_TpA, _NA> vec(lhs);
  typename estl::vector<_TpA, _NA>::iterator it;
  typename estl::vector<_TpB, _NB>::const_iterator rhs_it;
  for (it = vec.begin(), rhs_it = rhs.begin();
       it != vec.end() && rhs_it != rhs.end(); ++it, ++rhs_it) {
    *it = *it * *rhs_it;
  }
  return vec;
}
template <typename _Tp, std::size_t _N, typename _T>
inline estl::vector<_Tp, _N> operator/(const estl::vector<_Tp, _N>& lhs,
                                       const _T& rhs) {
  estl::vector<_Tp, _N> vec(lhs);
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin();
       it != vec.end(); ++it) {
    *it = *it / rhs;
  }
  return vec;
}
template <typename _TpA, typename _TpB, std::size_t _NA, std::size_t _NB>
inline estl::vector<_TpA, _NA> operator/(const estl::vector<_TpA, _NA>& lhs,
                                         const estl::vector<_TpB, _NB>& rhs) {
  estl::vector<_TpA, _NA> vec(lhs);
  typename estl::vector<_TpA, _NA>::iterator it;
  typename estl::vector<_TpB, _NB>::const_iterator rhs_it;
  for (it = vec.begin(), rhs_it = rhs.begin();
       it != vec.end() && rhs_it != rhs.end(); ++it, ++rhs_it) {
    *it = *it / *rhs_it;
  }
  return vec;
}

template <typename _Tp, std::size_t _N>
_Tp sum(const estl::vector<_Tp, _N>& lhs) {
  _Tp total = _Tp();
  for (typename estl::vector<_Tp, _N>::const_iterator it = lhs.begin();
       it != lhs.end(); ++it) {
    total += *it;
  }
  return total;
}

template <typename _TpA, typename _TpB, std::size_t _N>
_TpA dot(const estl::vector<_TpA, _N>& lhs, const estl::vector<_TpB, _N>& rhs) {
  estl::vector<_TpA, _N> vec = lhs * rhs;
  return sum(vec);
}

template <typename _Tp, std::size_t _N>
estl::vector<_Tp, _N> cross(const estl::vector<_Tp, _N>& lhs,
                            const estl::vector<_Tp, _N>& rhs) {
  return {lhs[1] * rhs[2] - lhs[2] * rhs[1], lhs[2] * rhs[0] - lhs[0] * rhs[2],
          lhs[0] * rhs[1] - lhs[1] * rhs[0]};
}

template <typename _Tp, std::size_t _N, typename... _Vecs>
estl::vector<_Tp, _N> cross(estl::vector<_Tp, _N> vec, _Vecs... args) {
  std::vector<estl::vector<_Tp, _N>> vecs = estl::unpack_vector(args...);
  vecs.insert(vecs.begin(), vec);
  estl::vector<_Tp, _N> res;
  for (std::size_t i = 0; i < res.size(); i++) {
    estl::matrix<_Tp, _N - 1, _N - 1> mat;
    for (std::size_t row = 0; row < _N - 1; row++) {
      std::size_t col_index = 0;
      for (std::size_t col = 0; col < _N; col++) {
        if (col != i) {
          mat(row, col_index) = vecs[row][col];
          col_index++;
        }
      }
    }
    std::cout << mat << "<<\n";
    res[i] = estl::determinant(mat);
    std::cout << res[i] << "<<\n";
  }
  return res;
}

}  // namespace estl

#endif  // ESTL_VECTOR_HPP_
