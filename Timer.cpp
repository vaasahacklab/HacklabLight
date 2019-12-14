#include "Timer.h"

Timer::Timer() {
    _start = 0;
    reset();
}

void Timer::reset() {
    _lastTime = millis() - _start;
    _start = millis();
}

String Timer::getLastTime() {
    unsigned long totalSeconds = _lastTime / 1000;
    int totalMinutes = totalSeconds / 60;
    int totalHours = totalMinutes / 60;
    int totalDays = totalHours / 24;

    String str = "";
    
    if (totalDays) {
        str += totalDays ;

        if (totalDays == 1) str += " day, ";
        else str += " days, ";

        str += totalHours % 24 ;

        if (totalHours % 24 == 1) str += " hour";
        else str += " hours";

    } else if (totalHours) {
        str += totalHours;

        if (totalHours == 1) str += " hour, ";
        else str += " hours, ";

        str += totalMinutes % 60 ;

        if (totalMinutes % 60 == 1) str += " minute";
        else str += " minutes";

    } else if (totalMinutes) {
        str += totalMinutes;

        if (totalMinutes == 1) str += " minute, ";
        else str += " minutes, ";

        str += totalSeconds % 60 ;

        if (totalSeconds % 60 == 1) str += " second";
        else str += " seconds";
    } else {
        str += totalSeconds;
        if (totalSeconds == 1) str += " second";
        else str += " seconds";
    }

    return str;
}