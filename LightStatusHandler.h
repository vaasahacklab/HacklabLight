#ifndef LightStatusHandler_h
#define LightStatusHandler_h

#include "Arduino.h"
#include "Timer.h"

class LightStatusHandler
{
  public:
    LightStatusHandler(int minOn, int maxOff);
    bool hasChanged(int reading);
    String statusToString();

    bool _lightStatus;
  private:
    Timer* _timer;
    int _minOn;
    int _maxOff;

    unsigned long _lastChangeMillis;
};

#endif