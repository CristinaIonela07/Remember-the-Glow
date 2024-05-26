#include <LedControl.h>

// Define the pins for the primary MAX7219 (SOLO)
#define DATA_IN_PIN_SOLO 40
#define CLK_PIN_SOLO 36
#define CS_PIN_SOLO 38

// Define the groups of LEDs that form a single LED (4 LEDs)
int leds_solo[16][4][2] = {
  { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } },
  { { 0, 2 }, { 0, 3 }, { 1, 2 }, { 1, 3 } },
  { { 0, 4 }, { 0, 5 }, { 1, 4 }, { 1, 5 } },
  { { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
  { { 2, 0 }, { 2, 1 }, { 3, 0 }, { 3, 1 } },
  { { 2, 2 }, { 2, 3 }, { 3, 2 }, { 3, 3 } },
  { { 2, 4 }, { 2, 5 }, { 3, 4 }, { 3, 5 } },
  { { 2, 6 }, { 2, 7 }, { 3, 6 }, { 3, 7 } },
  { { 4, 0 }, { 4, 1 }, { 5, 0 }, { 5, 1 } },
  { { 4, 2 }, { 4, 3 }, { 5, 2 }, { 5, 3 } },
  { { 4, 4 }, { 4, 5 }, { 5, 4 }, { 5, 5 } },
  { { 4, 6 }, { 4, 7 }, { 5, 6 }, { 5, 7 } },
  { { 6, 0 }, { 6, 1 }, { 7, 0 }, { 7, 1 } },
  { { 6, 2 }, { 6, 3 }, { 7, 2 }, { 7, 3 } },
  { { 6, 4 }, { 6, 5 }, { 7, 4 }, { 7, 5 } },
  { { 6, 6 }, { 6, 7 }, { 7, 6 }, { 7, 7 } }
};

// Initialize the primary MAX7219 (SOLO)
LedControl lc_solo = LedControl(DATA_IN_PIN_SOLO, CLK_PIN_SOLO, CS_PIN_SOLO, 1);

// Vector to store the indexes of the groups of LEDs that are lit
int random_solo_lights[5] = {};
int index_leds = 0;

// Count the number of groups of LEDs that are lit
int count_leds_lit = 0;

// Count the time to keep the lights on
int count_time_solo = 0;

// Variable to check if the time is still counting
bool still_counting_time_solo = false;