#ifndef ArduinoOtaHandler_h
#define ArduinoOtaHandler_h

#include <ArduinoOTA.h>

#include "Logger.h"

class ArduinoOtaHandler
{
  public:
    ArduinoOtaHandler();
    void setup(Logger *logger, int port, const char* hostname, const char* password);
    void handle();

  private:
    Logger *_logger;
};

#endif
