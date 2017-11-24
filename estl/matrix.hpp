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
 * @copyright GNU General Public License
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
#include <vector>

#include <iomanip>

/**
 * @brief Base ESTL namespace for all estl objects
 */
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

  /**
   * @name Constructor
   * @{ */

  /**
   * @brief Default matrix constructor
   *
   * This allocates the memory required for the desired matrix.
   */
  matrix() {
    _Al al;
    __data = al.allocate(size());
    fill(_Tp());
  }
  /**
   * @brief Matrix constructor
   *
   * Allocates the memory required for the matrx and fills every element with
   * the supplied value.
   *
   * @param val Value to copy to every element of the matrix.
   */
  matrix(_Tp val) {
    _Al al;
    __data = al.allocate(size());
    fill(val);
  }
  /**
   * @brief Matrix Constructor
   *
   * Allocates the memory required for the matrix, and copies the elements of
   * the initializer list to the elements of the matrix.
   *
   * @throw out_of_range Throws out of range if initializer_list list is
   * greater than the size of the matrix.
   *
   * @param mat initializer_list of elements to copy.
   */
  matrix(const std::initializer_list<_Tp>& mat) {
    _Al al;
    __data = al.allocate(size());
    if (mat.size() > size()) {
      std::__throw_out_of_range_fmt(
          __N("initializer_list.size() (which is %zu) > __Ne (which is %zu)"),
          mat.size(), size());
    }
    std::copy(mat.begin(), mat.end(), __data);
  }
  matrix(const std::initializer_list<std::initializer_list<_Tp>>& mat) {
    if (mat.size() != _Nr) {
      std::__throw_out_of_range_fmt(
          __N("initializer_list.size() (which is %zu) != _Nr (which is %zu)"),
          mat.size(), _Nr);
    }
    _Al al;
    __data = al.allocate(size());
    iterator index = begin();
    for (typename std::initializer_list<
             std::initializer_list<_Tp>>::const_iterator it = mat.begin();
         it != mat.end(); ++it) {
      if (it->size() != _Nc) {
        std::__throw_out_of_range_fmt(
            __N("initializer_list.size() (which is %zu) != _Nc (which is %zu)"),
            it->size(), _Nc);
      }
      std::copy(it->begin(), it->end(), index);
      index += it->size();
    }
  }
  template <class InputIt>
  matrix(InputIt first, InputIt last) {
    _Al al;
    __data = al.allocate(size());
    std::copy(first, last, __data);
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
  reference back() { return reference(__data[size() - 1]); }
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
   * containers, the returned pointer compares equal to the address of the first
   * element.
   */
  const_pointer data() const { return __data; }

  /**
   * @brief Direct access to the underlying array.
   *
   * Returns a `std::array` containing a copy of the underlying array serving as
   * element storage.
   *
   * @note This is a copy, so changing the values of the returned `std::array`
   * will not effect the values in the matrix.
   *
   * @return `std::array` containing a copy of the underlying element storage.
   */
  std::array<_Tp, _Nr * _Nc> data_array() const {
    std::array<_Tp, _Nr * _Nc> mat;
    std::copy(begin(), end(), mat.begin());
    return mat;
  }
  /**
   * @brief Direct access to the underlying array.
   *
   * Returns a `std::array<std::array>` containing a copy of the underlying
   * array serving as element storage.
   *
   * @note This is a copy, so changing the values of the returned
   * `std::array<std::array>` will not effect the values in the matrix.
   *
   * @return `std::array<std::array>` containing a copy of the underlying
   * element storage.
   */
  std::array<std::array<_Tp, _Nc>, _Nr> data_2darray() const {
    std::array<std::array<_Tp, _Nc>, _Nr> arr;
    const_iterator mat_it = begin();
    for (typename std::array<std::array<_Tp, _Nc>, _Nr>::iterator it =
             arr.begin();
         it != arr.end(); ++it) {
      for (typename std::array<_Tp, _Nc>::iterator sub_it = it->begin();
           sub_it != it->end(); ++sub_it, ++mat_it) {
        *sub_it = *mat_it;
      }
    }
    return arr;
  }
  /**
   * @brief Direct access to the underlying array.
   *
   * Returns a `std::vector` containing a copy of the underlying array serving
   * as element storage.
   *
   * @note This is a copy, so changing the values of the returned
   * `std::array<std::array>` will not effect the values in the matrix.
   *
   * @return `std::vector` containing a copy of the underlying element storage.
   */
  std::vector<_Tp> data_vector() const {
    return std::vector<_Tp>(begin(), end());
  }

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
   * @brief Returns a reverse iterator to the beginning.
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
   * reversed container. It corresponds to the element preceding the first
   * element of the non-reversed container. This element acts as a placeholder,
   * attemplting to access it results in undefined behavior.
   *
   * @return Reverse iterator to the element following the last element.
   */
  constexpr const_reverse_iterator crend() const {
    return const_reverse_iterator(__data + size());
  }

  /**
   * @brief Returns an iterator to specified element.
   *
   * Retuns an iterator to the element that is located at `[__r][__c]` in the
   * container.
   *
   * @param __r Row of the specified element.
   * @param __c Column of the specified element.
   *
   * @return Iterator to the specified element.
   */
  constexpr iterator element(size_type __r, size_type __c) {
    return iterator(__data + (__r * columns()) + __c);
  }

  /**
   * @brief Returns an iterator to specified element.
   *
   * Retuns an iterator to the element that is located at `[__r][__c]` in the
   * container.
   *
   * @param __r Row of the specified element.
   * @param __c Column of the specified element.
   *
   * @return Iterator to the specified element.
   */
  constexpr const_iterator element(size_type __r, size_type __c) const {
    return const_iterator(__data + (__r * columns()) + __c);
  }

  /**
   * @brief Returns an iterator to specified element.
   *
   * Retuns an iterator to the element that is located at `[__r][__c]` in the
   * container.
   *
   * @param __r Row of the specified element.
   * @param __c Column of the specified element.
   *
   * @return Iterator to the specified element.
   */
  constexpr const_iterator celement(size_type __r, size_type __c) const {
    return const_iterator(__data + (__r * columns()) + __c);
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
   * @brief Fills the diagonal of the matrix with specified value.
   *
   * Assigns the given value to all elements along the diagonal of the matrix.
   *
   * @param __u The value to assign to the elements.
   */
  void fill_diagonal(const value_type& __u) {
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type it = 0;
         it < columns() && it < rows(); it++) {
      at(it, it) = __u;
    }
  }
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
  /**
   * @brief Preform supplied function on elements.
   *
   * For every element in the matrix, executes `func` with that element as the
   * argument.
   *
   * @param func Function that takes one parameter of type `_Tp`.
   */
  inline void operator()(_Tp (*func)(_Tp)) {
    for (typename estl::matrix<_Tp, _Nr, _Nc>::iterator it = begin();
         it != end(); ++it) {
      *it = func(*it);
    }
  }

  /** @} */

  /**
   * @name Row/Column Operations
   * @{ */

  /**
   * @brief Swaps the contents to two rows of the container.
   *
   * Exchanges the contents of two rows of the container, with the other row.
   * Does not cause iterators and references to associate with the other row.
   *
   * @param __a First row to swap.
   * @param __b Seconed row to swap.
   */
  inline void swap_row(size_type __a, size_type __b) {
    for (typename estl::matrix<_Tp, _Nr, _Nc>::iterator it_a = element(__a, 0),
                                                        it_b = element(__b, 0);
         it_a != element(__a, columns()) && it_b != element(__b, columns());
         ++it_a, ++it_b) {
      std::iter_swap(it_a, it_b);
    }
  }
  /**
   * @brief Swaps the contents to two columns of the container.
   *
   * Exchanges the contents of two columns of the container, with the other
   * column. Does not cause iterators and references to associate with the other
   * column.
   *
   * @param __a First column to swap.
   * @param __b Seconed column to swap.
   */
  inline void swap_column(size_type __a, size_type __b) {
    for (typename estl::matrix<_Tp, _Nr, _Nc>::iterator it_a = element(0, __a),
                                                        it_b = element(0, __b);
         it_a != element(rows(), __a) && it_b != element(rows(), __b);
         it_a += columns(), it_b += columns()) {
      std::iter_swap(it_a, it_b);
    }
  }

  /**  @} */

  /**
   * @brief Compound assignment of two matricies, or a matrix and a sclar.
   *
   * Implements the compound addition operator for matrix arithmetic.
   *
   * @tparam _T Type to add to the matrix.
   * @param rhs Value to add to the matrix.
   *
   * @return `reference` of `*this` after arithmetic operation.
   */
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator+=(const _T& rhs) {
    *this = *this + rhs;
    return *this;
  }
  /**
   * @brief Compound assignment of two matricies, or a matrix and a sclar.
   *
   * Implements the compound subtraction operator for matrix arithmetic.
   *
   * @tparam _T Type to subtract from the matrix.
   * @param rhs Value to subtract from the matrix.
   *
   * @return `reference` of `*this` after arithmetic operation.
   */
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator-=(const _T& rhs) {
    *this = *this - rhs;
    return *this;
  }
  /**
   * @brief Compound assignment of two matricies, or a matrix and a sclar.
   *
   * Implements the compound multiplication operator for matrix arithmetic.
   *
   * @tparam _T Type to multiply to the matrix.
   * @param rhs Value to multiply to the matrix.
   *
   * @return `reference` of `*this` after arithmetic operation.
   */
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator*=(const _T& rhs) {
    *this = *this * rhs;
    return *this;
  }
  /**
   * @brief Compound assignment of two matricies, or a matrix and a sclar.
   *
   * Implements the compound division operator for matrix arithmetic.
   *
   * @tparam _T Type to divide the matrix by.
   * @param rhs Value to divide the matrix by.
   *
   * @return `reference` of `*this` after arithmetic operation.
   */
  template <typename _T>
  inline estl::matrix<_Tp, _Nr, _Nc>& operator/=(const _T& rhs) {
    *this = *this / rhs;
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
 * @brief Lexicographically compares the values in the matrix.
 *
 * Compares the contents of the two containers.
 *
 * Checks if the contents of `lhs` and `rhs` are equal, that is, whether
 * each element in `lhs` compares equal with the element in `rhs` at the same
 * position.
 *
 * @tparam _TpA Value type of the first containere.
 * @tparam _TpB Value type of the second container.
 * @tparam _Nr Number of rows in the containers.
 * @tparam _Nc Number of columns in the containers.
 * @param lhs First matrix to compare.
 * @param rhs Second matrix to compare.
 *
 * @return `true` if the contents of the containers are equal, `false`
 * otherwise.
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator==(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}
/**
 * @brief Lexicographically compares the values in the matrix.
 *
 * Checks if the contents of `lhs` and `rhs` are equal, that is, whether each
 * element in `lhs` compares equal with the element in `rhs` at the same
 * position.
 *
 * @tparam _TpA Value type of the first container.
 * @tparam _TpB Value type of the second container.
 * @tparam _Nr Number of rows in the containers.
 * @tparam _Nc Number of columns in the containes.
 * @param lhs First matrix to compare.
 * @param rhs Second matrix to compare.
 *
 * @return `true` if the contents of the containers are not equal, `false`
 * otherwise.
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator!=(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return !(lhs == rhs);
}

/**
 * @brief Lexicographically compares the values in the matrix.
 *
 * Compares the contents of `lhs` and `rhs` lexicographically. The comparison is
 * preformed by a function equivalent to `std::lexicographical_compare`.
 *
 * @tparam _TpA Value type of the first container.
 * @tparam _TpB Value type of the second container.
 * @tparam _Nr Number of rows in the containers.
 * @tparam _Nc Number of Columns in the containers.
 * @param lhs First matrix to compare.
 * @param rhs Second matrix to compare.
 *
 * @return `true` if the contents of the `lhs` are lexicographically *less* than
 * the contents of `rhs`, `false` otherwise.
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator<(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                      const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                      rhs.end());
}

/**
 * @brief Lexicographically compares the values in the matrix.
 *
 * Compares the contents of `lhs` and `rhs` lexicographically. The comparison is
 * preformed by a function equivalent to `std::lexicographical_compare`.
 *
 * @tparam _TpA Value type of the first container.
 * @tparam _TpB Value type of the second container.
 * @tparam _Nr Number of rows in the containers.
 * @tparam _Nc Number of Columns in the containers.
 * @param lhs First matrix to compare.
 * @param rhs Second matrix to compare.
 *
 * @return `true` if the contents of the `lhs` are lexicographically *greater*
 * than the contents of `rhs`, `false` otherwise.
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator>(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                      const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return rhs < lhs;
}

/**
 * @brief Lexicographically compares the values in the matrix.
 *
 * Compares the contents of `lhs` and `rhs` lexicographically. The comparison is
 * preformed by a function equivalent to `std::lexicographical_compare`.
 *
 * @tparam _TpA Value type of the first container.
 * @tparam _TpB Value type of the second container.
 * @tparam _Nr Number of rows in the containers.
 * @tparam _Nc Number of Columns in the containers.
 * @param lhs First matrix to compare.
 * @param rhs Second matrix to compare.
 *
 * @return `true` if the contents of the `lhs` are lexicographically *less* than
 * or *equal* the contents of `rhs`, `false` otherwise.
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator<=(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return !(lhs > rhs);
}
/**
 * @brief Lexicographically compares the values in the matrix.
 *
 * Compares the contents of `lhs` and `rhs` lexicographically. The comparison is
 * preformed by a function equivalent to `std::lexicographical_compare`.
 *
 * @tparam _TpA Value type of the first container.
 * @tparam _TpB Value type of the second container.
 * @tparam _Nr Number of rows in the containers.
 * @tparam _Nc Number of Columns in the containers.
 * @param lhs First matrix to compare.
 * @param rhs Second matrix to compare.
 *
 * @return `true` if the contents of the `lhs` are lexicographically *greater*
 * than or *equal* the contents of `rhs`, `false` otherwise.
 */
template <typename _TpA, typename _TpB, std::size_t _Nr, std::size_t _Nc>
inline bool operator>=(const estl::matrix<_TpA, _Nr, _Nc>& lhs,
                       const estl::matrix<_TpB, _Nr, _Nc>& rhs) {
  return !(lhs < rhs);
}

/**
 * @brief Preforms matrix arithmetics on a matrix and a scalar.
 *
 * Implements the binary operators for matrix arithmetic. Adds the scalar to
 * every element of the matrix.
 *
 * @tparam _A Value type of the matrix.
 * @tparam _R Number of rows in the matrix.
 * @tparam _C Number of columns in the matrix.
 * @tparam _B Value type of the scalar.
 * @param lhs The matrix.
 * @param rhs The scalar.
 *
 * @return The matrix after the arithmetic operation.
 */
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
/**
 * @brief Preforms matrix arithmetic on a matrix and another matrix.
 *
 * Implements the binary operators for matrix arithmetic. Lexicographically adds
 * every element of `lhs` with the element from `rhs` with the same position.
 *
 * @tparam _TpA Value type of `lhs`.
 * @tparam _TpB Value type of `rhs`.
 * @tparam _Nr Number of rows in the matrix.
 * @tparam _Nc Number of columns in the matrix.
 * @param lhs The first matrix.
 * @param rhs The second matrix.
 *
 * @return The matrix after the arithmetic operation.
 */
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

/**
 * @brief Preforms matrix arithmetics on a matrix and a scalar.
 *
 * Implements the binary operators for matrix arithmetic. Subtracts the scalar
 * from every element in the matrix.
 *
 * @tparam _A Value type of the matrix.
 * @tparam _R Number of rows in the matrix.
 * @tparam _C Number of columns in the matrix.
 * @tparam _B Value type of the scalar.
 * @param lhs The matrix.
 * @param rhs The scalar.
 *
 * @return The matrix after the arithmetic operation.
 */
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
/**
 * @brief Preforms matrix arithmetic on a matrix and another matrix.
 *
 * Implements the binary operators for matrix arithmetic. Lexicographically
 * subtracts every element of `lhs` with the element from `rhs` with the same
 * position.
 *
 * @tparam _TpA Value type of `lhs`.
 * @tparam _TpB Value type of `rhs`.
 * @tparam _Nr Number of rows in the matrix.
 * @tparam _Nc Number of columns in the matrix.
 * @param lhs The first matrix.
 * @param rhs The second matrix.
 *
 * @return The matrix after the arithmetic operation.
 */
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

/**
 * @brief Preforms matrix arithmetics on a matrix and a scalar.
 *
 * Implements the binary operators for matrix arithmetic. Multiplies the scalar
 * to every element of the matrix.
 *
 * @tparam _A Value type of the matrix.
 * @tparam _R Number of rows in the matrix.
 * @tparam _C Number of columns in the matrix.
 * @tparam _B Value type of the scalar.
 * @param lhs The matrix.
 * @param rhs The scalar.
 *
 * @return The matrix after the arithmetic operation.
 */
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
/**
 * @brief Preforms matrix arithmetic on a matrix and another matrix.
 *
 * Implements the binary operators for matrix arithmetic. Lexicographically
 * multiplies every element of `lhs` with the element from `rhs` with the same
 * position.
 *
 * @tparam _TpA Value type of `lhs`.
 * @tparam _TpB Value type of `rhs`.
 * @tparam _Nr Number of rows in the matrix.
 * @tparam _Nc Number of columns in the matrix.
 * @param lhs The first matrix.
 * @param rhs The second matrix.
 *
 * @return The matrix after the arithmetic operation.
 */
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

/**
 * @brief Preforms matrix arithmetics on a matrix and a scalar.
 *
 * Implements the binary operators for matrix arithmetic. Divides every element
 * of the matrix by the scalar.
 *
 * @tparam _A Value type of the matrix.
 * @tparam _R Number of rows in the matrix.
 * @tparam _C Number of columns in the matrix.
 * @tparam _B Value type of the scalar.
 * @param lhs The matrix.
 * @param rhs The scalar.
 *
 * @return The matrix after the arithmetic operation.
 */
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
/**
 * @brief Preforms matrix arithmetic on a matrix and another matrix.
 *
 * Implements the binary operators for matrix arithmetic. Lexicographically
 * divides every element of `lhs` with the element from `rhs` with the same
 * position.
 *
 * @tparam _TpA Value type of `lhs`.
 * @tparam _TpB Value type of `rhs`.
 * @tparam _Nr Number of rows in the matrix.
 * @tparam _Nc Number of columns in the matrix.
 * @param lhs The first matrix.
 * @param rhs The second matrix.
 *
 * @return The matrix after the arithmetic operation.
 */
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

/**
 * @brief Finds the trace of the matrix.
 *
 * Returns the trace of the matrix, which is computed by taking the sum of the
 * diagonal terms of the matrix. \f$\sum_{i}^{Nr} A_{(i,i)}\f$.
 *
 * @tparam _Tp Value type of the container.
 * @tparam _Nr Number of rows in the container.
 * @tparam _Nc Number of column in the container.
 * @param lhs Matrix to find the trace of.
 *
 * @return The trace of the matrix.
 */
template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
_Tp trace(const estl::matrix<_Tp, _Nr, _Nc>& lhs) {
  _Tp sum;
  for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type it = 0;
       it != lhs.rows() && it != lhs.columns(); it++) {
    sum += lhs.at(it, it);
  }
  return sum;
}

/**
 * @brief Finds the determinant of the given matrix.
 *
 * Returns the deterinant of the provided matrix.
 *
 * @warning This can only be as accurate as `_Tp`, because the determinant is
 * found in terms of `_Tp`. This means that the value only has the abbility to
 * be represented by a `_Tp` value. This means that if `_Tp` is `int`, then the
 * determinant will not be accurate, as it requires devision, and decimial
 * integers, instead use `_Tp` as a `double` or `float`.
 *
 * @tparam _Tp Value type of the container.
 * @tparam _Nr Number of rows in the container.
 * @tparam _Nc Number of columns in container.
 * @param lhs Matrix to find the determinat of.
 *
 * @return The determinant of the matrix.
 */
template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
_Tp determinant(const estl::matrix<_Tp, _Nr, _Nc>& lhs) {
  estl::matrix<_Tp, _Nr, _Nc> mat(lhs);
  _Tp sign = _Tp(1);
  for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type it = 0;
       it != mat.rows() && it != mat.columns(); it++) {
    typename estl::matrix<_Tp, _Nr, _Nc>::size_type sw;
    for (sw = it; sw != mat.rows(); sw++) {
      if (mat.at(sw, it) != _Tp()) {
        break;
      }
    }
    if (sw != it) {
      mat.swap_row(sw, it);
      sign *= _Tp(-1);
    }
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type row = it + 1;
         row != mat.rows(); row++) {
      _Tp mult = mat.at(row, it) / mat.at(it, it);
      for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type column = it;
           column != mat.columns(); column++) {
        mat.at(row, column) -= mult * mat.at(it, column);
      }
    }
  }
  _Tp sum = _Tp(1);
  for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type it = 0;
       it != mat.rows() && it != mat.columns(); it++) {
    sum *= mat.at(it, it);
  }
  sum *= sign;
  return sum;
}

/**
 * @brief Computes the inverse matrix of the specified matrix.
 *
 * Computes the inverse matrix throught the use of gausian elimination.
 *
 * @tparam _Tp Value type of the container.
 * @tparam _Nr Number of rows in the container.
 * @tparam _Nc Number of columns in the container.
 * @param lhs Matrix to find the inverse of.
 *
 * @return Inverse matrix to the givin matrix.
 */
template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
estl::matrix<_Tp, _Nr, _Nc> inverse(const estl::matrix<_Tp, _Nr, _Nc>& lhs) {
  estl::matrix<_Tp, _Nr, _Nc> mat(lhs);
  estl::matrix<_Tp, _Nr, _Nc> inv;
  inv.fill_diagonal(_Tp(1));
  for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type it = 0;
       it != mat.rows() && it != mat.columns(); it++) {
    _Tp pivot = mat.at(it, it);
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type column = 0;
         column != mat.columns(); column++) {
      mat.at(it, column) /= pivot;
      inv.at(it, column) /= pivot;
    }
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type row = 0;
         row != mat.rows(); row++) {
      _Tp mult = mat.at(row, it);
      for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type column = 0;
           column != mat.columns() && row != it; column++) {
        mat.at(row, column) -= mult * mat.at(it, column);
        inv.at(row, column) -= mult * inv.at(it, column);
      }
    }
  }
  return inv;
}

template <typename _Tp, std::size_t _Nr, std::size_t _Nc>
estl::matrix<_Tp, _Nr, _Nc> echelon_form(
    const estl::matrix<_Tp, _Nr, _Nc>& lhs) {
  estl::matrix<_Tp, _Nr, _Nc> mat(lhs);
  for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type it = 0;
       it != mat.rows() && it != mat.columns(); it++) {
    _Tp pivot = mat.at(it, it);
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type col = 0;
         col != mat.columns(); col++) {
      mat.at(it, col) /= pivot;
    }
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type row = 0;
         row != mat.rows(); row++) {
      _Tp mult = mat.at(row, it);
      for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type col = it;
           col != mat.columns() && row != it; col++) {
        mat.at(row, col) -= mult * mat.at(it, col);
      }
    }
  }
  return mat;
}

/**
 * @brief Multiplies two matricies together.
 *
 * Multiples two matricies together, in a simple method of iteration. It is well
 * suited for matricies with on order less than \f$2^{10}\f$, matricies larger
 * than this size should use an implementation of Strassen's algorithm.
 *
 * @note This is not an efficient algorithm for matrix multiplication, it has a
 * complexity of \f$O(n^2)\f$. If an efficient algorithm is needed for larger
 * matricies, use a different algorithm, or implement your own.
 *
 * @tparam _Tp Value type of the first matrix and the returned matrix.
 * @tparam _Nr Number of rows in the first matrix, and in the returned matrix.
 * @tparam _N Number of columns in the first matrix, and the number of rows in
 * the second matrix.
 * @tparam _Nc Number of columns in the second matrix and the returned matrix.
 * @param lhs First matrix to multiply.
 * @param rhs Second matrix to multiply.
 *
 * @return A matrix of `_Tp` that is `_Nr` by `_Nc`.
 */
template <typename _Tp, std::size_t _Nr, std::size_t _N, std::size_t _Nc>
estl::matrix<_Tp, _Nr, _Nc> multiplication(
    const estl::matrix<_Tp, _Nr, _N>& lhs,
    const estl::matrix<_Tp, _N, _Nc>& rhs) {
  estl::matrix<_Tp, _Nr, _Nc> mat;
  for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type row = 0;
       row != mat.rows(); row++) {
    for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type column = 0;
         column != mat.columns(); column++) {
      for (typename estl::matrix<_Tp, _Nr, _Nc>::size_type k = 0;
           k < lhs.columns() && k < rhs.rows(); k++) {
        mat.at(row, column) += (lhs.at(row, k) * rhs.at(k, column));
      }
    }
  }
  return mat;
}

/**  @} */
}  // namespace estl

#endif  // ESTL_MATRIX_HPP_
