#include "LAMPdisplays.h"

CRGB SolidLightDisplay::getColor(CRGB led, DisplayVariables &vars) {
    vars = resetVariables(vars);
    led.r = vars.brightness * vars.red / 255;
    led.g = vars.brightness * vars.green / 255;
    led.b = vars.brightness * vars.blue / 255;
    return led;
}

DisplayVariables SolidLightDisplay::resetVariables(DisplayVariables vars) {
    vars.rate = 5;
    vars.highLimit = 255;
    vars.lowLimit = 0;
    if (millis() - vars.time > vars.rate) {
        vars.time = millis();
        vars.brightness = bringTo(vars.brightness, 255);
        vars.red = bringTo(vars.red, 255);
        vars.green = bringTo(vars.green, 255);
        vars.blue = bringTo(vars.blue, 100);
    }
    return vars;
}

uint8_t SolidLightDisplay::bringTo(uint8_t val, uint8_t lim) {
    if (val < lim) {
        val++;
    } else if (lim < val) {
        val--;
    }
    return val;
}

CRGB RandomDotDisplay::getColor(CRGB led, DisplayVariables &vars) {
    if (millis() - vars.time > vars.rate) {
        vars.time = millis();
        int16_t temp = vars.brightness + vars.direction;
        if (temp > vars.highLimit) {
            vars.direction = -1;
            temp = vars.highLimit;
            vars.offCounter = millis();
        } else if (0 > temp) {
            if (millis() - vars.offCounter > vars.offTime) {
                vars = randomizeVariables(vars);
            }
        } else {
            vars.brightness = temp;
        }
    }
    led.r = vars.brightness * vars.red / 255;
    led.g = vars.brightness * vars.green / 255;
    led.b = vars.brightness * vars.blue / 255;
    return led;
}

DisplayVariables RandomDotDisplay::randomizeVariables(DisplayVariables vars) {
    vars.direction = 1;
    vars.rate = random(5, 15);
    vars.offTime = random(1000, 10000);
    vars.brightness = 0;
    vars.highLimit = random(100, 255);
    vars.lowLimit = random(10, 50);
    vars.red = random(255);
    vars.green = random(255);
    vars.blue = random(255);
    return vars;
}

CRGB FireDisplay::getColor(CRGB led, DisplayVariables &vars) {
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
    led.g = vars.brightness * vars.green / 255;
    led.b = vars.brightness * vars.blue / 255;
    return led;
}

DisplayVariables FireDisplay::randomizeVariables(DisplayVariables vars) {
    vars.direction = 1;
    vars.rate = random(1, 4);
    vars.brightness = 0;
    vars.highLimit = random(40, 255);
    vars.lowLimit = random(5, 20);
    vars.red = random(150, 255);
    vars.green = random(10, 30);
    vars.blue = random(0);
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
        break;
    case 2:
        color = Fire.getColor(led, Variables[index]);
        break;
    default:
        break;
    }
    return color;
}
