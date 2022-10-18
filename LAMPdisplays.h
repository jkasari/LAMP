#include <FastLED.h>
#define DISPLAY_NUM 1
#define LED_NUM 42
#define MAIN_COLOR 69
#define MAIN_SATURATION 180

class LightDisplayParent {

    public:
        virtual CRGB getColor() = 0;

        uint32_t increaseCounter();

        void setBrightness(uint8_t);

        uint8_t getBrightness();

    private:
        uint8_t Brightness;
        uint32_t Counter;
};

class SolidLightDisplayRed : public LightDisplayParent {

    public:
        CRGB getColor();

    private:
        const uint8_t SATURATION = 255;
        const uint8_t COLOR = 0;
};

class SolidLightDisplay : public LightDisplayParent {

    public:
        CRGB getColor();

    private:
        const uint8_t SATURATION = MAIN_SATURATION;
        const uint8_t COLOR = MAIN_COLOR;
};

class DisplayController {

    public:
        CRGB getColor(uint8_t, uint8_t);

    private:
        SolidLightDisplay SolidLight[LED_NUM];
        SolidLightDisplayRed SolidRed[LED_NUM];

};