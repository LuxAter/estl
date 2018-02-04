/* Copyright (C)
 * 2018 - Arden Rasmsussen
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
 * @file argument.hpp
 * @brief Arguments for argparse
 * @author Arden Rasmsussen
 * @version 0.0
 * @date 2018-02-04
 */

#ifndef ESTL_ARGPARSE_ARGUMENT_HPP_
#define ESTL_ARGPARSE_ARGUMENT_HPP_

#include <any>
#include <set>
#include <string>
#include <variant>

#include <iostream>

namespace estl {
enum Action {
  ACTION_STORE = 0,
  ACTION_STORE_CONST = 1,
  ACTION_STORE_TRUE = 2,
  ACTION_STORE_FALSE = 3,
  ACTION_APPEND = 4,
  ACTION_APPEND_CONST = 5,
  ACTION_COUNT = 6,
  ACTION_HELP = 7,
  ACTION_VERSION = 8
};

enum NArgs {
  ARGS_ONE = 0,
  ARGS_N = 1,
  ARGS_OPTIONAL = 2,
  ARGS_KLEENE_STAR = 3,
  ARGS_KLEENE_PLUS = 4
};

enum ArgOpt {
  ARG_OPT_NONE = 0,
  ARG_OPT_ACTION = 1,
  ARG_OPT_N_ARGS = 2,
  ARG_OPT_ARG_COUNT = 3,
  ARG_OPT_CONST = 4,
  ARG_OPT_DEFAULT = 5,
  ARG_OPT_CHOICES = 6,
  ARG_OPT_REQUIRED = 7,
  ARG_OPT_HELP = 8,
  ARG_OPT_METAVAR = 9,
  ARG_OPT_DEST = 10
};
class Argument {
 public:
  Argument() {}
  Argument(std::initializer_list<std::string> name) { SetName(name); }
  Argument(std::variant<std::initializer_list<std::string>, std::string,
                        std::set<std::string>>
               name) {
    SetName(name);
  }
  Argument(std::initializer_list<std::string> name, std::any a) {
    SetName(name);
    ArgOpt opt = SetVariable(a);
  }
  Argument(std::variant<std::initializer_list<std::string>, std::string,
                        std::set<std::string>>
               name,
           std::any a) {
    SetName(name);
    ArgOpt opt = SetVariable(a);
  }
  Argument(std::initializer_list<std::string> name, std::any a, std::any b) {
    SetName(name);
    ArgOpt opt = SetVariable(a);
    opt = SetVariable(b, opt);
  }
  Argument(const Argument& arg)
      : names_(arg.names_),
        action_(arg.action_),
        n_args_(arg.n_args_),
        n_args_count_(arg.n_args_count_),
        const_(arg.const_),
        default_(arg.default_),
        choices_(arg.choices_),
        required_(arg.required_),
        help_(arg.help_),
        metavar_(arg.metavar_),
        dest_(arg.dest_) {}
  ~Argument() {}

  void SetName(std::variant<std::initializer_list<std::string>, std::string,
                            std::set<std::string>>
                   name) {
    if (std::holds_alternative<std::initializer_list<std::string>>(name)) {
      names_ = std::set<std::string>(
          std::get<std::initializer_list<std::string>>(name));
    } else if (std::holds_alternative<std::string>(name)) {
      names_ = std::set<std::string>{std::get<std::string>(name)};
    } else if (std::holds_alternative<std::set<std::string>>(name)) {
      names_ = std::get<std::set<std::string>>(name);
    }
  }
  ArgOpt SetVariable(std::any val, ArgOpt opt = ARG_OPT_NONE) {
    if (opt == ARG_OPT_NONE) {
      if (val.type() == typeid(ArgOpt)) {
        return std::any_cast<ArgOpt>(val);
      } else if (val.type() == typeid(std::string)) {
        help_ = std::any_cast<std::string>(val);
      } else if (val.type() == typeid(const char*)) {
        help_ = std::string(std::any_cast<const char*>(val));
      } else if (val.type() == typeid(Action)) {
        action_ = std::any_cast<Action>(val);
      } else if (val.type() == typeid(NArgs)) {
        n_args_ = std::any_cast<NArgs>(val);
      }
    } else if (opt == ARG_OPT_ACTION) {
      if (val.type() == typeid(std::string) ||
          val.type() == typeid(const char*)) {
        std::string action_str;
        if (val.type() == typeid(std::string)) {
          action_str = std::any_cast<std::string>(val);
        } else {
          action_str = std::string(std::any_cast<const char*>(val));
        }
        if (action_str == "store") {
          action_ = ACTION_STORE;
        } else if (action_str == "store_const") {
          action_ = ACTION_STORE_CONST;
        } else if (action_str == "store_true") {
          action_ = ACTION_STORE_TRUE;
        } else if (action_str == "store_false") {
          action_ = ACTION_STORE_FALSE;
        } else if (action_str == "append") {
          action_ = ACTION_APPEND;
        } else if (action_str == "append_const") {
          action_ = ACTION_APPEND_CONST;
        } else if (action_str == "count") {
          action_ = ACTION_COUNT;
        } else if (action_str == "help") {
          action_ = ACTION_HELP;
        } else if (action_str == "version") {
          action_ = ACTION_VERSION;
        }
      } else if (val.type() == typeid(Action)) {
        action_ = std::any_cast<Action>(val);
      }
    } else if (opt == ARG_OPT_N_ARGS) {
      if (val.type() == typeid(std::string) ||
          val.type() == typeid(const char*)) {
      } else if (val.type() == typeid(int)) {
        n_args_count_ = std::any_cast<int>(val);
        if (n_args_count_ == 1) {
          n_args_ = ARGS_ONE;
        } else {
          n_args_ = ARGS_N;
        }
      } else if (val.type() == typeid(NArgs)) {
        n_args_ = std::any_cast<NArgs>(val);
      }
    }
    return ARG_OPT_NONE;
  }

  //  private:
  std::set<std::string> names_;
  Action action_ = ACTION_STORE;
  NArgs n_args_ = ARGS_ONE;
  unsigned int n_args_count_ = 1;
  std::any const_, default_;
  std::set<std::any> choices_;
  bool required_ = true;
  std::string help_, metavar_, dest_;
};

template <typename _T>
std::ostream& operator<<(std::ostream& out, const std::set<_T>& st) {
  out << "{";
  for (typename std::set<_T>::const_iterator it = st.begin(); it != st.end();
       ++it) {
    out << *it;
    if (it != --(st.end())) {
      out << ", ";
    }
  }
  out << "}";
  return out;
}

std::ostream& operator<<(std::ostream& out, const Argument& lhs) {
  out << "Names: " << lhs.names_ << "\n";
  out << "Action: " << lhs.action_ << "\n";
  out << "N Args: " << lhs.n_args_ << "\n";
  out << "N Args Count: " << lhs.n_args_count_ << "\n";
  // out << "Const: " << lhs.const_ << "\n";
  // out << "Default: " << lhs.default_ << "\n";
  out << "Required: " << lhs.required_ << "\n";
  out << "Help: " << lhs.help_ << "\n";
  out << "Metavar: " << lhs.metavar_ << "\n";
  out << "Dest: " << lhs.dest_ << "\n";
}

}  // namespace estl

#endif  // ESTL_ARGPARSE_ARGUMENT_HPP_
