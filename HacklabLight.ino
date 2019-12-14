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
#include "conf.h"

LightStatusHandler lightStatusHandler(minOn, maxOff);

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
  
  connectToWifi();
}

void loop() {
  if (millis() - lastMillis > loopInterval) {
    lastMillis = millis();
    if(WiFi.status() != WL_CONNECTED) {
      connectToWifi();
    }

    int lights = analogRead(LDR_PIN);

    if (lightStatusHandler.hasChanged(lights)) {
      sendStatus(lightStatusHandler.statusToString());
    }
  }
}

void connectToWifi() {
  Serial.println("");
  Serial.print("[NETWORK]: Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  // Wait for connection, print '.' every 500ms until connected
  Serial.print("[NETWORK]: ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("[NETWORK]: IP address: ");
  Serial.println(WiFi.localIP());
}

void sendStatus(String status) {
  Serial.print("[HTTP]: Sending message: ");
  Serial.println(status);

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

  #ifdef DEBUG
    Serial.println("[DEBUG]: [HTTP]: Trying URL: ");
    Serial.print("  ");
    Serial.println(url);
    Serial.println("[DEBUG]: [HTTP]: With message content:");
    Serial.print("  ");
    Serial.println(messageContent);
  #endif
  
  matrix.begin(*client, url);
  matrix.addHeader("Content-Type", "application/json");
  matrix.addHeader("Authorization", "Bearer " + String(accessToken));

  int httpCode = matrix.POST(messageContent);

  if(httpCode > 0) { // httpCode will be negative on error
    if(httpCode == HTTP_CODE_OK) {      
      Serial.printf("[HTTP]: OK, code: %d\n", httpCode);

      #ifdef DEBUG
        String payload = matrix.getString();
        Serial.println("[DEBUG]: [HTTP]: Response: " + payload);
      #endif
      
    } else {
      Serial.printf("[HTTP]: error, code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP]: POST failed, error: %s\n", matrix.errorToString(httpCode).c_str());
  }
  matrix.end();
}
