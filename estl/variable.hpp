#ifndef ESTL_VARIABLE_HPP_
#define ESTL_VARIABLE_HPP_

#include <string>
#include <variant>
#include <vector>

namespace estl {
class Variable {
 public:
  Variable() : is_valid_(false) {}
  Variable(const Variable& copy)
      : is_valid_(copy.is_valid_), value_(copy.value_) {}
  Variable(const bool& val) : is_valid_(true), value_(val) {}
  Variable(const signed char& val) : is_valid_(true), value_(val) {}
  Variable(const unsigned char& val) : is_valid_(true), value_(val) {}
  Variable(const signed short int& val) : is_valid_(true), value_(val) {}
  Variable(const unsigned short int& val) : is_valid_(true), value_(val) {}
  Variable(const signed int& val) : is_valid_(true), value_(val) {}
  Variable(const unsigned int& val) : is_valid_(true), value_(val) {}
  Variable(const signed long int& val) : is_valid_(true), value_(val) {}
  Variable(const unsigned long int& val) : is_valid_(true), value_(val) {}
  Variable(const signed long long int& val) : is_valid_(true), value_(val) {}
  Variable(const unsigned long long int& val) : is_valid_(true), value_(val) {}
  Variable(const float& val) : is_valid_(true), value_(val) {}
  Variable(const double& val) : is_valid_(true), value_(val) {}
  Variable(const long double& val) : is_valid_(true), value_(val) {}
  Variable(const std::string& val) : is_valid_(true), value_(val) {}
  Variable(const char* val) : is_valid_(true), value_(val) {}
  Variable(const std::vector<bool>& val) : is_valid_(true), value_(val) {}
  Variable(const std::vector<signed char>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<unsigned char>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<signed short int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<unsigned short int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<signed int>& val) : is_valid_(true), value_(val) {}
  Variable(const std::vector<unsigned int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<signed long int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<unsigned long int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<signed long long int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<unsigned long long int>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<float>& val) : is_valid_(true), value_(val) {}
  Variable(const std::vector<double>& val) : is_valid_(true), value_(val) {}
  Variable(const std::vector<long double>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<std::string>& val)
      : is_valid_(true), value_(val) {}
  Variable(const std::vector<const char*>& val)
      : is_valid_(true), value_(val) {}
  ~Variable() {}

  bool IsValid() { return is_valid_; }
  std::variant<
      bool, char, signed char, unsigned char, signed short int,
      unsigned short int, signed int, unsigned int, signed long int,
      unsigned long int, signed long long int, unsigned long long int, float,
      double, long double, std::string, const char*, std::vector<bool>,
      std::vector<char>, std::vector<signed char>, std::vector<unsigned char>,
      std::vector<signed short int>, std::vector<unsigned short int>,
      std::vector<signed int>, std::vector<unsigned int>,
      std::vector<signed long int>, std::vector<unsigned long int>,
      std::vector<signed long long int>, std::vector<unsigned long long int>,
      std::vector<float>, std::vector<double>, std::vector<long double>,
      std::vector<std::string>, std::vector<const char*>>
  GetValue() const {
    return value_;
  }

  Variable& operator=(const Variable& copy) {
    is_valid_ = copy.is_valid_;
    value_ = copy.is_valid_;
    return *this;
  }
  Variable& operator=(const bool& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const char& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const signed char& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const unsigned char& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const signed short int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const unsigned short int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const signed int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const unsigned int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const signed long int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const unsigned long int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const signed long long int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const unsigned long long int& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const float& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const double& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const long double& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::string& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const char* val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }

  Variable& operator=(const std::vector<bool>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<char>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<signed char>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<unsigned char>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<signed short int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<unsigned short int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<signed int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<unsigned int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<signed long int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<unsigned long int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<signed long long int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<unsigned long long int>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<float>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<double>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<long double>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<std::string>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }
  Variable& operator=(const std::vector<const char*>& val) {
    is_valid_ = true;
    value_ = val;
    return *this;
  }

  operator bool() const {
    if (is_valid_ == true && std::holds_alternative<bool>(value_) == true) {
      return std::get<bool>(value_);
    }
    return bool();
  }
  inline operator char() const {
    if (is_valid_ == true && std::holds_alternative<char>(value_) == true) {
      return std::get<char>(value_);
    }
    return char();
  }
  inline operator signed char() const {
    if (is_valid_ == true &&
        std::holds_alternative<signed char>(value_) == true) {
      return std::get<signed char>(value_);
    }
    return char();
  }
  inline operator unsigned char() const {
    if (is_valid_ == true &&
        std::holds_alternative<unsigned char>(value_) == true) {
      return std::get<unsigned char>(value_);
    }
    return char();
  }
  inline operator signed short int() const {
    if (is_valid_ == true &&
        std::holds_alternative<signed short int>(value_) == true) {
      return std::get<signed short int>(value_);
    }
    return int();
  }
  inline operator unsigned short int() const {
    if (is_valid_ == true &&
        std::holds_alternative<unsigned short int>(value_) == true) {
      return std::get<unsigned short int>(value_);
    }
    return int();
  }
  inline operator signed int() const {
    if (is_valid_ == true &&
        std::holds_alternative<signed int>(value_) == true) {
      return std::get<signed int>(value_);
    }
    return int();
  }
  inline operator unsigned int() const {
    if (is_valid_ == true &&
        std::holds_alternative<unsigned int>(value_) == true) {
      return std::get<unsigned int>(value_);
    }
    return int();
  }
  inline operator signed long int() const {
    if (is_valid_ == true &&
        std::holds_alternative<signed long int>(value_) == true) {
      return std::get<signed long int>(value_);
    }
    return int();
  }
  inline operator unsigned long int() const {
    if (is_valid_ == true &&
        std::holds_alternative<unsigned long int>(value_) == true) {
      return std::get<unsigned long int>(value_);
    }
    return int();
  }
  inline operator signed long long int() const {
    if (is_valid_ == true &&
        std::holds_alternative<signed long long int>(value_) == true) {
      return std::get<signed long long int>(value_);
    }
    return int();
  }
  inline operator unsigned long long int() const {
    if (is_valid_ == true &&
        std::holds_alternative<unsigned long long int>(value_) == true) {
      return std::get<unsigned long long int>(value_);
    }
    return int();
  }
  inline operator float() const {
    if (is_valid_ == true && std::holds_alternative<float>(value_) == true) {
      return std::get<float>(value_);
    }
    return float();
  }
  inline operator double() const {
    if (is_valid_ == true && std::holds_alternative<double>(value_) == true) {
      return std::get<double>(value_);
    }
    return double();
  }
  inline operator long double() const {
    if (is_valid_ == true &&
        std::holds_alternative<long double>(value_) == true) {
      return std::get<long double>(value_);
    }
    return double();
  }
  inline operator std::string() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::string>(value_) == true) {
      return std::get<std::string>(value_);
    }
    return std::string();
  }
  inline operator const char*() const {
    if (is_valid_ == true &&
        std::holds_alternative<const char*>(value_) == true) {
      return std::get<const char*>(value_);
    }
    return NULL;
  }

  operator std::vector<bool>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<bool>>(value_) == true) {
      return std::get<std::vector<bool>>(value_);
    }
    return std::vector<bool>();
  }
  inline operator std::vector<char>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<char>>(value_) == true) {
      return std::get<std::vector<char>>(value_);
    }
    return std::vector<char>();
  }
  inline operator std::vector<signed char>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<signed char>>(value_) == true) {
      return std::get<std::vector<signed char>>(value_);
    }
    return std::vector<signed char>();
  }
  inline operator std::vector<unsigned char>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<unsigned char>>(value_) == true) {
      return std::get<std::vector<unsigned char>>(value_);
    }
    return std::vector<unsigned char>();
  }
  inline operator std::vector<signed short int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<signed short int>>(value_) == true) {
      return std::get<std::vector<signed short int>>(value_);
    }
    return std::vector<signed short int>();
  }
  inline operator std::vector<unsigned short int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<unsigned short int>>(value_) ==
            true) {
      return std::get<std::vector<unsigned short int>>(value_);
    }
    return std::vector<unsigned short int>();
  }
  inline operator std::vector<signed int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<signed int>>(value_) == true) {
      return std::get<std::vector<signed int>>(value_);
    }
    return std::vector<signed int>();
  }
  inline operator std::vector<unsigned int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<unsigned int>>(value_) == true) {
      return std::get<std::vector<unsigned int>>(value_);
    }
    return std::vector<unsigned int>();
  }
  inline operator std::vector<signed long int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<signed long int>>(value_) == true) {
      return std::get<std::vector<signed long int>>(value_);
    }
    return std::vector<signed long int>();
  }
  inline operator std::vector<unsigned long int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<unsigned long int>>(value_) ==
            true) {
      return std::get<std::vector<unsigned long int>>(value_);
    }
    return std::vector<unsigned long int>();
  }
  inline operator std::vector<signed long long int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<signed long long int>>(value_) ==
            true) {
      return std::get<std::vector<signed long long int>>(value_);
    }
    return std::vector<signed long long int>();
  }
  inline operator std::vector<unsigned long long int>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<unsigned long long int>>(value_) ==
            true) {
      return std::get<std::vector<unsigned long long int>>(value_);
    }
    return std::vector<unsigned long long int>();
  }
  inline operator std::vector<float>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<float>>(value_) == true) {
      return std::get<std::vector<float>>(value_);
    }
    return std::vector<float>();
  }
  inline operator std::vector<double>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<double>>(value_) == true) {
      return std::get<std::vector<double>>(value_);
    }
    return std::vector<double>();
  }
  inline operator std::vector<long double>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<long double>>(value_) == true) {
      return std::get<std::vector<long double>>(value_);
    }
    return std::vector<long double>();
  }
  inline operator std::vector<std::string>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<std::string>>(value_) == true) {
      return std::get<std::vector<std::string>>(value_);
    }
    return std::vector<std::string>();
  }
  inline operator std::vector<const char*>() const {
    if (is_valid_ == true &&
        std::holds_alternative<std::vector<const char*>>(value_) == true) {
      return std::get<std::vector<const char*>>(value_);
    }
    return std::vector<const char*>();
  }

 private:
  bool is_valid_;
  std::variant<
      bool, char, signed char, unsigned char, signed short int,
      unsigned short int, signed int, unsigned int, signed long int,
      unsigned long int, signed long long int, unsigned long long int, float,
      double, long double, std::string, const char*, std::vector<bool>,
      std::vector<char>, std::vector<signed char>, std::vector<unsigned char>,
      std::vector<signed short int>, std::vector<unsigned short int>,
      std::vector<signed int>, std::vector<unsigned int>,
      std::vector<signed long int>, std::vector<unsigned long int>,
      std::vector<signed long long int>, std::vector<unsigned long long int>,
      std::vector<float>, std::vector<double>, std::vector<long double>,
      std::vector<std::string>, std::vector<const char*>>
      value_;
};

bool operator==(const Variable& lhs, const Variable& rhs) {
  return lhs.GetValue() == rhs.GetValue();
}
bool operator!=(const Variable& lhs, const Variable& rhs) {
  return lhs.GetValue() != rhs.GetValue();
}
bool operator<(const Variable& lhs, const Variable& rhs) {
  return lhs.GetValue() < rhs.GetValue();
}
bool operator>(const Variable& lhs, const Variable& rhs) {
  return lhs.GetValue() > rhs.GetValue();
}
bool operator<=(const Variable& lhs, const Variable& rhs) {
  return lhs.GetValue() <= rhs.GetValue();
}
bool operator>=(const Variable& lhs, const Variable& rhs) {
  return lhs.GetValue() >= rhs.GetValue();
}

std::ostream& operator<<(std::ostream& out, const Variable& lhs) {
  std::variant<
      bool, char, signed char, unsigned char, signed short int,
      unsigned short int, signed int, unsigned int, signed long int,
      unsigned long int, signed long long int, unsigned long long int, float,
      double, long double, std::string, const char*, std::vector<bool>,
      std::vector<char>, std::vector<signed char>, std::vector<unsigned char>,
      std::vector<signed short int>, std::vector<unsigned short int>,
      std::vector<signed int>, std::vector<unsigned int>,
      std::vector<signed long int>, std::vector<unsigned long int>,
      std::vector<signed long long int>, std::vector<unsigned long long int>,
      std::vector<float>, std::vector<double>, std::vector<long double>,
      std::vector<std::string>, std::vector<const char*>>
      val = lhs.GetValue();
  if (std::holds_alternative<bool>(val)) {
    out << std::get<bool>(val);
  } else if (std::holds_alternative<char>(val)) {
    out << std::get<char>(val);
  } else if (std::holds_alternative<signed char>(val)) {
    out << std::get<signed char>(val);
  } else if (std::holds_alternative<unsigned char>(val)) {
    out << std::get<unsigned char>(val);
  } else if (std::holds_alternative<signed short int>(val)) {
    out << std::get<signed short int>(val);
  } else if (std::holds_alternative<unsigned short int>(val)) {
    out << std::get<unsigned short int>(val);
  } else if (std::holds_alternative<signed int>(val)) {
    out << std::get<signed int>(val);
  } else if (std::holds_alternative<unsigned int>(val)) {
    out << std::get<unsigned int>(val);
  } else if (std::holds_alternative<signed long int>(val)) {
    out << std::get<signed long int>(val);
  } else if (std::holds_alternative<unsigned long int>(val)) {
    out << std::get<unsigned long int>(val);
  } else if (std::holds_alternative<signed long long int>(val)) {
    out << std::get<signed long long int>(val);
  } else if (std::holds_alternative<unsigned long long int>(val)) {
    out << std::get<unsigned long long int>(val);
  } else if (std::holds_alternative<float>(val)) {
    out << std::get<float>(val);
  } else if (std::holds_alternative<double>(val)) {
    out << std::get<double>(val);
  } else if (std::holds_alternative<long double>(val)) {
    out << std::get<long double>(val);
  } else if (std::holds_alternative<std::string>(val)) {
    out << std::get<std::string>(val);
  } else if (std::holds_alternative<const char*>(val)) {
    out << std::get<const char*>(val);
  } else if (std::holds_alternative<std::vector<bool>>(val)) {
    std::vector<bool> vec = std::get<std::vector<bool>>(val);
    for (std::vector<bool>::iterator it = vec.begin(); it != vec.end(); ++it) {
      out << static_cast<bool>(*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<char>>(val)) {
    std::vector<char> vec = std::get<std::vector<char>>(val);
    for (std::vector<char>::iterator it = vec.begin(); it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<signed char>>(val)) {
    std::vector<signed char> vec = std::get<std::vector<signed char>>(val);
    for (std::vector<signed char>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<unsigned char>>(val)) {
    std::vector<unsigned char> vec = std::get<std::vector<unsigned char>>(val);
    for (std::vector<unsigned char>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<signed short int>>(val)) {
    std::vector<signed short int> vec =
        std::get<std::vector<signed short int>>(val);
    for (std::vector<signed short int>::iterator it = vec.begin();
         it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<unsigned short int>>(val)) {
    std::vector<unsigned short int> vec =
        std::get<std::vector<unsigned short int>>(val);
    for (std::vector<unsigned short int>::iterator it = vec.begin();
         it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<signed int>>(val)) {
    std::vector<signed int> vec = std::get<std::vector<signed int>>(val);
    for (std::vector<signed int>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<unsigned int>>(val)) {
    std::vector<unsigned int> vec = std::get<std::vector<unsigned int>>(val);
    for (std::vector<unsigned int>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<signed long int>>(val)) {
    std::vector<signed long int> vec =
        std::get<std::vector<signed long int>>(val);
    for (std::vector<signed long int>::iterator it = vec.begin();
         it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<unsigned long int>>(val)) {
    std::vector<unsigned long int> vec =
        std::get<std::vector<unsigned long int>>(val);
    for (std::vector<unsigned long int>::iterator it = vec.begin();
         it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<signed long long int>>(val)) {
    std::vector<signed long long int> vec =
        std::get<std::vector<signed long long int>>(val);
    for (std::vector<signed long long int>::iterator it = vec.begin();
         it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<unsigned long long int>>(val)) {
    std::vector<unsigned long long int> vec =
        std::get<std::vector<unsigned long long int>>(val);
    for (std::vector<unsigned long long int>::iterator it = vec.begin();
         it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<float>>(val)) {
    std::vector<float> vec = std::get<std::vector<float>>(val);
    for (std::vector<float>::iterator it = vec.begin(); it != vec.end(); ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<double>>(val)) {
    std::vector<double> vec = std::get<std::vector<double>>(val);
    for (std::vector<double>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<long double>>(val)) {
    std::vector<long double> vec = std::get<std::vector<long double>>(val);
    for (std::vector<long double>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<std::string>>(val)) {
    std::vector<std::string> vec = std::get<std::vector<std::string>>(val);
    for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  } else if (std::holds_alternative<std::vector<const char*>>(val)) {
    std::vector<const char*> vec = std::get<std::vector<const char*>>(val);
    for (std::vector<const char*>::iterator it = vec.begin(); it != vec.end();
         ++it) {
      out << (*it);
      if (it != --vec.end()) {
        out << ", ";
      }
    }
  }
  return out;
}

}  // namespace estl

#endif  // ESTL_VARIABLE_HPP_
