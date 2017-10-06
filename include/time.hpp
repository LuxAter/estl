// Copyright 2017 Arden
#ifndef ESTL_TIME_HPP_
#define ESTL_TIME_HPP_

#include <time.h>
#include <string>
#include <utility>

namespace estl {
class Time {
 public:
  Time();
  Time(const Time& copy);
  explicit Time(unsigned int t);
  explicit Time(int t);
  explicit Time(double t);
  ~Time();

  void SetTimeUI(unsigned int t);
  void SetTimeI(int t);
  void SetTimeD(double t);
  unsigned int GetTimeUI();
  int GetTimeI();
  double GetTimeD();

  void ReadFormat(std::string fmt, std::string str);
  std::string Format(std::string fmt);

  int sec, min, hour, milli_sec, micro_sec, nano_sec;

 private:
  std::pair<int, int> ReadInt(std::string str, int i);
  std::pair<double, int> ReadDouble(std::string str, int i);
};
}  // namespace estl

#endif  // ESTL_TIME_HPP_
