#include "ArduinoOtaHandler.h"

ArduinoOtaHandler::ArduinoOtaHandler() {}

void ArduinoOtaHandler::setup(Logger *logger, int port, const char* hostname, const char* password)
{
  _logger = logger;

  ArduinoOTA.setPort(port);
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.setPassword(password);

  ArduinoOTA.onStart([this]() {
    this->_logger->debug("OTA started");
  });

  ArduinoOTA.onEnd([this]() {
    this->_logger->debug("OTA ended");
  });

  ArduinoOTA.onProgress([this](unsigned int progress, unsigned int total) {
    this->_logger->debug("OTA Progress: " + (progress / (total / 100)));
  });

  ArduinoOTA.onError([this](ota_error_t error) {
    this->_logger->error("OTA error: " + error);
    if (error == OTA_AUTH_ERROR) this->_logger->error("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) this->_logger->error("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) this->_logger->error("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) this->_logger->error("Receive Failed");
    else if (error == OTA_END_ERROR) this->_logger->error("End Failed");
  });

  ArduinoOTA.begin();
}

void ArduinoOtaHandler::handle() {
  ArduinoOTA.handle();
}
