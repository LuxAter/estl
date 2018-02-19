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
 * @file variadic.hpp
 * @brief Adds additional functions for handeling variadic templates.
 * @author Arden Rasmussen
 * @version 0.0
 * @date 2018-01-06
 *
 * THis file proveds additional functions for handeling variadic templates,
 * such as storing or retreving data.
 */

#ifndef ESTL_VARIADIC_HPP_
#define ESTL_VARIADIC_HPP_

#include <any>
#include <tuple>
#include <vector>

namespace estl {
namespace variadic {
  /**
   * @brief Unpacks parameter pack to a tuple.
   *
   * Unpacks a parameter pack to a tuple containing the parameters.
   *
   * @tparam _Types Type pack.
   * @param data Parameter pack.
   *
   * @return Tuple of parameter pack.
   */
  template <typename... _Types>
  std::tuple<_Types...> unpack_tuple(_Types... data) {
    return std::tuple<_Types...>(data...);
  }

  /**
   * @brief Unpacks a single parameter to a vector.
   *
   * Unpacks a single parameter to a vector containing the parameter.
   *
   * @tparam _T Type of parameter.
   * @param first Parameter to place in vector.
   *
   * @return Vector containing parameter.
   */
  template <typename _T>
  std::vector<_T> unpack_vector(_T first) {
    return std::vector<_T>{first};
  }
  /**
   * @brief Unpacks a parameter pack of the same type to a vector.
   *
   * Unpacks a parameter pack of the same type to a vector.
   *
   * @tparam _T Type of first parameter.
   * @tparam _Types Type pack.
   * @param first First parameter.
   * @param data Parameter pack.
   *
   * @return Vector containing parameter pack.
   */
  template <typename _T, typename... _Types>
  std::vector<_T> unpack_vector(_T first, _Types... data) {
    std::vector<_T> vec = unpack_vector(data...);
    vec.insert(vec.begin(), first);
    return vec;
  }

  template <typename _T>
  std::vector<std::any> unpack_any(_T first) {
    return std::vector<std::any>{first};
  }

  template <typename _T, typename... _Types>
  std::vector<std::any> unpack_any(_T first, _Types... data) {
    std::vector<std::any> vec = unpack_any(data...);
    vec.insert(vec.begin(), first);
    return vec;
  }
}  // namespace variadic
}  // namespace estl

#endif  // ESTL_VARIADIC_HPP_
