#ifndef ESTL_ARGPARSE_HPP_
#define ESTL_ARGPARSE_HPP_

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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
  explicit ArgumentParser(std::string prog)
      : prog_(prog), add_help_(true), add_version_(false) {}
  ArgumentParser(std::string prolog, std::string epilog)
      : prolog_(prolog),
        epilog_(epilog),
        add_help_(true),
        add_version_(false) {}
  ArgumentParser(std::string prog, std::string prolog, std::string epilog)
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
  void SetVersion(std::string version) { version_ = version; }
  void Group(std::string group) { current_group_ = group; }
  void SetAddHelp(bool setting) { add_help_ = setting; }
  void SetAddVersion(bool setting) { add_version_ = setting; }

  std::string GetHelp() {
    std::stringstream out;
    out << GetUsage() << "\n";
    if (GetVersion() != std::string()) {
      out << GetVersion() << "\n";
    }
    out << "\n";
    if (prolog_ != std::string()) {
      out << PrintBlockString(prolog_) << "\n\n";
    }
    std::map<std::string, std::vector<std::string>> help_data;
    for (auto& it : arguments_) {
      if (help_data.find(it.GetGroup()) != help_data.end()) {
        help_data.at(it.GetGroup()).push_back(it.GetHelp());
      } else {
        help_data.insert(std::pair<std::string, std::vector<std::string>>(
            it.GetGroup(), std::vector<std::string>{it.GetHelp()}));
      }
    }
    for (auto& it : help_data) {
      out << it.first << ":\n";
      for (auto& entry : it.second) {
        out << entry << "\n";
      }
    }
    if (help_data.size() != 0) {
      out << "\n";
    }
    if (epilog_ != std::string()) {
      out << PrintBlockString(epilog_) << "\n";
    }
    return out.str();
  }
  std::string GetUsage() {
    std::string res = "usage: ";
    if (prog_ != std::string()) {
      res += prog_ + ' ';
    }
    if (usage_ != std::string()) {
      res += usage_;
    } else {
      int len = res.size();
      int indent = res.size();
      for (auto& it : arguments_) {
        std::string usage_str = it.GetUsage();
        if (len + usage_str.size() >= 80) {
          len = indent;
          res += '\n' + std::string(indent, ' ');
        }
        res += usage_str + ' ';
        len += usage_str.size() + 1;
      }
    }
    return res;
  }
  std::string GetVersion() {
    if (version_ == std::string()) {
      return std::string();
    }
    std::string res;
    if (prog_ != std::string()) {
      res = prog_ + ' ';
    }
    res += version_;
    return res;
  }

  void AddArgument(
      std::initializer_list<std::string> names,
      estl::Variable a = estl::Variable(), estl::Variable b = estl::Variable(),
      estl::Variable c = estl::Variable(), estl::Variable d = estl::Variable(),
      estl::Variable e = estl::Variable(), estl::Variable f = estl::Variable(),
      estl::Variable g = estl::Variable(), estl::Variable h = estl::Variable(),
      estl::Variable i = estl::Variable(), estl::Variable j = estl::Variable(),
      estl::Variable k = estl::Variable(), estl::Variable l = estl::Variable(),
      estl::Variable m = estl::Variable(), estl::Variable n = estl::Variable(),
      estl::Variable o = estl::Variable(), estl::Variable p = estl::Variable(),
      estl::Variable q = estl::Variable(), estl::Variable r = estl::Variable(),
      estl::Variable s = estl::Variable(), estl::Variable t = estl::Variable(),
      estl::Variable u = estl::Variable(),
      estl::Variable v = estl::Variable()) {
    AddArgumentVector(names, {a, b, c, d, e, f, g, h, i, j, k,
                              l, m, n, o, p, q, r, s, t, u, v});
  }
  void AddArgument(
      std::string names, estl::Variable a = estl::Variable(),
      estl::Variable b = estl::Variable(), estl::Variable c = estl::Variable(),
      estl::Variable d = estl::Variable(), estl::Variable e = estl::Variable(),
      estl::Variable f = estl::Variable(), estl::Variable g = estl::Variable(),
      estl::Variable h = estl::Variable(), estl::Variable i = estl::Variable(),
      estl::Variable j = estl::Variable(), estl::Variable k = estl::Variable(),
      estl::Variable l = estl::Variable(), estl::Variable m = estl::Variable(),
      estl::Variable n = estl::Variable(), estl::Variable o = estl::Variable(),
      estl::Variable p = estl::Variable(), estl::Variable q = estl::Variable(),
      estl::Variable r = estl::Variable(), estl::Variable s = estl::Variable(),
      estl::Variable t = estl::Variable(), estl::Variable u = estl::Variable(),
      estl::Variable v = estl::Variable()) {
    AddArgumentVector(names, {a, b, c, d, e, f, g, h, i, j, k,
                              l, m, n, o, p, q, r, s, t, u, v});
  }

  std::map<std::string, estl::Variable> ParseArgs(int argc,
                                                  const char* argv[]) {
    if (add_help_ == true) {
      AddArgumentVector(std::initializer_list<std::string>{"-h", "--help"},
                        {HELP, "show this help message and exit"});
    }
    if (add_version_ == true) {
      AddArgumentVector({"--version"},
                        {VERSION, "show program's version number and exit"});
    }
    std::vector<std::string> args = PrepArguments(argc, argv);
    std::map<std::string, estl::Variable> data;
    int flag = 0;
    std::string last;
    while (args.size() > 0) {
      bool res = false;
      for (auto& it : arguments_) {
        if (it.IsPositional() == false) {
          res = it.ParseArgs(args);
          if (res == true) {
            if (it.GetAction() == HELP) {
              flag = 1;
            } else if (it.GetAction() == VERSION) {
              flag = 2;
            }
            break;
          }
        }
      }
      if (res == false && args.size() > 0 && last != args.front()) {
        for (auto& it : arguments_) {
          if (it.IsPositional() == true) {
            res = it.ParseArgs(args);
            if (res == true) {
              if (args.size() > 0) {
                last = args.front();
              }
              if (it.GetAction() == HELP) {
                flag = 1;
              } else if (it.GetAction() == VERSION) {
                flag = 2;
              }
              break;
            }
          }
        }
      }
      if (res == false) {
        std::cerr << "ERROR: Unrecognized argument \"" << args.front()
                  << "\"\n";
        args.erase(args.begin());
      }
      if (flag != 0) {
        break;
      }
    }
    if (flag == 1) {
      std::cout << GetHelp() << "\n";
      return data;
    } else if (flag == 2) {
      std::cout << GetVersion() << "\n";
      return data;
    }
    for (auto& it : arguments_) {
      if (it.Satisfied() == true) {
        if (it.HasValue() == true) {
          data.insert(std::pair<std::string, estl::Variable>(it.GetDest(),
                                                             it.GetValue()));
        }
      } else {
        std::cerr << "ERROR: Argument \"" << it.GetNamesStr()
                  << "\" is required\n";
      }
    }
    return data;
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

    ArgOpt SetVariable(estl::Variable val, ArgOpt opt) {
      if (opt == ARG_NONE) {
        if (val.Type() == estl::Variable::Types::UNSIGNED_INT ||
            val.Type() == estl::Variable::Types::SIGNED_INT) {
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
      unsigned int uint;
      if (val.Type() == estl::Variable::SIGNED_INT) {
        uint = val.GetSignedInt();
      } else {
        uint = val.GetUnsignedInt();
      }
      if (uint < 40) {
        type_ = static_cast<estl::Variable::Types>(uint);
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
        if (action_ == STORE_TRUE && default_.IsValid() == false) {
          default_ = false;
        } else if (action_ == STORE_FALSE && default_.IsValid() == false) {
          default_ = true;
        }
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
        // TODO(Arden): Add more string variants.
      }
    }
    void SetRequired(estl::Variable val) {
      usr_required_ = true;
      required_ = val;
    }
    void SetChoices(estl::Variable val) { choices_ = val; }
    void SetDefault(estl::Variable val) { default_ = val; }
    void SetConst(estl::Variable val) { const_ = val; }

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

    estl::Variable GetArgument(std::string arg_str) const {
      estl::Variable argument = ConvertToType(arg_str);
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
      return estl::Variable();
    }

    bool InChoices(estl::Variable argument) const {
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

    estl::Variable ConvertToType(std::string arg_str) const {
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

    bool required_ = false, usr_required_ = false;
    unsigned int n_args_count_ = 1;
    std::string help_, dest_, group_;
    mutable std::string metavar_;
    std::set<std::string> names_;
    Action action_ = STORE;
    NArgs n_args_ = ONE;
    estl::Variable default_, choices_, const_;
    mutable estl::Variable value_;
    estl::Variable::Types type_ = estl::Variable::NONE;
  };

  std::vector<std::string> PrepArguments(int argc, const char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    if (prog_ == std::string()) {
      prog_ = argv[0];
      prog_.erase(prog_.begin(), prog_.begin() + 2);
    }
    for (std::size_t i = 0; i < args.size(); i++) {
      std::stringstream ss(args[i]);
      std::string item;
      args.erase(args.begin() + i);
      while (std::getline(ss, item, '=')) {
        args.insert(args.begin() + i, item);
        i++;
      }
      i--;
    }
    for (std::size_t i = 0; i < args.size(); i++) {
      if (args[i].size() > 2 && args[i][0] == '-' && args[i][1] != '-' &&
          InAnyArgument(args[i]) == false) {
        std::string tmp = args[i];
        tmp.erase(tmp.begin());
        args.erase(args.begin() + i);
        for (auto& it : tmp) {
          args.insert(args.begin() + i, "-" + std::string(1, it));
          i++;
        }
        i--;
      }
    }
    return args;
  }

  void AddArgumentVector(
      std::variant<std::initializer_list<std::string>,
                   std::variant<std::string, std::set<std::string>>>
          name,
      std::vector<estl::Variable> args) {
    Argument new_arg(name, args);
    if (current_group_ == std::string()) {
      bool flag = false;
      if (std::holds_alternative<std::initializer_list<std::string>>(name) ==
          true) {
        std::vector<std::string> vec(
            std::get<std::initializer_list<std::string>>(name));
        for (auto& it : vec) {
          if (it[0] == '-') {
            flag = true;
            break;
          }
        }
      } else {
        std::variant<std::string, std::set<std::string>> var =
            std::get<std::variant<std::string, std::set<std::string>>>(name);
        if (std::holds_alternative<std::string>(var) == true) {
          std::string str = std::get<std::string>(var);
          if (str[0] == '-') {
            flag = true;
          }
        } else {
          std::set<std::string> st = std::get<std::set<std::string>>(var);
          for (auto& it : st) {
            if (it[0] == '-') {
              flag = true;
              break;
            }
          }
        }
      }
      if (flag == false) {
        new_arg.SetGroup("positional arguments");
      } else {
        new_arg.SetGroup("optional arguments");
      }
    } else {
      new_arg.SetGroup(current_group_);
    }
    arguments_.insert(new_arg);
  }

  std::string PrintBlockString(std::string str, int indent = 0) {
    if (str.size() + indent < 80) {
      return str;
    }
    int len = indent;
    std::string res;
    std::string word;
    std::stringstream out(str);
    while (getline(out, word, ' ')) {
      if (len + word.size() >= 80) {
        res += "\n";
        res += std::string(indent, ' ');
        len = indent;
      }
      res += word + ' ';
      len += word.size() + 1;
    }
    return res;
  }

  bool InAnyArgument(std::string arg_name) {
    for (auto& it : arguments_) {
      if (it.InNames(arg_name) == true) {
        return true;
      }
    }
    return false;
  }

  std::string prog_, prolog_, epilog_, usage_, version_, current_group_;
  std::set<Argument> arguments_;
  bool add_help_, add_version_;
};
}  // namespace estl

#endif  // ESTL_ARGPARSE_HPP_
