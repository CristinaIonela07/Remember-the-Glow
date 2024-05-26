#include "Adafruit_Keypad.h"

// Define the dimensions for KEYPAD (BUTTON MATRIX)
const byte ROWS = 4;  // rows
const byte COLS = 4;  // columns

// Define the pins for KEYPAD
byte rowPins[ROWS] = { 28, 26, 24, 22 };    //connect to the row pinouts of the keypad
byte colPins[COLS] = { 29, 27, 25, 23 };  //connect to the column pinouts of the keypad

// Define the symbols on the buttons of the KEYPAD
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Initialize KEYPAD
Adafruit_Keypad button_matrix = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// The number of pressed buttons
int nr_pressed = 0;

// The number of errors
int nr_greseli = 0;
