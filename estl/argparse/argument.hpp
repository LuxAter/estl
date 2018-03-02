#ifndef ESTL_ARGPARSE_ARGUMENT_HPP_
#define ESTL_ARGPARSE_ARGUMENT_HPP_

#include <iostream>

#include <algorithm>
#include <set>
#include <sstream>
#include <string>

#include "variable.hpp"

namespace estl {
namespace argparse {
  // TODO (Arden): Shift enum values to new bases from argparse varaible types.
  enum Action {
    STORE = 40,
    STORE_CONST = 41,
    STORE_TRUE = 42,
    STORE_FALSE = 43,
    APPEND = 44,
    APPEND_CONST = 45,
    COUNT = 46,
    HELP = 47,
    VERSION = 48
  };
  enum NArgs {
    ONE = 50,
    N = 51,
    OPTIONAL = 52,
    KLEENE_STAR = 53,
    KLEENE_PLUS = 54
  };
  enum ArgOpt {
    ARG_NONE = 60,
    ARG_ACTION = 61,
    ARG_N_ARGS = 62,
    ARG_CONST = 63,
    ARG_DEFAULT = 64,
    ARG_CHOICES = 65,
    ARG_REQUIRED = 66,
    ARG_HELP = 67,
    ARG_METAVAR = 68,
    ARG_DEST = 69,
    ARG_TYPE = 70
  };
  class Argument {
   public:
    Argument() {}
    Argument(std::set<std::string> names, std::vector<Variable> args) {
      SetName(names);
      ArgOpt opt = ARG_NONE;
      for (auto it : args) {
        if (it.IsValid() == false) {
          break;
        }
        opt = SetVariable(it, opt);
      }
      UpdateRequired();
    }
    Argument(const Argument& copy)
        : required_(copy.required_),
          n_args_count_(copy.n_args_count_),
          help_(copy.help_),
          metavar_(copy.metavar_),
          dest_(copy.dest_),
          group_(copy.group_),
          names_(copy.names_),
          action_(copy.action_),
          n_args_(copy.n_args_),
          value_(copy.value_),
          default_(copy.default_),
          type_(copy.type_),
          choices_(copy.choices_) {}

    void SetName(std::set<std::string> names) { names_ = names; }
    ArgOpt SetVariable(Variable val, ArgOpt opt) {
      if (opt == ARG_NONE) {
        if (val.Type() == INT) {
          return ParseUnsignedInt(val);
        } else if (val.Type() == STRING) {
          if (help_ == std::string()) {
            SetHelp(val);
          } else if (dest_ == std::string()) {
            SetDest(val);
          } else if (metavar_ == std::string()) {
            SetMetavar(val);
          } else {
            SetDefault(val);
          }
        } else if (val.IsVector() == true) {
          SetChoices(val);
        } else if (val.Type() == BOOL) {
          SetRequired(val);
        }
      } else if (opt == ARG_ACTION) {
        SetAction(val);
      } else if (opt == ARG_CHOICES) {
        SetChoices(val);
      } else if (opt == ARG_CONST) {
        SetConst(val);
      } else if (opt == ARG_DEFAULT) {
        SetDefault(val);
      } else if (opt == ARG_DEST) {
        SetDest(val);
      } else if (opt == ARG_HELP) {
        SetHelp(val);
      } else if (opt == ARG_METAVAR) {
        SetMetavar(val);
      } else if (opt == ARG_N_ARGS) {
        SetNArgs(val);
      } else if (opt == ARG_REQUIRED) {
        SetNArgs(val);
      } else if (opt == ARG_TYPE) {
        SetType(val);
      } else {
        SetDefault(val);
      }
      return ARG_NONE;
    }

    ArgOpt ParseUnsignedInt(Variable val) {
      unsigned int uint = val.GetInt();
      if (uint < 40) {
        type_ = static_cast<Types>(uint);
      } else if (uint < 50) {
        action_ = static_cast<Action>(uint);
        if (action_ == STORE_TRUE && default_.IsValid() == false) {
          default_ = false;
        } else if (action_ == STORE_FALSE && default_.IsValid() == false) {
          default_ = true;
        }
      } else if (uint < 60) {
        n_args_ = static_cast<NArgs>(uint);
      } else if (uint < 80) {
        return static_cast<ArgOpt>(uint);
      } else {
        SetDefault(val);
      }
      return ARG_NONE;
    }

    void SetHelp(Variable val) {
      if (val.Type() == STRING) {
        help_ = val.GetString();
      }
    }
    void SetDest(Variable val) {
      if (val.Type() == STRING) {
        dest_ = val.GetString();
      }
    }
    void SetMetavar(Variable val) {
      if (val.Type() == STRING) {
        metavar_ = val.GetString();
      }
    }
    void SetNArgs(Variable val) {
      if (val.Type() == INT) {
        unsigned int uint = val.GetInt();
        if (uint >= 50 && uint < 60) {
          n_args_ = static_cast<NArgs>(uint);
        } else if (uint == 1) {
          n_args_ = ONE;
          n_args_count_ = 1;
        } else {
          n_args_ = N;
          n_args_count_ = uint;
        }
      } else if (val.Type() == STRING) {
        std::string nargs = val.GetString();
        if (nargs == "one") {
          n_args_ = ONE;
          n_args_count_ = 1;
        } else if (nargs == "n") {
          n_args_ = N;
        } else if (nargs == "?") {
          n_args_ = OPTIONAL;
        } else if (nargs == "*") {
          n_args_ = KLEENE_STAR;
        } else if (nargs == "+") {
          n_args_ = KLEENE_PLUS;
        } else if (nargs.find_first_not_of("0123456789") == std::string::npos) {
          n_args_count_ = stoi(nargs);
          if (n_args_count_ == 1) {
            n_args_ = ONE;
          } else {
            n_args_ = N;
          }
        }
      }
      UpdateRequired();
    }
    void SetAction(Variable val) {
      if (val.Type() == INT) {
        action_ = static_cast<Action>(val.GetInt());
        if (action_ == STORE_TRUE && default_.IsValid() == false) {
          default_ = false;
        } else if (action_ == STORE_FALSE && default_.IsValid() == false) {
          default_ = true;
        }
      } else if (val.Type() == STRING) {
        std::string action_str = val.GetString();
        if (action_str == "store") {
          action_ = STORE;
        } else if (action_str == "store_const") {
          action_ = STORE_CONST;
        } else if (action_str == "store_true") {
          action_ = STORE_TRUE;
          if (default_.IsValid() == false) {
            default_ = false;
          }
        } else if (action_str == "store_false") {
          action_ = STORE_FALSE;
          if (default_.IsValid() == false) {
            default_ = true;
          }
        } else if (action_str == "append") {
          action_ = APPEND;
        } else if (action_str == "append_const") {
          action_ = APPEND_CONST;
        } else if (action_str == "count") {
          action_ = COUNT;
        } else if (action_str == "help") {
          action_ = HELP;
        } else if (action_str == "version") {
          action_ = VERSION;
        }
      }
    }
    void SetType(Variable val) {
      if (val.Type() == INT) {
        unsigned int uint = val.GetInt();
        if (uint < 40) {
          type_ = static_cast<Types>(uint);
        }
      } else if (val.Type() == STRING) {
        std::string type_str = val.GetString();
        if (type_str == "none") {
          type_ = NONE;
        } else if (type_str == "bool") {
          type_ = BOOL;
        } else if (type_str == "int") {
          type_ = INT;
        }
        // TODO(Arden): Add more string variants.
      }
    }
    void SetRequired(Variable val) {
      usr_required_ = true;
      if (val.Type() == BOOL) {
        required_ = val;
      }
    }
    void SetChoices(Variable val) { choices_ = val; }
    void SetDefault(Variable val) { default_ = val; }
    void SetConst(Variable val) { const_ = val; }

    void SetGroup(std::string val) { group_ = val; }

    std::set<std::string> GetNames() const { return names_; }
    Action GetAction() const { return action_; }
    Types GetType() const { return type_;}
    std::string GetDest() const {
      if (dest_ == std::string()) {
        std::string longest = std::string();
        for (auto& it : names_) {
          if (it.size() > longest.size()) {
            longest = it;
          }
        }
        while (longest.size() > 0 && longest[0] == '-') {
          longest.erase(longest.begin());
        }
        return longest;
      }
      return dest_;
    }
    std::string GetGroup() const { return group_; }

    std::string GetNamesStr() const {
      std::stringstream out;
      for (std::set<std::string>::reverse_iterator it = names_.rbegin();
           it != names_.rend(); ++it) {
        out << (*it);
        if (it != --names_.rend()) {
          out << ", ";
        }
      }
      return out.str();
    }
    std::string GetLongestNameStr() const {
      std::string longest;
      for (auto& it : names_) {
        if (it.size() > longest.size()) {
          longest = it;
        }
      }
      return longest;
    }
    std::string GetChoicesStr() const {
      std::stringstream out;
      out << '{';
      out << choices_;
      out << '}';
      return out.str();
    }

    Variable GetValue() const {
      if (value_.IsValid() == true) {
        return value_;
      } else if (default_.IsValid() == true) {
        return default_;
      }
      return Variable();
    }

    std::string GetHelp() const {
      std::stringstream out;
      std::string str;
      int len = 2;
      out << "  ";
      str = GetNamesStr();
      out << str;
      len += str.size();
      if (choices_.IsValid() == true) {
        out << "\n    ";
        str = GetChoicesStr();
        out << str;
        len = str.size() + 4;
      }
      if (len < 28) {
        out << std::string(30 - len, ' ');
      } else {
        out << "\n" << std::string(30, ' ');
      }
      if (help_.size() < 50) {
        out << help_;
      } else {
        len = 0;
        std::stringstream help_stream(help_);
        while (std::getline(help_stream, str, ' ')) {
          if (len + str.size() >= 50) {
            out << "\n" << std::string(32, ' ');
            len = 2;
          }
          out << str << ' ';
          len += str.size() + 1;
        }
      }
      return out.str();
    }
    std::string GetUsage() const {
      std::stringstream out;
      if (required_ == false) {
        out << '[';
      }
      if (IsPositional() == false) {
        out << GetLongestNameStr();
      }
      if (TakesArgs() == true) {
        if (IsPositional() == false) {
          out << ' ';
        }
        if (default_.IsValid() == true || n_args_ == OPTIONAL ||
            n_args_ == KLEENE_STAR) {
          out << '[';
        }
        if (metavar_ == std::string()) {
          for (auto& it : GetLongestNameStr()) {
            if (it != '-') {
              if (int(it) >= 97) {
                metavar_ += char(int(it) - 32);
              } else {
                metavar_ += it;
              }
            }
          }
        }
        if (n_args_ == ONE || n_args_ == N || n_args_ == OPTIONAL) {
          for (unsigned int i = 0; i < n_args_count_; i++) {
            out << metavar_;
            if (i != n_args_count_ - 1) {
              out << ' ';
            }
          }
        } else if (n_args_ == KLEENE_PLUS || n_args_ == KLEENE_STAR) {
          out << metavar_ << " [" << metavar_ << " ...]";
        }
        if (default_.IsValid() == true || n_args_ == OPTIONAL ||
            n_args_ == KLEENE_STAR) {
          out << ']';
        }
      }
      if (required_ == false) {
        out << ']';
      }
      return out.str();
    }

    bool InNames(std::string arg_name) const {
      if (names_.find(arg_name) != names_.end()) {
        return true;
      }
      return false;
    }
    bool HasValue() const { return (value_.IsValid() || default_.IsValid()); }

    bool IsPositional() const {
      bool flag = false;
      for (auto& it : names_) {
        if (it[0] == '-') {
          flag = true;
          break;
        }
      }
      return (!flag);
    }

    bool Satisfied() const {
      if (required_ == true) {
        return (value_.IsValid() || default_.IsValid());
      }
      return true;
    }
    bool TakesArgs() const {
      if (action_ == STORE || action_ == APPEND) {
        return true;
      }
      return false;
    }

    bool ParseArgs(std::vector<std::string>& args) const {
      if (args.size() == 0 ||
          (InNames(args.front()) == false && IsPositional() == false)) {
        return false;
      }
      if (IsPositional() == false) {
        args.erase(args.begin());
      }
      if (TakesArgs() == true && args.size() == 0 && n_args_ != KLEENE_STAR &&
          n_args_ != OPTIONAL) {
        ArgumentRequiredError(0);
      } else if (TakesArgs() == true) {
        PreformArgumentAction(args);
      } else {
        PreformAction();
      }
      return true;
    }

    friend bool operator<(const Argument& lhs, const Argument& rhs) {
      return lhs.GetNames() < rhs.GetNames();
    }

   private:
    void PreformArgumentAction(std::vector<std::string>& args) const {
      if (args.front()[0] == '-') {
        if (n_args_ == OPTIONAL || n_args_ == KLEENE_STAR) {
        } else {
          ArgumentRequiredError(0);
        }
        return;
      }
      if (n_args_ == N || n_args_ == OPTIONAL || n_args_ == ONE) {
        int num_args = 0;
        for (num_args = 0; num_args < n_args_count_ && args.size() > 0 &&
                           args.front()[0] != '-';
             num_args++) {
          Variable argument = GetArgument(args.front());
          if (argument.IsValid() == true) {
            args.erase(args.begin());
            if (action_ == STORE && n_args_count_ == 1) {
              value_ = argument;
            } else if (action_ == APPEND || n_args_count_ > 1) {
              value_.PushBack(argument);
            }
          } else {
            break;
          }
        }
        if (num_args != n_args_count_ && n_args_ != OPTIONAL) {
          ArgumentRequiredError(n_args_count_ - num_args);
        }
      } else if (n_args_ == KLEENE_PLUS || n_args_ == KLEENE_STAR) {
        int num_args = 0;
        while (args.size() > 0 && args.front()[0] != '-') {
          Variable argument = GetArgument(args.front());
          if (argument.IsValid() == true) {
            args.erase(args.begin());
            value_.PushBack(argument);
            num_args++;
          } else {
            break;
          }
        }
        if (n_args_ == KLEENE_PLUS && num_args == 0) {
          ArgumentRequiredError(1);
        }
      }
    }

    void PreformAction() const {
      switch (action_) {
        case STORE_TRUE: {
          value_ = true;
          break;
        }
        case STORE_FALSE: {
          value_ = false;
          break;
        }
        case STORE_CONST: {
          value_ = const_;
          break;
        }
        case APPEND_CONST: {
          value_.PushBack(const_);
          break;
        }
        default: { break; }
      }
    }

    void UpdateRequired() {
      if (usr_required_ == false) {
        if (default_.IsValid() == true) {
          required_ = false;
        } else {
          bool flag = false;
          for (auto& it : names_) {
            if (it[0] == '-') {
              flag = true;
              break;
            }
          }
          if (flag == false) {
            required_ = true;
          } else {
            required_ = false;
          }
        }
      }
    }

    void ArgumentRequiredError(int flag) const {
      if (flag == 0) {
        std::cerr << "ERROR: Argument(s) are required for \"";
      } else {
        std::cerr << "ERROR: " << flag << " more arguments are required for \"";
      }
      std::cerr << GetNamesStr();
      std::cerr << "\"\n";
    }

    Variable GetArgument(std::string arg_str) const {
      Variable argument = ConvertToType(arg_str);
      if (argument.IsValid() == false) {
        std::cerr << "ERROR: Invalid type for argument \"" << GetNamesStr()
                  << "\" (" << arg_str << ")\n";
      } else if (InChoices(argument) == false) {
        std::cerr << "ERROR: Argument (" << arg_str << ") not in choices for \""
                  << GetNamesStr() << "\" choices are: " << GetChoicesStr()
                  << "\n";
      } else {
        return argument;
      }
      return Variable();
    }

    bool InChoices(Variable argument) const {
      if (choices_.IsValid() == false || choices_.IsVector() == false) {
        return true;
      }
      unsigned int choices_type = choices_.Type(), arg_type = argument.Type();
      if (choices_type == BOOL_VECTOR && arg_type == BOOL) {
        std::vector<bool> vec = choices_.GetBoolVector();
        if (std::find(vec.begin(), vec.end(), argument.GetBool()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == CHAR_VECTOR && arg_type == CHAR) {
        std::vector<char> vec = choices_.GetCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == INT_VECTOR && arg_type == INT) {
        std::vector<signed int> vec = choices_.GetIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetInt()) != vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == DOUBLE_VECTOR && arg_type == DOUBLE) {
        std::vector<double> vec = choices_.GetDoubleVector();
        if (std::find(vec.begin(), vec.end(), argument.GetDouble()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == STRING_VECTOR && arg_type == STRING) {
        std::vector<std::string> vec = choices_.GetStringVector();
        if (std::find(vec.begin(), vec.end(), argument.GetString()) !=
            vec.end()) {
          return true;
        }
        return false;
      }
      return false;
    }

    Variable ConvertToType(std::string arg_str) const {
      switch (type_) {
        case NONE:
        case STRING: {
          return Variable(arg_str);
        }
        case CHAR: {
          return Variable(arg_str[0]);
        }
        case INT: {
          return Variable(std::stoi(arg_str));
        }
        case DOUBLE: {
          return Variable(std::stod(arg_str));
        }
        default: { return Variable(); }
      }
    }

    bool required_ = false, usr_required_ = false;
    unsigned int n_args_count_ = 1;
    std::string help_, dest_, group_;
    mutable std::string metavar_;
    std::set<std::string> names_;
    Action action_ = STORE;
    NArgs n_args_ = ONE;
    Variable default_, choices_, const_;
    mutable Variable value_;
    Types type_ = NONE;
  };
}  // namespace argparse
}  // namespace estl

#endif  // ESTL_ARGPARSE_ARGUMENT_HPP_
