#include <FastLED.h>
#define DISPLAY_NUM 1
#define LED_NUM 42

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

class SolidLightDisplay : public LightDisplayParent {

    public:
        CRGB getColor();

    private:
};

class DisplayController {

    public:
        DisplayController();

        CRGB getColor(uint8_t, uint8_t);

    private:
        LightDisplayParent *DisplayPointer;
        SolidLightDisplay SolidLight[LED_NUM];

};