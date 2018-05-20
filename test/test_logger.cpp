#include "logger.hpp"
#include "gtest/gtest.h"

using namespace estl::logger;

TEST(LoggerTest, ConsoleLogger){
 testing::internal::CaptureStdout();
 ConsoleLogger::Get()->FormatAll("[__TYPE__] (__FILE__:__FUNC__:__LINE__) __BODY__");
 ConsoleLogError("This is an %s test", "error");
 std::string output = testing::internal::GetCapturedStdout();
 EXPECT_EQ(output, "[ERROR  ] (test_logger.cpp:TestBody:9) This is an error test\n");
}
