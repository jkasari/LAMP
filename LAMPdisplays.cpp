#include "LAMPdisplays.h"

CRGB SolidLightDisplay::getColor(CRGB led, DisplayVariables &vars) {
    uint8_t b = 150;
    led.red = b;
    led.green = b;
    led.blue = b;
    return led;
}

CRGB RandomDotDisplay::getColor(CRGB led, DisplayVariables &vars) {
    if (millis() - vars.time > vars.rate) {
        vars.time = millis();
        int16_t temp = vars.brightness + vars.direction;
        if (temp > vars.highLimit) {
            vars.direction = -1;
            temp = vars.highLimit;
        } else if (0 > temp) {
            vars = randomizeVariables(vars);
        } else {
            vars.brightness = temp;
        }
    }
    led.r = vars.brightness * vars.red / 255;
    led.b = vars.brightness * vars.green / 255;
    led.g = vars.brightness * vars.blue / 255;
    return led;
}

DisplayVariables RandomDotDisplay::randomizeVariables(DisplayVariables vars) {
    vars.direction = 1;
    vars.rate = random8(5, 15);
    vars.brightness = 0;
    vars.highLimit = random(100, 255);
    vars.lowLimit = random(10, 50);
    vars.red = random8();
    vars.green = random8();
    vars.blue = random8();
    return vars;
}

CRGB DisplayController::getColor(uint8_t display, uint8_t index, CRGB led) {
    CRGB color = 0x000000;
    switch (display) {
    case 0:
        color = SolidLight.getColor(led, Variables[index]);
        break;
    case 1:
        color = RandomDot.getColor(led, Variables[index]);
    default:
        break;
    }
    return color;
}
