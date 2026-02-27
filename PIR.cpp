#include "PIR.h"


PIR::PIR(int pin):pin(pin), enabled(true) {
    pinMode(pin,INPUT_PULLUP);
}

void PIR::start(bool &nightMode, bool &ledStatus) {
    startNightModeState = nightMode;
    nightMode = true;
    ledStatus = true;
    hasTimerStarted = true;
    lastChange = millis();
}

void PIR::update(bool &nightMode, bool &ledStatus) {
    if (hasTimerStarted) {
        if (millis() - lastChange >= delaySeconds * 1000) {
            nightMode = startNightModeState;
            ledStatus = false;
            hasTimerStarted = false;
        }
    }
}

void PIR::setDelay(unsigned int delaySeconds) {
    this->delaySeconds = delaySeconds;
}

void PIR::setEnable(bool en) {
    enabled = en;
}

bool PIR::isTriggered() {
    return !digitalRead(pin) && enabled;
}