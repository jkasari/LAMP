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

ButtonController::ButtonController(uint8_t port1, uint8_t port2) : Butt1(port1), Butt2(port2) {
    Butt1.begin();
    Butt2.begin();
}

COMMAND ButtonController::getCommand() {
    COMMAND CMND = COMMAND::DO_NOTHING;
    if (millis() - Timer > Rate) {
        Timer = millis();
        if (Butt1.isPressed()) { CMND = COMMAND::ONE_PRESSED; }
        if (Butt2.isPressed()) { CMND = COMMAND::TWO_PRESSED; }
        if (Butt1.isPressed() && Butt2.isPressed()) { CMND = COMMAND::BOTH_PRESSED; }
    }
    return CMND;
}