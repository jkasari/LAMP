#include "LAMPdisplays.h"

void LightDisplayParent::setBrightness(uint8_t newValue) { Brightness = newValue; }

uint8_t LightDisplayParent::getBrightness() { return Brightness; }

CRGB SolidLightDisplayRed::getColor() {
    setBrightness(100);
    CRGB color = CHSV(COLOR, SATURATION, getBrightness());
    return color;
}

CRGB SolidLightDisplay::getColor() {
    setBrightness(100);
    CRGB color = CHSV(COLOR, SATURATION, getBrightness());
    return color;
}

CRGB DisplayController::getColor(uint8_t displayIndex, uint8_t LEDindex) {
    CRGB color;
    switch (displayIndex) {
        case 0:
            color = SolidLight[LEDindex].getColor();
            break;
        case 1:
            color = SolidRed[LEDindex].getColor();
            break;
        default:
            color = CRGB(0, 0, 0);
            break;
    }
    return color;
}