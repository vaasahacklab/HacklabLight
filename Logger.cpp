#include "Logger.h"

Logger::Logger() {}

void Logger::init(LogLevel logLevel, Print *output) {
    _logLevel = logLevel;
    _output = output;
}

void Logger::debug(String message) { 
    if (_logLevel >= LogLevel::Debug) _output->println("[DEBUG]: " + message);
}

void Logger::info(String message) {
    if (_logLevel >= LogLevel::Info) _output->println("[INFO]: " + message);
}

void Logger::error(String message) {
    if (_logLevel >= LogLevel::Error) _output->println("[ERROR]: " + message);
}
