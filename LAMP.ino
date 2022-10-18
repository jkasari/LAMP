#include "LAMPbutton.h"
#include "LAMPdisplays.h"
#include <FastLED.h>

#define LED_PIN 6
#define LED_NUM 42
#define BUTT_PIN1 9
#define BUTT_PIN2 3
#define LED_TYPE WS2811
#define COLOR_ORDER RGB

CRGB LEDArr[LED_NUM];
Button Butt1(BUTT_PIN1);
Button Butt2(BUTT_PIN2);

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(LEDArr, LED_NUM);
    Butt1.begin();
    Butt2.begin();
}

void loop() {
}