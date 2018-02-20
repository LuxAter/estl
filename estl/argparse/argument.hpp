#ifndef ESTL_ARGPARSE_ARGUMENT_HPP_
#define ESTL_ARGPARSE_ARGUMENT_HPP_

#include <iostream>

#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <variant>

#include "../variable.hpp"

namespace estl {
namespace argparse {
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
    Argument(std::variant<std::initializer_list<std::string>,
                          std::variant<std::string, std::set<std::string>>>
                 names,
             std::vector<estl::variable::Variable> args) {
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

    void SetName(std::variant<std::initializer_list<std::string>,
                              std::variant<std::string, std::set<std::string>>>
                     names) {
      if (std::holds_alternative<std::initializer_list<std::string>>(names)) {
        names_ = std::set<std::string>(
            std::get<std::initializer_list<std::string>>(names));
      } else if (std::holds_alternative<
                     std::variant<std::string, std::set<std::string>>>(names)) {
        std::variant<std::string, std::set<std::string>> sub_names =
            std::get<std::variant<std::string, std::set<std::string>>>(names);
        if (std::holds_alternative<std::string>(sub_names)) {
          names_ = std::set<std::string>{std::get<std::string>(sub_names)};
        } else {
          names_ = std::get<std::set<std::string>>(sub_names);
        }
      }
    }

    ArgOpt SetVariable(estl::variable::Variable val, ArgOpt opt) {
      if (opt == ARG_NONE) {
        if (val.Type() == estl::variable::Variable::Types::UNSIGNED_INT ||
            val.Type() == estl::variable::Variable::Types::SIGNED_INT) {
          return ParseUnsignedInt(val);
        } else if (val.Type() == estl::variable::Variable::Types::STRING ||
                   val.Type() == estl::variable::Variable::Types::CHAR_ARRAY) {
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
        } else if (val.Type() == estl::variable::Variable::Types::BOOL) {
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

    ArgOpt ParseUnsignedInt(estl::variable::Variable val) {
      unsigned int uint;
      if (val.Type() == estl::variable::Variable::SIGNED_INT) {
        uint = val.GetSignedInt();
      } else {
        uint = val.GetUnsignedInt();
      }
      if (uint < 40) {
        type_ = static_cast<estl::variable::Variable::Types>(uint);
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

    void SetHelp(estl::variable::Variable val) {
      if (val.Type() == estl::variable::Variable::STRING) {
        help_ = val.GetString();
      } else {
        help_ = std::string(val.GetCharArray());
      }
    }
    void SetDest(estl::variable::Variable val) {
      if (val.Type() == estl::variable::Variable::STRING) {
        dest_ = val.GetString();
      } else {
        dest_ = std::string(val.GetCharArray());
      }
    }
    void SetMetavar(estl::variable::Variable val) {
      if (val.Type() == estl::variable::Variable::STRING) {
        metavar_ = val.GetString();
      } else {
        metavar_ = std::string(val.GetCharArray());
      }
    }
    void SetNArgs(estl::variable::Variable val) {
      if (val.Type() == estl::variable::Variable::UNSIGNED_INT) {
        unsigned int uint = val.GetUnsignedInt();
        if (uint >= 50 && uint < 60) {
          n_args_ = static_cast<NArgs>(uint);
        } else if (uint == 1) {
          n_args_ = ONE;
          n_args_count_ = 1;
        } else {
          n_args_ = N;
          n_args_count_ = uint;
        }
      } else if (val.Type() == estl::variable::Variable::SIGNED_INT) {
        n_args_count_ = val.GetSignedInt();
        if (n_args_count_ == 1) {
          n_args_ = ONE;
        } else {
          n_args_ = N;
        }
      } else if (val.Type() == estl::variable::Variable::STRING ||
                 val.Type() == estl::variable::Variable::CHAR_ARRAY) {
        std::string nargs = val.GetString();
        if (val.Type() == estl::variable::Variable::CHAR_ARRAY) {
          nargs = std::string(val.GetCharArray());
        }
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
    }
    void SetAction(estl::variable::Variable val) {
      if (val.Type() == estl::variable::Variable::UNSIGNED_INT) {
        action_ = static_cast<Action>(val.GetUnsignedInt());
        if (action_ == STORE_TRUE && default_.IsValid() == false) {
          default_ = false;
        } else if (action_ == STORE_FALSE && default_.IsValid() == false) {
          default_ = true;
        }
      } else if (val.Type() == estl::variable::Variable::STRING ||
                 val.Type() == estl::variable::Variable::CHAR_ARRAY) {
        std::string action_str = val.GetString();
        if (val.Type() == estl::variable::Variable::CHAR_ARRAY) {
          action_str = std::string(val.GetCharArray());
        }
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
    void SetType(estl::variable::Variable val) {
      if (val.Type() == estl::variable::Variable::UNSIGNED_INT) {
        unsigned int uint = val.GetUnsignedInt();
        if (uint < 40) {
          type_ = static_cast<estl::variable::Variable::Types>(uint);
        }
      } else if (val.Type() == estl::variable::Variable::STRING ||
                 val.Type() == estl::variable::Variable::CHAR_ARRAY) {
        std::string type_str = val.GetString();
        if (val.Type() == estl::variable::Variable::CHAR_ARRAY) {
          type_str = std::string(val.GetCharArray());
        }
        if (type_str == "none") {
          type_ = estl::variable::Variable::NONE;
        } else if (type_str == "bool") {
          type_ = estl::variable::Variable::BOOL;
        } else if (type_str == "int") {
          type_ = estl::variable::Variable::SIGNED_INT;
        }
        // TODO(Arden): Add more string variants.
      }
    }
    void SetRequired(estl::variable::Variable val) {
      usr_required_ = true;
      required_ = val;
    }
    void SetChoices(estl::variable::Variable val) { choices_ = val; }
    void SetDefault(estl::variable::Variable val) { default_ = val; }
    void SetConst(estl::variable::Variable val) { const_ = val; }

    void SetGroup(std::string val) { group_ = val; }

    std::set<std::string> GetNames() const { return names_; }
    Action GetAction() const { return action_; }
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

    estl::variable::Variable GetValue() const {
      if (value_.IsValid() == true) {
        return value_;
      } else if (default_.IsValid() == true) {
        return default_;
      }
      return estl::variable::Variable();
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
          estl::variable::Variable argument = GetArgument(args.front());
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
          estl::variable::Variable argument = GetArgument(args.front());
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

    estl::variable::Variable GetArgument(std::string arg_str) const {
      estl::variable::Variable argument = ConvertToType(arg_str);
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
      return estl::variable::Variable();
    }

    bool InChoices(estl::variable::Variable argument) const {
      if (choices_.IsValid() == false || choices_.IsVector() == false) {
        return true;
      }
      unsigned int choices_type = choices_.Type(), arg_type = argument.Type();
      if (choices_type == estl::variable::Variable::BOOL_VECTOR &&
          arg_type == estl::variable::Variable::BOOL) {
        std::vector<bool> vec = choices_.GetBoolVector();
        if (std::find(vec.begin(), vec.end(), argument.GetBool()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::CHAR_VECTOR &&
                 arg_type == estl::variable::Variable::CHAR) {
        std::vector<char> vec = choices_.GetCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::SIGNED_CHAR_VECTOR &&
                 arg_type == estl::variable::Variable::SIGNED_CHAR) {
        std::vector<signed char> vec = choices_.GetSignedCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::UNSIGNED_CHAR_VECTOR &&
                 arg_type == estl::variable::Variable::UNSIGNED_CHAR) {
        std::vector<unsigned char> vec = choices_.GetUnsignedCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::SIGNED_SHORT_INT_VECTOR &&
                 arg_type == estl::variable::Variable::SIGNED_SHORT_INT) {
        std::vector<signed short int> vec = choices_.GetSignedShortIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedShortInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::UNSIGNED_SHORT_INT_VECTOR &&
                 arg_type == estl::variable::Variable::UNSIGNED_SHORT_INT) {
        std::vector<unsigned short int> vec =
            choices_.GetUnsignedShortIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedShortInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::SIGNED_INT_VECTOR &&
                 arg_type == estl::variable::Variable::SIGNED_INT) {
        std::vector<signed int> vec = choices_.GetSignedIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::UNSIGNED_INT_VECTOR &&
                 arg_type == estl::variable::Variable::UNSIGNED_INT) {
        std::vector<unsigned int> vec = choices_.GetUnsignedIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::SIGNED_LONG_INT_VECTOR &&
                 arg_type == estl::variable::Variable::SIGNED_LONG_INT) {
        std::vector<signed long int> vec = choices_.GetSignedLongIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedLongInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::UNSIGNED_LONG_INT_VECTOR &&
                 arg_type == estl::variable::Variable::UNSIGNED_LONG_INT) {
        std::vector<unsigned long int> vec =
            choices_.GetUnsignedLongIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedLongInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::SIGNED_LONG_LONG_INT_VECTOR &&
                 arg_type == estl::variable::Variable::SIGNED_LONG_LONG_INT) {
        std::vector<signed long long int> vec =
            choices_.GetSignedLongLongIntVector();
        if (std::find(vec.begin(), vec.end(),
                      argument.GetSignedLongLongInt()) != vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::variable::Variable::UNSIGNED_LONG_LONG_INT_VECTOR &&
                 arg_type == estl::variable::Variable::UNSIGNED_LONG_LONG_INT) {
        std::vector<unsigned long long int> vec =
            choices_.GetUnsignedLongLongIntVector();
        if (std::find(vec.begin(), vec.end(),
                      argument.GetUnsignedLongLongInt()) != vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::FLOAT_VECTOR &&
                 arg_type == estl::variable::Variable::FLOAT) {
        std::vector<float> vec = choices_.GetFloatVector();
        if (std::find(vec.begin(), vec.end(), argument.GetFloat()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::DOUBLE_VECTOR &&
                 arg_type == estl::variable::Variable::DOUBLE) {
        std::vector<double> vec = choices_.GetDoubleVector();
        if (std::find(vec.begin(), vec.end(), argument.GetDouble()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::LONG_DOUBLE_VECTOR &&
                 arg_type == estl::variable::Variable::LONG_DOUBLE) {
        std::vector<long double> vec = choices_.GetLongDoubleVector();
        if (std::find(vec.begin(), vec.end(), argument.GetLongDouble()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::STRING_VECTOR &&
                 arg_type == estl::variable::Variable::STRING) {
        std::vector<std::string> vec = choices_.GetStringVector();
        if (std::find(vec.begin(), vec.end(), argument.GetString()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::variable::Variable::CHAR_ARRAY_VECTOR &&
                 arg_type == estl::variable::Variable::CHAR_ARRAY) {
        std::vector<const char*> vec = choices_.GetCharArrayVector();
        if (std::find(vec.begin(), vec.end(), argument.GetCharArray()) !=
            vec.end()) {
          return true;
        }
        return false;
      }
      return false;
    }

    estl::variable::Variable ConvertToType(std::string arg_str) const {
      switch (type_) {
        case estl::variable::Variable::NONE:
        case estl::variable::Variable::STRING: {
          return arg_str;
        }
        case estl::variable::Variable::SIGNED_SHORT_INT: {
          return static_cast<signed short int>(std::stoi(arg_str));
        }
        case estl::variable::Variable::UNSIGNED_SHORT_INT: {
          return static_cast<unsigned short int>(std::stoi(arg_str));
        }
        case estl::variable::Variable::SIGNED_INT: {
          return std::stoi(arg_str);
        }
        case estl::variable::Variable::UNSIGNED_INT: {
          return static_cast<unsigned int>(std::stoul(arg_str));
        }
        case estl::variable::Variable::SIGNED_LONG_INT: {
          return std::stol(arg_str);
        }
        case estl::variable::Variable::UNSIGNED_LONG_INT: {
          return std::stoul(arg_str);
        }
        case estl::variable::Variable::SIGNED_LONG_LONG_INT: {
          return std::stoll(arg_str);
        }
        case estl::variable::Variable::UNSIGNED_LONG_LONG_INT: {
          return std::stoull(arg_str);
        }
        case estl::variable::Variable::FLOAT: {
          return std::stof(arg_str);
        }
        case estl::variable::Variable::DOUBLE: {
          return std::stod(arg_str);
        }
        case estl::variable::Variable::LONG_DOUBLE: {
          return std::stold(arg_str);
        }
        case estl::variable::Variable::CHAR_ARRAY: {
          return arg_str.c_str();
        }
        default: { return estl::variable::Variable(); }
      }
    }

    bool required_ = false, usr_required_ = false;
    unsigned int n_args_count_ = 1;
    std::string help_, dest_, group_;
    mutable std::string metavar_;
    std::set<std::string> names_;
    Action action_ = STORE;
    NArgs n_args_ = ONE;
    estl::variable::Variable default_, choices_, const_;
    mutable estl::variable::Variable value_;
    estl::variable::Variable::Types type_ = estl::variable::Variable::NONE;
  };
}  // namespace argparse
}  // namespace estl

#endif  // ESTL_ARGPARSE_ARGUMENT_HPP_
