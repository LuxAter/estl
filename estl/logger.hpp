#ifndef ESTL_LOGGER_HPP_
#define ESTL_LOGGER_HPP_

#include <memory>

namespace estl {
namespace logger {
  class Logger {
   public:
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    std::shared_ptr<Logger> GetInstance() {
      if (instance == nullptr) {
        instance = std::shared_ptr<Logger>(new Logger());
      }
      return instance;
    }


   private:
    std::shared_ptr<Logger> instance = nullptr;
    Logger() {}
  };

}  // namespace logger
}  // namespace estl

#endif  // ESTL_LOGGER_HPP_
