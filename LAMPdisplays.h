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
        const uint8_t SATURATION = 200;
        const uint8_t COLOR = 69;
};

class DisplayController {

    public:
        DisplayController();

        CRGB getColor(uint8_t, uint8_t);

    private:
        LightDisplayParent *DisplayPointer;
        SolidLightDisplay SolidLight[LED_NUM];

};