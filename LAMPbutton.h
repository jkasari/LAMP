#define BUTTON_RESPONSE_TIME 50
#define BRIGHTNESS_LOW_LIMIT 15
/**
 * The button class takes in a port number to read.
 * Call the check function in your loop to check if the button was pressed.
 * use the result to decide what to do based on how long the button was held down for.
 */

class Button {

  public:
  // Takes a port number to read
  Button(uint8_t);

  // Sets the button to input pull up
  void begin();

  // Returns a count of how long the button was pressed for only after it's been pressed and released. 
  uint32_t hasBeenPressed();

  // Returns true when the button is pressed and false when released.
  bool isPressed();

  private:
  uint32_t Count;
  uint8_t Port;
};

enum class COMMAND {
  DO_NOTHING,
  ONE_PRESSED,
  TWO_PRESSED,
  BOTH_PRESSED,
};

class MainController {

  public:
    MainController(uint8_t, uint8_t, uint8_t);

    COMMAND getCommand();

    void incMainBrightness(int16_t);

    uint8_t getMainBrightness();

  private:
    Button Butt1;
    Button Butt2;
    uint32_t Timer;
    uint8_t Brightness = 255;
    uint8_t Mode = 0;
    uint8_t NumOfModes;
    const uint32_t Rate = BUTTON_RESPONSE_TIME;
};