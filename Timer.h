#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer
{
  public:
    Timer();
    void reset();
    String getLastTime();
  private:
    unsigned long _start;
    unsigned long _lastTime;
};

#endif