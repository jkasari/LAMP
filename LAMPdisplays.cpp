#include "LAMPdisplays.h"

void LightDisplayParent::setBrightness(uint8_t newValue) { Brightness = newValue; }

uint8_t LightDisplayParent::getBrightness() { return Brightness; }

DisplayController::DisplayController() {
    DisplayPointer = SolidLight;
}

CRGB SolidLightDisplay::getColor() {
    setBrightness(150);
    return CRGB(getBrightness(), getBrightness(), getBrightness());
}

CRGB DisplayController::getColor(uint8_t displayIndex, uint8_t LEDindex) {
    return DisplayPointer[LEDindex].getColor();
}