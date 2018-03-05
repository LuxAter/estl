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

namespace estl {
namespace format {

  namespace {
    template <typename S, typename T>
    struct is_streamable {
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
      // XXX Better to use dynamic sizing, not this forced to 256.
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
    inline std::string data_fmt(int data[7], std::size_t n,
                                std::string_view type, T args) {
      std::string fmt = "%";
      if (data[3] == 0) fmt += '+';
      if (data[3] == 1) fmt += '-';
      if (data[3] == 2) fmt += ' ';
      if (data[1] == int('0')) fmt += '0';
      if (data[4] != -1 && (data[1] == int('0') || data[1] == -1) &&
          data[1] == -1 && data[2] == -1)
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
          fmt = std::string(data[4] - fmt.size(), data[1]) + fmt;  // TODO
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
    aformat(int data[7], T argument) {
      return argument.Format();
    }
    template <typename T>
    inline typename std::enable_if<!(has_format<T, std::string()>::value),
                                   std::string>::type
    aformat(int data[7], T argument) {
      std::string fmt = "%";
      // XXX Utilizing better and more efficient printf format, prefer this if
      // possilbe. Need to determin edgecases, inorder to allow backup stream
      // or default type nameing.
      std::string res;
      if (std::is_same<T, int>::value) {
        res = to_xstring<std::string>(4 * sizeof(int), "%d", argument);
      } else if (std::is_same<T, unsigned>::value) {
        res = to_xstring<std::string>(4 * sizeof(unsigned), "%u", argument);
      } else if (std::is_same<T, long>::value) {
        res = to_xstring<std::string>(4 * sizeof(long), "%ld", argument);
      } else if (std::is_same<T, unsigned long>::value) {
        res =
            to_xstring<std::string>(4 * sizeof(unsigned long), "%lu", argument);
      } else if (std::is_same<T, long long>::value) {
        res = to_xstring<std::string>(4 * sizeof(long long), "%lld", argument);
      } else if (std::is_same<T, unsigned long long>::value) {
        res = to_xstring<std::string>(4 * sizeof(unsigned long long), "%llu",
                                      argument);
      } else if (std::is_same<T, float>::value) {
        const int n = std::numeric_limits<float>::max_exponent10 + 20;
        res = to_xstring<std::string>(n, "%f", argument);
      } else if (std::is_same<T, double>::value) {
        const int n = std::numeric_limits<double>::max_exponent10 + 20;
        // std::cout << generate_fmt(data, "f") << "\n";
        res = data_fmt(data, n, "f", argument);
        // res = to_xstring<std::string>(n, generate_fmt(data, "f").c_str(),
        //                               argument);
      } else if (std::is_same<T, long double>::value) {
        const int n = std::numeric_limits<long double>::max_exponent10 + 20;
        res = to_xstring<std::string>(n, "%Lf", argument);
      } else if (std::is_same<T, const char*>::value) {
        res = to_xstring<std::string>(0, "%s", argument);
      }
      return res;
    }

    template <std::size_t I = 0, typename... Args>
    inline typename std::enable_if<I == sizeof...(Args), std::string>::type
    aiformat(std::size_t index, int data[7], std::tuple<Args...> args) {
      return std::string();
    }
    template <std::size_t I = 0, typename... Args>
        inline typename std::enable_if <
        I<sizeof...(Args), std::string>::type aiformat(
            std::size_t index, int data[7], std::tuple<Args...> args) {
      if (index == 0) {
        return aformat(data, std::get<I>(args));
      } else {
        return aiformat<I + 1, Args...>(index - 1, data, args);
      }
    }

    bool parse_argument(int data[7], std::string_view fmt) {
      for (std::size_t i = 0; i < 7; i++) {
        data[i] = -1;
      }
      if (fmt.find_first_of(':') != std::string_view::npos) {
        std::string_view index_fmt = fmt.substr(0, fmt.find_first_of(':'));
        if (index_fmt.size() != 0) {
          data[0] = atoi(index_fmt.begin());
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
      std::cout << fmt << "\n";
      for (int i = 0; i < fmt.size(); i++) {
        std::cout << i % 10;
      }
      std::cout << "\n";
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
        int data[7];
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
      // while (index < fmt.size() || arg_index < tuple_length) {
      //   std::size_t pos = fmt_text.find_first_of('{');
      //   if (pos != std::string_view::npos) {
      //     index += pos + 1;
      //   } else {
      //     break;
      //   }
      //   std::cout << index << ", " << pos << "\n";
      //   res += fmt.substr(index - pos - 1, pos);
      //   std::cout << fmt_text << "<\n";
      //   fmt_text = fmt.substr(index);
      //   std::cout << fmt_text << "<<\n";
      //   std::string_view arg_fmt =
      //       fmt.substr(index, fmt_text.find_first_of('}'));
      //   fmt_text = fmt.substr(index + fmt_text.find_first_of('}') + 1);
      //   std::cout << fmt_text << "<<<\n";
      //   // std::cout << ">" << arg_fmt << "<\n";
      //   int data[7];
      //   parse_argument(data, arg_fmt);
      //   printf("%d, %d, %d, %d, %d, %d\n", data[0], data[1], data[2],
      //   data[3],
      //          data[4], data[5], data[6]);
      //   // res += std::string(fmt_text.substr(0, index - 1));
      // }
      // if(index != fmt.size()){
      //   // res += fmt.substr(index + fmt_text.find_first_of('}') + 1);
      // }
      return res;
      // std::size_t first_open = fmt.find_first_of('{');
      // std::string_view remain = fmt.substr(first_open);
      // std::size_t first_close = remain.find_first_of('}');
      // remain = remain.substr(first_close + 1);
      // std::string_view argument = fmt.substr(first_open + 1, first_close -
      // 1); std::string output = std::string(fmt.substr(0, first_open));
      // std::cout << output << "|" << argument << "|" << remain << "\n";
      // int data[7];
      // parse_argument(data, argument);
      // if (data[0] != -1 &&
      //     data[0] < std::tuple_size<std::tuple<Args...>>::value) {
      //   output += aiformat(std::size_t(data[0]), data, args);
      // } else {
      //   output += aformat(data, std::get<I>(args));
      // }
      // std::string_view remain = fmt.substr(fmt.find_first_of('{') + 1);
      // std::string_view arg_name = remain.substr(
      //     0, std::max(remain.find_first_of(':'),
      //     remain.find_first_of('}')));
      // std::string_view arg_fmt =
      //     remain.substr(std::max(std::size_t(0),
      //     remain.find_first_of(':')),
      //                   remain.find_first_of('}'));
      // std::cout << arg_name << ":";
      // std::cout << arg_fmt << "\n";

      // return std::string(output) +
      //        std::string(vsformat<I + 1, Args...>(
      //            remain.substr(remain.find_first_of('}') + 1), args));
      // return output;
    }
  }  // namespace

  template <typename... Args>
  inline std::string Format(std::string_view fmt, const Args&... args) {
    return vsformat(fmt, estl::variadic::unpack_tuple(args...));
  }

}  // namespace format
}  // namespace estl

#endif  // ESTL_FORMAT_HPP_
