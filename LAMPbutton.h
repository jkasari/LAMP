/**
 * The button class takes in a port number to read.
 * Call the check function in your loop to check if the button was pressed.
 * use the result to decide what to do based on how long the button was held down for.
 */

class Button {

public:
// Takes a port number to read
  Button(uint8_t);

  // Returns a count of how long the button was pressed for only after it's been pressed and released. 
  uint32_t hasBeenPressed();

private:
  uint32_t Count = 0;
  uint8_t Port = 0;
  // Increments the count while pressed. 
  void countWhilePressed();
};