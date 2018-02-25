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

#include "argparse/argument.hpp"
#include "argparse/variable.hpp"

namespace estl {
namespace argparse {
  class ArgumentParser {
   public:
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

    void AddArgument(std::initializer_list<std::string> names,
                     Variable a = Variable(), Variable b = Variable(),
                     Variable c = Variable(), Variable d = Variable(),
                     Variable e = Variable(), Variable f = Variable(),
                     Variable g = Variable(), Variable h = Variable(),
                     Variable i = Variable(), Variable j = Variable(),
                     Variable k = Variable(), Variable l = Variable(),
                     Variable m = Variable(), Variable n = Variable(),
                     Variable o = Variable(), Variable p = Variable(),
                     Variable q = Variable(), Variable r = Variable(),
                     Variable s = Variable(), Variable t = Variable(),
                     Variable u = Variable(), Variable v = Variable()) {
      AddArgumentVector(
          std::set<std::string>(names),
          {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v});
    }
    void AddArgument(std::string names, Variable a = Variable(),
                     Variable b = Variable(), Variable c = Variable(),
                     Variable d = Variable(), Variable e = Variable(),
                     Variable f = Variable(), Variable g = Variable(),
                     Variable h = Variable(), Variable i = Variable(),
                     Variable j = Variable(), Variable k = Variable(),
                     Variable l = Variable(), Variable m = Variable(),
                     Variable n = Variable(), Variable o = Variable(),
                     Variable p = Variable(), Variable q = Variable(),
                     Variable r = Variable(), Variable s = Variable(),
                     Variable t = Variable(), Variable u = Variable(),
                     Variable v = Variable()) {
      AddArgumentVector(
          std::set<std::string>{names},
          {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v});
    }
    void AddArgument(std::set<std::string> names, Variable a = Variable(),
                     Variable b = Variable(), Variable c = Variable(),
                     Variable d = Variable(), Variable e = Variable(),
                     Variable f = Variable(), Variable g = Variable(),
                     Variable h = Variable(), Variable i = Variable(),
                     Variable j = Variable(), Variable k = Variable(),
                     Variable l = Variable(), Variable m = Variable(),
                     Variable n = Variable(), Variable o = Variable(),
                     Variable p = Variable(), Variable q = Variable(),
                     Variable r = Variable(), Variable s = Variable(),
                     Variable t = Variable(), Variable u = Variable(),
                     Variable v = Variable()) {
      AddArgumentVector(names, {a, b, c, d, e, f, g, h, i, j, k,
                                l, m, n, o, p, q, r, s, t, u, v});
    }

    std::map<std::string, Variable> ParseArgs(int argc, const char* argv[]) {
      if (add_help_ == true) {
        AddArgumentVector(std::initializer_list<std::string>{"-h", "--help"},
                          {HELP, "show this help message and exit"});
      }
      if (add_version_ == true) {
        AddArgumentVector({"--version"},
                          {VERSION, "show program's version number and exit"});
      }
      if (argc == 0) {
        return std::map<std::string, Variable>();
      }
      std::vector<std::string> args = PrepArguments(argc, argv);
      std::map<std::string, Variable> data;
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
            data.insert(
                std::pair<std::string, Variable>(it.GetDest(), it.GetValue()));
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

    void AddArgumentVector(std::set<std::string> name,
                           std::vector<Variable> args) {
      Argument new_arg(name, args);
      if (current_group_ == std::string()) {
        bool flag = false;
        for (auto& it : name) {
          if (it[0] == '-') {
            flag = true;
            break;
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
}  // namespace argparse
}  // namespace estl

#endif  // ESTL_ARGPARSE_HPP_
