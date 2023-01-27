#include <Arduino.h>
#include "LAMPbutton.h"

Button::Button(uint8_t Port) { this->Port = Port; }

void Button::begin() {
    pinMode(Port, INPUT_PULLUP);
}

uint32_t Button::hasBeenPressed() {
    uint32_t value = 0;
    if (isPressed()) {
        Count++; // Increase the count if the button is pressed.
    }
    if (!isPressed() && Count > 0) {
        value = Count; // Set the value to the count if the button is not pressed.
        Count = 0; // Reset the count once the value has been saved.
    }
    return value; // Return the time pressed.
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
    if (millis() - TimerBrightness > RateBrightness) { // Slight delay here to make the buttons less touchy
        TimerBrightness = millis();
        if (Butt1.isPressed()) { CMND = COMMAND::ONE_PRESSED; }
        if (Butt2.isPressed()) { CMND = COMMAND::TWO_PRESSED; }
        if (Butt1.isPressed() && Butt2.isPressed()) { 
            if (millis() - TimerMode > RateMode) { // Check to see if both buttons are pressed and then wait for a bit before responding. 
                TimerMode = millis();
                CMND = COMMAND::BOTH_PRESSED;
            } else {
                CMND = COMMAND::DO_NOTHING;
            }
        }
    }
    return CMND; // Return the command.
}

void MainController::incMainBrightness(int16_t inc) {
    int16_t test = Brightness + inc; // Create a test variable to make sure the new brightnes is not greater or less then 0-255
    if (test > 255) {
        test = 255;
    }
    if (BRIGHTNESS_LOW_LIMIT > test) { 
        test = BRIGHTNESS_LOW_LIMIT;
    }
    Brightness = test; // Set the master brightness to the test variable.
}

uint8_t MainController::getMainBrightness() {
    return Brightness;
}

void MainController::switchMode() {
    if (Mode == 0) { // If the mode is on the solid light mode, change it to a random mode.
        Mode = random(1, NumOfModes);
    } else { // If its not in the solid light mode, put it in the solid light mode. 
        Mode = 0;
    }
}

uint8_t MainController::getMode() {
    return Mode;
}