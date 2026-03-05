#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class PIR {
public:
    PIR(int pin);
    void start();  // Usunięto argumenty
    void update(); // Usunięto argumenty
    void setDelay(unsigned int delaySeconds);
    void setEnable(bool en);
    bool isTriggered();

private:
    int pin;
    bool enabled;
    bool hasTimerStarted = false;
    bool startNightModeState;
    unsigned int delaySeconds = 5;
    unsigned long lastChange;
};

#endif