/**
 * Value to fill up arrays or set initial values to be ignored
 * prevent null pointers and is a workaround with my crappy dynamic array knowledge
 */
#define IGNORE   100

// Turn the LEDs back to their state before the animation started
#define STORE_LED_STATE 1

/**
 * Map the value for button states
 * Because using internal pull_up resistor, high and low are flipped
 * This is purely for code readability
 */
#define SWITCH_ON   0
#define SWITCH_OFF  1

/**
 * Set the total number of leds and switches
 */
#define TOTAL_LEDS      12
#define TOTAL_COLOR_SWITCHES  18

// Configure the modes and options
#define NUMBER_OF_MODES 2

// Set the number of animations
#define NUMBER_OF_ANIMATIONS 10

// Number of options in each mode
const int NUMBER_OF_OPTIONS[][1] = {
  {4}
};
