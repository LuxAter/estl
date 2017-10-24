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
 *
 * @file matrix.hpp
 * @brief matrix template class for 2D matrices.
 * @author Arden Rasmussen
 * @version 0.0
 * @date 2017-10-23
 *
 * This class represents a two dimensional matrix. And provides iterator access
 * to the elements of the matrix through access operators. It also provides
 * basic matrix operations, as described below.
 */

#ifndef ESTL_MATRIX_HPP_
#define ESTL_MATRIX_HPP_

#include <memory>

namespace estl {
template <typename _Tp, std::size_t _Nr, std::size_t _Nc,
          typename _Al = std::allocator<_Tp> >
class matrix {
 public:
  typedef _Al allocator_type;
  typedef typename _Al::value_type value_type;
  typedef typename _Al::reference reference;
  typedef typename _Al::const_reference const_reference;
  typedef typename _Al::difference_type difference_type;
  typedef typename _Al::size_type size_type;

  class iterator {
   public:
    typedef typename _Al::difference_type difference_type;
    typedef typename _Al::value_type value_type;
    typedef typename _Al::reference reference;
    typedef typename _Al::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category;

    iterator();
    iterator(const iterator&);
    ~iterator();
  };

  matrix();
  matrix(const matrix&);
  ~matrix();
};

}  // namespace estl

#endif  // ESTL_MATRIX_HPP_
