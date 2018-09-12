#ifndef ESTL_FUZZ_HPP_
#define ESTL_FUZZ_HPP_

#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cmath>

#include <iostream>

namespace estl {
namespace fuzz {
  std::size_t Levenshtein(const std::string_view& lhs,
                          const std::string_view& rhs) {
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
        column[y] = std::min({column[y] + 1, column[y - 1] + 1,
                              last_diag + (lhs[y - 1] == rhs[x - 1] ? 0 : 1)});
        last_diag = old_diag;
      }
    }
    return column[lhs_len];
  }
  template <std::size_t N>
  std::array<std::string, N> Fuzz(const std::string& src,
      const std::vector<std::string>& data) {
    std::array<std::pair<std::size_t, std::string>, N> results;
    results.fill({10000, ""});
    for(auto &it : data){
      std::size_t dist = Levenshtein(src, it);
      for(std::size_t i = 0; i < N; ++i){
        if (dist < results[i].first){
          for(std::size_t j = N - 1; j > i; --j){
            results[j] = results[j - 1];
          }
          results[i] = {dist, it};
          break;
        }
      }
    }
    std::array<std::string, N> words;
    for(std::size_t i = 0; i < N; ++i){
      words[i] = results[i].second;
    }
    return words;
  }
}  // namespace fuzz
}  // namespace estl

#endif  // ESTL_FUZZ_HPP_
