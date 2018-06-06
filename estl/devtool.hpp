#ifndef ESTL_DEVTOOL_HPP_
#define ESTL_DEVTOOL_HPP_

#include <string>

namespace estl {
constexpr inline uint16_t parse_char(std::string_view chars) noexcept {
  uint16_t ret = 0;
  for (auto ch : chars) {
    if (ch == ' ') continue;
    ret = (10 * ret) + (ch - 48);
  }
  return ret;
}
constexpr inline uint16_t parse_mon(std::string_view chars) noexcept {
  if (chars[0] == 'A') {
    if (chars[1] == 'p') {
      return 3;
    } else {
      return 7;
    }
  } else if (chars[0] == 'D') {
    return 11;
  } else if (chars[0] == 'F') {
    return 1;
  } else if (chars[0] == 'J') {
    if (chars[1] == 'a') {
      return 0;
    } else if (chars[2] == 'l') {
      return 6;
    } else {
      return 5;
    }
  } else if (chars[0] == 'M') {
    if (chars[2] == 'r') {
      return 2;
    } else {
      return 4;
    }
  } else if (chars[0] == 'N') {
    return 10;
  } else if (chars[0] == 'O') {
    return 9;
  } else {
    return 8;
  }
}

constexpr void TODO(std::string_view date) {
  std::string_view cdate(__DATE__);
  uint16_t tyear = parse_char(date.substr(7, 4)),
           tmon = parse_mon(date.substr(0, 3)),
           tday = parse_char(date.substr(4, 2));
  uint16_t cyear = parse_char(cdate.substr(7, 4)),
           cmon = parse_mon(cdate.substr(0, 3)),
           cday = parse_char(cdate.substr(4, 2));
  if (cyear > tyear ||
      (cyear == tyear &&
       (cmon > tmon || (cmon == tmon && (cday > tday || cday == tday))))) {
    printf("NOPE\n");
#error "NOPE"
  }
  printf("%u/%u/%u %u/%u/%u", tday, tmon, tyear, cday, cmon, cyear);
}
}  // namespace estl

#endif  // ESTL_DEVTOOL_HPP_
