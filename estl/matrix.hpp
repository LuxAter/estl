/* Copyright (C)
 * 2017 - Arden Rasmussen
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
 */

/**
 * @file matrix.hpp
 * @brief Matrix template class for 2D matrices.
 * @author Arden Rasmussen
 * @version 0.0
 * @date 2017-10-30
 * @copyright GNUGeneral Public License
 *
 * This provides a two dimensional matrix container class, along with basic
 * matrix operations.
 */

#ifndef ESTL_MATRIX_HPP_
#define ESTL_MATRIX_HPP_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>

namespace estl {
/**
 * @brief A standard container for storing a fixed size matrix of elements.
 *
 * `estl::matrix` is a container that encapsulates fixed size matrices.
 *
 * This container is an aggregate type with the same semantics as a stuct
 * holding
 * a C-style array `T[N]` as its only non-static data member. Unlike a C-style
 * array, it doesn't decay to `T*` automatically. Elements of this container can
 * be referenced with a single index, but more commonly are referenced with
 * multiple induces.
 *
 * @tparam _Tp Type of element. Required to be a complete type.
 * @tparam _Nr Number of rows of elements.
 * @tparam _Nc Number of columns of elements.
 * @tparam _Al Allocator type, Not necessary in most situations.
 */
template <typename _Tp, std::size_t _Nr, std::size_t _Nc,
          typename _Al = std::allocator<_Tp>>
class matrix {
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

  // TODO(2017-10-31, Arden): Add iterator constructor.
  /**
   * @name Constructor
   * @{ */

  matrix() {
    _Al al;
    __data = al.allocate(size());
  }
  // TODO(2017-10-31, Arden): Add flag for initializer_list being too large.
  matrix(const std::initializer_list<_Tp>& mat) {
    _Al al;
    __data = al.allocate(size());
    std::copy(mat.begin(), mat.end(), __data);
  }
  // TODO(2017-10-31, Arden): Add flag for initializer_list being too large.
  matrix(const std::initializer_list<std::initializer_list<_Tp>>& mat) {
    _Al al;
    __data = al.allocate(size());
    std::copy(mat.begin()->begin(), mat.begin()->begin() + size(), __data);
  }
  matrix(const matrix& mat) {
    _Al al;
    __data = al.allocate(size());
    std::copy(mat.begin(), mat.end(), __data);
  }
  /**  @} */

  /**
   * @name Destructor
   * @{ */
  ~matrix() {
    _Al al;
    al.deallocate(__data, size());
  }
  /** @} */

  /**
   * @name Operator=
   * @{ */
  matrix& operator=(const matrix& mat) {
    _Al al;
    __data = al.allocate(size());
    std::copy(mat.begin(), mat.end(), __data);
  }
  matrix& operator=(const std::initializer_list<_Tp>& mat) {
    _Al al;
    __data = al.allocate(size());
    std::copy(mat.begin(), mat.end(), __data);
  }
  matrix& operator=(
      const std::initializer_list<std::initializer_list<_Tp>>& mat) {
    _Al al;
    __data = al.allocate(size());
    std::copy(mat.begin()->begin(), mat.end()->begin() + size(), __data);
  }
  /** @} */

  /**
   * @name Element Access
   * @{ */

  /**
   * @brief Access specified element with bounds checking.
   *
   * Returns a reference to the element at specified location `__n`, with bounds
   * checking. If `__n` is not within the range of the container, an exception
   * of type `std::out_of_range` is thrown.
   *
   * @param __n Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  reference at(size_type __n) {
    if (__n >= size()) {
      std::__throw_out_of_range_fmt(
          __N("array::at:__n (which is %zu) >= __Nm (which is %zu)"), __n,
          size());
    } else {
      return reference(__data[__n]);
    }
  }
  /**
   * @brief Access specified element with bounds checking.
   *
   * Returns a reference to the element at specified location `__n`, with bounds
   * checking. If `__n` is not within the range of the container, an exception
   * of type `std::out_of_range` is thrown.
   *
   * @param __n Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  constexpr const_reference at(size_type __n) const {
    if (__n >= size()) {
      std::__throw_out_of_range_fmt(
          __N("array::at:__n (which is %zu) >= __Nm (which is %zu)"), __n,
          size());
    } else {
      return const_reference(__data[__n]);
    }
  }
  /**
   * @brief Access specified element with bounds checking.
   *
   * Returns a reference to the element at specified location `__nr`,`__nc`,
   * with bounds checking. If `__nr` is not within the range of the container
   * rows or `__nc` is not within the range of the container columns, an
   * exception of type `std::out_of_range` is thrown.
   *
   * @param __nr Row position of the element to return.
   * @param __nc Column position of the element to return.
   *
   * @return Reference to the requested element.
   */
  reference at(size_type __nr, size_type __nc) {
    if (__nr >= rows()) {
      std::__throw_out_of_range_fmt(
          __N("std::at:__nr (which is %zu) >= __Nr (which is %zu)"), __nr,
          rows());
    } else if (__nc >= columns()) {
      std::__throw_out_of_range_fmt(
          __N("std::at:__nc (which is %zu) >= __Nc (which is %zu)"), __nc,
          columns());
    } else {
      return reference(__data[__nr * columns() + __nc]);
    }
  }
  /**
   * @brief Access specified element with bounds checking.
   *
   * Returns a reference to the element at specified location `__nr`,`__nc`,
   * with bounds checking. If `__nr` is not within the range of the container
   * rows or `__nc` is not within the range of the container columns, an
   * exception of type `std::out_of_range` is thrown.
   *
   * @throws std::out_of_range When either `__nr` or `__nc` is not within the
   * declared range of the container.
   *
   * @param __nr Row position of the element to return.
   * @param __nc Column position of the element to return.
   *
   * @return Reference to the requested element.
   */
  constexpr const_reference at(size_type __nr, size_type __nc) const {
    if (__nr >= rows()) {
      std::__throw_out_of_range_fmt(
          __N("std::at:__nr (which is %zu) >= __Nr (which is %zu)"), __nr,
          rows());
    } else if (__nc >= columns()) {
      std::__throw_out_of_range_fmt(
          __N("std::at:__nc (which is %zu) >= __Nc (which is %zu)"), __nc,
          columns());
    } else {
      return const_reference(__data[__nr * columns() + __nc]);
    }
  }
  /**
   * @brief Access specified element.
   *
   * Returns a reference to the element at specified location `__n`. No bounds
   * checking is preformed.
   *
   * @param __n Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  reference operator[](size_type __n) noexcept {
    return reference(__data[__n]);
  }
  /**
   * @brief Access specified element.
   *
   * Returns a reference to the element at specified location `__n`. No bounds
   * checking is preformed.
   *
   * @param __n Position of the element to return.
   *
   * @return Reference to the requested element.
   */
  constexpr const_reference operator[](size_type __n) const noexcept {
    return const_reference(__data[__n]);
  }
  /**
   * @brief Access specified element.
   *
   * Returns a reference to the element at specified location `__nr`,``__nc. No
   * bounds
   * checking is preformed.
   *
   * @param __nr Row position of the element to return.
   * @param __nr Column position of the element to return.
   *
   * @return Reference to the requested element.
   */
  reference operator()(size_type __nr, size_type __nc) {
    return reference(__data[__nr * columns() + __nc]);
  }
  /**
   * @brief Access specified element.
   *
   * Returns a reference to the element at specified location `__nr`,``__nc. No
   * bounds
   * checking is preformed.
   *
   * @param __nr Row position of the element to return.
   * @param __nr Column position of the element to return.
   *
   * @return Reference to the requested element.
   */
  constexpr const_reference operator()(size_type __nr, size_type __nc) const {
    return const_reference(__data[__nr * columns() + __nc]);
  }
  /**
   * @brief Access the first element.
   *
   * Returns a reference to the first element in the container. Calling `front`
   * on an empty container is undefined.
   *
   * @return Reference to the first element.
   */
  reference front() { return reference(__data[0]); }
  /**
   * @brief Access the first element.
   *
   * Returns a reference to the first element in the container. Calling `front`
   * on an empty container is undefined.
   *
   * @return Reference to the first element.
   */
  constexpr const_reference front() const { return const_reference(__data[0]); }
  /**
   * @brief Access the last element.
   *
   * Returns reference to the last element in the container. Calling `back` on
   * an empty container is undefined.
   *
   * @return Reference to the last element.
   */
  reference back() { return reference(__data[size()]); }
  /**
   * @brief Access the last element.
   *
   * Returns reference to the last element in the container. Calling `back` on
   * an empty container is undefined.
   *
   * @return Reference to the last element.
   */
  constexpr const_reference back() const {
    return const_reference(__data[size()]);
  }
  /**
   * @brief Direct access to the underlying array.
   *
   * Returns pointer to the underlying array serving as element storage. The
   * pointer is such that range `[data(); data() + size()]` is always a valid
   * range, even if the container is empty.
   *
   * @return Pointer to the underlying element storage. For non-empty
   * containers,
   * the returned pointer compares equal to the address of the first element.
   */
  pointer data() { return __data; }
  /**
   * @brief Direct access to the underlying array.
   *
   * Returns pointer to the underlying array serving as element storage. The
   * pointer is such that range `[data(); data() + size()]` is always a valid
   * range, even if the container is empty.
   *
   * @return Pointer to the underlying element storage. For non-empty
   * containers,
   * the returned pointer compares equal to the address of the first element.
   */
  const_pointer data() const { return __data; }

  /** @} */

  /**
   * @name Iterators
   * @{ */

  /**
   * @brief Returns an iterator to the beginning.
   *
   * Returns an iterator to the first element of the container. If the container
   * is empty, the returned iterator will be equal to `end()`.
   *
   * @return Iterator to the first element.
   */
  iterator begin() { return iterator(__data); }
  /**
   * @brief Returns an iterator to the beginning.
   *
   * Returns an iterator to the first element of the container. If the container
   * is empty, the returned iterator will be equal to `end()`.
   *
   * @return Iterator to the first element.
   */
  const_iterator begin() const { return const_iterator(__data); }
  /**
   * @brief Returns an iterator to the beginning.
   *
   * Returns an iterator to the first element of the container. If the container
   * is empty, the returned iterator will be equal to `end()`.
   *
   * @return Iterator to the first element.
   */
  const_iterator cbegin() const { return const_iterator(__data); }
  /**
   * @brief Returns an iterator to the end.
   *
   * Returns an iterator to the element following the last element of the
   * container. This element acts as a placeholder; attempting to access it
   * results in undefined behavior.
   *
   * @return Iterator to the element following the last element.
   */
  iterator end() { return iterator(__data + size()); }
  /**
   * @brief Returns an iterator to the end.
   *
   * Returns an iterator to the element following the last element of the
   * container. This element acts as a placeholder; attempting to access it
   * results in undefined behavior.
   *
   * @return Iterator to the element following the last element.
   */
  const_iterator end() const { return const_iterator(__data + size()); }
  /**
   * @brief Returns an iterator to the end.
   *
   * Returns an iterator to the element following the last element of the
   * container. This element acts as a placeholder; attempting to access it
   * results in undefined behavior.
   *
   * @return Iterator to the element following the last element.
   */
  const_iterator cend() const { return const_iterator(__data + size()); }
  /**
   * @brief Returns a revers iterator to the beginning.
   *
   * Returns a reverse iterator to the first element of the reversed container.
   * It corresponds to the last element of the non-reversed container.
   *
   * @return Reverse iterator to the first element.
   */
  reverse_iterator rbegin() { return reverse_iterator(__data); }
  /**
   * @brief Returns a revers iterator to the beginning.
   *
   * Returns a reverse iterator to the first element of the reversed container.
   * It corresponds to the last element of the non-reversed container.
   *
   * @return Reverse iterator to the first element.
   */
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(__data);
  }
  /**
   * @brief Returns a revers iterator to the beginning.
   *
   * Returns a reverse iterator to the first element of the reversed container.
   * It corresponds to the last element of the non-reversed container.
   *
   * @return Reverse iterator to the first element.
   */
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(__data);
  }
  /**
   * @brief Returns a reverse iterator to the end.
   *
   * Returns a reverse iterator to the element following the last element of the
   * reversed container. it corresponds to the element preceding the first
   * element of the non-reversed container. This element acts as a placeholder,
   * attemplting to access it results in undefined behavior.
   *
   * @return Reverse iterator to the element following the last element.
   */
  constexpr reverse_iterator rend() {
    return reverse_iterator(__data + size());
  }
  /**
   * @brief Returns a reverse iterator to the end.
   *
   * Returns a reverse iterator to the element following the last element of the
   * reversed container. it corresponds to the element preceding the first
   * element of the non-reversed container. This element acts as a placeholder,
   * attemplting to access it results in undefined behavior.
   *
   * @return Reverse iterator to the element following the last element.
   */
  constexpr const_reverse_iterator rend() const {
    return const_reverse_iterator(__data + size());
  }
  /**
   * @brief Returns a reverse iterator to the end.
   *
   * Returns a reverse iterator to the element following the last element of the
   * reversed container. it corresponds to the element preceding the first
   * element of the non-reversed container. This element acts as a placeholder,
   * attemplting to access it results in undefined behavior.
   *
   * @return Reverse iterator to the element following the last element.
   */
  constexpr const_reverse_iterator crend() const {
    return const_reverse_iterator(__data + size());
  }

  /** @} */

  /**
   * @name Capacity
   * @{ */

  /**
   * @brief Checks whether the container is empty.
   *
   * Checks if the container has no elements, i.e. whether `begin() == end()`.
   *
   * @return `true` is the container is empty, `false` otherwise.
   */
  bool empty() const noexcept { return size() == 0; }
  /**
   * @brief Retuns the number of elements
   *
   * Returns the number of elements in the container, i.e.
   * `std::distance(begin(), end())`.
   *
   * @return The number of elements in the container.
   */
  constexpr inline size_type size() const noexcept { return _Nr * _Nc; }
  /**
   * @brief Retuns the number of rows of elemnts.
   *
   * Returns the number of rows of elements in the container.
   *
   * @return The number of rows of elements in the container.
   */
  constexpr inline size_type rows() const noexcept { return _Nr; }
  /**
   * @brief Returns the number of columns of elements.
   *
   * Returns the number of columns of elements in the container.
   *
   * @return The number of columns of elements in the container.
   */
  constexpr inline size_type columns() const noexcept { return _Nc; }
  /**
   * @brief returns the maximum possible number of elements.
   *
   * Returns the maximum number of elements the container is able to hold do to
   * system or library implementation limitations, i.e. `std::distance(begin(),
   * end())` for the largest container.
   *
   * @return Maximum number of elements.
   */
  constexpr size_type max_size() const noexcept { return _Nr * _Nc; }

  /** @} */

  /**
   * @name Operations
   * @{ */

  /**
   * @brief Fill the container with specified value.
   *
   * Assigns the given value to all elements in the container.
   *
   * @param __u The value to assign to the elements.
   */
  void fill(const value_type& __u) { std::fill_n(begin(), size(), __u); }
  /**
   * @brief Swaps the contents
   *
   * Exchanges the contents of the container with those of `__other`. Does not
   * cause iterators and references to associate with the other container.
   *
   * @param __other Container to exchange the contents with.
   */
  void swap(matrix& __other) {
    std::swap_ranges(begin(), end(), __other.begin());
  }
  inline void operator()(_Tp (*func)(_Tp)) {
    for (typename estl::matrix<_Tp, _Nr, _Nc>::iterator it = begin();
         it != end(); ++it) {
      *it = func(*it);
    }
  }

  /** @} */

  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator+=(const _T& rhs) {
    *this = *this + rhs;
    return *this;
  }
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator-=(const _T& rhs) {
    *this = *this - rhs;
    return *this;
  }
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator*=(const _T& rhs) {
    *this = *this / rhs;
    return *this;
  }
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator/=(const _T& rhs) {
    *this = *this * rhs;
    return *this;
  }

 private:
  pointer __data = nullptr;
};

/**
 * @relates estl::matrix
 * @name Operators
 * @{
 */

/**
 * @brief Stream output operator for estl::matrix.
 *
 * Prints the matrix to the supplied stream. In the format of
 * `[[...],[...],...]`.
 *
 * @tparam _Tp Value type of the container.
 * @tparam _Nr Number of rows in the container.
 * @tparam _Nc Number of columns in the container.
 * @param __out Output stream to print to.
 * @param mat Matrix to print.
 *
 * @return Output stream containing representation of the matrix.
 */
template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
std::ostream& operator<<(std::ostream& __out,
                         const estl::matrix<_Tp, _Nr, _Nc>& mat) {
  __out << '[';
  for (std::size_t r = 0; r < _Nr; r++) {
    __out << '[';
    for (std::size_t c = 0; c < _Nc; c++) {
      __out << mat.at(r, c);
      if (c != _Nc - 1) {
        __out << ", ";
      }
    }
    __out << ']';
    if (r != _Nr - 1) {
      __out << ", ";
    }
  }
  __out << ']';
  return __out;
}

/**
 * @brief Lexicographically compares the values in the array.
 *
 * Compares the contents of the two containers.
 *
 * Checks if the contents of the `lhs` and `rhs` are
 *
 * @tparam _TpA
 * @tparam _TpB
 * @tparam _Nr
 * @tparam _Nc
 * @param lhs
 * @param rhs
 *
 * @return
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator==(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator!=(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return !(lhs == rhs);
}

template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator<(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                      const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator>(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                      const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return rhs < lhs;
}

template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator<=(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return !(lhs > rhs);
}
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator>=(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return !(lhs < rhs);
}

template <typename _A, std::size_t _R, std::size_t _C, typename _B>
inline estl::matrix<_A, _R, _C> operator+(const estl::matrix<_A, _R, _C>& lhs,
                                          const _B& rhs) {
  estl::matrix<_A, _R, _C> mat;
  typename estl::matrix<_A, _R, _C>::iterator it;
  typename estl::matrix<_A, _R, _C>::const_iterator lhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin();
       it != mat.end() && lhs_it != lhs.end(); ++it, ++lhs_it) {
    *it = *lhs_it + rhs;
  }
  return mat;
}
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline estl::matrix<_TpA, _Nr, _Nc> operator+(
    const estl::matrix<_TpA, _Nr, _Nc>& lhs,
    const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  estl::matrix<_TpA, _Nr, _Nc> mat;
  typename estl::matrix<_TpA, _Nr, _Nc>::iterator it;
  typename estl::matrix<_TpA, _Nr, _Nc>::const_iterator lhs_it;
  typename estl::matrix<_TpB, _Nr, _Nc>::const_iterator rhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin(), rhs_it = rhs.begin();
       it != mat.end() && lhs_it != lhs.end() && rhs_it != rhs.end();
       ++it, ++lhs_it, ++rhs_it) {
    *it = *lhs_it + *rhs_it;
  }
  return mat;
}

template <typename _A, std::size_t _R, std::size_t _C, typename _B>
inline estl::matrix<_A, _R, _C> operator-(const estl::matrix<_A, _R, _C>& lhs,
                                          const _B& rhs) {
  estl::matrix<_A, _R, _C> mat;
  typename estl::matrix<_A, _R, _C>::iterator it;
  typename estl::matrix<_A, _R, _C>::const_iterator lhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin();
       it != mat.end() && lhs_it != lhs.end(); ++it, ++lhs_it) {
    *it = *lhs_it - rhs;
  }
  return mat;
}
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline estl::matrix<_TpA, _Nr, _Nc> operator-(
    const estl::matrix<_TpA, _Nr, _Nc>& lhs,
    const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  estl::matrix<_TpA, _Nr, _Nc> mat;
  typename estl::matrix<_TpA, _Nr, _Nc>::iterator it;
  typename estl::matrix<_TpA, _Nr, _Nc>::const_iterator lhs_it;
  typename estl::matrix<_TpB, _Nr, _Nc>::const_iterator rhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin(), rhs_it = rhs.begin();
       it != mat.end() && lhs_it != lhs.end() && rhs_it != rhs.end();
       ++it, ++lhs_it, ++rhs_it) {
    *it = *lhs_it - *rhs_it;
  }
  return mat;
}

template <typename _A, std::size_t _R, std::size_t _C, typename _B>
inline estl::matrix<_A, _R, _C> operator*(const estl::matrix<_A, _R, _C>& lhs,
                                          const _B& rhs) {
  estl::matrix<_A, _R, _C> mat;
  typename estl::matrix<_A, _R, _C>::iterator it;
  typename estl::matrix<_A, _R, _C>::const_iterator lhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin();
       it != mat.end() && lhs_it != lhs.end(); ++it, ++lhs_it) {
    *it = *lhs_it * rhs;
  }
  return mat;
}
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline estl::matrix<_TpA, _Nr, _Nc> operator*(
    const estl::matrix<_TpA, _Nr, _Nc>& lhs,
    const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  estl::matrix<_TpA, _Nr, _Nc> mat;
  typename estl::matrix<_TpA, _Nr, _Nc>::iterator it;
  typename estl::matrix<_TpA, _Nr, _Nc>::const_iterator lhs_it;
  typename estl::matrix<_TpB, _Nr, _Nc>::const_iterator rhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin(), rhs_it = rhs.begin();
       it != mat.end() && lhs_it != lhs.end() && rhs_it != rhs.end();
       ++it, ++lhs_it, ++rhs_it) {
    *it = *lhs_it * *rhs_it;
  }
  return mat;
}

template <typename _A, std::size_t _R, std::size_t _C, typename _B>
inline estl::matrix<_A, _R, _C> operator/(const estl::matrix<_A, _R, _C>& lhs,
                                          const _B& rhs) {
  estl::matrix<_A, _R, _C> mat;
  typename estl::matrix<_A, _R, _C>::iterator it;
  typename estl::matrix<_A, _R, _C>::const_iterator lhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin();
       it != mat.end() && lhs_it != lhs.end(); ++it, ++lhs_it) {
    *it = *lhs_it / rhs;
  }
  return mat;
}
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline estl::matrix<_TpA, _Nr, _Nc> operator/(
    const estl::matrix<_TpA, _Nr, _Nc>& lhs,
    const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  estl::matrix<_TpA, _Nr, _Nc> mat;
  typename estl::matrix<_TpA, _Nr, _Nc>::iterator it;
  typename estl::matrix<_TpA, _Nr, _Nc>::const_iterator lhs_it;
  typename estl::matrix<_TpB, _Nr, _Nc>::const_iterator rhs_it;
  for (it = mat.begin(), lhs_it = lhs.begin(), rhs_it = rhs.begin();
       it != mat.end() && lhs_it != lhs.end() && rhs_it != rhs.end();
       ++it, ++lhs_it, ++rhs_it) {
    *it = *lhs_it / *rhs_it;
  }
  return mat;
}

/** @} */

/**
 * @relates estl::matrix
 * @name Functions
 * @{ */
template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
inline _Tp determinate(const estl::matrix<_Tp, _Nr, _Nc>& lhs) {
  _Tp det;
  if (_Nr != _Nc) {
    std::__throw_invalid_argument(
        "Matrix must be square to take to determinate");
  }
  if (_Nr == 2 && _Nc == 2) {
    det = (lhs(0, 0) * lhs(1, 1)) - (lhs(0, 1) * lhs(1, 0));
  } else {
    // std::cout << "oHELLO>>" << lhs.columns() << std::endl;
    // std::size_t columns_index = 0;
    // for (typename estl::matrix<_Tp, _Nr, _Nc>::const_iterator it =
    // lhs.begin();
    // it != lhs.begin() + lhs.columns(); ++it) {
    // std::cout << *it << "[";
    // estl::matrix<_Tp, _Nr - 1, _Nc - 1> mat;
    // std::size_t index = 0;
    // typename estl::matrix<_Tp, _Nr, _Nc>::iterator res_it = mat.begin();
    // for (typename estl::matrix<_Tp, _Nr, _Nc>::const_iterator i =
    // lhs.begin() + lhs.columns();
    // i != lhs.end(); ++i) {
    // if ((index % lhs.columns()) == columns_index) {
    // ++i;
    // index += 1;
    // }
    // *res_it = *i;
    // index += 1;
    // ++res_it;
    // if (i == lhs.end()) {
    // break;
    // }
    // std::cout << *i << ",";
    // }
    // std::cout << "]->" << mat << "\n";
    // det += *it * determinate(mat);
    // columns_index += 1;
    // }
  }
  std::cout << "\n";
  return det;
}
/**  @} */
}  // namespace estl

#endif  // ESTL_MATRIX_HPP_
