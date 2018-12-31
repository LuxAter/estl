#ifndef ESTL_LUA_HPP_
#define ESTL_LUA_HPP_

#include <stdarg.h>
#include <lua5.3/lua.hpp>
#include <string>
#include <vector>

namespace estl {
namespace lua {
  class Script {
   public:
    Script(const std::string& file_name) {
      L = luaL_newstate();
      luaL_openlibs(L);
      if (luaL_loadfile(L, file_name.c_str()) || lua_pcall(L, 0, 0, 0)) {
      }
    }
    ~Script() {
      if (L) lua_close(L);
    }

    template <typename _T>
    _T get(const std::string& var) {
      if (!L) {
        return lua_get_default<_T>();
      }
      _T result;
      if (lua_get_to_stack(var)) {
        result = lua_get<_T>(var);
      } else {
        result = _T();
      }
      lua_pop(L, level + 1);
      return result;
    }
    bool lua_get_to_stack(const std::string& varName) {
      level = 0;
      std::string var = "";
      for (uint32_t i = 0; i < varName.size(); ++i) {
        if (varName.at(i) == '.') {
          if (level == 0) {
            lua_getglobal(L, var.c_str());
          } else {
            lua_getfield(L, -1, var.c_str());
          }

          if (lua_isnil(L, -1)) {
            return false;
          } else {
            var = "";
            level++;
          }
        } else {
          var += varName.at(i);
        }
      }
      if (level == 0) {
        lua_getglobal(L, var.c_str());

      } else {
        lua_getfield(L, -1, var.c_str());
      }
      if (lua_isnil(L, -1)) {
        return false;
      }
      return true;
    }
    template <typename _T>
    _T lua_get(const std::string& var) {
      return _T();
    }
    template <typename _T>
    std::vector<_T> lua_get_vector(const std::string& var) {
      std::vector<_T> vec;
      lua_getglobal(L, var.c_str());
      if (lua_isnil(L, -1)) {
        return vec;
      }
      lua_pushnil(L);
      while (lua_next(L, -2)) {
        vec.push_back(lua_get<_T>(var));
        lua_pop(L, 1);
      }
      clean();
      return vec;
    }
    template <typename _T>
    inline _T lua_get_default() {
      return _T();
    }

    int fib(int n){
      lua_getglobal(L, "fib");
      lua_pushnumber(L, n);
      lua_pcall(L, 1, 1, 0);
      int res = lua_tonumber(L, -1);
      lua_pop(L, 1);
      return res;
    }

    template <typename _T>
    _T call(const std::string func, const std::string fmt, ...) {
      va_list vl;
      int nargs, nres;
      va_start(vl, fmt);
      lua_getglobal(L, func.c_str());
      nargs = 0;
      for (char ch : fmt) {
        switch (ch) {
          case 'd':
            lua_pushnumber(L, va_arg(vl, double));
            break;
          case 'i':
            lua_pushnumber(L, va_arg(vl, int));
            break;
          case 's':
            lua_pushstring(L, va_arg(vl, char*));
            break;
          case '>':
            goto endwhile;
        }
        nargs++;
        luaL_checkstack(L, 1, "too many arguments");
      }
    endwhile:
      if (lua_pcall(L, nargs, nres, 0) != 0) {
      }
      va_end(vl);
      switch (fmt.back()) {
        case 'd':
          return (_T)lua_tonumber(L, -1);
        case 'i':
          return (_T)lua_tonumber(L, -1);
        // case 's':
        //   return _T(lua_tostring(L, -1));
        default:
          return _T();
      }
    }

    void clean() {
      int n = lua_gettop(L);
      lua_pop(L, n);
    }

   private:
    int level = 0;
    lua_State* L;
  };
  template <>
  inline bool Script::lua_get(const std::string& var) {
    return (bool)lua_toboolean(L, -1);
  }
  template <>
  inline float Script::lua_get(const std::string& var) {
    return (float)lua_tonumber(L, -1);
  }
  template <>
  inline int Script::lua_get(const std::string& var) {
    return (int)lua_tonumber(L, -1);
  }
  template <>
  inline std::string Script::lua_get(const std::string& var) {
    std::string s = "null";
    if (lua_isstring(L, -1)) {
      s = std::string(lua_tostring(L, -1));
    }
    return s;
  }
  template <>
  inline std::string Script::lua_get_default() {
    return "null";
  }
}  // namespace lua
}  // namespace estl

#endif  // ESTL_LUA_HPP_
