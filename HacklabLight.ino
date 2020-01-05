#include <time.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>

/*  ESP8266 LDR ArduinoIDE https example code
 * 
 *  Based on: https://vaasa.hacklab.fi/2016/02/06/esp8266-on-nodemcu-board-ds18b20-arduinoide-thingspeak/
 *  ESP8266 Witty: http://www.schatenseite.de/en/2016/04/22/esp8266-witty-cloud-module/
 */

#include "LightStatusHandler.h"
#include "Logger.h"
#include "conf.h"

LightStatusHandler lightStatusHandler(minOn, maxOff);
Logger *logger = new Logger();

unsigned long lastMillis = 0;

void setup() {
  pinMode(LDR_PIN, INPUT);

  Serial.begin(baudRate);
  logger->init(logLevel, &Serial);

  connectToWifi();
}

void loop() {
  if (millis() - lastMillis > loopInterval) {
    lastMillis = millis();
    if (WiFi.status() != WL_CONNECTED) {
      connectToWifi();
    }

    int lights = analogRead(LDR_PIN);

    if (lightStatusHandler.hasChanged(lights)) {
      sendStatus(lightStatusHandler.statusToString());
    }
  }
}

void connectToWifi() {
  WiFi.begin(ssid, pass);

  // Wait for connection, print '.' every 500ms until connected
  logger->debug("[NETWORK]: Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    logger->debug(".");
  }

  logger->info("[NETWORK]: IP address: " + WiFi.localIP().toString());
}

void sendStatus(String status) {
  logger->info("[HTTP]: Sending message: " + status);

  String messageContent  = "{\"msgtype\":\"m.notice\", \"body\":\"";
         messageContent += status;
         messageContent += "\"}";
  
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  
  HTTPClient matrix;

  String url  = "https://";
         url += server;
         url += "/_matrix/client/r0/rooms/";
         url += room;
         url += "/send/m.room.message";

  logger->debug("[HTTP]: Trying URL: " + url);
  logger->debug("[HTTP]: With message content:" + messageContent);
  
  matrix.begin(*client, url);
  matrix.addHeader("Content-Type", "application/json");
  matrix.addHeader("Authorization", "Bearer " + String(accessToken));

  int httpCode = matrix.POST(messageContent);

  if(httpCode > 0) { // httpCode will be negative on error
    if(httpCode == HTTP_CODE_OK) {      
      logger->info("[HTTP]: OK, code: " + httpCode);
      logger->debug("[HTTP]: Response: " + matrix.getString());
    } else {
      logger->error("[HTTP]: error, code: " + httpCode);
    }
  } else {
    String error = matrix.errorToString(httpCode).c_str();
    logger->error("[HTTP]: POST failed, error: " + error);
  }
  matrix.end();
}
