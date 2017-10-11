// Copyright 2017 Arden
#ifndef ESTL_STREAM_HPP_
#define ESTL_STREAM_HPP_

#include <string.h>
#include <iostream>
#include <string>
#include <type_traits>

namespace estl {
void print(std::ostream& out, std::string __format) { out << __format; }
template <typename T, typename... Args>
std::ostream& print(std::ostream& out, std::string __format, T first,
                    Args... args) {
  // out << "\"" << __format << "\"\n";
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
  if (__format[i] == '*') {
    out << first;
  } else if (__format[i] == 'i' || __format[i] == 'd') {
    if (std::is_same<T, int>::value) {
      out << first;
    } else {
      out << int();
    }
  } else if (__format[i] == 'u') {
    if (std::is_same<T, unsigned int>::value) {
      out << first;
    } else {
      out << unsigned();
    }
  } else if (__format[i] == 'f' || __format[i] == 'F') {
    if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
      out << std::fixed << first << std::defaultfloat;
    } else {
      out << std::fixed << double() << std::defaultfloat;
    }
  } else if (__format[i] == 'e' || __format[i] == 'E') {
    if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
      out << std::scientific << first << std::defaultfloat;
    } else {
      out << std::scientific << double() << std::defaultfloat;
    }
  } else if (__format[i] == 'g' || __format[i] == 'G') {
    if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
      out << std::defaultfloat << first;
    } else {
      out << std::defaultfloat << double();
    }
  } else if (__format[i] == 'c') {
    if (std::is_same<T, char>::value) {
      out << first;
    } else {
      out << char();
    }
  } else if (__format[i] == 's') {
    if (std::is_same<T, const char*>::value ||
        std::is_same<T, std::string>::value) {
      out << first;
    }
  }
  i++;
  __format.erase(__format.begin(), __format.begin() + i);
  print(out, __format, args...);
  return out;
}
}  // namespace estl

#endif  // ESTL_STREAM_HPP_
