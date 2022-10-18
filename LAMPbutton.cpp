#include <Arduino.h>
#include "LAMPbutton.h"

Button::Button(uint8_t Port) { this->Port = Port; }

void Button::begin() {
    pinMode(Port, INPUT_PULLUP);
}

uint32_t Button::hasBeenPressed() {
    uint32_t value = 0;
    if (isPressed()) {
        Count++;
    }
    if (!isPressed() && Count > 0) {
        value = Count;
        Count = 0;
    }
    return value;
}

bool Button::isPressed() {
    return digitalRead(Port) == HIGH;
}

MainController::MainController(uint8_t port1, uint8_t port2, uint8_t NumOfModes) : Butt1(port1), Butt2(port2) {
    this->NumOfModes = NumOfModes;
    Butt1.begin();
    Butt2.begin();
}

COMMAND MainController::getCommand() {
    COMMAND CMND = COMMAND::DO_NOTHING;
    if (millis() - Timer > Rate) {
        Timer = millis();
        if (Butt1.isPressed()) { CMND = COMMAND::ONE_PRESSED; }
        if (Butt2.isPressed()) { CMND = COMMAND::TWO_PRESSED; }
        if (Butt1.isPressed() && Butt2.isPressed()) { CMND = COMMAND::BOTH_PRESSED; }
    }
    return CMND;
}

void MainController::incMainBrightness(int16_t inc) {
    int16_t test = Brightness + inc;
    Brightness = test;
    if (test > 255) {
        Brightness = 255;
    }
    if (BRIGHTNESS_LOW_LIMIT > test) {
        Brightness = BRIGHTNESS_LOW_LIMIT;
    }
}

uint8_t MainController::getMainBrightness() {
    return Brightness;
}

void MainController::switchMode() {
    int8_t test = Mode + 1;
    if (test > NumOfModes) {
        Mode = 0;
    } else {
        Mode = test;
    }
}

uint8_t MainController::getMode() {
    return Mode;
}