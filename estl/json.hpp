#ifndef ESTL_JSON_HPP_
#define ESTL_JSON_HPP_

#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <variant>
#include <vector>

namespace estl {
namespace json {
  class Json {
   public:
    enum JsonType { DICT, LIST, STRING, BOOL, INT, DOUBLE, NILL, ERR };
    enum JsonToken {
      T_NILL,
      T_BOOL,
      T_INT,
      T_DOUBLE,
      T_STRING,
      T_OPEN_DICT,
      T_CLOSE_DICT,
      T_OPEN_LIST,
      T_CLOSE_LIST,
      T_COLLON,
      T_COMMA,
      T_EOS
    };

    class iterator {
     public:
      iterator() {}
      iterator(const iterator& copy)
          : list_it_(copy.list_it_),
            dict_it_(copy.dict_it_),
            dict_(copy.dict_) {}
      iterator(std::vector<Json>::iterator it) : list_it_(it), dict_(false) {}
      iterator(std::map<std::string, Json>::iterator it)
          : dict_it_(it), dict_(true) {}

      Json& operator*() const { return dict_ ? dict_it_->second : *list_it_; }
      Json* operator->() const {
        return dict_ ? &(dict_it_->second) : &(*list_it_);
      }

      std::pair<std::string, Json> get_dict() const { return *dict_it_; }
      Json get_list() const { return *list_it_; }

      bool operator==(const iterator& rhs) const {
        if (dict_ == rhs.dict_) {
          return dict_ ? dict_it_ == rhs.dict_it_ : list_it_ == rhs.list_it_;
        } else {
          return false;
        }
      }
      bool operator!=(const iterator& rhs) const { return !(*this == rhs); }

      iterator& operator++() {
        if (dict_) {
          ++dict_it_;
        } else {
          ++list_it_;
        }
        return *this;
      }
      iterator& operator--() {
        if (dict_) {
          --dict_it_;
        } else {
          --list_it_;
        }
        return *this;
      }
      iterator& operator+(unsigned n) {
        if (dict_) {
          while (n > 0) {
            dict_it_++;
            --n;
          }
        } else {
          list_it_ += n;
        }
        return *this;
      }
      iterator& operator-(unsigned n) {
        if (dict_) {
          while (n > 0) {
            dict_it_--;
            --n;
          }
        } else {
          list_it_ -= n;
        }
        return *this;
      }

      std::vector<Json>::iterator list_it_;
      std::map<std::string, Json>::iterator dict_it_;
      bool dict_;
    };

    Json() : type_(NILL) {}
    explicit Json(const JsonType& type) : type_(type) {}
    explicit Json(const std::vector<Json>& val) : type_(LIST), list_(val) {}
    explicit Json(const std::map<std::string, Json>& val)
        : type_(DICT), dict_(val) {}
    Json(const bool& val) : type_(BOOL), bool_(val) {}
    Json(const int& val) : type_(INT), int_(val) {}
    Json(const double& val) : type_(DOUBLE), double_(val) {}
    Json(const std::string& val) : type_(STRING), string_(val) {}
    Json(const char* val) : type_(STRING), string_(val) {}
    Json(const Json& copy)
        : type_(copy.type_),
          dict_(copy.dict_),
          list_(copy.list_),
          bool_(copy.bool_),
          int_(copy.int_),
          double_(copy.double_),
          string_(copy.string_) {}

    JsonType Type() const { return type_; }
    std::map<std::string, Json> GetDict() const { return dict_; }
    std::vector<Json> GetList() const { return list_; }
    bool GetBool() const { return bool_; }
    int GetInt() const { return int_; }
    double GetDouble() const { return double_; }
    std::string GetString() const { return string_; }

    iterator begin() {
      if (type_ == LIST) {
        return iterator(list_.begin());
      } else {
        return iterator(dict_.begin());
      }
    }
    iterator end() {
      if (type_ == LIST) {
        return iterator(list_.end());
      } else {
        return iterator(dict_.end());
      }
    }

    void insert(const std::size_t& pos, const Json& item) {
      if (type_ != LIST) {
        if (type_ == DICT) {
          dict_.clear();
        }
        type_ = LIST;
      }
      list_.insert(list_.begin() + pos, item);
    }
    void insert(const std::string& key, const Json& value) {
      if (type_ != DICT) {
        if (type_ == LIST) {
          list_.clear();
        }
        type_ = DICT;
      }
      dict_.insert({key, value});
    }

    void prepend(const Json& item) {
      if (type_ != LIST) {
        if (type_ == DICT) {
          dict_.clear();
        }
        type_ = LIST;
      }
      list_.insert(list_.begin(), item);
    }
    void append(const Json& item) {
      if (type_ != LIST) {
        if (type_ == DICT) {
          dict_.clear();
        }
        type_ = LIST;
      }
      list_.push_back(item);
    }
    void append(const std::string& key, const Json& value) {
      if (type_ != DICT) {
        if (type_ == LIST) {
          list_.clear();
        }
        type_ = DICT;
      }
      dict_.insert({key, value});
    }

    Json& operator[](std::string str) { return dict_.find(str)->second; }
    Json& operator[](std::size_t ind) { return list_.at(ind); }

   private:
    JsonType type_;
    std::map<std::string, Json> dict_;
    std::vector<Json> list_;
    bool bool_;
    int int_;
    double double_;
    std::string string_;
  };

  std::ostream& operator<<(std::ostream& out, const Json& json) {
    switch (json.Type()) {
      case Json::DICT: {
        out << '{';
        std::map<std::string, Json> json_dict = json.GetDict();
        for (auto it = json_dict.begin(); it != json_dict.end(); ++it) {
          out << it->first << ": " << it->second;
          if (it != --json_dict.end()) {
            out << ", ";
          }
        }
        out << '}';
        break;
      }
      case Json::LIST: {
        out << '[';
        std::vector<Json> json_list = json.GetList();
        for (auto it = json_list.begin(); it != json_list.end(); ++it) {
          out << *it;
          if (it != --json_list.end()) {
            out << ", ";
          }
        }
        out << ']';
        break;
      }
      case Json::INT: {
        out << json.GetInt();
        break;
      }
      case Json::DOUBLE: {
        out << json.GetDouble();
        break;
      }
      case Json::STRING: {
        out << json.GetString();
        break;
      }
      case Json::BOOL: {
        out << json.GetBool();
        break;
      }
      default:
        out << "null";
        break;
    }
    return out;
  }

  std::pair<Json::JsonToken, std::string> GetNextToken(std::istream& str) {
    while (!str.eof() && (str.peek() == ',' || str.peek() == ' ' || str.peek() == '\n')) {
      str.get();
    }
    switch (str.peek()) {
      case '{':
        str.get();
        return {Json::T_OPEN_DICT, "{"};
      case '}':
        str.get();
        return {Json::T_CLOSE_DICT, "}"};
      case '[':
        str.get();
        return {Json::T_OPEN_LIST, "["};
      case ']':
        str.get();
        return {Json::T_CLOSE_LIST, "]"};
      case ':':
        str.get();
        return {Json::T_COLLON, ":"};
      case 'n': {
        std::string result(4, ' ');
        str.read(&result[0], 4);
        return {Json::T_NILL, "null"};
      }
      case 't': {
        std::string result(4, ' ');
        str.read(&result[0], 4);
        return {Json::T_BOOL, "true"};
      }
      case 'f': {
        std::string result(5, ' ');
        str.read(&result[0], 5);
        return {Json::T_BOOL, "false"};
      }
      case '"': {
        str.get();
        std::string token;
        char ch;
        while ((ch = str.get()) != '"') {
          token += ch;
        }
        return {Json::T_STRING, token};
      }
      case '\'': {
        str.get();
        std::string token;
        char ch;
        while ((ch = str.get()) != '\'') {
          token += ch;
        }
        return {Json::T_STRING, token};
      }
      default:
        std::string token_str;
        if ((str.peek() >= 48 && str.peek() <= 57) || str.peek() == 46) {
          bool decimal = false;
          if (str.peek() == 46) {
            decimal = true;
          }
          token_str += str.get();
          while ((str.peek() >= 48 && str.peek() <= 57) || str.peek() == 46) {
            if (str.peek() == 46) {
              if (decimal) {
                break;
              }
              decimal = true;
            }
            token_str += str.get();
          }
          return {decimal ? Json::T_DOUBLE : Json::T_INT, token_str};
        }
    }
    return {Json::T_NILL, ""};
  }
  Json ParseStream(std::istream& str) {
    // TODO: Slow down is at creating JSON, not reading, and not in GetNextToken. Must Be Fixed!!
    std::pair<Json::JsonToken, std::string> token;
    if (str.eof()) {
      return Json();
    }
    token = GetNextToken(str);
    switch (token.first) {
      case Json::T_NILL:
        return Json();
      case Json::T_BOOL:
        return token.second == "false" ? Json(false) : Json(true);
      case Json::T_INT:
        return Json(std::stoi(token.second));
      case Json::T_DOUBLE:
        return Json(std::stod(token.second));
      case Json::T_STRING:
        return Json(token.second);
      case Json::T_OPEN_DICT: {
        Json json_dict;
        std::string key;
        token = GetNextToken(str);
        while (!str.eof() && token.first != Json::T_CLOSE_DICT) {
          key = token.second;
          token = GetNextToken(str);
          if (token.first != Json::T_COLLON) {
            std::cout << "ERROR[EXPECTED COLLON]\n";
          }
          Json ret = ParseStream(str);
          if (ret.Type() != Json::ERR) {
            json_dict.append(key, ret);
          }else{
            break;
          }
          token = GetNextToken(str);
        }
        return json_dict;
      }
      case Json::T_OPEN_LIST: {
        Json json_list;
        while (!str.eof() && token.first != Json::T_CLOSE_LIST) {
          Json ret = ParseStream(str);
          if (ret.Type() != Json::ERR) {
            json_list.append(ret);
          }else{
            break;
          }
        }
        return json_list;
      }
      default:
        return Json(Json::ERR);
    }
    return Json();
  }
  Json ParseString(const std::string& str) {
    std::stringstream stream(str);
    return ParseStream(stream);
  }

}  // namespace json
}  // namespace estl

#endif  // ESTL_JSON_HPP_
