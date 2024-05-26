#include <TM1637Display.h>

// Define the pins for TIMER
#define DIO_PIN_TIMER 5
#define CLK_PIN_TIMER 4

// Initialize the timer
TM1637Display countdown(CLK_PIN_TIMER, DIO_PIN_TIMER);

// Define the countdown time
const unsigned long COUNTDOWN_TIME = 90;

// Variable that will store the elapsed time
volatile unsigned long elapsedTime = 0;

// Variable to check if the time is still counting
bool finish_timer = false;

// Variable to measure the time between blinks
float blink_timer = 0;

/*
 * Variable to check if the timer reached the end and
 * if the timer is blinking or not
 */ 
int on_off_timer = -1;

