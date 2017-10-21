// Copyright 2017 Arden Rasmussen
/**
 * @file stream.hpp
 * @brief iostream functions utilizing variadic templates.
 * @author Arden Rasmussen
 * @version 0.0
 * @date 2017-10-12
 *
 * These functions improve upon the default `printf` and `scanf` functions both
 * in type safety, and in extensibility. As these implementations can task any
 * class or type that has an `<<` and `>>` operator defined.
 */
#ifndef ESTL_STREAM_HPP_
#define ESTL_STREAM_HPP_

#include <string.h>

#include <iomanip>
#include <iostream>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include <type_traits>

namespace estl {

/**
 * @brief Enum to specify additional format information for scan.
 *
 * @see scan_delim
 */
enum Format { NONE = 0, OCT = 1, HEX = 2, FLOAT_HEX = 3 };

/**
 * @brief Prints the rest of the formated string, after all variables have been
 * used.
 *
 * @param out ostream to write output to.
 * @param __format format string defining the format of the output to `out`.
 */
void print(std::ostream& out, std::string __format) { out << __format; }

/**
 * @brief Varadic template implementation of print.
 *
 * This function takes any number of variables of any type, where the first one
 * must be an ostream, and the second must be a format style string. Then every
 * variable after that is applied according to the format string.
 *
 * @tparam T The type of the first additional variable.
 * @tparam Args Packed set of variadic template arguments.
 * @param out ostream to write output to.
 * @param __format Format string defining the format of the output to `out`.
 * @param first First additional variable.
 * @param args Packed set of additional variables.
 */
template <typename T, typename... Args>
void print(std::ostream& out, std::string __format, T first, Args... args) {
  int i;
  for (i = 0; i < __format.size(); i++) {
    if (__format[i] != '%') {
      out << __format[i];
    } else {
      if (__format.size() <= i + 1) {
        out << '%';
      } else if (__format[i + 1] == '%') {
        out << '%';
        i++;
      } else {
        break;
      }
    }
  }
  i++;
  bool __left = false;
  bool __show_pos = false;
  bool __zero_pad = false;
  bool __plus_space = false;
  bool __width = false;
  bool __precision = false;
  bool __upper_case = false;
  bool __looping_flags = false;
  bool __is_int_base = false;
  if (std::is_integral<T>::value == true ||
      std::is_same<T, double>::value == true ||
      std::is_same<T, float>::value == true) {
    __is_int_base = true;
  }
  if (__format[i] == '-' || __format[i] == '+' || __format[i] == ' ' ||
      __format[i] == '0') {
    __looping_flags = true;
  }
  while (__looping_flags == true) {
    if (__format[i] == '-') {
      __left = true;
    } else if (__format[i] == '+') {
      __show_pos = true;
    } else if (__format[i] == ' ') {
      __plus_space = true;
    } else if (__format[i] == '0') {
      __zero_pad = true;
    } else {
      __looping_flags = false;
      i--;
    }
    i++;
  }
  bool __looping_width = false;
  unsigned int __print_width = 0;
  if (static_cast<int>(__format[i]) >= 48 &&
      static_cast<int>(__format[i]) <= 57) {
    __looping_width = true;
    __width = true;
  }
  while (__looping_width == true) {
    if (static_cast<int>(__format[i]) >= 48 &&
        static_cast<int>(__format[i]) <= 57) {
      __print_width =
          (__print_width * 10) + (static_cast<int>(__format[i]) - 48);
    } else if (__format[i] == '*') {
    } else {
      __looping_width = false;
      i--;
    }
    i++;
  }
  bool __looping_precision = false;
  if (__format[i] == '.') {
    __looping_precision = true;
    __precision = true;
    i++;
  }
  unsigned int __print_precision = 0;
  while (__looping_precision == true) {
    if (static_cast<int>(__format[i]) >= 48 &&
        static_cast<int>(__format[i]) <= 57) {
      __print_precision =
          (__print_precision * 10) + (static_cast<int>(__format[i]) - 48);
    } else if (__format[i] == '*') {
    } else {
      __looping_precision = false;
      i--;
    }
    i++;
  }
  if (__left == true) {
    out << std::left;
  }
  if (__show_pos == true && __is_int_base == true && first > T()) {
    out << '+';
    if (__width == true) {
      __print_width -= 1;
    }
  } else if (__plus_space == true && __is_int_base == true && first > T()) {
    out << ' ';
  }
  if (__zero_pad == true && __is_int_base == true) {
    out << std::setfill('0');
    if (__is_int_base && first < T()) {
      out << std::internal;
    }
  }
  if (__width == true) {
    out << std::setw(__print_width);
  }
  if (__precision == true) {
    out << std::setprecision(__print_precision);
  }
  if (static_cast<int>(__format[i]) >= 65 &&
      static_cast<int>(__format[i]) <= 90) {
    __format[i] = static_cast<char>(static_cast<int>(__format[i]) + 32);
    out << std::uppercase;
    __upper_case = true;
  }
  switch (__format[i]) {
    case 'd':
    case 'i':
      if (std::is_same<T, int>::value) {
        out << first;
      } else {
        out << int();
      }
      break;
    case 'u':
      if (std::is_same<T, unsigned int>::value) {
        out << first;
      } else {
        out << unsigned();
      }
      break;
    case 'o':
      if (std::is_same<T, unsigned int>::value) {
        out << std::oct << first << std::dec;
      } else {
        out << std::oct << unsigned() << std::dec;
      }
      break;
    case 'x':
      if (std::is_same<T, unsigned int>::value) {
        out << std::hex << first << std::dec;
      } else {
        out << std::hex << unsigned() << std::dec;
      }
      break;
    case 'f':
      if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        out << std::fixed << first << std::defaultfloat;
      } else {
        out << double();
      }
      break;
    case 'e':
      if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        out << std::scientific << first << std::defaultfloat;
      } else {
        out << double();
      }
      break;
    case 'g':
      if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        out << std::defaultfloat << first;
      } else {
        out << double();
      }
      break;
    case 'a':
      if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        out << std::hexfloat << first << std::defaultfloat;
      } else {
        out << double();
      }
      break;
    case 'c':
      if (std::is_same<T, char>::value) {
        out << first;
      } else {
        out << char();
      }
      break;
    case 's':
      if (std::is_same<T, const char*>::value ||
          std::is_same<T, std::string>::value) {
        out << first;
      } else {
        out << "";
      }
      break;
    case 'n':
    default:
      out << first;
      break;
  }
  i++;
  if (__left == true) {
    out << std::right;
  }
  if (__zero_pad == true) {
    out << std::setfill(' ');
  }
  if (__width == true) {
    out << std::setw(0);
  }
  if (__precision == true) {
    out << std::setprecision(6);
  }
  if (__upper_case == true) {
    out << std::nouppercase;
  }
  __format.erase(__format.begin(), __format.begin() + i);
  print(out, __format, args...);
}

/**
 * @brief String interface to stream formatted print.
 *
 * @tparam Args Packed set of variadic template arguments.
 * @param __format Format string defining the format of the output to resulting
 * string.
 * @param args Packed set of additional variables.
 *
 * @return String containing formated information.
 */
template <typename... Args>
std::string sprint(std::string __format, Args... args) {
  std::stringstream out;
  print(out, __format, args...);
  return out.str();
}

/**
 * @brief Default IO stream interface for formatted print.
 *
 * @tparam Args Packed set of variadic template arguments.
 * @param __format Format string defining the format of the output to `cout`.
 * @param args Packed set of additional variables.
 */
template <typename... Args>
void cprint(std::string __format, Args&... args) {
  print(std::cout, __format, args...);
}

/**
 * @brief Reads from *istream* until stopped.
 *
 * Reads characters from istream until there are no more characters to read, or
 * until on of the characters in `__delim` is read. Then reads data from set of
 * characters using `>>` operators for type `T`.
 *
 * @tparam T Type to read from stream.
 * @param in istream to read input from.
 * @param __delim string of characters that will stop the reading.
 * @param __width Boolean flat to set scan width to stop reading at.
 * @param __scan_width Width to stop reading at if `__width` is true.
 * @param num_fmt Additional format information for reading values.
 *
 * @return T value read from `in`.
 */
template <typename T>
T scan_delim(std::istream& in, std::string __delim, bool __width = false,
             unsigned int __scan_width = 0,
             unsigned int num_fmt = estl::Format::NONE) {
  bool __preloaded = false;
  if (in.rdbuf()->in_avail() > 0) {
    __preloaded = true;
  }
  T __var = T();
  std::string __str = std::string();
  char __ch = char();
  if (__width == false) {
    __scan_width = __str.max_size();
  } else {
    __scan_width--;
  }
  for (size_t s = 0; s < __scan_width; s++) {
    if (__preloaded == true && in.rdbuf()->in_avail() <= 0) {
      break;
    }
    __ch = in.get();
    bool __is_in = false;
    for (int i = 0; i < __delim.size() && __is_in == false; i++) {
      if (__ch == __delim[i]) {
        __is_in = true;
      }
    }
    if (__is_in == false) {
      __str += __ch;
    } else if (__is_in == true) {
      if (__ch != '\n') {
        in.unget();
      }
      break;
    }
  }
  std::istringstream ss(__str);
  if (num_fmt == estl::Format::HEX) {
    ss >> std::hex;
  } else if (num_fmt == estl::Format::OCT) {
    ss >> std::oct;
  } else if (num_fmt == estl::Format::FLOAT_HEX) {
    __var = std::strtod(__str.c_str(), NULL);
    return __var;
  }
  ss >> __var;
  return __var;
}

/**
 * @brief Ignores the rest of the __format string, and clears stream.
 *
 * @param in Stream to read information from.
 * @param __format Format string defining the format of the input form `in`.
 */
void scan(std::istream& in, std::string __format) {
  std::streambuf* buf = in.rdbuf();
  for (size_t i = 0; i < __format.size(); i++) {
    char ch;
    in.get(ch);
    if (__format[i] != ch) {
      return;
    }
    if (buf->in_avail() <= 0) {
      return;
    }
  }
}

/**
 * @brief Varadic template implementation of scan.
 *
 * This function takes any number of variables of any type, where the first one
 * must of an istream, and the second must be a format style string. Then every
 * variable after that is read according to the format string.
 *
 * @tparam T The type of the first additional variable.
 * @tparam Args Packed set of variadic template arguments.
 * @param in istream to read input from.
 * @param __format Format string defining the format of the input from `in`.
 * @param first First additional variable to save read data to.
 * @param args Packed set of additional variables.
 */
template <typename T, typename... Args>
void scan(std::istream& in, std::string __format, T& first, Args&... args) {
  int i;
  for (i = 0; i < __format.size(); i++) {
    if (__format[i] != '%') {
      char ch;
      in.get(ch);
      if (ch != __format[i]) {
        return;
      }
    } else {
      if (__format.size() <= i + 1) {
        char ch;
        in.get(ch);
        if (ch != __format[i]) {
          return;
        }
      } else if (__format[i + 1] == '%') {
        char ch;
        in.get(ch);
        if (ch != __format[i]) {
          return;
        }
        i++;
      } else {
        break;
      }
    }
  }
  if (i >= __format.size()) {
    return;
  }
  i++;
  bool __width = false;
  unsigned int __scan_width = 0;
  bool __looping_width = false;
  if (static_cast<int>(__format[i]) >= 48 &&
      static_cast<int>(__format[i]) <= 57) {
    __looping_width = true;
    __width = true;
  }
  while (__looping_width == true) {
    if (static_cast<int>(__format[i]) >= 48 &&
        static_cast<int>(__format[i]) <= 57) {
      __scan_width = (10 * __scan_width) + (static_cast<int>(__format[i]) - 48);
    } else {
      __looping_width = false;
      i--;
    }
    i++;
  }
  if (__width == true) {
    __scan_width += 1;
  }
  if (static_cast<int>(__format[i]) >= 65 &&
      static_cast<int>(__format[i]) <= 90) {
    __format[i] = static_cast<char>(static_cast<int>(__format[i]) + 32);
  }
  std::string __delim = "\n ";
  if (i + 1 < __format.size() && __format[i + 1] != ' ') {
    __delim += __format[i + 1];
  }
  switch (__format[i]) {
    case 'i':
    case 'd':
      if (std::is_same<T, int>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width);
      }
      break;
    case 'u':
      if (std::is_same<T, unsigned int>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width);
      }
      break;
    case 'o':
      if (std::is_same<T, unsigned int>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width,
                                    estl::Format::OCT);
      }
      break;
    case 'x':
      if (std::is_same<T, unsigned int>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width,
                                    estl::Format::HEX);
      }
      break;
    case 'f':
    case 'e':
    case 'g':
      if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width);
      }
      break;
    case 'a':
      if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width,
                                    estl::Format::FLOAT_HEX);
      }
      break;
    case 'c':
      if (std::is_same<T, char>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width);
      }
      break;
    case 's':
      if (std::is_same<T, const char*>::value ||
          std::is_same<T, std::string>::value) {
        first = estl::scan_delim<T>(in, __delim, __width, __scan_width);
      }
      break;
    case 'n':
    default:
      first = estl::scan_delim<T>(in, __delim, __width, __scan_width);
      break;
  }
  i++;
  __format.erase(__format.begin(), __format.begin() + i);
  scan(in, __format, args...);
}

/**
 * @brief String interface to stream formatted scan.
 *
 * @tparam Args Packed set of variadic template arguments.
 * @param __str String containing formated input data.
 * @param __format Format string defining the format of the input to read from
 * `__str`.
 * @param args Packed set of additional variable.
 */
template <typename... Args>
void sscan(std::string __str, std::string __format, Args&... args) {
  std::istringstream in(__str);
  scan(in, __format, args...);
}

/**
 * @brief Default IO stream interface for formatted scan.
 *
 * @tparam Args Packed set of variadic template arguments.
 * @param __format Format string defining the format of the input to read from
 * `cin`.
 * @param args Packed set of additional variables.
 */
template <typename... Args>
void cscan(std::string __format, Args&... args) {
  scan(std::cin, __format, args...);
}
}  // namespace estl

#endif  // ESTL_STREAM_HPP_
