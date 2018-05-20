#include <iostream>

// #include "argparse/variable.hpp"
// #include "argparse.hpp"
// #include "format.hpp"

// #include <climits>
// #include "matrix.hpp"
// #include "stream.hpp"
// #include "variable.hpp"
// #include "variadic.hpp"
// #include "vector.hpp"
#include "logger.hpp"
using namespace estl::logger;

void test();

int main(int argc, char const* argv[]) {
  // Logger::instance = NULL;
  // auto console = Logger::GetInstance();
  // auto conosole = Logger::instance;
  // ConsoleLogger lg;
  ConsoleLogger *lg = ConsoleLogger::Get();
  lg->SetColor(false);
  lg->LogFatal("Fatal log message");
  test();
  lg->LogVersion("Info log message");
  ConsoleLogFatal("OH NO %s!!", "GO");
  // lg.LogError("Error log message");
  // lg.LogWarning("Error log message");
  // lg.LogSuccess("Error log message");
  // lg.LogDebug("Error log message");
  // lg.LogTrace("Error log message");
  // lg.LogInfo("Error log message");
  // lg.LogVersion("Error log message");
  DailyLogger dl("./log");
  dl.LogWarning("This is a warning message");
  CounterLogger cl("./log/test");
  cl.LogError("This is an error");

  return 0;
}
