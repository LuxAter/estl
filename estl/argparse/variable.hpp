#ifndef ESTL_ARGPARSE_VARIABLE_HPP_
#define ESTL_ARGPARSE_VARIABLE_HPP_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace estl {
namespace argparse {
  namespace {
    inline std::string char_to_string(const char* val) {
      return std::string(val);
    }
  }  // namespace
  enum Types {
    NONE = 0,
    BOOL = 1,
    CHAR = 2,
    INT = 3,
    DOUBLE = 4,
    STRING = 5,
    BOOL_VECTOR = 6,
    CHAR_VECTOR = 7,
    INT_VECTOR = 8,
    DOUBLE_VECTOR = 9,
    STRING_VECTOR = 10
  };
  class Variable {
   public:
    Variable() {}
    Variable(const bool& val) : type_(BOOL), bool_(val) {}
    Variable(const char& val) : type_(CHAR), char_(val) {}
    Variable(const int& val) : type_(INT), int_(val) {}
    Variable(const double& val) : type_(DOUBLE), double_(val) {}
    Variable(const char* val) : type_(STRING), string_(val) {}
    Variable(const std::string& val) : type_(STRING), string_(val) {}
    Variable(const std::vector<bool>& val)
        : type_(BOOL_VECTOR), bool_vec_(val) {}
    Variable(const std::vector<char>& val)
        : type_(CHAR_VECTOR), char_vec_(val) {}
    Variable(const std::vector<int>& val) : type_(INT_VECTOR), int_vec_(val) {}
    Variable(const std::vector<double>& val)
        : type_(DOUBLE_VECTOR), double_vec_(val) {}
    Variable(const std::vector<std::string>& val)
        : type_(STRING_VECTOR), string_vec_(val) {}
    Variable(const std::initializer_list<bool>& val)
        : type_(BOOL_VECTOR), bool_vec_(val) {}
    Variable(const std::initializer_list<char>& val)
        : type_(CHAR_VECTOR), char_vec_(val) {}
    Variable(const std::initializer_list<int>& val)
        : type_(INT_VECTOR), int_vec_(val) {}
    Variable(const std::initializer_list<double>& val)
        : type_(DOUBLE_VECTOR), double_vec_(val) {}
    Variable(const std::initializer_list<const char*>& val)
        : type_(STRING_VECTOR) {
      std::transform(val.begin(), val.end(), std::back_inserter(string_vec_),
                     char_to_string);
    }
    Variable(const std::initializer_list<std::string>& val)
        : type_(STRING_VECTOR), string_vec_(val) {}
    Variable(const Variable& copy) : type_(copy.type_) {
      switch (type_) {
        case BOOL: {
          bool_ = copy.bool_;
          break;
        }
        case CHAR: {
          char_ = copy.char_;
          break;
        }
        case INT: {
          int_ = copy.int_;
          break;
        }
        case DOUBLE: {
          double_ = copy.double_;
          break;
        }
        case STRING: {
          string_ = copy.string_;
          break;
        }
        case BOOL_VECTOR: {
          bool_vec_ = copy.bool_vec_;
          break;
        }
        case CHAR_VECTOR: {
          char_vec_ = copy.char_vec_;
          break;
        }
        case INT_VECTOR: {
          int_vec_ = copy.int_vec_;
          break;
        }
        case DOUBLE_VECTOR: {
          double_vec_ = copy.double_vec_;
          break;
        }
        case STRING_VECTOR: {
          string_vec_ = copy.string_vec_;
          break;
        }
        default:
          break;
      }
    }
    ~Variable() {}

    bool IsValid() const { return type_ != NONE; }
    bool IsVector() const {
      return (type_ == BOOL_VECTOR || type_ == CHAR_VECTOR ||
              type_ == INT_VECTOR || type_ == DOUBLE_VECTOR ||
              type_ == STRING_VECTOR);
    }

    Types Type() const { return type_; }

    inline bool GetBool() const { return (type_ == BOOL) ? bool_ : bool(); }
    inline char GetChar() const { return (type_ == CHAR) ? char_ : char(); }
    inline int GetInt() const { return (type_ == INT) ? int_ : int(); }
    inline double GetDouble() const {
      return (type_ == DOUBLE) ? double_ : double();
    }
    inline std::string GetString() const {
      return (type_ == STRING) ? string_ : std::string();
    }
    inline std::vector<bool> GetBoolVector() const {
      return (type_ == BOOL_VECTOR) ? bool_vec_ : std::vector<bool>();
    }
    inline std::vector<char> GetCharVector() const {
      return (type_ == CHAR_VECTOR) ? char_vec_ : std::vector<char>();
    }
    inline std::vector<int> GetIntVector() const {
      return (type_ == INT_VECTOR) ? int_vec_ : std::vector<int>();
    }
    inline std::vector<double> GetDoubleVector() const {
      return (type_ == DOUBLE_VECTOR) ? double_vec_ : std::vector<double>();
    }
    inline std::vector<std::string> GetStringVector() const {
      return (type_ == STRING_VECTOR) ? string_vec_
                                      : std::vector<std::string>();
    }

    void PushBack(Variable val) {
      switch (val.Type()) {
        case BOOL: {
          PushBack(val.GetBool());
          break;
        }
        case CHAR: {
          PushBack(val.GetChar());
          break;
        }
        case INT: {
          PushBack(val.GetInt());
          break;
        }
        case DOUBLE: {
          PushBack(val.GetDouble());
          break;
        }
        case STRING: {
          PushBack(val.GetString());
          break;
        }
        default:
          break;
      }
    }

    void PushBack(bool val) {
      if (type_ == BOOL_VECTOR) {
        bool_vec_.push_back(val);
      } else {
        type_ = BOOL_VECTOR;
        bool_vec_ = std::vector<bool>{val};
      }
    }
    void PushBack(char val) {
      if (type_ == CHAR_VECTOR) {
        char_vec_.push_back(val);
      } else {
        type_ = CHAR_VECTOR;
        char_vec_ = std::vector<char>{val};
      }
    }
    void PushBack(int val) {
      if (type_ == INT_VECTOR) {
        int_vec_.push_back(val);
      } else {
        type_ = INT_VECTOR;
        int_vec_ = std::vector<int>{val};
      }
    }
    void PushBack(double val) {
      if (type_ == DOUBLE_VECTOR) {
        double_vec_.push_back(val);
      } else {
        type_ = DOUBLE_VECTOR;
        double_vec_ = std::vector<double>{val};
      }
    }
    void PushBack(const char* val) {
      if (type_ == STRING_VECTOR) {
        string_vec_.push_back(std::string(val));
      } else {
        type_ = STRING_VECTOR;
        string_vec_ = std::vector<std::string>{std::string(val)};
      }
    }
    void PushBack(std::string val) {
      if (type_ == STRING_VECTOR) {
        string_vec_.push_back(val);
      } else {
        type_ = STRING_VECTOR;
        string_vec_ = std::vector<std::string>{val};
      }
    }

    Variable& operator=(const Variable& copy) {
      type_ = copy.type_;
      switch (type_) {
        case BOOL: {
          bool_ = copy.bool_;
          break;
        }
        case CHAR: {
          char_ = copy.char_;
          break;
        }
        case INT: {
          int_ = copy.int_;
          break;
        }
        case DOUBLE: {
          double_ = copy.double_;
          break;
        }
        case STRING: {
          string_ = copy.string_;
          break;
        }
        case BOOL_VECTOR: {
          bool_vec_ = copy.bool_vec_;
          break;
        }
        case CHAR_VECTOR: {
          char_vec_ = copy.char_vec_;
          break;
        }
        case INT_VECTOR: {
          int_vec_ = copy.int_vec_;
          break;
        }
        case DOUBLE_VECTOR: {
          double_vec_ = copy.double_vec_;
          break;
        }
        case STRING_VECTOR: {
          string_vec_ = copy.string_vec_;
          break;
        }
        default:
          break;
      }
      return *this;
    }
    Variable& operator=(const bool& val) {
      type_ = BOOL;
      bool_ = val;
      return *this;
    }
    Variable& operator=(const char& val) {
      type_ = CHAR;
      char_ = val;
      return *this;
    }
    Variable& operator=(const int& val) {
      type_ = INT;
      int_ = val;
      return *this;
    }
    Variable& operator=(const double& val) {
      type_ = DOUBLE;
      double_ = val;
      return *this;
    }
    Variable& operator=(const char* val) {
      type_ = STRING;
      string_ = std::string(val);
      return *this;
    }
    Variable& operator=(const std::string& val) {
      type_ = STRING;
      string_ = val;
      return *this;
    }
    Variable& operator=(const std::vector<bool>& val) {
      type_ = BOOL_VECTOR;
      bool_vec_ = val;
      return *this;
    }
    Variable& operator=(const std::vector<char>& val) {
      type_ = CHAR_VECTOR;
      char_vec_ = val;
      return *this;
    }
    Variable& operator=(const std::vector<int>& val) {
      type_ = INT_VECTOR;
      int_vec_ = val;
      return *this;
    }
    Variable& operator=(const std::vector<double>& val) {
      type_ = DOUBLE_VECTOR;
      double_vec_ = val;
      return *this;
    }
    Variable& operator=(const std::vector<std::string>& val) {
      type_ = STRING_VECTOR;
      string_vec_ = val;
      return *this;
    }
    Variable& operator=(const std::initializer_list<bool>& val) {
      type_ = BOOL_VECTOR;
      bool_vec_ = std::vector<bool>(val);
      return *this;
    }
    Variable& operator=(const std::initializer_list<char>& val) {
      type_ = CHAR_VECTOR;
      char_vec_ = std::vector<char>(val);
      return *this;
    }
    Variable& operator=(const std::initializer_list<int>& val) {
      type_ = INT_VECTOR;
      int_vec_ = std::vector<int>(val);
      return *this;
    }
    Variable& operator=(const std::initializer_list<double>& val) {
      type_ = DOUBLE_VECTOR;
      double_vec_ = std::vector<double>(val);
      return *this;
    }
    Variable& operator=(const std::initializer_list<const char*>& val) {
      type_ = STRING_VECTOR;
      std::transform(val.begin(), val.end(), std::back_inserter(string_vec_),
                     char_to_string);
      return *this;
    }
    Variable& operator=(const std::initializer_list<std::string>& val) {
      type_ = STRING_VECTOR;
      string_vec_ = std::vector<std::string>(val);
      return *this;
    }

    explicit inline operator bool() const { return GetBool(); }
    explicit inline operator char() const { return GetChar(); }
    explicit inline operator int() const { return GetInt(); }
    explicit inline operator double() const { return GetDouble(); }
    explicit inline operator std::string() const { return GetString(); }
    explicit inline operator std::vector<bool>() const {
      return GetBoolVector();
    }
    explicit inline operator std::vector<char>() const {
      return GetCharVector();
    }
    explicit inline operator std::vector<int>() const { return GetIntVector(); }
    explicit inline operator std::vector<double>() const {
      return GetDoubleVector();
    }
    explicit inline operator std::vector<std::string>() const {
      return GetStringVector();
    }

    template <class T>
    std::ostream& GetVectorString(std::ostream& out, std::vector<T> lhs) const {
      for (typename std::vector<T>::const_iterator it = lhs.begin();
           it != lhs.end(); ++it) {
        out << *it;
        if (it != --lhs.end()) {
          out << ", ";
        }
      }
      return out;
    }

   private:
    Types type_ = NONE;
    union {
      bool bool_;
      char char_;
      int int_;
      double double_;
    };
    std::string string_;
    std::vector<bool> bool_vec_;
    std::vector<char> char_vec_;
    std::vector<int> int_vec_;
    std::vector<double> double_vec_;
    std::vector<std::string> string_vec_;
  };

  inline bool operator==(const Variable& lhs, const Variable& rhs) {
    if (lhs.Type() == rhs.Type()) {
      switch (lhs.Type()) {
        case BOOL: {
          return lhs.GetBool() == rhs.GetBool();
        }
        case CHAR: {
          return lhs.GetChar() == rhs.GetChar();
        }
        case INT: {
          return lhs.GetInt() == rhs.GetInt();
        }
        case DOUBLE: {
          return lhs.GetDouble() == rhs.GetDouble();
        }
        case STRING: {
          return lhs.GetString() == rhs.GetString();
        }
        case BOOL_VECTOR: {
          return lhs.GetBoolVector() == rhs.GetBoolVector();
        }
        case CHAR_VECTOR: {
          return lhs.GetCharVector() == rhs.GetCharVector();
        }
        case INT_VECTOR: {
          return lhs.GetIntVector() == rhs.GetIntVector();
        }
        case DOUBLE_VECTOR: {
          return lhs.GetDoubleVector() == rhs.GetDoubleVector();
        }
        case STRING_VECTOR: {
          return lhs.GetStringVector() == rhs.GetStringVector();
        }
        default: { return false; }
      }
    }
    return false;
  }
  inline bool operator!=(const Variable& lhs, const Variable& rhs) {
    return !(lhs == rhs);
  }
  inline bool operator<(const Variable& lhs, const Variable& rhs) {
    if (lhs.Type() == rhs.Type()) {
      switch (lhs.Type()) {
        case BOOL: {
          return lhs.GetBool() < rhs.GetBool();
        }
        case CHAR: {
          return lhs.GetChar() < rhs.GetChar();
        }
        case INT: {
          return lhs.GetInt() < rhs.GetInt();
        }
        case DOUBLE: {
          return lhs.GetDouble() < rhs.GetDouble();
        }
        case STRING: {
          return lhs.GetString() < rhs.GetString();
        }
        case BOOL_VECTOR: {
          return lhs.GetBoolVector() < rhs.GetBoolVector();
        }
        case CHAR_VECTOR: {
          return lhs.GetCharVector() < rhs.GetCharVector();
        }
        case INT_VECTOR: {
          return lhs.GetIntVector() < rhs.GetIntVector();
        }
        case DOUBLE_VECTOR: {
          return lhs.GetDoubleVector() < rhs.GetDoubleVector();
        }
        case STRING_VECTOR: {
          return lhs.GetStringVector() < rhs.GetStringVector();
        }
        default: { return false; }
      }
    }
    return lhs.Type() < rhs.Type();
  }
  inline bool operator>(const Variable& lhs, const Variable& rhs) {
    return rhs < lhs;
  }
  inline bool operator<=(const Variable& lhs, const Variable& rhs) {
    return !(rhs < lhs);
  }
  inline bool operator>=(const Variable& lhs, const Variable& rhs) {
    return !(lhs < rhs);
  }
  inline std::ostream& operator<<(std::ostream& out, const Variable& lhs) {
    switch (lhs.Type()) {
      case BOOL: {
        out << lhs.GetBool();
        break;
      }
      case CHAR: {
        out << lhs.GetChar();
        break;
      }
      case INT: {
        out << lhs.GetInt();
        break;
      }
      case DOUBLE: {
        out << lhs.GetDouble();
        break;
      }
      case STRING: {
        out << lhs.GetString();
        break;
      }
      case BOOL_VECTOR: {
        lhs.GetVectorString(out, lhs.GetBoolVector());
        break;
      }
      case CHAR_VECTOR: {
        lhs.GetVectorString(out, lhs.GetCharVector());
        break;
      }
      case INT_VECTOR: {
        lhs.GetVectorString(out, lhs.GetIntVector());
        break;
      }
      case DOUBLE_VECTOR: {
        lhs.GetVectorString(out, lhs.GetDoubleVector());
        break;
      }
      case STRING_VECTOR: {
        lhs.GetVectorString(out, lhs.GetStringVector());
        break;
      }
      default: { out << "(null)"; }
    }
    return out;
  }
}  // namespace argparse
}  // namespace estl

#endif  // ESTL_ARGPARSE_VARIABLE_HPP_
