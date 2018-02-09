#ifndef ESTL_ARGPARSE_ARGUMENT_HPP_
#define ESTL_ARGPARSE_ARGUMENT_HPP_

#include <algorithm>
#include <any>
#include <set>
#include <string>

#include "../any.hpp"

namespace estl {

namespace {
  std::any AnyInt(std::string val) {
    if (val.find_first_not_of("0123456789") == std::string::npos) {
      return stoi(val);
    } else {
      return std::any();
    }
  }
  std::any AnyDouble(std::string val) {
    if (val.find_first_not_of(".0123456789") == std::string::npos &&
        std::count(val.begin(), val.end(), '.') <= 1) {
      return stod(val);
    } else {
      return std::any();
    }
  }
  std::any AnyBool(std::string val) {
    std::transform(val.begin(), val.end(), val.begin(), ::tolower);
    if (val == "true" || val == "t" || val == "1") {
      return true;
    } else if (val == "false" || val == "f" || val == "0") {
      return false;
    } else {
      return std::any();
    }
  }
  std::any AnyString(std::string val) { return val; }

  struct any_comp {
    bool operator()(const std::any& lhs, const std::any& rhs) {
      return lhs < rhs;
    }
  };
}  // namespace

class Argument {
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
  enum Type { STRING = 0, INT = 1, DOUBLE = 2, BOOL = 3 };
  enum ArgOpt {
    ARG_NONE = 0,
    ARG_ACTION = 1,
    ARG_N_ARGS = 2,
    ARG_N_ARGS_COUNT = 3,
    ARG_CONST = 4,
    ARG_DEFAULT = 5,
    ARG_CHOICES = 6,
    ARG_REQUIRED = 7,
    ARG_HELP = 8,
    ARG_METAVAR = 9,
    ARG_DEST = 10,
    ARG_TYPE = 11
  };

  Argument(std::variant<std::initializer_list<std::string>,
                        std::variant<std::string, std::set<std::string>>>
               names,
           std::vector<std::any> args) {
    if (std::holds_alternative<std::initializer_list<std::string>>(names)) {
      names_ = std::set<std::string>(
          std::get<std::initializer_list<std::string>>(names));
    } else if (std::holds_alternative<
                   std::variant<std::string, std::set<std::string>>>(names)) {
      std::variant<std::string, std::set<std::string>> tmp =
          std::get<std::variant<std::string, std::set<std::string>>>(names);
      if (std::holds_alternative<std::string>(tmp)) {
        names_ = std::set<std::string>{std::get<std::string>(tmp)};
      } else if (std::holds_alternative<std::set<std::string>>(tmp)) {
        names_ = std::get<std::set<std::string>>(tmp);
      }
    }
    ArgOpt opt = ARG_NONE;
    for (std::vector<std::any>::iterator it = args.begin(); it != args.end();
         ++it) {
      opt = SetVariable(*it, opt);
    }
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
        group_(arg.group_),
        type_(arg.type_),
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
  ArgOpt SetVariable(std::any val, ArgOpt opt) {
    if (opt == ARG_NONE) {
      if (val.type() == typeid(ArgOpt)) {
        return std::any_cast<ArgOpt>(val);
      } else if (val.type() == typeid(std::string) ||
                 val.type() == typeid(const char*)) {
        if (help_ == std::string()) {
          SetHelp(val);
        } else if (dest_ == std::string()) {
          SetDest(val);
        } else if (metavar_ == std::string()) {
          SetMetavar(val);
        } else {
          SetDefault(val);
        }
      } else if (val.type() == typeid(int)) {
        SetNArgsCount(val);
      } else if (val.type() == typeid(Action)) {
        SetAction(val);
      } else if (val.type() == typeid(NArgs)) {
        SetNArgs(val);
      } else if (val.type() == typeid(std::initializer_list<std::any>) ||
                 val.type() == typeid(std::set<std::any, any_comp>) ||
                 val.type() == typeid(std::vector<std::any>)) {
        SetChoices(val);
      } else if (val.type() == typeid(bool)) {
        SetRequired(val);
      } else if (val.type() == typeid(Type) ||
                 val.type() == typeid(std::function<std::any(std::string)>) ||
                 val.type() == typeid(std::any(*)(std::string))) {
        SetType(val);
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
    } else if (opt == ARG_N_ARGS_COUNT) {
      SetNArgsCount(val);
    } else if (opt == ARG_REQUIRED) {
      SetRequired(val);
    } else if (opt == ARG_TYPE) {
      SetType(val);
    } else {
      SetDefault(val);
    }
    return ARG_NONE;
  }

  void SetAction(std::any val) {
    if (val.type() == typeid(std::string) ||
        val.type() == typeid(const char*)) {
      std::string action_str;
      if (val.type() == typeid(std::string)) {
        action_str = std::any_cast<std::string>(val);
      } else {
        action_str = std::string(std::any_cast<const char*>(val));
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
      } else if (action_str == "count") {
        action_ = COUNT;
      } else if (action_str == "help") {
        action_ = HELP;
      } else if (action_str == "version") {
        action_ = VERSION;
      }
    } else if (val.type() == typeid(Action)) {
      action_ = std::any_cast<Action>(val);
    }
  }

  void SetNArgs(std::any val) {
    if (val.type() == typeid(std::string) ||
        val.type() == typeid(const char*)) {
      std::string args_str;
      if (val.type() == typeid(std::string)) {
        args_str = std::any_cast<std::string>(val);
      } else {
        args_str = std::string(std::any_cast<const char*>(val));
      }
      if (args_str == "one") {
        n_args_ = ONE;
      } else if (args_str == "n") {
        n_args_ = N;
      } else if (args_str == "?") {
        n_args_ = OPTIONAL;
      } else if (args_str == "*") {
        n_args_ = KLEENE_STAR;
      } else if (args_str == "+") {
        n_args_ = KLEENE_PLUS;
      } else if (args_str.find_first_not_of("0123456789") ==
                 std::string::npos) {
        n_args_count_ = stoi(args_str);
        if (n_args_count_ == 1) {
          n_args_ = ONE;
        } else {
          n_args_ = N;
        }
      }
    } else if (val.type() == typeid(int)) {
      n_args_count_ = std::any_cast<int>(val);
      if (n_args_count_ == 1) {
        n_args_ = ONE;
      } else {
        n_args_ = N;
      }
    } else if (val.type() == typeid(NArgs)) {
      n_args_ = std::any_cast<NArgs>(val);
    }
  }

  void SetNArgsCount(std::any val) {
    if (val.type() == typeid(int)) {
      n_args_count_ = std::any_cast<int>(val);
      if (n_args_count_ == 1) {
        n_args_ = ONE;
      } else {
        n_args_ = N;
      }
    }
  }

  void SetConst(std::any val) { const_ = val; }

  void SetDefault(std::any val) { default_ = val; }

  void SetChoices(std::any val) {
    if (val.type() == typeid(std::initializer_list<std::any>)) {
      choices_ = std::set<std::any, estl::any_comp>(
          std::any_cast<std::initializer_list<std::any>>(val));
    } else if (val.type() == typeid(std::set<std::any, estl::any_comp>)) {
      choices_ = std::any_cast<std::set<std::any, estl::any_comp>>(val);
    } else if (val.type() == typeid(std::vector<std::any>)) {
      std::vector<std::any> vec = std::any_cast<std::vector<std::any>>(val);
      choices_ = std::set<std::any, estl::any_comp>(vec.begin(), vec.end());
    }
  }

  void SetRequired(std::any val) {
    if (val.type() == typeid(bool)) {
      required_ = std::any_cast<bool>(val);
    }
  }

  void SetHelp(std::any val) {
    if (val.type() == typeid(std::string)) {
      help_ = std::any_cast<std::string>(val);
    } else if (val.type() == typeid(const char*)) {
      help_ = std::string(std::any_cast<const char*>(val));
    }
  }

  void SetMetavar(std::any val) {
    if (val.type() == typeid(std::string)) {
      metavar_ = std::any_cast<std::string>(val);
    } else if (val.type() == typeid(const char*)) {
      metavar_ = std::any_cast<const char*>(val);
    }
  }

  void SetDest(std::any val) {
    if (val.type() == typeid(std::string)) {
      dest_ = std::any_cast<std::string>(val);
    } else if (val.type() == typeid(const char*)) {
      dest_ = std::string(std::any_cast<const char*>(val));
    }
  }

  void SetGroup(std::any val) {
    if (val.type() == typeid(std::string)) {
      group_ = std::any_cast<std::string>(val);
    } else if (val.type() == typeid(const char*)) {
      group_ = std::string(std::any_cast<const char*>(val));
    }
  }

  void SetType(std::any val) {
    if (val.type() == typeid(std::function<std::any(std::string)>)) {
      type_ = std::any_cast<std::function<std::any(std::string)>>(val);
    } else if (val.type() == typeid(std::any(*)(std::string))) {
      type_ = std::function<std::any(std::string)>(
          std::any_cast<std::any (*)(std::string)>(val));
    } else if (val.type() == typeid(Type)) {
      Type type_enum = std::any_cast<Type>(val);
      if (type_enum == STRING) {
        type_ = std::function<std::any(std::string)>(AnyString);
      } else if (type_enum == INT) {
        type_ = std::function<std::any(std::string)>(AnyInt);
      } else if (type_enum == DOUBLE) {
        type_ = std::function<std::any(std::string)>(AnyDouble);
      } else if (type_enum == BOOL) {
        type_ = std::function<std::any(std::string)>(AnyBool);
      }
    }
  }

  std::string GetHelp() const {
    std::stringstream out;
    int index = 2;
    out << "  ";
    for (std::set<std::string>::iterator it = names_.begin();
         it != names_.end(); ++it) {
      out << *it;
      index += (*it).size();
      if (it != --names_.end()) {
        out << ", ";
        index += 2;
      }
    }
    if (choices_.size() != 0) {
      index = 4;
      out << "\n    ";
      std::string choices_str = GetChoicesStr();
      out << choices_str;
      index += choices_str.size();
    }
    if (index < 28) {
      out << std::string(30 - index, ' ');
    } else {
      out << "\n" << std::string(30, ' ');
    }
    if (help_.size() < 50) {
      out << help_;
    } else {
      index = 0;
      std::stringstream help_stream(help_);
      std::string word;
      while (std::getline(help_stream, word, ' ')) {
        if (index >= 50) {
          out << "\n" << std::string(30, ' ');
          index = 0;
        }
        out << word << ' ';
        index += word.size();
      }
    }
    return out.str();
  }
  std::string GetGroup() const { return group_; }
  std::set<std::string> GetNames() const { return names_; }
  std::string GetChoicesStr() const {
    std::stringstream out;
    out << '{';
    for (std::set<std::any, any_comp>::iterator it = choices_.begin();
         it != choices_.end(); ++it) {
      out << *it;
      if (it != --choices_.end()) {
        out << ", ";
      }
    }
    out << '}';
    return out.str();
  }
  std::string GetNamesStr() const {
    std::stringstream out;
    for (std::set<std::string>::iterator it = names_.begin();
         it != names_.end(); ++it) {
      out << *it;
      if (it != --names_.end()) {
        out << ", ";
      }
    }
    return out.str();
  }

  std::string GetDest() const {
    if (dest_ != std::string()) {
      return dest_;
    } else if (names_.size() != 0) {
      std::string longest;
      for (std::set<std::string>::iterator it = names_.begin();
           it != names_.end(); ++it) {
        if ((*it).size() > longest.size()) {
          longest = *it;
        }
      }
      while (longest.size() != 0 && longest[0] == '-') {
        longest.erase(longest.begin());
      }
      return longest;
    } else {
      return "null";
    }
  }
  std::any GetValue() const {
    if (value_.has_value() == true) {
      return value_;
    } else if (default_.has_value() == true) {
      return default_;
    }
    return std::any();
  }

  bool IsMatch(std::string arg_name) const {
    if (names_.find(arg_name) != names_.end()) {
      return true;
    }
    return false;
  }
  bool Positional() const {
    bool has_flag = false;
    for (std::set<std::string>::iterator it = names_.begin();
         it != names_.end() && has_flag == false; ++it) {
      if ((*it).size() > 1 && (*it)[0] == '-') {
        has_flag = true;
      }
    }
    return !has_flag;
  }
  bool TakesArgs() const {
    if (action_ == STORE || action_ == APPEND) {
      return true;
    }
    return false;
  }

  bool HasValue() const { return value_.has_value(); }

  bool Satisfied() const {
    if (required_ == true) {
      return value_.has_value();
    }
    return true;
  }

  bool ParseArgs(std::vector<std::string>& args) const {
    if (args.size() == 0) {
      return false;
    }
    if (names_.find(args.front()) != names_.end()) {
      args.erase(args.begin());
      if (TakesArgs() == true && args.size() == 0 && n_args_ != KLEENE_STAR &&
          n_args_ != OPTIONAL) {
        ArgumentRequiredError();
      } else if (TakesArgs() == true) {
        PreformArgumentAction(args);
      } else {
        PreformAction();
      }
      return true;
    }
    return false;
  }

 private:
  void PreformArgumentAction(std::vector<std::string>& args) const {
    if (args.front()[0] == '-' &&
        (n_args_ == OPTIONAL || n_args_ == KLEENE_STAR)) {
      return;
    } else if (args.front()[0] == '-') {
      ArgumentRequiredError();
      return;
    } else if (n_args_ == N || n_args_ == OPTIONAL || n_args_ == ONE) {
      int i;
      for (i = 0;
           i < n_args_count_ && args.size() > 0 && args.front()[0] != '-';
           i++) {
        std::any res = GetArgument(args.front());
        if (res.has_value() == true) {
          args.erase(args.begin());
          if (action_ == STORE && n_args_count_ == 1) {
            value_ = res;
          } else if (action_ == APPEND || n_args_count_ != 1) {
            if (value_.has_value() == true) {
              std::vector<std::any> vec =
                  std::any_cast<std::vector<std::any>>(value_);
              vec.push_back(res);
              value_ = vec;
            } else {
              value_ = std::vector<std::any>{res};
            }
          }
        } else {
          break;
        }
      }
      if (i != n_args_count_ && n_args_ != OPTIONAL) {
        ArgumentRequiredError(2);
      }
    } else if (n_args_ == KLEENE_PLUS || n_args_ == KLEENE_STAR) {
      while (args.size() > 0 && args.front()[0] != '-') {
        std::any res = GetArgument(args.front());
        if (res.has_value() == true) {
          args.erase(args.begin());
          if (value_.has_value() == true) {
            std::vector<std::any> vec =
                std::any_cast<std::vector<std::any>>(value_);
            vec.push_back(res);
            value_ = vec;
          } else {
            value_ = std::vector<std::any>{res};
          }
        } else {
          break;
        }
      }
    }
  }

  void PreformAction() const {
    if (action_ == STORE_TRUE) {
      value_ = true;
    } else if (action_ == STORE_FALSE) {
      value_ = false;
    } else if (action_ == STORE_CONST) {
      value_ = const_;
    } else if (action_ == APPEND_CONST) {
      if (value_.has_value() == true) {
        std::vector<std::any> vec =
            std::any_cast<std::vector<std::any>>(value_);
        vec.push_back(const_);
        value_ = vec;
      } else {
        value_ = std::vector<std::any>{const_};
      }
    }
  }

  std::any GetArgument(std::string val) const {
    std::any tmp = ConvertToType(val);
    if (tmp.has_value() == false) {
      std::cerr << "ERROR: Invalid type for argument \"" << GetNamesStr()
                << "\" (" << val << ")\n";
      return tmp;
    }
    if (InChoices(tmp) == true) {
      return tmp;
    } else {
      std::cerr << "ERROR: Argument not in choices for \"" << GetNamesStr()
                << "\" choices are: " << GetChoicesStr() << "\n";
    }
    return std::any();
  }

  std::any ConvertToType(std::string val) const {
    if (type_ != NULL) {
      return type_(val);
    } else {
      return val;
    }
  }

  bool InChoices(std::any val) const {
    if (choices_.size() == 0) {
      return true;
    } else {
      bool type_match = false;
      for (std::set<std::any>::iterator it = choices_.begin();
           it != choices_.end(); ++it) {
        if (val == *it) {
          return true;
        } else if (val.type() == (*it).type()) {
          type_match = true;
        }
      }
    }
    return false;
  }

  void ArgumentRequiredError(int flag = 1) const {
    if (flag == 1) {
      std::cerr << "ERROR: Argument is required for \"";
    } else if (flag == 2) {
      std::cerr << "ERROR: More arguments are required for \"";
    }
    for (std::set<std::string>::iterator it = names_.begin();
         it != names_.end(); ++it) {
      std::cerr << *it;
      if (it != --names_.end()) {
        std::cerr << ", ";
      }
    }
    std::cerr << "\"\n";
  }

  bool required_ = false;
  std::string help_, metavar_, dest_, group_;
  unsigned int n_args_count_ = 1;
  std::any const_, default_;
  std::set<std::string> names_;
  std::set<std::any, estl::any_comp> choices_;
  std::function<std::any(std::string)> type_;
  Action action_ = STORE;
  NArgs n_args_ = ONE;
  mutable std::any value_;
};

bool operator<(const estl::Argument& lhs, const estl::Argument& rhs) {
  return lhs.GetNames() < rhs.GetNames();
}
}  // namespace estl

#endif  // ESTL_ARGPARSE_ARGUMENT_HPP_
