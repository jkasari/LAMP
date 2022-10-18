#include "LAMPbutton.h"

Button::Button(uint8_t Port) { this->Port = Port; }

uint32_t Button::hasBeenPressed() {
    uint32_t value = 0;
    if (isPressed) {
        Count++;
    }
    if (!isPressed && Count != 0) {
        value = Count;
        Count = 0;
    }
    return value;
}

bool Button::isPressed() {
    return digitalRead(Port) == LOW;
}