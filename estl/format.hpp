#ifndef ESTL_FORMAT_HPP_
#define ESTL_FORMAT_HPP_

#include <stdio.h>
#include <iostream>

#include <stdarg.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>

#include "variadic.hpp"

namespace estl {
namespace format {

  namespace {
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
    inline typename std::enable_if<!std::is_same<TString, std::string>::value,
                                   TString>::type
    to_xstring(std::size_t n, const TChar* fmt, ...) {
      TChar* res = static_cast<TChar*>(malloc(sizeof(TChar) * n));
      va_list args;
      va_start(args, fmt);
      const int len = std::vsnprintf(res, n, fmt, args);
      va_end(args);
      return TString(res, len);
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
      std::stringstream out;
      out << argument;
      return out.str();
      // XXX Utilizing better and more efficient printf format, prefer this if
      // possilbe. Need to determin edgecases, inorder to allow backup stream or
      // default type nameing. if (std::is_same<T, int>::value) {
      
      //   return to_xstring<std::string>(4 * sizeof(int), "%d", argument);
      // } else if (std::is_same<T, unsigned>::value) {
      //   return to_xstring<std::string>(4 * sizeof(unsigned), "%u", argument);
      // } else if (std::is_same<T, long>::value) {
      //   return to_xstring<std::string>(4 * sizeof(long), "%ld", argument);
      // } else if (std::is_same<T, unsigned long>::value) {
      //   return to_xstring<std::string>(4 * sizeof(unsigned long), "%lu",
      //                                  argument);
      // } else if (std::is_same<T, long long>::value) {
      //   return to_xstring<std::string>(4 * sizeof(long long), "%lld",
      //   argument);
      // } else if (std::is_same<T, unsigned long long>::value) {
      //   return to_xstring<std::string>(4 * sizeof(unsigned long long),
      //   "%llu",
      //                                  argument);
      // } else if (std::is_same<T, float>::value) {
      //   return to_xstring<std::string>(4 * sizeof(float), "%f", argument);
      // } else if (std::is_same<T, double>::value) {
      //   return to_xstring<std::string>(4 * sizeof(double), "%f", argument);
      // } else if (std::is_same<T, long double>::value) {
      //   return to_xstring<std::string>(4 * sizeof(long double), "%Lf",
      //                                  argument);
      // }
      return std::string("");
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
      bool ret = 1;
      data[0] = -1;
      data[1] = -1;
      data[2] = -1;
      data[3] = 1;
      data[4] = 0;
      data[5] = 0;
      data[6] = -1;
      std::size_t split = fmt.find_first_of(':');
      std::string_view front = fmt.substr(0, split);
      std::string_view back = fmt.substr(split + 1);
      if (front.size() != 0) {
        bool good = true;
        for (std::string_view::const_iterator it = front.begin();
             it != front.end() && good == true; ++it) {
          if (!isdigit(*it)) {
            good = false;
          }
        }
        if (good == true) {
          data[0] = atoi(front.begin());
        } else {
          data[0] = -2;
          ret = false;
        }
      }
      std::size_t index = 0;
      if (back.size() > 2 && (back[1] == '<' || back[1] == '>' ||
                              back[1] == '=' || back[1] == '^')) {
        data[1] = int(back[0]);
        if (back[1] == '<') {
          data[2] = 0;
        } else if (back[1] == '>') {
          data[2] = 1;
        } else if (back[1] == '=') {
          data[2] = 2;
        } else if (back[1] == '^') {
          data[2] = 3;
        }
        index = 2;
      } else if (back[0] == '<' || back[0] == '>' || back[0] == '=' ||
                 back[0] == '^') {
        if (back[0] == '<') {
          data[2] = 0;
        } else if (back[0] == '>') {
          data[2] = 1;
        } else if (back[0] == '=') {
          data[2] = 2;
        } else if (back[0] == '^') {
          data[2] = 3;
        }
        index = 1;
      }
      unsigned int state = 0;
      while (index < back.size()) {
        if (state == 0 &&
            (back[index] == '+' || back[index] == '-' || back[index] == ' ')) {
          if (back[index] == '+') {
            data[3] = 0;
          } else if (back[index] == '-') {
            data[3] = 1;
          } else if (back[index] == ' ') {
            data[3] = 2;
          }
          state = 1;
        } else if (state <= 1 && back[index] == '0') {
          data[1] = 48;
          state = 2;
        } else if (state <= 2 && isdigit(back[index])) {
          data[4] = (data[4] * 10) + (static_cast<int>(back[index]) - 48);
        } else if (state <= 2 && back[index] == '.') {
          state = 3;
        } else if (state == 3 && isdigit(back[index])) {
          data[5] = (data[5] * 10) + (static_cast<int>(back[index]) - 48);
        }
        index++;
      }
      return ret;
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
      std::size_t first_open = fmt.find_first_of('{');
      std::string_view remain = fmt.substr(first_open);
      std::size_t first_close = remain.find_first_of('}');
      remain = remain.substr(first_close + 1);
      std::string_view argument = fmt.substr(first_open + 1, first_close - 1);
      std::string output = std::string(fmt.substr(0, first_open));
      std::cout << output << "|" << argument << "|" << remain << "\n";
      int data[7];
      parse_argument(data, argument);
      if (data[0] != -1 &&
          data[0] < std::tuple_size<std::tuple<Args...>>::value) {
        output += aiformat(std::size_t(data[0]), data, args);
      } else {
        output += aformat(data, std::get<I>(args));
      }
      // std::string_view remain = fmt.substr(fmt.find_first_of('{') + 1);
      // std::string_view arg_name = remain.substr(
      //     0, std::max(remain.find_first_of(':'), remain.find_first_of('}')));
      // std::string_view arg_fmt =
      //     remain.substr(std::max(std::size_t(0), remain.find_first_of(':')),
      //                   remain.find_first_of('}'));
      // std::cout << arg_name << ":";
      // std::cout << arg_fmt << "\n";

      // return std::string(output) +
      //        std::string(vsformat<I + 1, Args...>(
      //            remain.substr(remain.find_first_of('}') + 1), args));
      return output;
    }
  }  // namespace

  template <typename... Args>
  inline std::string Format(std::string_view fmt, const Args&... args) {
    return vsformat(fmt, estl::variadic::unpack_tuple(args...));
  }

}  // namespace format
}  // namespace estl

#endif  // ESTL_FORMAT_HPP_
