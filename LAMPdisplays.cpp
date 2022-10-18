#include "LAMPdisplays.h"

CRGB SolidLightDisplayRed::getColor() {
    Brightness = 100;
    CRGB color = CHSV(COLOR, SATURATION, Brightness);
    return color;
}

CRGB SolidLightDisplay::getColor() {
    Brightness = 255;
    CRGB color = CHSV(COLOR, SATURATION, Brightness);
    return color;
}

RandomColor::RandomColor() {
    resetValues();
}

CRGB RandomColor::getColor() {
    if (millis() - Counter > Rate) {
        Counter = millis();
        int16_t test = Brightness + Dir;
        if (test >= HighLimit) {
            Dir = -1;
            Brightness = HighLimit;
        } else if (0 >= test) {
            resetValues();
        } else {
            Brightness = test;
        }
    }
   CRGB color = CHSV(Color, Sat, Brightness);
   return color;
}

void RandomColor::resetValues() {
    Brightness = 0;
    Dir = 1;
    Color = random8();
    HighLimit = random8(50);
    Counter = 0;
    Rate = random8(20, 90);
}

CRGB DisplayController::getColor(uint8_t displayIndex, uint8_t LEDindex) {
    CRGB color;
    switch (displayIndex) {
        case 0:
            color = SolidLight[LEDindex].getColor();
            break;
        case 1:
            color = RandColor[LEDindex].getColor();
            break;
        default:
            color = CRGB(0, 0, 0);
            break;
    }
    return color;
}