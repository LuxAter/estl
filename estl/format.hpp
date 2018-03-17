#ifndef ESTL_FORMAT_HPP_
#define ESTL_FORMAT_HPP_

#include <stdio.h>
#include <iostream>

#include <cxxabi.h>
#include <stdarg.h>

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

#include "variadic.hpp"

// TODO(Arden): Add type conversion checks, and type conversion.

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
    template <class T>
    std::string type_name() {
      typedef typename std::remove_reference<T>::type TR;
      std::unique_ptr<char, void (*)(void*)> own(
#ifndef _MSC_VER
          abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
          nullptr,
#endif
          std::free);
      std::string r = own != nullptr ? own.get() : typeid(TR).name();
      if (std::is_const<TR>::value) r += " const";
      if (std::is_volatile<TR>::value) r += " volatile";
      if (std::is_lvalue_reference<T>::value)
        r += "&";
      else if (std::is_rvalue_reference<T>::value)
        r += "&&";
      return r;
    }

    template <typename T>
    inline typename std::enable_if<std::is_convertible<T, long long>::value,
                                   bool>::type
    negetive_int(T argument) {
      return static_cast<long long>(argument) < 0;
    }
    template <typename T>
    inline typename std::enable_if<!std::is_convertible<T, long long>::value,
                                   bool>::type
    negetive_int(T argument) {
      return false;
    }
    template <typename T>
    inline typename std::enable_if<std::is_same<T, int>::value, T>::type
    make_positive(T argument) {
      if (negetive_int(argument) == true) {
        return (-1 * argument);
      } else {
        return argument;
      }
    }
    template <typename T>
    inline typename std::enable_if<std::is_same<T, long>::value, T>::type
    make_positive(T argument) {
      if (negetive_int(argument) == true) {
        return (-1 * argument);
      } else {
        return argument;
      }
    }
    template <typename T>
    inline typename std::enable_if<std::is_same<T, long long>::value, T>::type
    make_positive(T argument) {
      if (negetive_int(argument) == true) {
        return (-1 * argument);
      } else {
        return argument;
      }
    }
    template <typename T>
    inline typename std::enable_if<!(std::is_same<T, long long>::value ||
                                     std::is_same<T, long>::value ||
                                     std::is_same<T, int>::value),
                                   T>::type
    make_positive(T argument) {
      return argument;
    }

    template <typename TString, typename TChar = typename TString::value_type>
    inline TString to_xstring(std::size_t n, const TChar* fmt, ...) {
      TChar* res;
      if (n != 0) {
        res = static_cast<TChar*>(malloc(sizeof(TChar) * (n + 255)));
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

    template <typename TString, typename T,
              typename TChar = typename TString::value_type>
    inline typename std::enable_if<
        std::is_convertible<T, unsigned long long>::value, TString>::type
    to_binary(std::size_t n, const TChar* fmt, T argument) {
      std::bitset<sizeof(T) * 8> bits(make_positive(argument));
      if (negetive_int(argument) == true) {
        bits.set((sizeof(T) * 8) - 1);
      }
      std::cout << "FMT: " << fmt << "\n";
      return to_xstring<TString, TChar>((sizeof(T) * 8) + n, fmt,
                                        bits.to_string().c_str());
    }
    template <typename TString, typename T,
              typename TChar = typename TString::value_type>
    inline typename std::enable_if<
        !std::is_convertible<T, unsigned long long>::value, TString>::type
    to_binary(std::size_t n, const TChar* fmt, T argument) {
      return TString();
    }

    template <typename T>
    inline std::string data_fmt(int data[8], std::size_t n,
                                std::string_view type, T args) {
      std::string fmt = "%";
      if (type[0] == '-') {
        fmt = '-' + fmt;
        type = type.substr(1);
      }
      if (data[3] == 0) fmt += '+';
      if (data[3] == 1) fmt += '-';
      if (data[3] == 2) fmt += ' ';
      if (data[1] == int('0')) fmt += '0';
      if (data[4] != -1 && (data[1] == int('0') || data[1] == -1) &&
          data[2] == -1)
        fmt += std::to_string(data[4]);
      if (data[5] != -1) fmt += '.' + std::to_string(data[5]);
      fmt += std::string(type);
      if (fmt.back() == 'b') {
        fmt.back() = 's';
        fmt = to_binary<std::string>(n, fmt.c_str(), args);
      } else {
        fmt = to_xstring<std::string>(n, fmt.c_str(), args);
      }
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
    inline typename std::enable_if<
        has_format<T, std::string(char, unsigned, unsigned, int, int)>::value,
        std::string>::type
    aformat(int data[8], T argument) {
      if (data[1] == -1) {
        data[1] = int(' ');
      }
      return argument.Format(data[1], data[2], data[3], data[4], data[5]);
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
      // TODO(Arden): Enable support for negetive hex, and oct.
      // TODO(Arden): Enable binary format.
      if (std::is_same<T, bool>::value) {
        return data_fmt(data, 4 * 5 * sizeof(char), "s",
                        argument ? "true" : "false");
      } else if (std::is_same<T, char>::value) {
        return data_fmt(data, 4 * sizeof(char), "c", argument);
      } else if (std::is_same<T, int>::value) {
        if (data[6] == -1) {
          return data_fmt(data, 4 * sizeof(int), "d", argument);
        } else if (data[6] == 88) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(int), "-X",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(int), "X", argument);
          }
        } else if (data[6] == 98) {
          return data_fmt(data, 4 * sizeof(int), "b", argument);
        } else if (data[6] == 100) {
          return data_fmt(data, 4 * sizeof(int), "d", argument);
        } else if (data[6] == 111) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(int), "-o",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(int), "o", argument);
          }
        } else if (data[6] == 120) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(int), "-x",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(int), "x", argument);
          }
        } else {
          return data_fmt(data, 4 * sizeof(int), "d", argument);
        }
      } else if (std::is_same<T, unsigned>::value) {
        if (data[6] == -1) {
          return data_fmt(data, 4 * sizeof(unsigned), "u", argument);
        } else if (data[6] == 88) {
          return data_fmt(data, 4 * sizeof(unsigned), "X", argument);
        } else if (data[6] == 98) {
          return data_fmt(data, 4 * sizeof(unsigned), "b", argument);
        } else if (data[6] == 100) {
          return data_fmt(data, 4 * sizeof(unsigned), "u", argument);
        } else if (data[6] == 111) {
          return data_fmt(data, 4 * sizeof(unsigned), "o", argument);
        } else if (data[6] == 120) {
          return data_fmt(data, 4 * sizeof(unsigned), "x", argument);
        } else {
          return data_fmt(data, 4 * sizeof(unsigned), "u", argument);
        }
      } else if (std::is_same<T, long>::value) {
        if (data[6] == -1) {
          return data_fmt(data, 4 * sizeof(long), "ld", argument);
        } else if (data[6] == 88) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(long), "-lH",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(long), "lH", argument);
          }
        } else if (data[6] == 98) {
          return data_fmt(data, 4 * sizeof(long), "b", argument);
        } else if (data[6] == 100) {
          return data_fmt(data, 4 * sizeof(long), "ld", argument);
        } else if (data[6] == 111) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(long), "-lo",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(long), "lo", argument);
          }
        } else if (data[6] == 120) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(long), "-lh",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(long), "lh", argument);
          }
        } else {
          return data_fmt(data, 4 * sizeof(long), "ld", argument);
        }
      } else if (std::is_same<T, unsigned long>::value) {
        if (data[6] == -1) {
          return data_fmt(data, 4 * sizeof(unsigned long), "lu", argument);
        } else if (data[6] == 88) {
          return data_fmt(data, 4 * sizeof(unsigned long), "lX", argument);
        } else if (data[6] == 98) {
          return data_fmt(data, 4 * sizeof(unsigned long), "b", argument);
        } else if (data[6] == 100) {
          return data_fmt(data, 4 * sizeof(unsigned long), "lu", argument);
        } else if (data[6] == 111) {
          return data_fmt(data, 4 * sizeof(unsigned long), "lo", argument);
        } else if (data[6] == 120) {
          return data_fmt(data, 4 * sizeof(unsigned long), "lx", argument);
        } else {
          return data_fmt(data, 4 * sizeof(unsigned long), "lu", argument);
        }
      } else if (std::is_same<T, long long>::value) {
        return data_fmt(data, 4 * sizeof(long long), "lld", argument);
        if (data[6] == -1) {
          return data_fmt(data, 4 * sizeof(long long), "lld", argument);
        } else if (data[6] == 88) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(long long), "-llH",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(long long), "llH", argument);
          }
        } else if (data[6] == 98) {
          return data_fmt(data, 4 * sizeof(long long), "b", argument);
        } else if (data[6] == 100) {
          return data_fmt(data, 4 * sizeof(long long), "lld", argument);
        } else if (data[6] == 111) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(long long), "-llo",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(long long), "llo", argument);
          }
        } else if (data[6] == 120) {
          if (negetive_int(argument) == true) {
            return data_fmt(data, 4 * sizeof(long long), "-llh",
                            make_positive(argument));
          } else {
            return data_fmt(data, 4 * sizeof(long long), "llh", argument);
          }
        } else {
          return data_fmt(data, 4 * sizeof(long long), "lld", argument);
        }
      } else if (std::is_same<T, unsigned long long>::value) {
        if (data[6] == -1) {
          return data_fmt(data, 4 * sizeof(unsigned long long), "llu",
                          argument);
        } else if (data[6] == 88) {
          return data_fmt(data, 4 * sizeof(unsigned long long), "llX",
                          argument);
        } else if (data[6] == 98) {
          return data_fmt(data, 4 * sizeof(unsigned long long), "b", argument);
        } else if (data[6] == 100) {
          return data_fmt(data, 4 * sizeof(unsigned long long), "llu",
                          argument);
        } else if (data[6] == 111) {
          return data_fmt(data, 4 * sizeof(unsigned long long), "llo",
                          argument);
        } else if (data[6] == 120) {
          return data_fmt(data, 4 * sizeof(unsigned long long), "llx",
                          argument);
        } else {
          return data_fmt(data, 4 * sizeof(unsigned long long), "llu",
                          argument);
        }
      } else if (std::is_same<T, float>::value) {
        const int n = std::numeric_limits<float>::max_exponent10 + 20;
        if (data[6] == -1) {
          return data_fmt(data, n, "g", argument);
        } else if (data[6] == 69) {
          return data_fmt(data, n, "E", argument);
        } else if (data[6] == 70) {
          return data_fmt(data, n, "F", argument);
        } else if (data[6] == 71) {
          return data_fmt(data, n, "G", argument);
        } else if (data[6] == 101) {
          return data_fmt(data, n, "e", argument);
        } else if (data[6] == 102) {
          return data_fmt(data, n, "f", argument);
        } else if (data[6] == 103) {
          return data_fmt(data, n, "g", argument);
        } else {
          return data_fmt(data, n, "g", argument);
        }
      } else if (std::is_same<T, double>::value) {
        const int n = std::numeric_limits<double>::max_exponent10 + 20;
        if (data[6] == -1) {
          return data_fmt(data, n, "g", argument);
        } else if (data[6] == 69) {
          return data_fmt(data, n, "E", argument);
        } else if (data[6] == 70) {
          return data_fmt(data, n, "F", argument);
        } else if (data[6] == 71) {
          return data_fmt(data, n, "G", argument);
        } else if (data[6] == 101) {
          return data_fmt(data, n, "e", argument);
        } else if (data[6] == 102) {
          return data_fmt(data, n, "f", argument);
        } else if (data[6] == 103) {
          return data_fmt(data, n, "g", argument);
        } else {
          return data_fmt(data, n, "g", argument);
        }
      } else if (std::is_same<T, long double>::value) {
        const int n = std::numeric_limits<long double>::max_exponent10 + 20;
        if (data[6] == -1) {
          return data_fmt(data, n, "lg", argument);
        } else if (data[6] == 69) {
          return data_fmt(data, n, "lE", argument);
        } else if (data[6] == 70) {
          return data_fmt(data, n, "lF", argument);
        } else if (data[6] == 71) {
          return data_fmt(data, n, "lG", argument);
        } else if (data[6] == 101) {
          return data_fmt(data, n, "le", argument);
        } else if (data[6] == 102) {
          return data_fmt(data, n, "lf", argument);
        } else if (data[6] == 103) {
          return data_fmt(data, n, "lg", argument);
        } else {
          return data_fmt(data, n, "lg", argument);
        }
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
      int print_width = data[4];
      if (data[1] == -1) {
        data[1] = int(' ');
      }
      out << std::setfill(char(data[1]));
      if (data[2] == 1) {
        out << std::left;
      } else if (data[2] == 2) {
        out << std::internal;
      }
      if (print_width > -1 && data[2] != 3) {
        out << std::setw(print_width);
      }
      if (data[5] != -1) {
        out << std::setprecision(data[5]);
      }
      out << argument;
      if (data[2] == 3) {
        std::string out_str = out.str();
        return std::string(std::floor((print_width - out_str.size()) / 2.0),
                           data[1]) +
               out_str +
               std::string(std::ceil((print_width - out_str.size()) / 2.0),
                           data[1]);
      }
      return out.str();
    }

    template <typename T, typename U>
    inline typename std::enable_if<std::is_convertible<T, U>::value,
                                   std::string>::type
    acformat(int data[8], T argument) {
      return aformat(data, U(argument));
    }
    template <typename T, typename U>
    inline typename std::enable_if<!std::is_convertible<T, U>::value,
                                   std::string>::type
    acformat(int data[8], T argument) {
      throw std::invalid_argument(
          "argument index (which is " + std::to_string(data[0]) + ") of type " +
          type_name<T>() + " is not convertable to type of " + type_name<U>());
    }

    template <typename T>
    std::string acdformat(int data[8], T argument) {
      if (data[6] == -1 || data[6] == 115) {
        return aformat(data, argument);
      } else if (data[6] == 37 || data[6] == 69 || data[6] == 70 ||
                 data[6] == 71 || data[6] == 101 || data[6] == 102 ||
                 data[6] == 103) {
        if (std::is_same<T, float>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, double>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, long double>::value == true) {
          return aformat(data, argument);
        } else {
          return acformat<T, double>(data, argument);
        }
      } else if (data[6] == 88 || data[6] == 98 || data[6] == 100 ||
                 data[6] == 111 || data[6] == 120) {
        if (std::is_same<T, int>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, unsigned>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, long>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, unsigned long>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, long long>::value == true) {
          return aformat(data, argument);
        } else if (std::is_same<T, unsigned long long>::value == true) {
          return aformat(data, argument);
        } else {
          return acformat<T, int>(data, argument);
        }
      } else if (data[6] == 99) {
        if (std::is_same<T, char>::value == true) {
          return aformat(data, argument);
        } else {
          return acformat<T, char>(data, argument);
        }
      } else {
        return std::string();
      }
    }

    template <typename T>
    inline
        typename std::enable_if<has_subscript<T, int>::value, std::string>::type
        asformat(int data[8], T argument) {
      if (data[7] == -1) {
        return acdformat(data, argument);
      } else {
        return acdformat(data, argument[data[7]]);
      }
    }
    template <typename T>
    inline typename std::enable_if<!(has_subscript<T, int>::value),
                                   std::string>::type
    asformat(int data[8], T argument) {
      if (data[7] != -1) {
        throw std::invalid_argument(
            "argument index (which is " + std::to_string(data[0]) +
            ") of type " + type_name<T>() +
            " is not subscriptable, but format string requested subscript");
      }
      return acdformat(data, argument);
    }

    template <std::size_t I = 0, typename... Args>
    inline typename std::enable_if<I == sizeof...(Args), std::string>::type
    aiformat(std::size_t index, int data[8], std::tuple<Args...> args) {
      throw std::out_of_range("argument index (which is " +
                              std::to_string(index) +
                              ") >= argument count (which is " +
                              std::to_string(sizeof...(Args)) + ")");
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
        if (fmt.find_first_of('[') == std::string_view::npos) {
          data[0] = atoi(fmt.begin());
        } else {
          std::string_view subscript =
              fmt.substr(fmt.find_first_of('[') + 1,
                         fmt.size() - fmt.find_first_of('[') - 2);
          fmt = fmt.substr(0, fmt.find_first_of('['));
          if (fmt.size() != 0) {
            data[0] = atoi(fmt.begin());
          }
          data[7] = atoi(subscript.begin());
        }
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
      if (fmt_index >= fmt.size()) {
        return true;
      }
      if ((fmt[fmt_index] == 37) ||
          (fmt[fmt_index] >= 69 && fmt[fmt_index] <= 71) ||
          (fmt[fmt_index] == 88) ||
          (fmt[fmt_index] >= 98 && fmt[fmt_index] <= 103) ||
          (fmt[fmt_index] == 111) || (fmt[fmt_index] == 115) ||
          (fmt[fmt_index] == 120)) {
        data[6] = fmt[fmt_index];
        fmt_index++;
      }
      if (fmt_index < fmt.size()) {
        return false;
      }
      return true;
    }

    // template <std::size_t I = 0, typename... Args>
    // inline typename std::enable_if<I == sizeof...(Args), std::string>::type
    // vsformat(std::string_view fmt, std::tuple<Args...> args) {
    //   return std::string();
    // }
    // template <std::size_t I = 0, typename... Args>
    //     inline typename std::enable_if <
    //     I<sizeof...(Args), std::string>::type vsformat(
    template <typename... Args>
    inline std::string vsformat(std::string_view fmt,
                                std::tuple<Args...> args) {
      std::size_t arg_index = 0;
      const std::size_t tuple_length =
          std::tuple_size<std::tuple<Args...>>::value;
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
        bool parse_res = parse_argument(data, arg_fmt);
        if (parse_res == false) {
          throw std::invalid_argument("Format string specifier (which is \"" +
                                      std::string(arg_fmt) +
                                      "\") is of an invalid format");
        }
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
