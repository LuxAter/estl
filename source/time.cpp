// Copyright 2017 Arden

#include "time.hpp"

#include <math.h>
#include <time.h>
#include <sstream>
#include <string>

#include <iostream>

estl::Time::Time()
    : sec(0), min(0), hour(0), milli_sec(0), micro_sec(0), nano_sec(0) {}
estl::Time::Time(const Time& copy)
    : sec(copy.sec),
      min(copy.min),
      hour(copy.hour),
      milli_sec(copy.milli_sec),
      micro_sec(copy.micro_sec),
      nano_sec(copy.nano_sec) {}
estl::Time::Time(unsigned int t) : sec(t) {
  min = sec / 60;
  sec = sec % 60;
  hour = min / 60;
  min = min % 60;
}
estl::Time::Time(int t) : sec(t) {
  min = sec / 60;
  sec = sec % 60;
  hour = min / 60;
  min = min % 60;
}
estl::Time::Time(double t) {
  t += 0.0000000001;
  sec = static_cast<int>(t);
  t = (t - static_cast<double>(sec)) * 1000;
  milli_sec = static_cast<int>(t);
  t = (t - static_cast<double>(milli_sec)) * 1000;
  micro_sec = static_cast<int>(t);
  t = (t - static_cast<double>(micro_sec)) * 1000;
  nano_sec = static_cast<int>(t);
  min = sec / 60;
  sec = sec % 60;
  hour = min / 60;
  min = min % 60;
}

estl::Time::~Time() {}

void estl::Time::SetTimeUI(unsigned int t) {
  sec = t;
  min = sec / 60;
  sec = sec % 60;
  hour = min / 60;
  min = min % 60;
}

void estl::Time::SetTimeI(int t) {
  sec = t;
  min = sec / 60;
  sec = sec % 60;
  hour = min / 60;
  min = min % 60;
}

void estl::Time::SetTimeD(double t) {
  t += 0.0000000001;
  sec = static_cast<int>(t);
  t = (t - static_cast<double>(sec)) * 1000;
  milli_sec = static_cast<int>(t);
  t = (t - static_cast<double>(milli_sec)) * 1000;
  micro_sec = static_cast<int>(t);
  t = (t - static_cast<double>(micro_sec)) * 1000;
  nano_sec = static_cast<int>(t);
  min = sec / 60;
  sec = sec % 60;
  hour = min / 60;
  min = min % 60;
}

unsigned int estl::Time::GetTimeUI() {
  unsigned int time_;
  time_ = 0;
  time_ += sec;
  time_ += (60 * min);
  time_ += (3600 * hour);
  return time_;
}

int estl::Time::GetTimeI() {
  int time_;
  time_ = 0;
  time_ += sec;
  time_ += (60 * min);
  time_ += (3600 * hour);
  return time_;
}

double estl::Time::GetTimeD() {
  double time_;
  time_ = 0;
  time_ += (1.0e-9 * nano_sec);
  time_ += (1.0e-6 * micro_sec);
  time_ += (1.0e-3 * milli_sec);
  time_ += sec;
  time_ += (60 * min);
  time_ += (3600 * hour);
  return time_;
}

std::string estl::Time::Format(std::string fmt) {
  std::stringstream out;
  for (size_t i = 0; i < fmt.size(); i++) {
    if (fmt[i] != '%') {
      out << fmt[i];
      continue;
    }
    i++;
    if (fmt[i] == '%') {
      out << '%';
    } else if (fmt[i] == 'h') {
      out << hour;
    } else if (fmt[i] == 'm') {
      if (i + 1 != fmt.size() && fmt[i + 1] == 's') {
        out << milli_sec;
        i++;
      } else {
        out << min;
      }
    } else if (fmt[i] == 's') {
      out << sec;
    } else if (fmt[i] == 'u' && i + 1 != fmt.size() && fmt[i + 1] == 's') {
      out << micro_sec;
      i++;
    } else if (fmt[i] == 'n' && i + 1 != fmt.size() && fmt[i + 1] == 's') {
      out << nano_sec;
      i++;
    }
  }
  return out.str();
}
