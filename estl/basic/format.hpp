#ifndef ESTL_BASIC_FORMAT_HPP_
#define ESTL_BASIC_FORMAT_HPP_

#include <cstdarg>

#include <string>

namespace estl {
namespace base {
  template <typename _TString = std::string,
            typename _TChar = typename _TString::value_type>
  inline _TString format(const _TChar* fmt, ...) {
    _TChar* buffer = static_cast<_TChar*>(malloc(sizeof(_TChar) * 255));
    va_list args;
    va_start(args, fmt);
    const int len = std::vsnprintf(buffer, 255, fmt, args);
    va_end(args);
    _TString res(buffer, len);
    delete[] buffer;
    return res;
  }
}  // namespace base
}  // namespace estl

#endif  // ESTL_BASIC_FORMAT_HPP_
