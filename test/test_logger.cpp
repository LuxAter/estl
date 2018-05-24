#include "gtest/gtest.h"
#include "logger.hpp"

using namespace estl::logger;

TEST(LoggerTest, ConsoleLogger) {
  testing::internal::CaptureStdout();
  ConsoleLogger::Get()->FormatAll(
      "[__TYPE__] (__FILE__:__FUNC__:__LINE__) __BODY__");
  ConsoleLogFatal("This is an %s test", "fatal");
  ConsoleLogError("This is a %d test", 2);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output,
            "[FATAL  ] (test_logger.cpp:TestBody:10) This is an fatal "
            "test\n[ERROR  ] (test_logger.cpp:TestBody:11) This is a 2 test\n");
}

TEST(LoggerTest, FileLogger) {
  FileLogger::Get()->Open("tmp.txt");
  FileLogger::Get()->FormatAll(
      "[__TYPE__] (__FILE__:__FUNC__:__LINE__) __BODY__");
  FileLogWarning("This is a %f test", 3.1415);
  std::ifstream load("tmp.txt");
  std::string output;
  if (load.is_open()) {
    std::string line;
    while (std::getline(load, line)) {
      output += line + "\n";
    }
    load.close();
    remove("tmp.txt");
  }
  EXPECT_EQ(
      output,
      "[WARNING] (test_logger.cpp:TestBody:22) This is a 3.141500 test\n");
}

TEST(LoggerTest, DailyLogger) {
  DailyLogger::Get()->FormatAll(
      "[__TYPE__] (__FILE__:__FUNC__:__LINE__) __BODY__");
  DailyLogSuccess("This is a Success!");
  char fmt[255];
  std::time_t raw_time;
  std::time(&raw_time);
  std::tm* current_tm = std::localtime(&raw_time);
  std::strftime(fmt, 255, "%Y-%m-%d", current_tm);
  std::string date_str(fmt);
  std::ifstream load(date_str + ".log");
  std::string output;
  if (load.is_open()) {
    std::string line;
    while (std::getline(load, line)) {
      output += line + "\n";
    }
    load.close();
    remove((date_str + ".log").c_str());
  }
  EXPECT_EQ(output,
            "[SUCCESS] (test_logger.cpp:TestBody:41) This is a Success!\n");
}

TEST(LoggerTest, CounterLogger) {
  CounterLogger::Get()->FormatAll(
      "[__TYPE__] (__FILE__:__FUNC__:__LINE__) __BODY__");
  CounterLogger::Get()->SetPath("test");
  CounterLogDebug("This is a debug message");
  CounterLogTrace("This is a trace message");
  CounterLogger::Get()->Flush();
  std::ifstream load("test.log");
  std::string output;
  if (load.is_open()) {
    std::string line;
    while (std::getline(load, line)) {
      output += line + "\n";
    }
    load.close();
    remove("test.log");
  }
  EXPECT_EQ(output,
            "[DEBUG  ] (test_logger.cpp:TestBody:66) This is a debug "
            "message\n[TRACE  ] (test_logger.cpp:TestBody:67) This is a trace "
            "message\n");
}

TEST(LoggerTest, StreamLogger) {
  std::stringstream ss;
  StreamLogger::Get()->FormatAll(
      "[__TYPE__] (__FILE__:__FUNC__:__LINE__) __BODY__");
  StreamLogger::Get()->SetStream(&ss);
  StreamLogInfo("This is an info message");
  StreamLogVersion("This is version information");
  std::string output = ss.str();
  EXPECT_EQ(output,
            "[INFO   ] (test_logger.cpp:TestBody:90) This is an info "
            "message\n[VESION ] (test_logger.cpp:TestBody:91) This is version "
            "information\n");
}
