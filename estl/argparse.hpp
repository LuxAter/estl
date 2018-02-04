/* Copyright (C)
 * 2018 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

/**
 * @file argparse.hpp
 * @brief Argument parser class for C++
 * @author Arden Rasmussen
 * @version 0.0
 * @date 2018-02-03
 */

#ifndef ESTL_ARGPARSE_HPP_
#define ESTL_ARGPARSE_HPP_

#include <any>
#include <set>
#include <string>

#include <iostream>

template <typename _T>
std::ostream& operator<<(std::ostream& out, const std::set<_T>& st) {
  out << "{";
  for (typename std::set<_T>::const_iterator it = st.begin(); it != st.end();
       ++it) {
    out << *it;
    // if (it != st.end() - 1) {
    //   out << ", ";
    // }
  }
  out << "}";
  return out;
}

namespace estl {
class ArgumentParser {
 public:
  enum Action {
    STORE = 0,
    STORE_CONST = 1,
    STORE_TRUE = 2,
    STORE_FALSE = 3,
    APPEND = 4,
    APPEND_CONST = 5,
    COUNT = 6,
    HELP = 7,
    VERSION = 8
  };

  enum NArgs { ONE = 0, N = 1, OPTIONAL = 2, KLEENE_STAR = 3, KLEENE_PLUS = 4 };

  struct Argument {
    std::set<std::string> names_;
    Action action_;
    NArgs n_args_;
    unsigned int n_args_count_;
    std::any const_, default_;
    std::string type_regex_str_;
    std::set<std::any> choices_;
    bool required_;
    std::string help_, metavar_, dest_;
  };

  ArgumentParser(std::string description = std::string(),
                 std::string epilog = std::string())
      : description_(description), epilog_(epilog) {}
  ArgumentParser(const ArgumentParser& parser) {}
  ~ArgumentParser() {}

  void SetProg(std::string prog = std::string()) { prog_ = prog; }
  void SetUsage(std::string usage = std::string()) { usage_ = usage; }
  void SetDescription(std::string description = std::string()) {
    description_ = description;
  }
  void SetEpilog(std::string epilog = std::string()) { epilog_ = epilog; }
  void SetPrefixChars(std::string prefix_chars = std::string("-")) {
    prefix_chars_ = prefix_chars;
  }
  void SetAddHelp(bool help = true) { add_help_ = help; }

  void AddArgument(std::string name) {
    Argument new_argument;
    new_argument.names_ = std::set<std::string>{name};
    arguments_.insert(new_argument);
  }

  void ParseArgs(int argc, const char* argv[]) {
    std::cout << prog_ << ' ' << usage_ << std::endl;
    std::cout << description_ << std::endl;
    for (std::set<Argument>::iterator it = arguments_.begin();
         it != arguments_.end(); ++it) {
      std::cout << (*it).names_ << std::endl;
    }
    std::cout << epilog_ << std::endl;
  }

 private:
  std::string prog_, usage_, description_, epilog_, prefix_chars_;
  std::set<Argument> arguments_;
  bool add_help_;
};

bool operator<(const estl::ArgumentParser::Argument& lhs,
               const estl::ArgumentParser::Argument& rhs) {
  return lhs.names_ < rhs.names_;
}

}  // namespace estl

#endif  // ESTL_ARGPARSE_HPP_
