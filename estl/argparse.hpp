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
#include <map>
#include <set>
#include <string>
#include <typeinfo>

#include <iostream>

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

namespace estl {

class ArgumentParser {
 public:
  // class Argument {
  //  public:
  //   Argument() {}
  //   Argument(std::set<std::string> name, Action action, NArgs n_args,
  //            unsigned int n_args_count, std::any con, std::any def,
  //            std::string type, std::set<std::any> choices, bool required,
  //            std::string help, std::string metavar, std::string dest)
  //       : names_(name),
  //         action_(action),
  //         n_args_(n_args),
  //         n_args_count_(n_args_count),
  //         const_(con),
  //         default_(def),
  //         type_regex_str_(type),
  //         choices_(choices),
  //         required_(required),
  //         help_(help),
  //         metavar_(metavar),
  //         dest_(dest) {}
  //   Argument(std::map<std::string, std::any> arg_def) {
  //     if (arg_def.find("name") != arg_def.end()) {
  //       std::any name = arg_def.at("name");
  //       std::cout << "TYPE: " << name.type().name() << "\n";
  //       if (name.type() == typeid(std::string) ||
  //           name.type() == typeid(const char*)) {
  //         std::cout << "IS STRING!\n";
  //         std::cout << "NAME: "
  //                   << std::any_cast<const char*>(arg_def.at("name")) <<
  //                   "<\n";
  //       } else {
  //         std::cout << "NAME: "
  //                   <<
  //                   std::any_cast<std::set<std::string>>(arg_def.at("name"))
  //                   << "<\n";
  //       }
  //     }
  //   }
  //   void SetNames(std::initializer_list<std::string> name) {
  //     names_ = std::set<std::string>(name);
  //   }
  //   void SetNames(std::string name) { names_ = std::set<std::string>{name}; }
  //   void SetNames(std::set<std::string> name) { names_ = name; }
  //   void SetAction(Action action) { action_ = action; }
  //   void SetAction(std::string action) {
  //     if (action == "store") {
  //       action_ = ACTION_STORE;
  //     } else if (action == "store_const") {
  //       action_ = ACTION_STORE_CONST;
  //     } else if (action == "store_true") {
  //       action_ = ACTION_STORE_TRUE;
  //     } else if (action == "store_false") {
  //       action_ = ACTION_STORE_FALSE;
  //     } else if (action == "append") {
  //       action_ = ACTION_APPEND;
  //     } else if (action == "append_const") {
  //       action_ = ACTION_APPEND_CONST;
  //     } else if (action == "count") {
  //       action_ = ACTION_COUNT;
  //     } else if (action == "help") {
  //       action_ = ACTION_HELP;
  //     } else if (action == "version") {
  //       action_ = ACTION_VERSION;
  //     } else {
  //       fprintf(stderr, "\"%s\" is not a valid action string\n",
  //               action.c_str());
  //     }
  //   }
  //   void SetNArgs(NArgs n_args, unsigned int n_args_count = 0) {
  //     n_args_ = n_args;
  //     n_args_count_ = n_args_count;
  //   }
  //   void SetNArgs(std::string n_args, unsigned int n_args_count = 0) {
  //     if (n_args == "?") {
  //       n_args_ = ARGS_OPTIONAL;
  //     } else if (n_args == "*") {
  //       n_args_ = ARGS_KLEENE_STAR;
  //     } else if (n_args == "+") {
  //       n_args_ = ARGS_KLEENE_PLUS;
  //     } else if (n_args.find_first_not_of("0123456789") == std::string::npos)
  //     {
  //       n_args_count = stoi(n_args);
  //       if (n_args_count == 1) {
  //         n_args_ = ARGS_ONE;
  //       } else {
  //         n_args_ = ARGS_N;
  //       }
  //     } else {
  //       fprintf(stderr, "\"%s\" is not a valid n_args string\n",
  //               n_args.c_str());
  //     }
  //     n_args_count_ = n_args_count;
  //   }
  //   void SetConst(std::any con) { const_ = con; }
  //   void SetDefault(std::any def) { default_ = def; }
  //   std::set<std::string> names_;
  //   Action action_;
  //   NArgs n_args_;
  //   unsigned int n_args_count_;
  //   std::any const_, default_;
  //   std::string type_regex_str_;
  //   std::set<std::any> choices_;
  //   bool required_;
  //   std::string help_, metavar_, dest_;
  // };

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

  void AddArgument(std::initializer_list<std::string> names) {
    AddArgument(std::set<std::string>(names));
  }
  void AddArgument(std::string names) {
    Argument new_argument(std::set<std::string>{names}, ACTION_STORE, ARGS_ONE,
                          0, {}, {}, std::string(), {}, true, "", "", "dest");
    arguments_.insert(new_argument);
  }
  void AddArgument(std::set<std::string> names) {
    Argument new_argument(names, ACTION_STORE, ARGS_ONE, 0, {}, {},
                          std::string(), {}, true, "", "", "dest");
    arguments_.insert(new_argument);
  }
  void AddArgument(Argument argument) { arguments_.insert(argument); }

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
