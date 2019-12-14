#include "LightStatusHandler.h"

LightStatusHandler::LightStatusHandler(int minOn, int maxOff) {
    _minOn = minOn;
    _maxOff = maxOff;

    _lastChangeMillis = 0;
    _lightStatus = false;
    
    _timer = new Timer();
}

bool LightStatusHandler::hasChanged(int reading) {
    bool newStatus;
    if (reading > _minOn) newStatus = true;
    else if (reading < _maxOff) newStatus = false;
    else newStatus = _lightStatus;

    bool hasChanged = newStatus != _lightStatus;
    if (hasChanged) _timer->reset();
    _lightStatus = newStatus;
    return hasChanged;
}

String LightStatusHandler::statusToString() {
    String state;
    String pastState;

    if (_lightStatus) {
        state = "ON";
        pastState = "dark";
    }
    else {
        state = "OFF";
        pastState = "light";
    }

    String str = "Lights are ";
    str += state;
    str += ". It was ";
    str += pastState;
    str += " for ";
    str += _timer->getLastTime();
    str += ".";

    return str;
}