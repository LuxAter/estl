#ifndef ESTL_ARGPARSE_DATA_HPP_
#define ESTL_ARGPARSE_DATA_HPP_

#include <string>
#include <variant>
#include <vector>

namespace estl {
namespace argparse {
  class DataValue {
   public:
    DataValue() : is_valid_(false) {}
    DataValue(const DataValue& copy)
        : is_valid_(copy.is_valid_), value_(copy.value_) {}
    ~DataValue() {}

    bool IsValid() { return is_valid_; }

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
        value_ = (signed short int)15;
  };
}  // namespace argparse
}  // namespace estl

#endif  // ESTL_ARGPARSE_DATA_HPP_
