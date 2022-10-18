#include "LAMPbutton.h"
#include "LAMPdisplays.h"
#include <FastLED.h>

#define LED_PIN 6
#define BUTT_PIN1 9
#define BUTT_PIN2 3
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
const uint8_t LEDnum = LED_NUM; // LED_NUM is defined in LAMPdisplays.h

CRGB LEDArr[LED_NUM];
DisplayController Display;
Button Butt1(BUTT_PIN1);
Button Butt2(BUTT_PIN2);

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(LEDArr, LEDnum);
    FastLED.setBrightness(255);
    FastLED.clear();
    Butt1.begin();
    Butt2.begin();
}

void loop() {
    for (int i = 0; i < LED_NUM; ++i) {
        LEDArr[i] = Display.getColor(0, i);
    }
    FastLED.show();
}