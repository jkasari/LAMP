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
    vars.lowLimit = 10;
    if (millis() - vars.time > vars.rate) { // Check the time to see if it's time to increment the variables toward the same color
        vars.time = millis(); // Reset timer
        vars.brightness = bringTo(vars.brightness, 255); // Bring brightness back to full
        vars.red = bringTo(vars.red, 255); // Bring the rgb variables back to a nice white light.
        vars.green = bringTo(vars.green, 255);
        vars.blue = bringTo(vars.blue, 100);
    }
    return vars;
}

uint8_t SolidLightDisplay::bringTo(uint8_t val, uint8_t targ) {
    if (val < targ) { // If the value is less then the desired target, increase it.
        val++;
    } else if (targ < val) { // If it's greater, decrease it. 
        val--;
    }
    return val;
}

CRGB RandomDotDisplay::getColor(CRGB led, DisplayVariables &vars) {
    if (millis() - vars.time > vars.rate) { // Check the time to make sure it's go time.
        vars.time = millis();
        int16_t temp = vars.brightness + vars.direction; // create a temp variable, use a signed 16bit int to avoid looping back around over 255.
        if (temp > vars.highLimit) { // If the variable is greater then the high limit.
            vars.direction = -1; // Set the direction to decrease
            temp = vars.highLimit; // Set the temp variable to the high limit
            vars.offCounter = millis(); // Start the off counter
        } else if (0 > temp) {
            if (millis() - vars.offCounter > vars.offTime) { // Keep the light off for a random amount of time. 
                vars = randomizeVariables(vars);
            }
        } else {
            vars.brightness = temp; // If nothing is going on, set the brightness variable equal to the temp variable.
        }
    }
    led.r = vars.brightness * vars.red / 255; // Set the leds to the proper rgb values.
    led.g = vars.brightness * vars.green / 255;
    led.b = vars.brightness * vars.blue / 255;
    return led;
}

DisplayVariables RandomDotDisplay::randomizeVariables(DisplayVariables vars) {
    vars.direction = 1;
    vars.rate = random(5, 15);
    vars.offTime = random(5000, 10000);
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
