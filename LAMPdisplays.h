#include <FastLED.h>
#define DISPLAY_NUM 1
#define LED_NUM 42
#define MAIN_COLOR 69
#define MAIN_SATURATION 180


// A parent class for each light display, in the future the light displays will be help in an array of this class.
class LightDisplayParent {

    public:
        // Returns a color, if its a moving display this color will change each time it is called. 
        virtual CRGB getColor() = 0;

        // Sets the brightness for this specific led on this specific display. 
        void setBrightness(uint8_t);

        // Returns the brightness of that specific display object.
        uint8_t getBrightness();

    private:
        uint8_t Brightness;
        uint32_t Counter;
};


// Temporary class just to get a second display.
class SolidLightDisplayRed : public LightDisplayParent {

    public:
        CRGB getColor();

    private:
        const uint8_t SATURATION = 255;
        const uint8_t COLOR = 0;
};


// Just lights all the leds the same color to function as a desk light
class SolidLightDisplay : public LightDisplayParent {

    public:
        CRGB getColor();

    private:
        const uint8_t SATURATION = MAIN_SATURATION;
        const uint8_t COLOR = MAIN_COLOR;
};

// Stores an array of all the display classes.
class DisplayController {

    public:
        // Takes in an display number and index for that array and returns a color.
        CRGB getColor(uint8_t, uint8_t);

    private:
        SolidLightDisplay SolidLight[LED_NUM];
        SolidLightDisplayRed SolidRed[LED_NUM];
        uint32_t Timer = 0;
        uint32_t Rate = 1000;

};