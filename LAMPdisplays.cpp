#include "LAMPdisplays.h"

void LightDisplayParent::setBrightness(uint8_t newValue) { Brightness = newValue; }

uint8_t LightDisplayParent::getBrightness() { return Brightness; }

DisplayController::DisplayController() {
    DisplayPointer = SolidLight;
}

CRGB SolidLightDisplay::getColor() {
    setBrightness(150);
    CRGB color = CHSV(COLOR, SATURATION, getBrightness());
    return color;
}

CRGB DisplayController::getColor(uint8_t displayIndex, uint8_t LEDindex) {
    return DisplayPointer[LEDindex].getColor();
}