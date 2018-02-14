#ifndef ESTL_ARGPARSE_HPP_
#define ESTL_ARGPARSE_HPP_

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
      switch (choices_.Type()) {
        case estl::Variable::BOOL_VECTOR: {
          std::vector<bool> vec = choices_.GetBoolVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<bool>(out, ", "));
        }
        case estl::Variable::CHAR_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::SIGNED_SHORT_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::UNSIGNED_SHORT_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::SIGNED_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::UNSIGNED_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::SIGNED_LONG_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::UNSIGNED_LONG_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::SIGNED_LONG_LONG_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::UNSIGNED_LONG_LONG_INT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::FLOAT_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::DOUBLE_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::LONG_DOUBLE_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::STRING_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
        case estl::Variable::CHAR_ARRAY_VECTOR: {
          std::vector<char> vec = choices_.GetCharVector();
          std::copy(vec.begin(), vec.end(),
                    std::ostream_iterator<char>(out, ", "));
        }
      }
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

   private:
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
