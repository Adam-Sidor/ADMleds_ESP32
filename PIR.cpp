#include "PIR.h"
#include "GlobalConfig.h"

extern DeviceConfig cfg;

PIR::PIR(int pin):pin(pin), enabled(true) {
    pinMode(pin,INPUT_PULLUP);
}

void PIR::start() {
    startNightModeState = cfg.isNightModeOn;
    cfg.isNightModeOn = true;
    cfg.ledStatus = true;
    hasTimerStarted = true;
    lastChange = millis();
}

void PIR::update() {
    if (hasTimerStarted) {
        if (millis() - lastChange >= delaySeconds * 1000) {
            cfg.isNightModeOn = startNightModeState;
            cfg.ledStatus = false;
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