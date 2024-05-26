// Define the pins for SERVOs
#define SERVO1_PIN 2
#define SERVO2_PIN 3

// Moving time for the servos (in ms)
unsigned long MOVING_TIME = 300;
unsigned long startTimeServos = 0;

// Define the angles for the servos
int startAngle = 0;
int stopAngle  = 180;