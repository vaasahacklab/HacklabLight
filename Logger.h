#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include "globals.h"

class Logger
{
  public:
    Logger();

    void init(LogLevel logLevel, Print *output);

    void debug(String message);
    void info(String message);
    void error(String message);

  private:
    LogLevel _logLevel;
    Print *_output;
};

#endif