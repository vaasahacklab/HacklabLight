#ifndef LIGHTCONF_H
#define LIGHTCONF_H

#include "globals.h"

const char* ssid = "WifiName";
const char* pass = "TotallySecret";

const char* server = "matrix.example.com";
const char* room = "!RoomIDString:example.com";
const char* accessToken = "FreakingLongAccessTokenString";

const int LDR_PIN = A0;

// minimum sensor reading when lights are considered ON
const int minOn = 950;

// maximum sensor reading when lights are considered OFF
const int maxOff = 700;

const unsigned int loopInterval = 5*1000;

const LogLevel logLevel = LogLevel::Info;
const int baudRate = 115200;

#endif
