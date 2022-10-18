#include "LAMPbutton.h"
#include "LAMPdisplays.h"
#include <FastLED.h>

#define LED_PIN 6
#define LED_NUM 38
#define BUTT_PIN1 4
#define BUTT_PIN2 5
#define LED_TYPE WS2811
#define COLOR_ORDER __cpp_range_based_for

CRGB LEDArr[LED_NUM];

void setup() {
    Serial.being(115200);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(LEDArr, LED_NUM);
}

void loop() {

}