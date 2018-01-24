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

#include <cmath>
#include <initializer_list>
#include <iostream>

#include "matrix.hpp"
#include "variadic.hpp"

namespace estl {

/**
 * @brief A standard container representing a mathmatical vector.
 *
 * `estl::matrix` is a container that encapsulates fixed size mathmatical
 * vectors.
 *
 * This container is an aggregate type with the same sematics as a struct
 * holding a C-stype array `T[N]` as its only non-static data member. Elements
 * of this container can be referenced witha  single index.
 *
 * @tparam _Tp Type of element. Required to be a complete type.
 * @tparam _N Number of elements in the container.
 * @tparam _Al Allocator type, Not necessary in most situations.
 */
template <typename _Tp, std::size_t _N, typename _Al = std::allocator<_Tp>>
class vector {
 public:
  /**
   * @brief _Al
   */
  typedef _Al allocator_type;
  /**
   * @brief _Tp
   */
  typedef typename _Al::value_type value_type;
  /**
   * @brief value_type&
   */
  typedef typename _Al::reference reference;
  /**
   * @brief const value_type&
   */
  typedef typename _Al::const_reference const_reference;
  /**
   * @brief std::ptrdiff_t
   */
  typedef typename _Al::difference_type difference_type;
  /**
   * @brief std::size_t
   */
  typedef typename _Al::size_type size_type;
  /**
   * @brief value_type*
   */
  typedef typename _Al::pointer pointer;
  /**
   * @brief const value_type*
   */
  typedef typename _Al::const_pointer const_pointer;
  /**
   * @brief Random access iterator
   */
  typedef typename _Al::pointer iterator;
  /**
   * @brief Constant random access iterator
   */
  typedef typename _Al::const_pointer const_iterator;
  /**
   * @brief std::reverse_iterator<iterator>
   */
  typedef std::reverse_iterator<iterator> reverse_iterator;
  /**
   * @brief std::reverse_iterator<const_iterator>
   */
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  /**
   * @name Constructor
   * @{ */

  /**
   * @brief Default vector constructor
   *
   * THis allocates the memory required for the desired vector.
   */
  vector() {
    _Al al;
    data_ = al.allocate(size());
    fill(_Tp());
  }
  /**
   * @brief Vector constructor
   *
   * Allocates the memory required for the vector and fills every element with
   * the supplied value.
   *
   * @param val
   */
  vector(_Tp val) {
    _Al al;
    data_ = al.allocate(size());
    fill(val);
  }
  /**
   * @brief Vector constructor
   *
   * Allocates the memory required for the vector, and copies the elements fo
   * the initializer list to the elements of the vector.
   *
   * @throw out_of_range Thows out of range if initializer_list is greater than
   * the size of the matrix.
   *
   * @param vec initializer_list of elements to copy.
   */
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
  /**
   * @brief Vector constructor
   *
   * Allocates the memory required for the vector, and copies the contents of
   * the memory between `first` and `last` to the elements of the vector.
   *
   * @tparam _InputIt Type of iterator of source data.
   * @param first First location in memory of source data.
   * @param last Last location in memory of source data.
   */
  template <class _InputIt>
  vector(_InputIt first, _InputIt last) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(first, last, data_);
  }
  /**
   * @brief Copy constructor
   *
   * Allocates the memory required for the vector, and copies the elements of
   * `vec` to the elements of the vector.
   *
   * @param vec Vector to copy.
   */
  vector(const vector& vec) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(vec.begin(), vec.end(), data_);
  }

  /**  @} */

  /**
   * @name Destructor
   * @{ */

  /**
   * @brief Destructor
   *
   * Deallocates the memory for the vector.
   */
  ~vector() {
    _Al al;
    al.deallocate(data_, size());
  }

  /**  @} */

  /**
   * @name Operator=
   * @{ */

  vector& operator=(const vector& vec) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(vec.begin(), vec.end(), data_);
    return *this;
  }
  vector& operator=(const std::initializer_list<_Tp>& vec) {
    _Al al;
    data_ = al.allocate(size());
    std::copy(vec.begin(), vec.end(), data_);
    return *this;
  }

  /**  @} */

  /**
   * @name Element Access
   * @{ */

  /**
   * @brief Access specified element with bounds checking.
   *
   * Returns a reference to the element at specified location `i`, with bounds
   * checking. If `i` is not withing the range of the container, an exception of
   * type `std::out_of_range` is thrown.
   *
   * @throw out_of_range If `i` is outside of the range of the container.
   *
   * @param i Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  reference at(size_type i) {
    if (i >= size()) {
      std::__throw_out_of_range_fmt(
          __N("vector::at:i (which is %zu) >= _N (which is %zu)"), i, size());
    } else {
      return reference(data_[i]);
    }
  }
  /**
   * @brief Access specified element with bounds checking.
   *
   * Returns a reference to the element at specified location `i`, with bounds
   * checking. If `i` is not withing the range of the container, an exception of
   * type `std::out_of_range` is thrown.
   *
   * @throw out_of_range If `i` is outside of the range of the container.
   *
   * @param i Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  constexpr const_reference at(size_type i) const {
    if (i >= size()) {
      std::__throw_out_of_range_fmt(
          __N("vector::at:i (which is %zu) >= _N (which is %zu)"), i, size());
    } else {
      return const_reference(data_[i]);
    }
  }
  /**
   * @brief Access specified element.
   *
   * Returns a reference to the element at specified location `i`. No bounds
   * checking is preformed.
   *
   * @param i Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  reference operator[](size_type i) noexcept { return reference(data_[i]); }
  /**
   * @brief Access specified element.
   *
   * Returns a reference to the element at specified location `i`. No bounds
   * checking is preformed.
   *
   * @param i Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  constexpr const_reference operator[](size_type i) const noexcept {
    return const_reference(data_[i]);
  }
  /**
   * @brief Access the first element.
   *
   * Returns a reference to the first element in the container. Calling `front` on an empty container is undefined.
   *
   * @return Reference to the first element.
   */
  reference front() { return reference(data_[0]); }
  /**
   * @brief Access the first element.
   *
   * Returns a reference to the first element in the container. Calling `front` on an empty container is undefined.
   *
   * @return Reference to the first element.
   */
  constexpr const_reference font() const { return const_reference(data_[0]); }
  /**
   * @brief Access the last element.
   *
   * Returns reference to the last element in the container. Calling `back` on an empty container is undefined.
   *
   * @return Reference to the last element.
   */
  reference back() { return reference(data_[size() - 1]); }
  /**
   * @brief Access the last element.
   *
   * Returns reference to the last element in the container. Calling `back` on an empty container is undefined.
   *
   * @return Reference to the last element.
   */
  constexpr const_reference back() const {
    return const_reference(data_[size() - 1]);
  }
  /**
   * @brief Direct access to the underlying array.
   *
   * Returns pointer to the underlying array serving as element storage. The pointer is such that range `[data(); data() + size()]` is always a valid range, even if the container is empty.
   *
   * @return Pointer to the underlying element storage. For non-empty containers, the returned pointer compares equal to the address of the first element.
   */
  pointer data() { return data_; }
  /**
   * @brief Direct access to the underlying array.
   *
   * Returns pointer to the underlying array serving as element storage. The pointer is such that range `[data(); data() + size()]` is always a valid range, even if the container is empty.
   *
   * @return Pointer to the underlying element storage. For non-empty containers, the returned pointer compares equal to the address of the first element.
   */
  const_pointer data() const { return data_; }

  /**  @} */

  /**
   * @name Iterators
   * @{ */

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

  /**  @} */

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
    res[i] = estl::determinant(mat);
  }
  return res;
}

template <typename _Tp, std::size_t _N>
_Tp length(estl::vector<_Tp, _N> vec) {
  _Tp total;
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin();
       it != vec.end(); ++it) {
    total += pow(*it, 2.0);
  }
  return pow(total, 0.5);
}

template <typename _Tp, std::size_t _N>
estl::vector<_Tp, _N> normalize(estl::vector<_Tp, _N> vec) {
  estl::vector<_Tp, _N> new_vec(vec);
  _Tp len = length(vec);
  for (typename estl::vector<_Tp, _N>::iterator it = new_vec.begin();
       it != new_vec.end(); it++) {
    *it /= len;
  }
  return new_vec;
}

template <typename _Tp, std::size_t _N>
estl::vector<_Tp, _N> SphericalCoordinates(estl::vector<_Tp, _N> vec) {
  estl::vector<_Tp, _N> res;
  *res.begin() = estl::length(vec);
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin(),
                                                res_it = res.begin() + 1;
       it != vec.end() - 1 && res_it != res.end(); ++it, ++res_it) {
    _Tp len(0);
    for (typename estl::vector<_Tp, _N>::iterator sub = it; sub != vec.end();
         ++sub) {
      len += pow(*sub, 2.0);
    }
    len = pow(len, 0.5);
    if (it == vec.end() - 2 && vec.back() < 0) {
      *res_it = (2 * M_PI) - acos(*it / len);
    } else {
      *res_it = acos(*it / len);
    }
  }
  return res;
}

template <typename _Tp, std::size_t _N>
estl::vector<_Tp, _N> CartesianCoordinates(estl::vector<_Tp, _N> vec) {
  estl::vector<_Tp, _N> res;
  _Tp prod = vec[0];
  for (typename estl::vector<_Tp, _N>::iterator it = vec.begin() + 1,
                                                res_it = res.begin();
       it != vec.end() && res_it != res.end(); ++it, ++res_it) {
    *res_it = prod * cos(*it);
    prod *= sin(*it);
  }
  *(res.end() - 1) = prod;
  return res;
}

}  // namespace estl

#endif  // ESTL_VECTOR_HPP_
