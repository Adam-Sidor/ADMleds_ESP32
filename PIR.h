#ifndef ADMLEDS_PIR_H
#define ADMLEDS_PIR_H

#include <Arduino.h>

class PIR {
    uint8_t pin;
    unsigned int delaySeconds;
    bool startNightModeState;
    bool hasTimerStarted;
    unsigned int lastChange;
    bool enabled;
public:
    PIR(int pin);
    void start(bool &nightMode, bool &ledStatus);
    void update(bool &nightMode, bool &ledStatus);
    void setDelay(unsigned int delaySeconds);
    void setEnable(bool en);
    bool isTriggered();
};

#endif