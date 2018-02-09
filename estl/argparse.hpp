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
#include <sstream>
#include <string>
#include <typeinfo>

#include "argparse/argument.hpp"
#include "variadic.hpp"

#include <iostream>

namespace estl {

class ArgumentParser {
 public:
  ArgumentParser(std::string prolog, std::string epilog)
      : prolog_(prolog), epilog_(epilog) {}
  ~ArgumentParser() {}

  void SetVersion(std::string version) { version_ = version; }
  void SetProlog(std::string prolog) { prolog_ = prolog; }
  void SetEpilog(std::string epilog) { epilog_ = epilog; }
  void SetProg(std::string prog) { prog_ = prog; }
  void SetUsage(std::string usage) { usage_ = usage; }

  void Group(std::string group) { current_group_ = group; }

  std::string GetUsage() { return "Usage: " + prog_ + " " + usage_; }
  std::string GetVersion() { return prog_ + " " + version_; }
  std::string GetHelp() {
    std::stringstream out;
    if (GetUsage() != std::string()) {
      out << GetUsage() << "\n";
    }
    if (GetVersion() != std::string()) {
      out << GetVersion() << "\n";
    }
    out << prolog_ << "\n\n";
    std::map<std::string, std::vector<std::string>> help_groups;
    for (std::set<Argument>::iterator it = arguments_.begin();
         it != arguments_.end(); ++it) {
      if (help_groups.find((*it).GetGroup()) != help_groups.end()) {
        help_groups.at((*it).GetGroup()).push_back((*it).GetHelp());
      } else {
        help_groups.insert(std::pair<std::string, std::vector<std::string>>(
            (*it).GetGroup(), std::vector<std::string>{(*it).GetHelp()}));
      }
    }
    for (std::map<std::string, std::vector<std::string>>::iterator it =
             help_groups.begin();
         it != help_groups.end(); ++it) {
      out << (*it).first << ":\n";
      for (std::vector<std::string>::iterator args = (*it).second.begin();
           args != (*it).second.end(); ++args) {
        out << (*args) << "\n";
      }
    }
    if (help_groups.size() != 0) {
      out << "\n";
    }
    out << epilog_ << "\n";
    return out.str();
  }

  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b = std::monostate(), std::any c = std::monostate(),
                   std::any d = std::monostate(), std::any e = std::monostate(),
                   std::any f = std::monostate(), std::any g = std::monostate(),
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::initializer_list<std::any> b,
                   std::any c = std::monostate(), std::any d = std::monostate(),
                   std::any e = std::monostate(), std::any f = std::monostate(),
                   std::any g = std::monostate(), std::any h = std::monostate(),
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::initializer_list<std::any> c,
                   std::any d = std::monostate(), std::any e = std::monostate(),
                   std::any f = std::monostate(), std::any g = std::monostate(),
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::initializer_list<std::any> d,
                   std::any e = std::monostate(), std::any f = std::monostate(),
                   std::any g = std::monostate(), std::any h = std::monostate(),
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d,
                   std::initializer_list<std::any> e,
                   std::any f = std::monostate(), std::any g = std::monostate(),
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e,
                   std::initializer_list<std::any> f,
                   std::any g = std::monostate(), std::any h = std::monostate(),
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::initializer_list<std::any> g,
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::initializer_list<std::any> h,
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::initializer_list<std::any> i,
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i,
                   std::initializer_list<std::any> j,
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j,
                   std::initializer_list<std::any> k,
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::initializer_list<std::any> l,
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::initializer_list<std::any> m,
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::initializer_list<std::any> n,
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n,
                   std::initializer_list<std::any> o,
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o,
                   std::initializer_list<std::any> p,
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o, std::any p,
                   std::initializer_list<std::any> q,
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o, std::any p,
                   std::any q, std::initializer_list<std::any> r,
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o, std::any p,
                   std::any q, std::any r, std::initializer_list<std::any> s,
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o, std::any p,
                   std::any q, std::any r, std::any s,
                   std::initializer_list<std::any> t,
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o, std::any p,
                   std::any q, std::any r, std::any s, std::any t,
                   std::initializer_list<std::any> u,
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::variant<std::string, std::set<std::string>> a,
                   std::any b, std::any c, std::any d, std::any e, std::any f,
                   std::any g, std::any h, std::any i, std::any j, std::any k,
                   std::any l, std::any m, std::any n, std::any o, std::any p,
                   std::any q, std::any r, std::any s, std::any t, std::any u,
                   std::initializer_list<std::any> v) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }

  void AddArgument(std::initializer_list<std::string> a,
                   std::any b = std::monostate(), std::any c = std::monostate(),
                   std::any d = std::monostate(), std::any e = std::monostate(),
                   std::any f = std::monostate(), std::any g = std::monostate(),
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a,
                   std::initializer_list<std::any> b,
                   std::any c = std::monostate(), std::any d = std::monostate(),
                   std::any e = std::monostate(), std::any f = std::monostate(),
                   std::any g = std::monostate(), std::any h = std::monostate(),
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b,
                   std::initializer_list<std::any> c,
                   std::any d = std::monostate(), std::any e = std::monostate(),
                   std::any f = std::monostate(), std::any g = std::monostate(),
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::initializer_list<std::any> d,
                   std::any e = std::monostate(), std::any f = std::monostate(),
                   std::any g = std::monostate(), std::any h = std::monostate(),
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::initializer_list<std::any> e,
                   std::any f = std::monostate(), std::any g = std::monostate(),
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::initializer_list<std::any> f,
                   std::any g = std::monostate(), std::any h = std::monostate(),
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f,
                   std::initializer_list<std::any> g,
                   std::any h = std::monostate(), std::any i = std::monostate(),
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g,
                   std::initializer_list<std::any> h,
                   std::any i = std::monostate(), std::any j = std::monostate(),
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::initializer_list<std::any> i,
                   std::any j = std::monostate(), std::any k = std::monostate(),
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::initializer_list<std::any> j,
                   std::any k = std::monostate(), std::any l = std::monostate(),
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::initializer_list<std::any> k,
                   std::any l = std::monostate(), std::any m = std::monostate(),
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k,
                   std::initializer_list<std::any> l,
                   std::any m = std::monostate(), std::any n = std::monostate(),
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l,
                   std::initializer_list<std::any> m,
                   std::any n = std::monostate(), std::any o = std::monostate(),
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::initializer_list<std::any> n,
                   std::any o = std::monostate(), std::any p = std::monostate(),
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::initializer_list<std::any> o,
                   std::any p = std::monostate(), std::any q = std::monostate(),
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::initializer_list<std::any> p,
                   std::any q = std::monostate(), std::any r = std::monostate(),
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::any p,
                   std::initializer_list<std::any> q,
                   std::any r = std::monostate(), std::any s = std::monostate(),
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::any p, std::any q,
                   std::initializer_list<std::any> r,
                   std::any s = std::monostate(), std::any t = std::monostate(),
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::any p, std::any q, std::any r,
                   std::initializer_list<std::any> s,
                   std::any t = std::monostate(), std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::any p, std::any q, std::any r,
                   std::any s, std::initializer_list<std::any> t,
                   std::any u = std::monostate(),
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::any p, std::any q, std::any r,
                   std::any s, std::any t, std::initializer_list<std::any> u,
                   std::any v = std::monostate()) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }
  void AddArgument(std::initializer_list<std::string> a, std::any b, std::any c,
                   std::any d, std::any e, std::any f, std::any g, std::any h,
                   std::any i, std::any j, std::any k, std::any l, std::any m,
                   std::any n, std::any o, std::any p, std::any q, std::any r,
                   std::any s, std::any t, std::any u,
                   std::initializer_list<std::any> v) {
    AddAnyArgument(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v);
  }

  std::map<std::string, std::any> ParseArgs(int argc, const char* argv[]) {
    std::vector<std::string> args = PrepArguments(argc, argv);
    std::map<std::string, std::any> data;
    while (args.size() > 0) {
      bool res = false;
      for (std::set<Argument>::iterator it = arguments_.begin();
           it != arguments_.end() && res == false; ++it) {
        res = (*it).ParseArgs(args);
      }
      if (res == false) {
        std::cerr << "ERROR: Unrecognized argument \"" << args.front()
                  << "\"\n";
        args.erase(args.begin());
      }
    }
    for (std::set<Argument>::iterator it = arguments_.begin();
         it != arguments_.end(); ++it) {
      if ((*it).Satisfied() == true) {
        if ((*it).HasValue() == true) {
          data.insert(std::pair<std::string, std::any>((*it).GetDest(),
                                                       (*it).GetValue()));
        }
      } else {
        std::cerr << "ERROR: Argument \"" << (*it).GetNamesStr()
                  << "\" is required\n";
      }
    }
    return data;
  }

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
        for (std::string::iterator it = tmp.begin(); it != tmp.end(); ++it) {
          args.insert(args.begin() + i, "-" + std::string(1, *it));
          i++;
        }
        i--;
      }
    }
    return args;
  }
  void AddAnyArgument(
      std::variant<std::initializer_list<std::string>,
                   std::variant<std::string, std::set<std::string>>>
          a,
      std::any b, std::any c, std::any d, std::any e, std::any f, std::any g,
      std::any h, std::any i, std::any j, std::any k, std::any l, std::any m,
      std::any n, std::any o, std::any p, std::any q, std::any r, std::any s,
      std::any t, std::any u, std::any v) {
    std::vector<std::any> tmp{b, c, d, e, f, g, h, i, j, k, l,
                              m, n, o, p, q, r, s, t, u, v};
    std::vector<std::any> args;
    for (std::size_t i = 0; i < tmp.size(); i++) {
      if (tmp[i].type() != typeid(std::monostate)) {
        args.push_back(tmp[i]);
      }
    }
    Argument new_arg(a, args);
    if (current_group_ == std::string()) {
      if (new_arg.Positional() == true) {
        new_arg.SetGroup("Positional Arguments");
      } else {
        new_arg.SetGroup("Optional Arguments");
      }
    } else {
      new_arg.SetGroup(current_group_);
    }
    arguments_.insert(new_arg);
  }

  bool InAnyArgument(std::string arg_name) {
    for (std::set<Argument>::iterator it = arguments_.begin();
         it != arguments_.end(); ++it) {
      if ((*it).IsMatch(arg_name) == true) {
        return true;
      }
    }
    return false;
  }

  std::string prog_, usage_, prolog_, epilog_, version_, current_group_;
  std::set<Argument> arguments_;
  bool add_help_, add_version_;
};

}  // namespace estl

#endif  // ESTL_ARGPARSE_HPP_
