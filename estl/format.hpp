#ifndef ESTL_FORMAT_HPP_
#define ESTL_FORMAT_HPP_

#include <stdio.h>
#include <iostream>

#include <stdarg.h>

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include "variadic.hpp"

// TODO(Arden): Add compile time breaks for invalid format strings, attempting
// to subscript a non subscriptable object, ect.

namespace estl {
namespace format {

  namespace {
    template <typename S, typename T>
    struct has_stream {
     private:
      template <typename SS, typename TT>
      static auto check(int)
          -> decltype(std::declval<SS&>() << std::declval<TT>(),
                      std::true_type());
      template <typename, typename>
      static auto check(...) -> std::false_type;

     public:
      static constexpr bool value = decltype(check<S, T>(0))::value;
    };
    template <class T, class Index>
    struct has_subscript_impl {
      template <class T1, class IndexDeduced = Index,
                class Reference = decltype(
                    (*std::declval<T*>())[std::declval<IndexDeduced>()]),
                class = typename std::enable_if<
                    !std::is_void<Reference>::value>::type>
      static std::true_type test(int);

      template <class>
      static std::false_type test(...);

      using type = decltype(test<T>(0));
    };

    template <class T, class Index>
    using has_subscript = typename has_subscript_impl<T, Index>::type;

    template <typename, typename T>
    struct has_format {
      static_assert(std::integral_constant<T, false>::value,
                    "Second template parameter needs to be of function type");
    };
    template <typename T, typename Ret, typename... Args>
    struct has_format<T, Ret(Args...)> {
     private:
      template <typename U>
      static constexpr auto check(U*) -> typename std::is_same<
          decltype(std::declval<U>().Format(std::declval<Args>()...)),
          Ret>::type;
      template <typename>
      static constexpr std::false_type check(...);
      typedef decltype(check<T>(0)) type;

     public:
      static constexpr bool value = type::value;
    };

    template <typename TString, typename TChar = typename TString::value_type>
    inline TString to_xstring(std::size_t n, const TChar* fmt, ...) {
      TChar* res;
      if (n != 0) {
        res = static_cast<TChar*>(malloc(sizeof(TChar) * n));
      } else {
        res = static_cast<TChar*>(malloc(sizeof(TChar) * 255));
        n = 255;
      }
      va_list args;
      va_start(args, fmt);
      const int len = std::vsnprintf(res, n, fmt, args);
      va_end(args);
      return TString(res, len);
    }

    template <typename T>
    inline std::string data_fmt(int data[8], std::size_t n,
                                std::string_view type, T args) {
      std::string fmt = "%";
      if (data[3] == 0) fmt += '+';
      if (data[3] == 1) fmt += '-';
      if (data[3] == 2) fmt += ' ';
      if (data[1] == int('0')) fmt += '0';
      if (data[4] != -1 && (data[1] == int('0') || data[1] == -1) &&
          data[2] == -1)
        fmt += std::to_string(data[4]);
      if (data[5] != -1) fmt += '.' + std::to_string(data[5]);
      fmt += std::string(type);
      fmt = to_xstring<std::string>(n, fmt.c_str(), args);
      if (data[4] != -1 && data[4] > fmt.size()) {
        if (data[1] == -1) {
          data[1] = int(' ');
        }
        if (data[2] == 0) {
          fmt += std::string(data[4] - fmt.size(), data[1]);
        } else if (data[2] == 1) {
          fmt = std::string(data[4] - fmt.size(), data[1]) + fmt;
        } else if (data[2] == 2) {
          if (fmt[0] == '-' || fmt[0] == '+') {
            fmt = fmt[0] + std::string(data[4] - fmt.size(), data[1]) +
                  fmt.substr(1);
          } else {
            fmt = std::string(data[4] - fmt.size(), data[1]) + fmt;
          }
        } else if (data[2] == 3) {
          fmt = std::string(std::floor((data[4] - fmt.size()) / 2.0), data[1]) +
                fmt +
                std::string(std::ceil((data[4] - fmt.size()) / 2.0), data[1]);
        }
      }
      return fmt;
    }

    template <typename T>
    inline typename std::enable_if<has_format<T, std::string()>::value,
                                   std::string>::type
    aformat(int data[8], T argument) {
      // TODO(Arden): Implement class format tremplate, and provide requirements
      // and data.
      return argument.Format();
    }

    template <typename T>
    inline typename std::enable_if<
        !(has_format<T, std::string()>::value) &&
            (std::is_same<T, bool>::value || std::is_same<T, char>::value ||
             std::is_same<T, int>::value || std::is_same<T, unsigned>::value ||
             std::is_same<T, long>::value ||
             std::is_same<T, unsigned long>::value ||
             std::is_same<T, long long>::value ||
             std::is_same<T, unsigned long long>::value ||
             std::is_same<T, float>::value || std::is_same<T, double>::value ||
             std::is_same<T, long double>::value ||
             std::is_same<T, const char*>::value),
        std::string>::type
    aformat(int data[8], T argument) {
      if (std::is_same<T, bool>::value) {
        return data_fmt(data, 4 * sizeof(bool), "b", argument);
      } else if (std::is_same<T, char>::value) {
        return data_fmt(data, 4 * sizeof(char), "c", argument);
      } else if (std::is_same<T, int>::value) {
        return data_fmt(data, 4 * sizeof(int), "d", argument);
      } else if (std::is_same<T, unsigned>::value) {
        return data_fmt(data, 4 * sizeof(unsigned), "u", argument);
      } else if (std::is_same<T, long>::value) {
        return data_fmt(data, 4 * sizeof(long), "ld", argument);
      } else if (std::is_same<T, unsigned long>::value) {
        return data_fmt(data, 4 * sizeof(unsigned long), "lu", argument);
      } else if (std::is_same<T, long long>::value) {
        return data_fmt(data, 4 * sizeof(long long), "lld", argument);
      } else if (std::is_same<T, unsigned long long>::value) {
        return data_fmt(data, 4 * sizeof(unsigned long long), "llu", argument);
      } else if (std::is_same<T, float>::value) {
        const int n = std::numeric_limits<float>::max_exponent10 + 20;
        return data_fmt(data, n, "f", argument);
      } else if (std::is_same<T, double>::value) {
        const int n = std::numeric_limits<double>::max_exponent10 + 20;
        return data_fmt(data, n, "f", argument);
      } else if (std::is_same<T, long double>::value) {
        const int n = std::numeric_limits<long double>::max_exponent10 + 20;
        return data_fmt(data, n, "lf", argument);
      } else if (std::is_same<T, const char*>::value) {
        return data_fmt(data, 255, "s", argument);
      }
      return std::string();
    }
    template <typename T>
    inline typename std::enable_if<
        !(has_format<T, std::string()>::value) &&
            has_stream<std::stringstream, T>::value &&
            !(std::is_same<T, bool>::value || std::is_same<T, char>::value ||
              std::is_same<T, int>::value || std::is_same<T, unsigned>::value ||
              std::is_same<T, long>::value ||
              std::is_same<T, unsigned long>::value ||
              std::is_same<T, long long>::value ||
              std::is_same<T, unsigned long long>::value ||
              std::is_same<T, float>::value || std::is_same<T, double>::value ||
              std::is_same<T, long double>::value ||
              std::is_same<T, const char*>::value),
        std::string>::type
    aformat(int data[8], T argument) {
      std::stringstream out;
      // TODO(Arden): Add add flags to stream, such that formatting requirements
      // are met.
      out << argument;
      return out.str();
    }

    template <typename T>
    inline
        typename std::enable_if<has_subscript<T, int>::value, std::string>::type
        asformat(int data[8], T argument) {
      if (data[7] == -1) {
        return aformat(data, argument);
      } else {
        return aformat(data, argument[data[7]]);
      }
    }
    template <typename T>
    inline typename std::enable_if<!(has_subscript<T, int>::value),
                                   std::string>::type
    asformat(int data[8], T argument) {
      return aformat(data, argument);
    }

    template <std::size_t I = 0, typename... Args>
    inline typename std::enable_if<I == sizeof...(Args), std::string>::type
    aiformat(std::size_t index, int data[8], std::tuple<Args...> args) {
      return std::string();
    }
    template <std::size_t I = 0, typename... Args>
        inline typename std::enable_if <
        I<sizeof...(Args), std::string>::type aiformat(
            std::size_t index, int data[8], std::tuple<Args...> args) {
      if (index == 0) {
        return asformat(data, std::get<I>(args));
      } else {
        return aiformat<I + 1, Args...>(index - 1, data, args);
      }
    }

    bool parse_argument(int data[8], std::string_view fmt) {
      for (std::size_t i = 0; i < 8; i++) {
        data[i] = -1;
      }
      if (fmt.find_first_of(':') != std::string_view::npos) {
        std::string_view index_fmt = fmt.substr(0, fmt.find_first_of(':'));
        if (index_fmt.size() != 0) {
          if (index_fmt.find_first_of('[') == std::string_view::npos) {
            data[0] = atoi(index_fmt.begin());
          } else {
            std::string_view subscript = index_fmt.substr(
                index_fmt.find_first_of('[') + 1,
                index_fmt.size() - index_fmt.find_first_of('[') - 2);
            index_fmt = index_fmt.substr(0, index_fmt.find_first_of('['));
            if (index_fmt.size() != 0) {
              data[0] = atoi(index_fmt.begin());
            }
            data[7] = atoi(subscript.begin());
          }
        }
        fmt = fmt.substr(fmt.find_first_of(':') + 1);
      } else if (fmt.size() != 0) {
        data[0] = atoi(fmt.begin());
        return true;
      } else {
        return true;
      }
      std::size_t fmt_index = 0;
      if (fmt.size() > 2 &&
          (fmt[1] == '<' || fmt[1] == '>' || fmt[1] == '=' || fmt[1] == '^')) {
        data[1] = int(fmt[0]);
        fmt_index += 1;
      }
      if (fmt[fmt_index] == '<' || fmt[fmt_index] == '>' ||
          fmt[fmt_index] == '=' || fmt[fmt_index] == '^') {
        if (fmt[fmt_index] == '<') data[2] = 0;
        if (fmt[fmt_index] == '>') data[2] = 1;
        if (fmt[fmt_index] == '=') data[2] = 2;
        if (fmt[fmt_index] == '^') data[2] = 3;
        fmt_index += 1;
        if (fmt_index >= fmt.size()) return true;
      }
      if (fmt[fmt_index] == '+' || fmt[fmt_index] == '-' ||
          fmt[fmt_index] == ' ') {
        if (fmt[fmt_index] == '+') data[3] = 0;
        if (fmt[fmt_index] == '-') data[3] = 1;
        if (fmt[fmt_index] == ' ') data[3] = 2;
        fmt_index += 1;
        if (fmt_index >= fmt.size()) return true;
      }
      if (fmt[fmt_index] == '0') {
        data[1] = int('0');
        fmt_index += 1;
        if (fmt_index >= fmt.size()) {
          return true;
        }
      }
      while (fmt_index < fmt.size() && isdigit(fmt[fmt_index])) {
        if (data[4] == -1) {
          data[4] = 0;
        }
        data[4] = (data[4] * 10) + (int(fmt[fmt_index]) - 48);
        fmt_index += 1;
      }
      if (fmt_index >= fmt.size()) {
        return true;
      }
      if (fmt[fmt_index] == '.') {
        fmt_index += 1;
        data[5] = 0;
        while (fmt_index < fmt.size() && isdigit(fmt[fmt_index])) {
          data[5] = (data[5] * 10) + (int(fmt[fmt_index]) - 48);
          fmt_index += 1;
        }
        if (fmt_index >= fmt.size()) {
          return true;
        }
      }
      if (fmt_index < fmt.size() - 1) {
        return false;
      }
      return true;
    }

    template <std::size_t I = 0, typename... Args>
    inline typename std::enable_if<I == sizeof...(Args), std::string>::type
    vsformat(std::string_view fmt, std::tuple<Args...> args) {
      return std::string();
    }
    template <std::size_t I = 0, typename... Args>
        inline typename std::enable_if <
        I<sizeof...(Args), std::string>::type vsformat(
            std::string_view fmt, std::tuple<Args...> args) {
      std::size_t arg_index = 0;
      std::size_t tuple_length = std::tuple_size<std::tuple<Args...>>::value;
      std::string res;
      std::string_view fmt_text = fmt;
      while (true) {
        std::string_view arg_fmt, rem_fmt;
        std::size_t pos = fmt_text.find_first_of('{');
        if (pos == std::string_view::npos) {
          res += fmt_text;
          break;
        }
        res += fmt_text.substr(0, pos);
        rem_fmt = fmt_text.substr(pos + 1);
        arg_fmt = fmt_text.substr(pos + 1, rem_fmt.find_first_of('}'));
        fmt_text = rem_fmt.substr(rem_fmt.find_first_of('}') + 1);
        int data[8];
        parse_argument(data, arg_fmt);
        if (data[0] != -1) {
          res += aiformat(std::size_t(data[0]), data, args);
        } else {
          res += aiformat(arg_index, data, args);
          arg_index++;
          if (arg_index >= tuple_length) {
            arg_index = 0;
          }
        }
      }
      return res;
    }
  }  // namespace

  template <typename... Args>
  inline std::string Format(std::string_view fmt, const Args&... args) {
    return vsformat(fmt, estl::variadic::unpack_tuple(args...));
  }

}  // namespace format
}  // namespace estl

#endif  // ESTL_FORMAT_HPP_
