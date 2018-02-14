#ifndef ESTL_ARGPARSE_HPP_
#define ESTL_ARGPARSE_HPP_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

#include "variable.hpp"

namespace estl {
class ArgumentParser {
 public:
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

  ArgumentParser() {}
  explicit ArgumentParser(std::string& prog)
      : prog_(prog), add_help_(true), add_version_(false) {}
  ArgumentParser(std::string& prolog, std::string& epilog)
      : prolog_(prolog),
        epilog_(epilog),
        add_help_(true),
        add_version_(false) {}
  ArgumentParser(std::string& prog, std::string& prolog, std::string& epilog)
      : prog_(prog),
        prolog_(prolog),
        epilog_(epilog),
        add_help_(true),
        add_version_(false) {}
  ArgumentParser(const ArgumentParser& copy)
      : prog_(copy.prog_),
        prolog_(copy.prolog_),
        epilog_(copy.epilog_),
        usage_(copy.usage_),
        version_(copy.version_),
        current_group_(copy.current_group_),
        add_help_(copy.add_help_),
        add_version_(copy.add_version_) {}
  ~ArgumentParser() {}

  void SetProg(std::string prog) { prog_ = prog; }
  void SetProlog(std::string prolog) { prolog_ = prolog; }
  void SetEpilog(std::string epilog) { epilog_ = epilog; }
  void SetUsage(std::string usage) { usage_ = usage; }
  void Group(std::string group) { current_group_ = group; }

  std::string GetHelp() {}
  std::string GetUsage() {
    std::string res = "usage: ";
    if (prog_ != std::string()) {
      res += prog_ + ' ';
    }
    if (usage_ != std::string()) {
      res += usage_;
    } else {
      res += "WIP";
    }
    return res;
  }
  std::string GetVersion() {
    std::string res;
    if (prog_ != std::string()) {
      res = prog_ + ' ';
    }
    res += version_;
    return res;
  }

 protected:
 private:
  class Argument {
   public:
    Argument() {}
    Argument(std::variant<std::initializer_list<std::string>,
                          std::variant<std::string, std::set<std::string>>>
                 names,
             std::vector<estl::Variable> args) {
      SetName(names);
      ArgOpt opt = ARG_NONE;
      for (auto it : args) {
        opt = SetVariable(it, opt);
      }
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

    ArgOpt SetVariable(estl::Variable val, ArgOpt opt) {
      if (opt == ARG_NONE) {
        if (val.Type() == estl::Variable::Types::UNSIGNED_INT) {
          return ParseUnsignedInt(val);
        } else if (val.Type() == estl::Variable::Types::STRING ||
                   val.Type() == estl::Variable::Types::CHAR_ARRAY) {
          if (help_ == std::string()) {
            SetHelp(val);
          } else if (dest_ == std::string()) {
            SetDest(val);
          } else if (metavar_ == std::string()) {
            SetMetavar(val);
          } else {
            SetDefault(val);
          }
        } else if (val.Type() == estl::Variable::Types::SIGNED_INT) {
          SetNArgs(val);
        } else if (val.IsVector() == true) {
          SetChoices(val);
        } else if (val.Type() == estl::Variable::Types::BOOL) {
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

    ArgOpt ParseUnsignedInt(estl::Variable val) {
      unsigned int uint = val;
      if (uint < 40) {
        type_ = static_cast<estl::Variable::Types>(uint);
      } else if (uint < 50) {
        action_ = static_cast<Action>(uint);
      } else if (uint < 60) {
        n_args_ = static_cast<NArgs>(uint);
      } else if (uint < 80) {
        return static_cast<ArgOpt>(uint);
      } else {
        SetDefault(val);
      }
      return ARG_NONE;
    }

    void SetHelp(estl::Variable val) {
      if (val.Type() == estl::Variable::STRING) {
        help_ = val.GetString();
      } else {
        help_ = std::string(val.GetCharArray());
      }
    }
    void SetDest(estl::Variable val) {
      if (val.Type() == estl::Variable::STRING) {
        dest_ = val.GetString();
      } else {
        dest_ = std::string(val.GetCharArray());
      }
    }
    void SetMetavar(estl::Variable val) {
      if (val.Type() == estl::Variable::STRING) {
        metavar_ = val.GetString();
      } else {
        metavar_ = std::string(val.GetCharArray());
      }
    }
    void SetNArgs(estl::Variable val) {
      if (val.Type() == estl::Variable::UNSIGNED_INT) {
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
      } else if (val.Type() == estl::Variable::SIGNED_INT) {
        n_args_count_ = val.GetSignedInt();
        if (n_args_count_ == 1) {
          n_args_ = ONE;
        } else {
          n_args_ = N;
        }
      } else if (val.Type() == estl::Variable::STRING ||
                 val.Type() == estl::Variable::CHAR_ARRAY) {
        std::string nargs = val.GetString();
        if (val.Type() == estl::Variable::CHAR_ARRAY) {
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
    void SetAction(estl::Variable val) {
      if (val.Type() == estl::Variable::UNSIGNED_INT) {
        action_ = static_cast<Action>(val.GetUnsignedInt());
      } else if (val.Type() == estl::Variable::STRING ||
                 val.Type() == estl::Variable::CHAR_ARRAY) {
        std::string action_str = val.GetString();
        if (val.Type() == estl::Variable::CHAR_ARRAY) {
          action_str = std::string(val.GetCharArray());
        }
        if (action_str == "store") {
          action_ = STORE;
        } else if (action_str == "store_const") {
          action_ = STORE_CONST;
        } else if (action_str == "store_true") {
          action_ = STORE_TRUE;
        } else if (action_str == "store_false") {
          action_ = STORE_FALSE;
        } else if (action_str == "append") {
          action_ = APPEND;
        } else if (action_str == "append_const") {
          action_ = APPEND_CONST;
        } else if (action_str == "COUNT") {
          action_ = COUNT;
        } else if (action_str == "help") {
          action_ = HELP;
        } else if (action_str == "version") {
          action_ = VERSION;
        }
      }
    }
    void SetType(estl::Variable val) {
      if (val.Type() == estl::Variable::UNSIGNED_INT) {
        unsigned int uint = val.GetUnsignedInt();
        if (uint < 40) {
          type_ = static_cast<estl::Variable::Types>(uint);
        }
      } else if (val.Type() == estl::Variable::STRING ||
                 val.Type() == estl::Variable::CHAR_ARRAY) {
        std::string type_str = val.GetString();
        if (val.Type() == estl::Variable::CHAR_ARRAY) {
          type_str = std::string(val.GetCharArray());
        }
        if (type_str == "none") {
          type_ = estl::Variable::NONE;
        } else if (type_str == "bool") {
          type_ = estl::Variable::BOOL;
        }
      }
    }
    void SetRequired(estl::Variable val) { required_ = val; }
    void SetChoices(estl::Variable val) { choices_ = val; }
    void SetDefault(estl::Variable val) { default_ = val; }
    void SetConst(estl::Variable val) { const_ = val; }

    void SetGroup(std::string val) { group_ = val; }

    std::set<std::string> GetNames() const { return names_; }
    std::string GetDest() const { return dest_; }
    std::string GetGroup() const { return group_; }

    std::string GetNamesStr() const {
      std::stringstream out;
      std::copy(names_.begin(), names_.end(),
                std::ostream_iterator<std::string>(out, ", "));
      return out.str();
    }
    std::string GetChoicesStr() const {
      std::stringstream out;
      out << '{';
      out << choices_;
      out << '}';
      return out.str();
    }

    estl::Variable GetValue() const {
      if (value_.IsValid() == true) {
        return value_;
      } else if (default_.IsValid() == true) {
        return default_;
      }
      return estl::Variable();
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
          if (len >= 50) {
            out << "\n" << std::string(30, ' ');
            len = 0;
          }
          out << str << ' ';
          len += str.size();
        }
      }
      return out.str();
    }
    std::string GetUsage() const {
      std::stringstream out;
      if (required_ == false) {
        out << '[';
      }
      out << GetNamesStr();
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
    bool HasValue() const { return value_.IsValid(); }

    bool Satisfied() const {
      if (required_ == true) {
        return value_.IsValid();
      }
      return true;
    }
    bool TakesArgs() const {
      if (action_ == STORE || action_ == APPEND) {
        return true;
      }
      return false;
    }

    bool ParseArgss(std::vector<std::string>& args) {
      if (args.size() == 0 || InNames(args.front()) == false) {
        return false;
      }
      args.erase(args.begin());
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

   private:
    void PreformArgumentAction(std::vector<std::string>& args) {
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
          estl::Variable argument = GetArgument(args.front());
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
          estl::Variable argument = GetArgument(args.front());
          if (argument.IsValid() == true) {
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

    void PreformAction() {
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

    void ArgumentRequiredError(int flag) const {
      if (flag == 0) {
        std::cerr << "ERROR: Argument(s) are required for \"";
      } else {
        std::cerr << "ERROR: " << flag << " more arguments are required for \"";
      }
      std::cerr << GetNamesStr();
      std::cerr << "\"\n";
    }

    estl::Variable GetArgument(std::string arg_str) {
      estl::Variable argument = ConvertToType(arg_str);
      if (argument.IsValid() == false) {
        std::cerr << "ERROR: Invalid type for argument \"" << GetNamesStr()
                  << "\" (" << arg_str << ")\n";
      } else if (InChoices(argument) == false) {
        std::cerr << "ERROR: Argument (" << arg_str << ") not in choices for\""
                  << GetNamesStr() << "\" choices are: " << GetChoicesStr()
                  << "\n";
      } else {
        return argument;
      }
      return estl::Variable();
    }

    bool InChoices(estl::Variable argument) {
      if (choices_.IsValid() == false || choices_.IsVector() == false) {
        return true;
      }
      unsigned int choices_type = choices_.Type(), arg_type = argument.Type();
      if (choices_type == estl::Variable::BOOL_VECTOR &&
          arg_type == estl::Variable::BOOL) {
        std::vector<bool> vec = choices_.GetBoolVector();
        if (std::find(vec.begin(), vec.end(), argument.GetBool()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::CHAR_VECTOR &&
                 arg_type == estl::Variable::CHAR) {
        std::vector<char> vec = choices_.GetCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::SIGNED_CHAR_VECTOR &&
                 arg_type == estl::Variable::SIGNED_CHAR) {
        std::vector<signed char> vec = choices_.GetSignedCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::UNSIGNED_CHAR_VECTOR &&
                 arg_type == estl::Variable::UNSIGNED_CHAR) {
        std::vector<unsigned char> vec = choices_.GetUnsignedCharVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedChar()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::SIGNED_SHORT_INT_VECTOR &&
                 arg_type == estl::Variable::SIGNED_SHORT_INT) {
        std::vector<signed short int> vec = choices_.GetSignedShortIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedShortInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::UNSIGNED_SHORT_INT_VECTOR &&
                 arg_type == estl::Variable::UNSIGNED_SHORT_INT) {
        std::vector<unsigned short int> vec =
            choices_.GetUnsignedShortIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedShortInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::SIGNED_INT_VECTOR &&
                 arg_type == estl::Variable::SIGNED_INT) {
        std::vector<signed int> vec = choices_.GetSignedIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::UNSIGNED_INT_VECTOR &&
                 arg_type == estl::Variable::UNSIGNED_INT) {
        std::vector<unsigned int> vec = choices_.GetUnsignedIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::SIGNED_LONG_INT_VECTOR &&
                 arg_type == estl::Variable::SIGNED_LONG_INT) {
        std::vector<signed long int> vec = choices_.GetSignedLongIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetSignedLongInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::UNSIGNED_LONG_INT_VECTOR &&
                 arg_type == estl::Variable::UNSIGNED_LONG_INT) {
        std::vector<unsigned long int> vec =
            choices_.GetUnsignedLongIntVector();
        if (std::find(vec.begin(), vec.end(), argument.GetUnsignedLongInt()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::SIGNED_LONG_LONG_INT_VECTOR &&
                 arg_type == estl::Variable::SIGNED_LONG_LONG_INT) {
        std::vector<signed long long int> vec =
            choices_.GetSignedLongLongIntVector();
        if (std::find(vec.begin(), vec.end(),
                      argument.GetSignedLongLongInt()) != vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type ==
                     estl::Variable::UNSIGNED_LONG_LONG_INT_VECTOR &&
                 arg_type == estl::Variable::UNSIGNED_LONG_LONG_INT) {
        std::vector<unsigned long long int> vec =
            choices_.GetUnsignedLongLongIntVector();
        if (std::find(vec.begin(), vec.end(),
                      argument.GetUnsignedLongLongInt()) != vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::FLOAT_VECTOR &&
                 arg_type == estl::Variable::FLOAT) {
        std::vector<float> vec = choices_.GetFloatVector();
        if (std::find(vec.begin(), vec.end(), argument.GetFloat()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::DOUBLE_VECTOR &&
                 arg_type == estl::Variable::DOUBLE) {
        std::vector<double> vec = choices_.GetDoubleVector();
        if (std::find(vec.begin(), vec.end(), argument.GetDouble()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::LONG_DOUBLE_VECTOR &&
                 arg_type == estl::Variable::LONG_DOUBLE) {
        std::vector<long double> vec = choices_.GetLongDoubleVector();
        if (std::find(vec.begin(), vec.end(), argument.GetLongDouble()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::STRING_VECTOR &&
                 arg_type == estl::Variable::STRING) {
        std::vector<std::string> vec = choices_.GetStringVector();
        if (std::find(vec.begin(), vec.end(), argument.GetString()) !=
            vec.end()) {
          return true;
        }
        return false;
      } else if (choices_type == estl::Variable::CHAR_ARRAY_VECTOR &&
                 arg_type == estl::Variable::CHAR_ARRAY) {
        std::vector<const char*> vec = choices_.GetCharArrayVector();
        if (std::find(vec.begin(), vec.end(), argument.GetCharArray()) !=
            vec.end()) {
          return true;
        }
        return false;
      }
      return false;
    }

    estl::Variable ConvertToType(std::string arg_str) {
      switch (type_) {
        case estl::Variable::NONE:
        case estl::Variable::STRING: {
          return arg_str;
        }
        case estl::Variable::SIGNED_SHORT_INT: {
          return static_cast<signed short int>(std::stoi(arg_str));
        }
        case estl::Variable::UNSIGNED_SHORT_INT: {
          return static_cast<unsigned short int>(std::stoi(arg_str));
        }
        case estl::Variable::SIGNED_INT: {
          return std::stoi(arg_str);
        }
        case estl::Variable::UNSIGNED_INT: {
          return static_cast<unsigned int>(std::stoul(arg_str));
        }
        case estl::Variable::SIGNED_LONG_INT: {
          return std::stol(arg_str);
        }
        case estl::Variable::UNSIGNED_LONG_INT: {
          return std::stoul(arg_str);
        }
        case estl::Variable::SIGNED_LONG_LONG_INT: {
          return std::stoll(arg_str);
        }
        case estl::Variable::UNSIGNED_LONG_LONG_INT: {
          return std::stoull(arg_str);
        }
        case estl::Variable::FLOAT: {
          return std::stof(arg_str);
        }
        case estl::Variable::DOUBLE: {
          return std::stod(arg_str);
        }
        case estl::Variable::LONG_DOUBLE: {
          return std::stold(arg_str);
        }
        case estl::Variable::CHAR_ARRAY: {
          return arg_str.c_str();
        }
        default: { return estl::Variable(); }
      }
    }

    bool required_ = false;
    unsigned int n_args_count_ = 1;
    std::string help_, metavar_, dest_, group_;
    std::set<std::string> names_;
    Action action_;
    NArgs n_args_;
    estl::Variable value_, default_, choices_, const_;
    estl::Variable::Types type_;
  };

  std::string prog_, prolog_, epilog_, usage_, version_, current_group_;
  bool add_help_, add_version_;
};
}  // namespace estl

#endif  // ESTL_ARGPARSE_HPP_
