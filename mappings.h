/**
 * Value to fill up arrays or set initial values to be ignored
 * prevent null pointers and is a workaround with my crappy dynamic array knowledge
 */
#define IGNORE   100


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
#define TOTAL_SWITCHES  18


// Create a mapping between array index and pin number
const int LED_PIN_MAP[] = {
  PIN_LED_RED_LEFT,     PIN_LED_RED_RIGHT,
  PIN_LED_YELLOW_LEFT,  PIN_LED_YELLOW_RIGHT,
  PIN_LED_GREEN_LEFT,   PIN_LED_GREEN_RIGHT,
  PIN_LED_BLUE_LEFT,    PIN_LED_BLUE_RIGHT,
  PIN_LED_WHITE_LEFT,   PIN_LED_WHITE_RIGHT,
  PIN_LED_PURPLE_LEFT,  PIN_LED_PURPLE_RIGHT
};

// Create a mapping between array index and pin number
const int COLOR_SWITCH_PIN_MAP[] = {
  PIN_SWITCH_RED_LEFT,    PIN_SWITCH_RED_MIDDLE,    PIN_SWITCH_RED_RIGHT,
  PIN_SWITCH_YELLOW_LEFT, PIN_SWITCH_YELLOW_MIDDLE, PIN_SWITCH_YELLOW_RIGHT,
  PIN_SWITCH_GREEN_LEFT,  PIN_SWITCH_GREEN_MIDDLE,  PIN_SWITCH_GREEN_RIGHT,
  PIN_SWITCH_BLUE_LEFT,   PIN_SWITCH_BLUE_MIDDLE,   PIN_SWITCH_BLUE_RIGHT,
  PIN_SWITCH_WHITE_LEFT,  PIN_SWITCH_WHITE_MIDDLE,  PIN_SWITCH_WHITE_RIGHT,
  PIN_SWITCH_PURPLE_LEFT, PIN_SWITCH_PURPLE_MIDDLE, PIN_SWITCH_PURPLE_RIGHT
};
