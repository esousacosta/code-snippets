#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class ILogger {
 public:
  virtual ~ILogger() = default;

  enum class LogLevel { Error, Info, Debug };

  virtual void log(std::string_view iLogMessage, LogLevel iLogLevel) = 0;
  virtual void setLogLevel(LogLevel iLogLevel) = 0;
};

class Logger : public ILogger {
 public:
  Logger(std::string_view iOutputFile);
  virtual ~Logger();

  void log(std::string_view iLogMessage, LogLevel iLogLevel) override;
  void setLogLevel(LogLevel iLogLevel) override { m_logLevel = iLogLevel; }

 private:
  std::string getLogLevelAsString() const;

  std::ofstream m_outputFile;
  LogLevel m_logLevel{LogLevel::Error};
};

Logger::Logger(std::string_view iOutputFile) {
  m_outputFile.open(iOutputFile.data(), std::ios::app);
  if (!m_outputFile.good()) {
    throw std::runtime_error{"Unable to initialize the looger. Exiting..."};
  }
}

Logger::~Logger() {
  std::cout << "Closing log file..." << std::endl;
  m_outputFile.close();
}

void Logger::log(std::string_view iLogMessage, LogLevel iLogLevel) {
  // No logging of less severe messages that the minimum level
  if (m_logLevel < iLogLevel) return;

  if (!m_outputFile.good()) {
    throw std::runtime_error("Output file in corrupted state.");
  }

  const std::string logMessage =
      std::string{getLogLevelAsString() + iLogMessage.data() + "\n"}.c_str();

  m_outputFile.write(logMessage.c_str(), logMessage.size());
}

std::string Logger::getLogLevelAsString() const {
  switch (m_logLevel) {
    case LogLevel::Error:
      return "ERROR - ";
    case LogLevel::Info:
      return "INFO - ";
    case LogLevel::Debug:
      return "DEBUG - ";
  }

  throw std::runtime_error("Unexpected log level on the logger. Exiting...");
}

class Foo final {
 public:
  // Dependency Injection
  explicit Foo(ILogger& iLogger) : m_logger(iLogger) {}
  ~Foo() = default;

  void doSometing();

 private:
  ILogger& m_logger;
};

void Foo::doSometing() {
  m_logger.log("Unrecognized information. Exiting...", ILogger::LogLevel::Info);
}

int main() {
  Logger logger{"logs.out"};
  logger.setLogLevel(ILogger::LogLevel::Debug);

  Foo f{logger};
  logger.log("Olá, meu chapa!", ILogger::LogLevel::Debug);
  logger.log("Network failure.", ILogger::LogLevel::Error);
  f.doSometing();

  return 0;
}