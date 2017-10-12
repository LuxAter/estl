// Copyright 2017 Arden
#ifndef ESTL_STREAM_HPP_
#define ESTL_STREAM_HPP_

#include <string.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

namespace estl {
void print(std::ostream& out, std::string __format) { out << __format; }
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
        i++;
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
  bool __looping_flags = true;
  while (__looping_flags == true) {
    switch (__format[i]) {
      case '-':
        __left = true;
        break;
      case '+':
        __show_pos = true;
        break;
      case ' ':
        __plus_space = true;
        break;
      case '0':
        __zero_pad = true;
        break;
      default:
        __looping_flags = false;
        i--;
        break;
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
    }
    i++;
  }
  i--;
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
  if (__show_pos == true) {
    if (std::numeric_limits<T>::is_integer == false && first > T()) {
      out << '+';
      if (__width == true) {
        __print_width -= 1;
      }
    }
  } else if (__plus_space == true) {
    if (std::numeric_limits<T>::is_integer == false && first > T()) {
      out << ' ';
    }
  }
  if (__zero_pad == true) {
    out << std::setfill('0');
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
  __format.erase(__format.begin(), __format.begin() + i);
  print(out, __format, args...);
}
template <typename... Args>
std::string sprint(std::string __format, Args... args) {
  std::stringstream out;
  print(out, __format, args...);
  return out.str();
}
}  // namespace estl

#endif  // ESTL_STREAM_HPP_
