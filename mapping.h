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

// Create a mapping between notes and switches
int SWITCH_NOTE_MAP[] = {
  NOTE_G3, NOTE_A3, NOTE_B3,  // Red
  NOTE_C4, NOTE_D4, NOTE_E4,  // Yellow
  NOTE_F4, NOTE_G4, NOTE_A4,  // Green
  NOTE_B4, NOTE_C5, NOTE_D5,  // Blue
  NOTE_E5, NOTE_F5, NOTE_G5,  // White
  NOTE_A5, NOTE_B5, NOTE_C6   // Pink
};

// Create a mapping between what buttons trigger what LEDs
int COLOR_SWITCH_LED_MAP[][2] {
  {0, IGNORE},  // Red left button      --> left red led & 100 == IGNORE
  {0, 1},       // Red middle button    --> left red & right red led
  {1, IGNORE},  // Red right button     --> right red led & 100 == IGNORE

  {2, IGNORE},  // Yellow left button   --> left yellow led & 100 == IGNORE
  {2, 3},       // Yellow middle button --> left yellow & right yellow led
  {3, IGNORE},  // Yellow right button  --> right yellow led & 100 == IGNORE

  {4, IGNORE},  // Green left button    --> left green led & 100 == IGNORE
  {4, 5},       // Green middle button  --> left green & right green led
  {5, IGNORE},  // Green right button   --> right green led & 100 == IGNORE

  {6, IGNORE},  // Blue left button     --> left blue led & 100 == IGNORE
  {6, 7},       // Blue middle button   --> left blue & right blue led
  {7, IGNORE},  // Blue right button    --> right blue led & 100 == IGNORE

  {8, IGNORE},  // White left button    --> left white led & 100 == IGNORE
  {8, 9},       // White middle button  --> left white & right white led
  {9, IGNORE},  // White right button   --> right white led & 100 == IGNORE

  {10, IGNORE}, // Purple left button   --> left purple led & 100 == IGNORE
  {10, 11},     // Purple middle button --> left purple & right purple led
  {11, IGNORE}  // Purple right button  --> right purple led & 100 == IGNORE
};
