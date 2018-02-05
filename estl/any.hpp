#ifndef ESTL_ANY_HPP_
#define ESTL_ANY_HPP_

#include <any>
#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::any& lhs) {
  if (lhs.type() == typeid(bool)) {
    out << std::any_cast<bool>(lhs);
  } else if (lhs.type() == typeid(char)) {
    out << std::any_cast<char>(lhs);
  } else if (lhs.type() == typeid(signed char)) {
    out << std::any_cast<signed char>(lhs);
  } else if (lhs.type() == typeid(unsigned char)) {
    out << std::any_cast<unsigned char>(lhs);
  } else if (lhs.type() == typeid(signed short int)) {
    out << std::any_cast<signed short int>(lhs);
  } else if (lhs.type() == typeid(unsigned short int)) {
    out << std::any_cast<unsigned short int>(lhs);
  } else if (lhs.type() == typeid(signed int)) {
    out << std::any_cast<signed int>(lhs);
  } else if (lhs.type() == typeid(unsigned int)) {
    out << std::any_cast<unsigned int>(lhs);
  } else if (lhs.type() == typeid(signed long int)) {
    out << std::any_cast<signed long int>(lhs);
  } else if (lhs.type() == typeid(unsigned long int)) {
    out << std::any_cast<unsigned long int>(lhs);
  } else if (lhs.type() == typeid(signed long long int)) {
    out << std::any_cast<signed long long int>(lhs);
  } else if (lhs.type() == typeid(unsigned long long int)) {
    out << std::any_cast<unsigned long long int>(lhs);
  } else if (lhs.type() == typeid(float)) {
    out << std::any_cast<float>(lhs);
  } else if (lhs.type() == typeid(double)) {
    out << std::any_cast<double>(lhs);
  } else if (lhs.type() == typeid(long double)) {
    out << std::any_cast<long double>(lhs);
  } else if (lhs.type() == typeid(const char*)) {
    out << std::any_cast<const char*>(lhs);
  } else if (lhs.type() == typeid(std::string)) {
    out << std::any_cast<std::string>(lhs);
  } else {
    out << "UNKNOWN";
  }
  return out;
}

bool operator==(const std::any& lhs, const std::any& rhs) {
  if (lhs.type() != rhs.type()) {
    return false;
  } else {
    if (lhs.type() == typeid(bool)) {
      return std::any_cast<bool>(lhs) == std::any_cast<bool>(rhs);
    } else if (lhs.type() == typeid(char)) {
      return std::any_cast<char>(lhs) == std::any_cast<char>(rhs);
    } else if (lhs.type() == typeid(signed char)) {
      return std::any_cast<signed char>(lhs) == std::any_cast<signed char>(rhs);
    } else if (lhs.type() == typeid(unsigned char)) {
      return std::any_cast<unsigned char>(lhs) ==
             std::any_cast<unsigned char>(rhs);
    } else if (lhs.type() == typeid(signed short int)) {
      return std::any_cast<signed short int>(lhs) ==
             std::any_cast<signed short int>(rhs);
    } else if (lhs.type() == typeid(unsigned short int)) {
      return std::any_cast<unsigned short int>(lhs) ==
             std::any_cast<unsigned short int>(rhs);
    } else if (lhs.type() == typeid(signed int)) {
      return std::any_cast<signed int>(lhs) == std::any_cast<signed int>(rhs);
    } else if (lhs.type() == typeid(unsigned int)) {
      return std::any_cast<unsigned int>(lhs) ==
             std::any_cast<unsigned int>(rhs);
    } else if (lhs.type() == typeid(signed long int)) {
      return std::any_cast<signed long int>(lhs) ==
             std::any_cast<signed long int>(rhs);
    } else if (lhs.type() == typeid(unsigned long int)) {
      return std::any_cast<unsigned long int>(lhs) ==
             std::any_cast<unsigned long int>(rhs);
    } else if (lhs.type() == typeid(signed long long int)) {
      return std::any_cast<signed long long int>(lhs) ==
             std::any_cast<signed long long int>(rhs);
    } else if (lhs.type() == typeid(unsigned long long int)) {
      return std::any_cast<unsigned long long int>(lhs) ==
             std::any_cast<unsigned long long int>(rhs);
    } else if (lhs.type() == typeid(float)) {
      return std::any_cast<float>(lhs) == std::any_cast<float>(rhs);
    } else if (lhs.type() == typeid(double)) {
      return std::any_cast<double>(lhs) == std::any_cast<double>(rhs);
    } else if (lhs.type() == typeid(long double)) {
      return std::any_cast<long double>(lhs) == std::any_cast<long double>(rhs);
    } else if (lhs.type() == typeid(const char*)) {
      return std::any_cast<const char*>(lhs) == std::any_cast<const char*>(rhs);
    } else if (lhs.type() == typeid(std::string)) {
      return std::any_cast<std::string>(lhs) == std::any_cast<std::string>(rhs);
    }
  }
  return false;
}

bool operator!=(const std::any& lhs, const std::any& rhs) {
  return !(lhs == rhs);
}

bool operator<(const std::any& lhs, const std::any& rhs) {
  if (lhs.type() != rhs.type()) {
    return false;
  } else {
    if (lhs.type() == typeid(bool)) {
      return std::any_cast<bool>(lhs) < std::any_cast<bool>(rhs);
    } else if (lhs.type() == typeid(char)) {
      return std::any_cast<char>(lhs) < std::any_cast<char>(rhs);
    } else if (lhs.type() == typeid(signed char)) {
      return std::any_cast<signed char>(lhs) < std::any_cast<signed char>(rhs);
    } else if (lhs.type() == typeid(unsigned char)) {
      return std::any_cast<unsigned char>(lhs) <
             std::any_cast<unsigned char>(rhs);
    } else if (lhs.type() == typeid(signed short int)) {
      return std::any_cast<signed short int>(lhs) ==
             std::any_cast<signed short int>(rhs);
    } else if (lhs.type() == typeid(unsigned short int)) {
      return std::any_cast<unsigned short int>(lhs) <
             std::any_cast<unsigned short int>(rhs);
    } else if (lhs.type() == typeid(signed int)) {
      return std::any_cast<signed int>(lhs) < std::any_cast<signed int>(rhs);
    } else if (lhs.type() == typeid(unsigned int)) {
      return std::any_cast<unsigned int>(lhs) <
             std::any_cast<unsigned int>(rhs);
    } else if (lhs.type() == typeid(signed long int)) {
      return std::any_cast<signed long int>(lhs) <
             std::any_cast<signed long int>(rhs);
    } else if (lhs.type() == typeid(unsigned long int)) {
      return std::any_cast<unsigned long int>(lhs) <
             std::any_cast<unsigned long int>(rhs);
    } else if (lhs.type() == typeid(signed long long int)) {
      return std::any_cast<signed long long int>(lhs) <
             std::any_cast<signed long long int>(rhs);
    } else if (lhs.type() == typeid(unsigned long long int)) {
      return std::any_cast<unsigned long long int>(lhs) <
             std::any_cast<unsigned long long int>(rhs);
    } else if (lhs.type() == typeid(float)) {
      return std::any_cast<float>(lhs) < std::any_cast<float>(rhs);
    } else if (lhs.type() == typeid(double)) {
      return std::any_cast<double>(lhs) < std::any_cast<double>(rhs);
    } else if (lhs.type() == typeid(long double)) {
      return std::any_cast<long double>(lhs) < std::any_cast<long double>(rhs);
    } else if (lhs.type() == typeid(const char*)) {
      return std::any_cast<const char*>(lhs) < std::any_cast<const char*>(rhs);
    } else if (lhs.type() == typeid(std::string)) {
      return std::any_cast<std::string>(lhs) < std::any_cast<std::string>(rhs);
    }
  }
  return false;
}

bool operator>(const std::any& lhs, const std::any& rhs) { return rhs < lhs; }
bool operator<=(const std::any& lhs, const std::any& rhs) {
  return !(rhs < lhs);
}
bool operator>=(const std::any& lhs, const std::any& rhs) {
  return !(lhs < rhs);
}

#endif  // ESTL_ANY_HPP_
