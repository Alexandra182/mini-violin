/*
  Songs by Robson Couto, more available at https://github.com/robsoncouto/arduino-songs
  TimerFreeTone library by Tim Eckel, available at https://bitbucket.org/teckel12/arduino-timer-free-tone/downloads/
*/

#include <TimerFreeTone.h>
#include "notes.h"

#define TONE_PIN     4
#define LED_PIN      3
#define BUTTON_PIN   1
#define STRINGS_PIN  A1

const int ode_to_joy[] PROGMEM = {

  // Ode to Joy - Beethoven's Symphony No. 9

  NOTE_E4, 4,  NOTE_E4, 4,  NOTE_F4, 4,  NOTE_G4, 4, //1
  NOTE_G4, 4,  NOTE_F4, 4,  NOTE_E4, 4,  NOTE_D4, 4,
  NOTE_C4, 4,  NOTE_C4, 4,  NOTE_D4, 4,  NOTE_E4, 4,
  NOTE_E4, -4, NOTE_D4, 8,  NOTE_D4, 2,

  NOTE_E4, 4,  NOTE_E4, 4,  NOTE_F4, 4,  NOTE_G4, 4, //4
  NOTE_G4, 4,  NOTE_F4, 4,  NOTE_E4, 4,  NOTE_D4, 4,
  NOTE_C4, 4,  NOTE_C4, 4,  NOTE_D4, 4,  NOTE_E4, 4,
  NOTE_D4, -4,  NOTE_C4, 8,  NOTE_C4, 2,

  NOTE_D4, 4,  NOTE_D4, 4,  NOTE_E4, 4,  NOTE_C4, 4, //8
  NOTE_D4, 4,  NOTE_E4, 8,  NOTE_F4, 8,  NOTE_E4, 4, NOTE_C4, 4,
  NOTE_D4, 4,  NOTE_E4, 8,  NOTE_F4, 8,  NOTE_E4, 4, NOTE_D4, 4,
  NOTE_C4, 4,  NOTE_D4, 4,  NOTE_G3, 2,

  NOTE_E4, 4,  NOTE_E4, 4,  NOTE_F4, 4,  NOTE_G4, 4, //12
  NOTE_G4, 4,  NOTE_F4, 4,  NOTE_E4, 4,  NOTE_D4, 4,
  NOTE_C4, 4,  NOTE_C4, 4,  NOTE_D4, 4,  NOTE_E4, 4,
  NOTE_D4, -4,  NOTE_C4, 8,  NOTE_C4, 2

};

const int harry_potter[] PROGMEM = {

  // Hedwig's theme fromn the Harry Potter Movies
  // Score from https://musescore.com/user/3811306/scores/4906610

  REST, 2, NOTE_D4, 4,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_C5, -2,
  NOTE_A4, -2,
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
  NOTE_F4, 2, NOTE_GS4, 4,
  NOTE_D4, -1,
  NOTE_D4, 4,

  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
  NOTE_G4, 2, NOTE_D5, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_B4, 4,
  NOTE_G4, -1,
  NOTE_AS4, 4,

  NOTE_D5, 2, NOTE_AS4, 4,//18
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_DS5, 2, NOTE_D5, 4,
  NOTE_CS5, 2, NOTE_A4, 4,
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_D4, 4,
  NOTE_D5, -1,
  REST, 4, NOTE_AS4, 4,

  NOTE_D5, 2, NOTE_AS4, 4,//26
  NOTE_D5, 2, NOTE_AS4, 4,
  NOTE_F5, 2, NOTE_E5, 4,
  NOTE_DS5, 2, NOTE_B4, 4,
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
  NOTE_CS4, 2, NOTE_AS4, 4,
  NOTE_G4, -1,

};

const int greensleeves[] PROGMEM = {

  // Greensleeves
  // Score available at https://musescore.com/user/168402/scores/1396946
  // Alexander Trompoukis

  NOTE_G4, 8, //1
  NOTE_AS4, 4, NOTE_C5, 8, NOTE_D5, -8, NOTE_DS5, 16, NOTE_D5, 8,
  NOTE_C5, 4, NOTE_A4, 8, NOTE_F4, -8, NOTE_G4, 16, NOTE_A4, 8,
  NOTE_AS4, 4, NOTE_G4, 8, NOTE_G4, -8, NOTE_FS4, 16, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_FS4, 8, NOTE_D4, 4, NOTE_G4, 8,

  NOTE_AS4, 4, NOTE_C5, 8, NOTE_D5, -8, NOTE_DS5, 16, NOTE_D5, 8, //6
  NOTE_C5, 4, NOTE_A4, 8, NOTE_F4, -8, NOTE_G4, 16, NOTE_A4, 8,
  NOTE_AS4, -8, NOTE_A4, 16, NOTE_G4, 8, NOTE_FS4, -8, NOTE_E4, 16, NOTE_FS4, 8,
  NOTE_G4, -2,
  NOTE_F5, 2, NOTE_E5, 16, NOTE_D5, 8,

  NOTE_C5, 4, NOTE_A4, 8, NOTE_F4, -8, NOTE_G4, 16, NOTE_A4, 8, //11
  NOTE_AS4, 4, NOTE_G4, 8, NOTE_G4, -8, NOTE_FS4, 16, NOTE_G4, 8,
  NOTE_A4, 4, NOTE_FS4, 8, NOTE_D4, 04,
  NOTE_F5, 2, NOTE_E5, 16, NOTE_D5, 8,
  NOTE_C5, 4, NOTE_A4, 8, NOTE_F4, -8, NOTE_G4, 16, NOTE_A4, 8,

  NOTE_AS4, -8, NOTE_A4, 16, NOTE_G4, 8, NOTE_FS4, -8, NOTE_E4, 16, NOTE_FS4, 8, //16
  NOTE_G4, -2,

};

// Melody variables
int tempo, wholenote, notes;
int divider = 0, noteDuration = 0;
int strings;

// Button variables
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

const int PRESS_TIME1 = 1000; // 1000 milliseconds
const int PRESS_TIME2 = 2000; // 1000 milliseconds
const int PRESS_TIME3 = 3000; // 1000 milliseconds

int button;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(STRINGS_PIN, INPUT_PULLUP);

  buttonPress();
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

void loop() {
  buttonPress(); // Read button state
  switch (button) {
    case 1: // if the button was pressed for < 1s
      tempo = 220;
      play_ode_to_joy();
      break;
    case 2: // if the button was pressed for < 2s
      tempo = 140;
      play_greensleeves();
      break;
    case 3: // if the button was pressed for < 3s
      tempo = 140;
      play_harry_potter();
      break;
    case 4: // if the button was pressed for > 3s
      freestyle(); // Read analog values from the strings
      break;
    default: break;
  }
}

void play_ode_to_joy() {
  wholenote = (60000 * 4) / tempo; // This calculates the duration of a whole note in ms (60s/tempo)*4 beats
  notes = sizeof(ode_to_joy) / sizeof(ode_to_joy[0]) / 2;
  // Loop through the notes in the array.
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // Turn the LED on
    digitalWrite(LED_PIN, HIGH);
    // Calculates the duration of each note
    divider = pgm_read_word_near(ode_to_joy + thisNote + 1);
    compute_note_duration(divider);
    TimerFreeTone(TONE_PIN, pgm_read_word_near(ode_to_joy + thisNote), noteDuration); // Play melody[thisNote] for duration[thisNote].
    digitalWrite(LED_PIN, LOW);
    delay(100); // Short delay between notes.
  }
}

void play_harry_potter() {
  wholenote = (60000 * 4) / tempo; // This calculates the duration of a whole note in ms (60s/tempo)*4 beats
  // Loop through the notes in the array.
  notes = sizeof(harry_potter) / sizeof(harry_potter[0]) / 2;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // Turn the LED on
    digitalWrite(LED_PIN, HIGH);
    // Calculates the duration of each note
    divider = pgm_read_word_near(harry_potter + thisNote + 1);
    compute_note_duration(divider);
    TimerFreeTone(TONE_PIN, pgm_read_word_near(harry_potter + thisNote), noteDuration); // Play melody[thisNote] for duration[thisNote].
    digitalWrite(LED_PIN, LOW);
    delay(100); // Short delay between notes.
  }
}

void play_greensleeves() {
  wholenote = (60000 * 4) / tempo; // This calculates the duration of a whole note in ms (60s/tempo)*4 beats
  // Loop through the notes in the array.
  notes = sizeof(greensleeves) / sizeof(greensleeves[0]) / 2;
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // Turn the LED on
    digitalWrite(LED_PIN, HIGH);
    // Calculates the duration of each note
    divider = pgm_read_word_near(greensleeves + thisNote + 1);
    compute_note_duration(divider);
    TimerFreeTone(TONE_PIN, pgm_read_word_near(greensleeves + thisNote), noteDuration); // Play melody[thisNote] for duration[thisNote].
    digitalWrite(LED_PIN, LOW);
    delay(100); // Short delay between notes.
  }
}

float compute_note_duration(int divider) {
  if (divider > 0) {
    // Regular note, just proceed
    noteDuration = (wholenote) / divider;
  } else if (divider < 0) {
    // Dotted notes are represented with negative durations
    noteDuration = (wholenote) / abs(divider);
    noteDuration *= 1.5; // Increases the duration in half for dotted notes
  }
}

int buttonPress() {
  currentState = digitalRead(BUTTON_PIN);
  if (button != 4)
    button = 0;
  if (lastState == HIGH && currentState == LOW)       // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration < PRESS_TIME1 && pressDuration > 100)
      button = 1;
    else if (pressDuration < PRESS_TIME2)
      button = 2;
    else if (pressDuration < PRESS_TIME3)
      button = 3;
    else {
      button = 4;
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
    }
  }
  // save the the last state
  lastState = currentState;
}

void freestyle() {
  strings = analogRead(STRINGS_PIN);
  if (strings < 200) {
    digitalWrite(LED_PIN, HIGH);
    strings = map(strings, 0, 200, 31, 40000);
    TimerFreeTone(TONE_PIN, strings, 500);
  }
  digitalWrite(LED_PIN, LOW);
  delay(100);
}
