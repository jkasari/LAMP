#include "LAMPbutton.h"
#include "LAMPdisplays.h"
#include <FastLED.h>

#define LED_PIN 6
#define BUTT_PIN1 9
#define BUTT_PIN2 3
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS_INC 5
const uint8_t LEDnum = LED_NUM; // LED_NUM is defined in LAMPdisplays.h
const uint8_t numberOfDisplays = DISPLAY_NUM; // Display num is defined in LAMPdisplays.h

CRGB LEDArr[LED_NUM];
DisplayController Display;
MainController Controller(BUTT_PIN1, BUTT_PIN2, numberOfDisplays);
uint8_t GlobalBrightness = 255;

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(LEDArr, LEDnum);
    FastLED.setBrightness(GlobalBrightness);
    FastLED.clear();
}

void loop() {
    switch (Controller.getCommand()) { // Check for a command.
        case COMMAND::ONE_PRESSED:
            Controller.incMainBrightness(BRIGHTNESS_INC); // Change the brightness up
            break;
        case COMMAND::TWO_PRESSED:
            Controller.incMainBrightness(-BRIGHTNESS_INC); // Change the brightness down
            break;
        case COMMAND::BOTH_PRESSED:
            Controller.switchMode(); // Switch the mode
            break;
        case COMMAND::DO_NOTHING:
            break;
    }
    uint8_t mode = Controller.getMode();
    for (int i = 0; i < LED_NUM; ++i) { // loop through all the CRGB objects and pair them with specific color from a display object.
        LEDArr[i] = Display.getColor(mode, i);
    }
    // Keep Fast led happy and running
    FastLED.setBrightness(Controller.getMainBrightness());
    FastLED.show();
    delay(1);
}