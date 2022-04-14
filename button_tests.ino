/**
   Mode 0
    Option 0  - Press a LED button it goes on,  Press a color button, both go on
    Option 1  - Press a LED button it goes on,  Press a color button, both go on, plays music whilst pressing button
    Option 2  - Press a LED button it stays on, Press a color button, both stay on
    Option 3  - Press a LED button it stays on, Press a color button, both stay on, plays music whilst pressing button
    [] - Add resistor to the speaker
    [] - Add a swich to switch off the speaker
    [] - Add button release to mode and option button
    [] - Create "Previously active" array and fix that bug
    [] - Put mappings in a header file
    [] - fix delays... Maybe delay as a variable
*/
// Include header files
#include "config.h"     // App configuration
#include "pin_config.h" // Pin configuration
#include "tones.h"      // Music notes :-)
#include "mapping.h"    // Pin array mapping

// Enable / Disable the speaker
int speakerEnabled = 1;

// Set the default mode and option
int mode  = 1;
int option= 0;
int animation = 0;

// Delay for the animations
int animationSpeed = 125;

// Array to hold the states (on/off) for the leds
int ledStates[] = {
  0, 0, // Red
  0, 0, // Yellow
  0, 0, // Green
  0, 0, // Blue
  0, 0, // White
  0, 0  // Pink
};

// Set default state for the push buttons, by default they are all UP (Not pushed)
int colorSwitchStates[] = {
  SWITCH_OFF, SWITCH_OFF, SWITCH_OFF,  // Red
  SWITCH_OFF, SWITCH_OFF, SWITCH_OFF,  // Yellow
  SWITCH_OFF, SWITCH_OFF, SWITCH_OFF,  // Green
  SWITCH_OFF, SWITCH_OFF, SWITCH_OFF,  // Blue
  SWITCH_OFF, SWITCH_OFF, SWITCH_OFF,  // White
  SWITCH_OFF, SWITCH_OFF, SWITCH_OFF   // Pink
};

// Variables for keeping track of the currenly pressed switch to prevent overlap
int activeColorSwitch = IGNORE;
int previousactiveColorSwitch = IGNORE;

// Release states for
int modeSwitchReleaseState  = 0;
int optionSwitchReleaseState = 0;

// Aray to hold the released status of a color switch
int colorSwitchReleaseStates[] = {
  0, 0, 0, // Red
  0, 0, 0, // Yellow
  0, 0, 0, // Green
  0, 0, 0, // Blue
  0, 0, 0, // White
  0, 0, 0 // Purple
};

// Set a changed variable, this is for performance
// Any led / music writes should only happen when a change has occurred
int ledStateChanged = 0;
int speakerStateChanged = 0;

// Only play the fanfare at the start up
int fanfarePlayed = 0;

// Fanfare melody
int fanfareMelody[] = {NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, 0, NOTE_GS3, 0, NOTE_AS3, 0, NOTE_C4, NOTE_AS3, NOTE_C4};
  
// Fanfare note durations
int fanfareNoteDurations[] = {8,8,8,4,8,4,8,4,8,4,8,1 };

/**
 * SETUP
 */
void setup() {

  //start serial connection for debugging
  Serial.begin(19200);
  
  // Speaker pin
  pinMode(SPEAKER_PIN, OUTPUT);

  // Speaker switch pin
  pinMode(SPEAKER_SWITCH_PIN, INPUT_PULLUP);

  // Mode switch pin (player one)
  pinMode(MODE_SWITCH_PIN, INPUT_PULLUP);

  // Option button (Player two)
  pinMode(OPTION_SWITCH_PIN, INPUT_PULLUP);

  // Configure the led pins as outputs
  for (int i = 0; i < TOTAL_LEDS; i++) {
    pinMode(LED_PIN_MAP[i], OUTPUT);
  }

  // Configure the switch pins as inputs and enable the internal pull-up resistor
  for (int i = 0; i < TOTAL_COLOR_SWITCHES; i++) {
    pinMode(COLOR_SWITCH_PIN_MAP[i], INPUT_PULLUP);
  }
  
  playFanfare();
}


/**
 * MAIN LOOP
 */
void loop() {
  
  // Handle button presses
  handleModeSwitchPress();
  handleOptionSwitchPress();

  switch(mode) {
    case 0: {

      // Handle the playing of the animation
      handleAnimation(animation, animationSpeed);
      
      // Move to the "normal" mode from animation mode
      mode++;
      break;
    }

    case 1 :{

      // Handle what to do when a color button is pressed
      handleColorSwitchPress();

      // Handle the state (on/off) for the LEDs
      handleLedState();
      
      break;
    }
  }
}


void aniAllOff(){
  // Turn off all LEDS
  for (int i = 0; i < TOTAL_LEDS; i++) {
    digitalWrite(LED_PIN_MAP[i], 0);

    // If the led states are not stored they need to be reset
    if(STORE_LED_STATE == 0){
      ledStates[i] = 0;
    }
  }
}


void aniAllOneByOneDown(int dly){
  // Right line of leds walking down
  for (int i = 0; i < TOTAL_LEDS; i++) {
    if(i>0){
      digitalWrite(LED_PIN_MAP[i-1], 0);
    }
    digitalWrite(LED_PIN_MAP[i], 1);
    delay(dly);
  }
  // Turn off the last led
  digitalWrite(LED_PIN_MAP[TOTAL_LEDS-1], 0);
  delay(dly);
}


void aniAllOneByOneUp(int dly){
  // Right line of leds walking up
  for (int i = TOTAL_LEDS; i > 0 ; i--) {
    digitalWrite(LED_PIN_MAP[i-1], 1);
    digitalWrite(LED_PIN_MAP[i], 0);
    delay(dly);
  }
  // Turn off the first led
  digitalWrite(LED_PIN_MAP[0], 0);
  delay(dly);
}


void aniAllDown(int dly){
  // Right line of leds walking down
  for (int i = 0; i < TOTAL_LEDS; i++) {
    digitalWrite(LED_PIN_MAP[i], 1);
    delay(dly);
  }
}

void aniAllUp(int dly){
  // Right line of leds walking up
  for (int i = TOTAL_LEDS; i >= 0 ; i--) {
    digitalWrite(LED_PIN_MAP[i], 1);
    delay(dly);
  }
}


void aniLeftRightDown(int dly){
  // Both lef and right down
  for (int i = 0; i <= TOTAL_LEDS-1; i=i+2) {
    // Left
    digitalWrite(LED_PIN_MAP[i], 1);
    
    // Right
    digitalWrite(LED_PIN_MAP[i+1], 1);
    delay(dly);
  }
}

void aniLeftRightUp(int dly){
  // Both lef and right up
  for (int i = TOTAL_LEDS-1; i > 0; i=i-2) {
    // Left
    digitalWrite(LED_PIN_MAP[i], 1);
    
    // Right
    digitalWrite(LED_PIN_MAP[i-1], 1);
    delay(dly);
  }
}


void aniLeftDown(int dly){
// Left line of leds walking down
  for (int i = 0; i < TOTAL_LEDS; i=i+2) {
    digitalWrite(LED_PIN_MAP[i], 1);
    delay(dly);
  }
}


void aniLeftUp(int dly){
  // Left line of leds walking up
  for (int i = TOTAL_LEDS; i >= 0; i=i-2) {
    digitalWrite(LED_PIN_MAP[i], 1);
    delay(dly);
  }
}


void aniRightDown(int dly){
  // Right line of leds walking down
  for (int i = 0; i < TOTAL_LEDS; i=i+2) {
    digitalWrite(LED_PIN_MAP[i+1], 1);
    delay(dly);
  }
}


void aniRightUp(int dly){
  // Right line of leds walking up
  for (int i = TOTAL_LEDS; i > 0 ; i=i-2) {
    digitalWrite(LED_PIN_MAP[i-1], 1);
    delay(dly);
  }
}


/**
 * Handler for switching the sound on and off
 */
void handleSpeakerSwitchPress() {
  if(digitalRead(SPEAKER_SWITCH_PIN) == SWITCH_ON) {
    speakerEnabled = 1;
  }else{
    speakerEnabled = 0;
  }
}

/**
 * Handler for pressing the Mode (player one) button
 */
void handleModeSwitchPress() {
  if(digitalRead(MODE_SWITCH_PIN) == SWITCH_ON) {
      
    if(mode + 1 == NUMBER_OF_MODES){
      mode=0;
    }else{
      mode++;  
    }
    
    // Move through different animations
    if(animation + 1 >= NUMBER_OF_ANIMATIONS){
      animation = 0;
    }else{
      animation++;
    }    
    delay(50);
  }
}


/**
 *   Handler for pressing the Option (player two) button
 */
void handleOptionSwitchPress() {
  if (digitalRead(OPTION_SWITCH_PIN) == SWITCH_ON) {
    
    // Toggle all leds on or off
    toggleAllLeds();

    // Allow for some button travel
    delay(300);
  }
}


/**
 * Handler for pressing the any of the color switches
 */
void handleColorSwitchPress() {

  // Check for any button presses
  for (int i = 0; i < TOTAL_COLOR_SWITCHES; i++) {

    // Set the state for a button
    colorSwitchStates[i] = digitalRead(COLOR_SWITCH_PIN_MAP[i]);

    // A button is pressed
    if (colorSwitchStates[i] == SWITCH_ON) {
      previousactiveColorSwitch = activeColorSwitch;
      activeColorSwitch = i;
     
      if (colorSwitchReleaseStates[i] == 1) {

        // Enable all the LEDs related to the switch
        toggleLedsBasedOnColorSwitchMap(i);

        // Update the switch release state
        colorSwitchReleaseStates[i] = 0;

        // Play a sound when a key is pressed
        if (speakerEnabled == 1) {
          tone(SPEAKER_PIN, SWITCH_NOTE_MAP[i]);
        }
      }
      delay(40);
    } else {

      colorSwitchReleaseStates[i] = 1;

      if (activeColorSwitch == i ) {
        if (speakerEnabled == 1) {
          noTone(SPEAKER_PIN);
        }
      }
    }
  }
}

/**
 * Method to switch on or off all leds based on the state array
 * Only change any led state if an actual change has occurred (aka a button is pressed)
 */
void handleLedState() {
  if (ledStateChanged == 1) {
    for (int i = 0; i < TOTAL_LEDS; i++) {
      digitalWrite(LED_PIN_MAP[i], ledStates[i]);
    }
    // Reset the led state changed
    ledStateChanged = 0;
  }
}


/**
 * Method to play animations
 */
void handleAnimation(int animation, int animationSpeed){
   
   // Turn of all leds
    aniAllOff();

    // Play an animation
    switch(animation){
      case 0:{ aniAllOneByOneDown(animationSpeed);  break;}
      case 1:{ aniAllOneByOneUp(animationSpeed);    break;}
      case 2:{ aniAllDown(animationSpeed);          break;}
      case 3:{ aniAllUp(animationSpeed);            break;}
      case 4:{ aniLeftDown(animationSpeed);         break;}
      case 5:{ aniLeftUp(animationSpeed);           break;}
      case 6:{ aniRightDown(animationSpeed);        break;}
      case 7:{ aniRightUp(animationSpeed);          break;}
      case 8:{ aniLeftRightDown(animationSpeed);    break;}
      case 9:{ aniLeftRightUp(animationSpeed);      break;}
    }

    // Add some extra delay at the end 
    delay(300);

    // Turn off all leds
    aniAllOff();

    // Indicate the led state has changed when the state of the LEDs is stored
    if(STORE_LED_STATE == 1){
      ledStateChanged=1;
    }
}

/**
 * Method to enable leds based on the switch / led mapping
 */
void enableLedsBasedOnColorSwitchMap(int switchIndex) {
  for (int j = 0; j < 2; j++) {
    if (COLOR_SWITCH_LED_MAP[switchIndex][j] != IGNORE) {

      // Update the state of the Led in the array
      ledStates[COLOR_SWITCH_LED_MAP[switchIndex][j]] = 1;

      // Indicate that a change has occurred and an update needs to be executed
      ledStateChanged = 1;
    }
  }
}


/**
 * Method to disable leds based on the switch / led mapping
 */
void disableLedsBasedOnColorSwitchMap(int switchIndex) {
  for (int j = 0; j < 2; j++) {
    if (COLOR_SWITCH_LED_MAP[switchIndex][j] != IGNORE) {

      // Update the state of the Leds
      ledStates[COLOR_SWITCH_LED_MAP[switchIndex][j]] = 0;

      // Indicate that a change has occurred and an update needs to be executed
      ledStateChanged = 1;
    }
  }
}

/**
   Method to disable leds based on the switch / led mapping
*/
void toggleLedsBasedOnColorSwitchMap(int switchIndex) {

  // Hold the overall state (all on or all off)
  int state = 0;
    
  for (int j = 0; j < 2; j++) {
    if (COLOR_SWITCH_LED_MAP[switchIndex][j] != IGNORE) {

      // Update the state of the Leds
      ledStates[COLOR_SWITCH_LED_MAP[switchIndex][j]] = (ledStates[COLOR_SWITCH_LED_MAP[switchIndex][j]] == 0) ? 1 : 0;

      // Indicate that a change has occurred and an update needs to be executed
      ledStateChanged = 1;
    }
  }
}

void turnOnAllLeds() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    ledStates[i] = 1;
  }

  // Indicate that a change has occurred and an update needs to be executed
  ledStateChanged = 1;
}


void turnOffAllLeds() {
  for (int i = 0; i < TOTAL_LEDS; i++) {
    ledStates[i] = 0;
  }

  // Indicate that a change has occurred and an update needs to be executed
  ledStateChanged = 1;
}

void toggleAllLeds() {

  // Hold the overall state (all on or all off)
  int state = 0;

  // Switch all leds on when a single led is off, Switch all leds off when all leds are on
  for (int i = 0; i < TOTAL_LEDS; i++) {
    if (ledStates[i] == 1) {
      state = 1;
    }
  }
  if (state == 0) {
    turnOnAllLeds();
  } else {
    turnOffAllLeds();
  }
}

void toggleSpeaker() {
  if (speakerEnabled == 1) {
    speakerEnabled = 0;
  } else {
    speakerEnabled = 1;
  }
}

void playFanfare(){
  for (int thisNote = 0; thisNote < 12; thisNote++) {
    int noteDuration = 1000 / fanfareNoteDurations[thisNote];
    if(speakerEnabled == 1){
      tone(SPEAKER_PIN, fanfareMelody[thisNote], noteDuration);
    }
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER_PIN);
  }
}
