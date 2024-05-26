
// Define the pins for BUTTONS DA/NU
#define BUTTON_DA_PIN 20
#define BUTTON_NU_PIN 21

// Number of buttons DA/NU pressed correctly
int num_buttons_DANU_correct = 0;

// The time when the last interruption on the buttons DA/NU occurred
unsigned long last_interruption_time;