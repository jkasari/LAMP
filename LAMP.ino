#include "LAMPbutton.h"
#include "LAMPdisplays.h"
#include <FastLED.h>

#define LED_PIN 6
#define BUTT_PIN1 9
#define BUTT_PIN2 3
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
const uint8_t LEDnum = LED_NUM; // LED_NUM is defined in LAMPdisplays.h

CRGB LEDArr[LED_NUM];
DisplayController Display;
ButtonController Controller(BUTT_PIN1, BUTT_PIN2);
uint8_t GlobalBrightness = 255;

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(LEDArr, LEDnum);
    FastLED.setBrightness(GlobalBrightness);
    FastLED.clear();
}

void loop() {
    switch (Controller.getCommand()) {
        case COMMAND::ONE_PRESSED:
            Serial.println("One Pressed");
            break;
        case COMMAND::TWO_PRESSED:
            Serial.println("TWO Pressed");
            break;
        case COMMAND::BOTH_PRESSED:
            Serial.println("Both Pressed");
            break;
        case COMMAND::DO_NOTHING:
            break;
    }
    for (int i = 0; i < LED_NUM; ++i) {
        LEDArr[i] = Display.getColor(0, i);
    }
    FastLED.show();
    delay(1);
}