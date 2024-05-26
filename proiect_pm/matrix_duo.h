#include <LedControl.h>

// Define the pins for the secondary MAX7219 (DUO)
#define DATA_IN_PIN_DUO  51
#define CLK_PIN_DUO 52
#define CS_PIN_DUO 53

// Initialize the secondary MAX7219 (DUO)
LedControl lc_duo = LedControl(DATA_IN_PIN_DUO, CLK_PIN_DUO, CS_PIN_DUO, 2);

// Number of differences between the two matrices
int num_differences = 0;

// Count the time to keep the lights on
int count_time_duo = 0;

// Variable to check if the time is still counting
bool still_counting_time_duo = false;
