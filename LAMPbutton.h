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

  private:
  uint32_t Count;
  uint8_t Port;
  // Returns true when the button is pressed and false when released.
  bool isPressed();
};
