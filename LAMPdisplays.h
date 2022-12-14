#include <FastLED.h>
#define DISPLAY_NUM 3
#define LED_NUM 42
#define MAIN_COLOR 69
#define MAIN_SATURATION 180


struct DisplayVariables {
    uint32_t rate = 30;
    uint32_t time = 0;
    uint32_t offTime = 0;
    uint32_t offCounter = 0;
    
    uint8_t brightness = 0;
    uint8_t highLimit = 5;
    uint8_t lowLimit = 0;
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    
    int8_t direction = 1;
};

// A parent class for each light display, in the future the light displays will be help in an array of this class.
class LightDisplayParent {

    public:
        // Takes a CRGB and DisplayVariable and returns an adjusted CRGB
        virtual CRGB getColor(CRGB, DisplayVariables&);

    protected:
};

class SolidLightDisplay : public LightDisplayParent {

    public:
        CRGB getColor(CRGB, DisplayVariables&);
    private:
        // reset all the values to all the same color
        DisplayVariables resetVariables(DisplayVariables);
        
        // Takes in a current value and a target, retruns the current value incremented by one toward that target.
        uint8_t bringTo(uint8_t, uint8_t);
};

class RandomDotDisplay : public LightDisplayParent {

    public: 
        CRGB getColor(CRGB, DisplayVariables&);

    private:
        // Takes in a displayvariable struct and returns a randomized version.
        DisplayVariables randomizeVariables(DisplayVariables);

};

class FireDisplay : public LightDisplayParent {

    public:
        CRGB getColor(CRGB, DisplayVariables&);

    private:
        DisplayVariables randomizeVariables(DisplayVariables);
};


// Stores an array of all the display classes.
class DisplayController {

    public:
        // Takes in an display number and index for that array and returns a color.
        CRGB getColor(uint8_t, uint8_t, CRGB);

    private:
        DisplayVariables Variables[LED_NUM];
        SolidLightDisplay SolidLight;
        RandomDotDisplay RandomDot;
        FireDisplay Fire;
};