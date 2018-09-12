#ifndef ESTL_FUZZ_HPP_
#define ESTL_FUZZ_HPP_

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <iostream>

namespace estl {
namespace fuzz {
  std::size_t Levenshtein(const std::string_view& lhs,
                          const std::string_view& rhs,
                          bool case_sensitive = true) {
    std::size_t lhs_len = lhs.size();
    std::size_t rhs_len = rhs.size();
    std::size_t column[lhs_len + 1];
    for (std::size_t y = 1; y <= lhs_len; ++y) {
      column[y] = y;
    }
    for (std::size_t x = 1; x <= rhs_len; ++x) {
      column[0] = x;
      for (std::size_t y = 1, last_diag = x - 1; y <= lhs_len; ++y) {
        std::size_t old_diag = column[y];
        if (case_sensitive) {
          column[y] =
              std::min({column[y] + 1, column[y - 1] + 1,
                        last_diag + (lhs[y - 1] == rhs[x - 1] ? 0 : 1)});
        } else {
          column[y] = std::min(
              {column[y] + 1, column[y - 1] + 1,
               last_diag + (std::tolower(lhs[y - 1]) == std::tolower(rhs[x - 1])
                                ? 0
                                : 1)});
        }
        last_diag = old_diag;
      }
    }
    return column[lhs_len];
  }
  std::size_t Manhattin(const std::string_view& lhs,
                        const std::string_view& rhs) {
    std::map<char, std::pair<uint8_t, uint8_t>> key_map = {
        {'`', {0, 0}},  {'~', {0, 0}},   {'1', {1, 0}},   {'!', {1, 0}},
        {'2', {2, 0}},  {'@', {2, 0}},   {'3', {3, 0}},   {'#', {3, 0}},
        {'4', {4, 0}},  {'$', {4, 0}},   {'5', {5, 0}},   {'%', {5, 0}},
        {'6', {6, 0}},  {'^', {6, 0}},   {'7', {7, 0}},   {'&', {7, 0}},
        {'8', {8, 0}},  {'*', {8, 0}},   {'9', {9, 0}},   {'(', {9, 0}},
        {'0', {10, 0}}, {')', {10, 0}},  {'\t', {0, 1}},  {'q', {1, 1}},
        {'w', {2, 1}},  {'e', {3, 1}},   {'r', {4, 1}},   {'t', {5, 1}},
        {'y', {6, 1}},  {'u', {7, 1}},   {'i', {8, 1}},   {'o', {9, 1}},
        {'p', {10, 1}}, {'[', {11, 1}},  {'{', {11, 1}},  {']', {12, 1}},
        {'}', {12, 1}}, {'\\', {13, 1}}, {'|', {13, 1}},  {'a', {1, 2}},
        {'s', {2, 2}},  {'d', {3, 2}},   {'f', {4, 2}},   {'g', {5, 2}},
        {'h', {6, 2}},  {'j', {7, 2}},   {'k', {8, 2}},   {'l', {9, 2}},
        {';', {10, 2}}, {':', {10, 2}},  {'\'', {11, 2}}, {'"', {11, 2}},
        {'z', {1, 3}},  {'x', {2, 3}},   {'c', {3, 3}},   {'v', {4, 3}},
        {'b', {5, 3}},  {'n', {6, 3}},   {'m', {7, 3}},   {',', {8, 3}},
        {'<', {8, 3}},  {'.', {9, 3}},   {'>', {9, 3}},   {'/', {10, 3}},
        {'?', {10, 3}}, {' ', {5, 4}}};
    std::size_t lhs_len = lhs.size();
    std::size_t rhs_len = rhs.size();
    std::size_t column[lhs_len + 1];
    for (std::size_t y = 1; y <= lhs_len; ++y) {
      column[y] = y;
    }
    for (std::size_t x = 1; x <= rhs_len; ++x) {
      column[0] = x;
      for (std::size_t y = 1, last_diag = x - 1; y <= lhs_len; ++y) {
        std::size_t old_diag = column[y];
        std::size_t value = 0;
        if (std::tolower(lhs[y - 1]) != std::tolower(rhs[x - 1])) {
          std::pair<uint8_t, uint8_t> key_l, key_r;
          key_l = key_map[std::tolower(lhs[y - 1])];
          key_r = key_map[std::tolower(rhs[x - 1])];
          value = static_cast<std::size_t>(key_l.first > key_r.first
                                               ? key_l.first - key_r.first
                                               : key_r.first - key_l.first) +
                  static_cast<std::size_t>(key_l.second > key_r.second
                                               ? key_l.second - key_r.second
                                               : key_r.second - key_l.second);
        }
        column[y] =
            std::min({column[y] + 1, column[y - 1] + 1, last_diag + value});
        last_diag = old_diag;
      }
    }
    return column[lhs_len];
  }
  std::size_t LevenshteinCaseSensitive(const std::string_view& lhs,
                                       const std::string_view& rhs) {
    return Levenshtein(lhs, rhs, true);
  }
  std::size_t LevenshteinCaseInsensitive(const std::string_view& lhs,
                                         const std::string_view& rhs) {
    return Levenshtein(lhs, rhs, false);
  }
  std::size_t ManhattinCaseSensitive(const std::string_view& lhs,
                                     const std::string_view& rhs) {
    return Manhattin(lhs, rhs);
  }
  std::size_t ManhattinCaseInsensitive(const std::string_view& lhs,
                                       const std::string_view& rhs) {
    return Manhattin(lhs, rhs);
  }
  template <std::size_t N>
  std::array<std::string, N> Fuzz(
      const std::string& src, const std::vector<std::string>& data,
      const std::function<std::size_t(const std::string_view&,
                                      const std::string_view&)>& Dist =
          LevenshteinCaseSensitive) {
    std::array<std::pair<std::size_t, std::string>, N> results;
    results.fill({10000, ""});
    for (auto& it : data) {
      // std::size_t dist = Levenshtein(src, it, false);
      std::size_t dist = Dist(src, it);
      for (std::size_t i = 0; i < N; ++i) {
        if (dist < results[i].first) {
          for (std::size_t j = N - 1; j > i; --j) {
            results[j] = results[j - 1];
          }
          results[i] = {dist, it};
          break;
        }
      }
    }
    std::array<std::string, N> words;
    for (std::size_t i = 0; i < N; ++i) {
      words[i] = results[i].second;
    }
    return words;
  }
}  // namespace fuzz
}  // namespace estl

#endif  // ESTL_FUZZ_HPP_
