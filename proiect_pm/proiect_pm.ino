// #include <TimerOne.h>
#include "keypad.h"
#include "matrix_solo.h"
#include "matrix_duo.h"
#include "buzzer.h"
#include "servos.h"
#include "timer.h"
#include "buttonsdanu.h"
#include "number_matrix.h"

// Define boolean variables for each step of the game
bool light_one_led = true;
bool wait_button_matrix = false;
bool light_matrix = false;
bool wait_DANU = false;
bool game_final = false;

// Variables to calculate the score and display it only once
int scor = 10;
bool display_score = false;

// Variable to retain if the player won or lost
bool win = false;

// Variables to check if a button was pressed and if it was pressed correctly
bool was_pressed_smth = false;
bool pressed_wrong = false;

// Variable to calculate the time for the final song
int time_final_song = 0;

// Turn off all LEDs from primary matrix
void blank_matrix_uno() {
  lc_solo.clearDisplay(0);
}

// Turn off all LEDs from secondary matrix
void blank_matrix_duo() {
  lc_duo.clearDisplay(0);
  lc_duo.clearDisplay(1);
}

// Function to turn on a group of LEDs on primary matrix
void displayPatternSolo() {
  // Randomly select the group
  int randomLED = random(0, 16);

  // Light up all 4 LEDs from the selected group
  for (int i = 0; i < 4; i++) {
    lc_solo.setLed(0, leds_solo[randomLED][i][0], leds_solo[randomLED][i][1], true);
  }

  // The group number is retained for further use
  random_solo_lights[index_leds] = randomLED;
  Serial.println(randomLED);
  index_leds++;
}

// Function to light a random number of LEDs on each secondary matrix
void displayPatternDuo() {
  // Reset the number of differences
  num_differences = 0;

  // Randomly select the number of LEDs to light up
  int numLEDs = random(18, 30);
  
  // Randomly decide if the two matrix will be the same
  int similar = random(0, 2);
  int dif = 0;

  // If not, randomly decide the number of LEDs that will be different
  if (similar == 0) {
    dif = random(1, 3);
  }
 
 // 0 = LED stins, 1 = LED aprins pe primul display, 2 = LED aprins pe al doilea display, 3 = LED aprins pe ambele display-uri
  int matrix_lit[8][8] = {0};
  int i = 0;

  // Light up random similar LEDs on both displays
  for (int i = 0; i < numLEDs - dif; i++) {
    int x = random(0, 8);
    int y = random(0, 8);
    lc_duo.setLed(0, x, y, true);
    lc_duo.setLed(1, x, y, true);
    if (similar == 0) {
      matrix_lit[x][y] = 3;
    }
  }
  
  if (similar == 0) {
    for (int i = 0; i < dif; i++) {
      int x1 = random(0, 8);
      int y1 = random(0, 8);
      while (matrix_lit[x1][y1] == 2 || matrix_lit[x1][y1] == 3) {
        x1 = random(0, 8);
        y1 = random(0, 8);
      }
      
      matrix_lit[x1][y1] = 1;
      lc_duo.setLed(0, x1, y1, true);

      /*
       * Decide random where the LED on the second display will be
       * For increase difficulty, it can be only near the position
       * of the LED from the first display
       */
      int x2 = x1 + 1;
      int y2 = y1 + 1;
      int x3 = x1 - 1;
      int y3 = y1 - 1;
      int x_final = random(x3, x2 + 1);
      int y_final = random(y3, y2 + 1);

      while (matrix_lit[x_final][y_final] == 1 || (x_final == x1 && y_final == y1)) {
        x_final = random(x3, x2 + 1);
        y_final = random(y3, y2 + 1);
      }

      if (matrix_lit[x_final][y_final] != 3)
        matrix_lit[x_final][y_final] = 2;
      num_differences++;
      lc_duo.setLed(1, x_final, y_final, true);
    }
  
  }
  Serial.print("Diferente:");
  Serial.println(num_differences);
}

// Function to manage interrupts on buttons DA/NU
void manage_buttonsDANU(int interruption) {
  // Check if a button is expected to be pressed
  if (wait_DANU == true) {
    unsigned long current_interruption_time = millis();
    // Manage the time between two interrupts
    if (current_interruption_time - last_interruption_time > 500) {
      // Check if the button was pressed correctly
      if (interruption == 0 && num_differences != 0) {
        num_buttons_DANU_correct++;
      } else if (interruption == 1 && num_differences == 0) {
        num_buttons_DANU_correct++;
      } else {
        /*
         * If not, increment the number of mistakes and
         * retain the fact that the song should not be played
         * and the disapproval sound should be played
         */
        nr_greseli++;
        play_songs = false;
        pressed_wrong = true;
      }

      // Update the time of the last interruption
      last_interruption_time = current_interruption_time;

      // Retain the fact that a button was pressed
      was_pressed_smth = true;

      // Update the number of LEDs that were lit
      count_leds_lit++;

      // No longer wait for a button to be pressed
      wait_DANU = false;
    }
  }
}

// Function to check the buttons pressed on the keypad
void check_keypad() {
  // Check if a button was pressed
  button_matrix.tick();
  keypadEvent e = button_matrix.read();
  if (e.bit.EVENT == KEY_JUST_PRESSED) {
    // Check if the button pressed is the correct one
    char key = (char)e.bit.KEY;
    if (random_solo_lights[nr_pressed] == 0 && key != 'A') {
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 1 && key != '3'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 2 && key != '2'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 3 && key != '1'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 4 && key != 'B'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 5 && key != '6'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 6 && key != '5'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 7 && key != '4'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 8 && key != 'C'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 9 && key != '9'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 10 && key != '8'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 11 && key != '7'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 12 && key != 'D'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 13 && key != '#'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 14 && key != '0'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    if (random_solo_lights[nr_pressed] == 15 && key != '*'){
      nr_greseli++;
      play_songs = false;
      pressed_wrong = true;
    }
    
    // Update the number of buttons pressed
    nr_pressed++;
  }
}

// Handle the interrupt on button NU
ISR(INT0_vect) {
  manage_buttonsDANU(0);
}

// Handle the interrupt on button DA
ISR(INT1_vect) {
  manage_buttonsDANU(1);
}

// Handle the interrupt on timer1 (each second)
ISR(TIMER1_COMPA_vect) {
  // Count the time to keep the lights on
  if (still_counting_time_solo == true) 
    count_time_solo += 1;
  if (still_counting_time_duo == true) {
    count_time_duo += 1;
  }
  
  // Check if the countdown timer is still running and update it
  if (finish_timer == false && game_final == false) {
    elapsedTime++;
    if (elapsedTime < COUNTDOWN_TIME) {
      unsigned long remainingTime = COUNTDOWN_TIME - elapsedTime;

      // Display remaining time in Minutes:Seconds format
      unsigned int minutes = remainingTime / 60;
      unsigned int seconds = remainingTime % 60;
      countdown.showNumberDecEx(minutes * 100 + seconds, 0b01000000, true);
    }
    if (elapsedTime == COUNTDOWN_TIME) {
      finish_timer = true;
      on_off_timer = 0;
    }
  }
  /* 
   * If the countdown timer is finished, it blinks
   * Display the number 0 on the countdown timer for 1 second
   * and turn it off for 1 second
   */
  else if (finish_timer == true) {
    if (on_off_timer == 0 && blink_timer== 0) {
      countdown.clear();
      blink_timer++;
    }
  
    if (blink_timer == 2 && on_off_timer == 0) {
      blink_timer = 0;
      on_off_timer = 1;
      
    }
    if (on_off_timer == 0 && blink_timer!= 0) {
      blink_timer++;
    }

    if (on_off_timer == 1 && blink_timer == 0) {
      countdown.showNumberDecEx(0, 0b01000000, true);
      blink_timer++;
    }
    
    if (blink_timer == 1 && on_off_timer == 1) {
      blink_timer = 0;
      on_off_timer = 0;
    }
    
    if (on_off_timer == 1 && blink_timer != 0) {
      
      blink_timer++;
    }
  }

  // Count the time to play the final song
  if (game_final == true) {
    time_final_song++;
  }
}

// Function to configure timer1
void configure_timer1() {
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1C = 0;
  TCNT1 = 0;
  TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
  TCCR1B |= (1<<CS12) | (1 << CS10) | (1 << WGM12);
  OCR1A = 15625;
  TIMSK1 = 0;
  TIMSK1 |= (1 << OCIE1A);
}

// Function to configure timer3 used for the servos
void configure_timer3() {
  TCCR3A = 0;
  TCCR3B = 0;
  TCCR3A = (1 << WGM31);
  TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);
  ICR3 = 39999;
  OCR3B = 2999;
  OCR3C = 2999;
  TCCR3A |= (1 << COM3B1) | (1 << COM3C1);
}

// Function to configure external interrupts
void configure_extern_int(){
  EIMSK &= ~(1 << INT0); 
  EIMSK &= ~(1 << INT1);
  EICRA |= (1 << ISC01)|(1 << ISC00);
  EICRA |= (1 << ISC11)|(1 << ISC10);
  EIFR &= ~(1 << INTF0);
  EIFR &= ~(1 << INTF1);
  EIMSK |= (1 << INT0);
  EIMSK |= (1 << INT1);
}

// Function to initialize the principal matrix
void initialize_solo() {
  lc_solo.shutdown(0, false);
  lc_solo.setIntensity(0, 6);
  lc_solo.clearDisplay(0);
}

// Function to initialize the secondary matrix
void initialize_duo() {
  lc_duo.shutdown(0, false);
  lc_duo.setIntensity(0, 3); 
  lc_duo.shutdown(1, false);
  lc_duo.setIntensity(1, 3);
  lc_duo.clearDisplay(0);
  lc_duo.clearDisplay(1);
}

// Function to rotate the servos
void rotate_servos(){
  unsigned long progress = millis() - startTimeServos;
  // Check if the servos have reached the desired position
  if (progress >= MOVING_TIME) {
    startTimeServos = millis();
    if (startAngle == 0) {
      startAngle = 180;
      stopAngle = 0;
    } else {
      startAngle = 0;
      stopAngle = 180;
    }
    progress = millis() - startTimeServos;
  }

  // Calculate the angle and pulse width
  if (progress < MOVING_TIME) {
    long angle = map(progress, 0, MOVING_TIME, startAngle, stopAngle);
    int pulseWidth = map(angle, 0, 180, 2000, 4000);
  
    // Set the pulse width
    OCR3B = pulseWidth;
    OCR3C = pulseWidth;
  }
}

void setup() {
  // Setup the timers and interrupts
  configure_timer1();
  configure_timer3();
  configure_extern_int();

  // Initialize random seed
  randomSeed(analogRead(0));

  // Start the serial communication
  Serial.begin(9600);

  // Setup the primary and secondary matrix
  initialize_solo();
  initialize_duo();
  
  // Setup the buttons
  last_interruption_time = millis();
  pinMode(BUTTON_DA_PIN, INPUT);
  pinMode(BUTTON_NU_PIN, INPUT);

  // Setup the servos 
  pinMode(SERVO1_PIN, OUTPUT);
  pinMode(SERVO2_PIN, OUTPUT);
  
  // Setup the keypad
  button_matrix.begin();

  // Setup the countdown timer
  countdown.setBrightness(5);
  countdown.clear();
  
  // Enable interrupts
  sei();
}

void loop() {
  buzzer.loop();
  
  // Check if a melody is to be played and which one and play it
  if (play_songs == true) {
    if (play_song_game == true) {
      if (buzzer.getState() == BUZZER_IDLE) {
        int length = sizeof(noteDurations_game) / sizeof(int);
        buzzer.playMelody(melody_game, noteDurations_game, length);
      }
    }
    if (play_song_keypad== true) {
      if (buzzer.getState() == BUZZER_IDLE) {
        int length = sizeof(noteDurations_keypad) / sizeof(int);
        buzzer.playMelody(melody_keypad, noteDurations_keypad, length);
      }
    }
    if (play_victory == true) {
      if (buzzer.getState() == BUZZER_IDLE) {
        int length = sizeof(noteDurations_victory) / sizeof(int);
        buzzer.playMelody(melody_victory, noteDurations_victory, length);
      }
    }
    if (play_lose == true) {
      if (buzzer.getState() == BUZZER_IDLE) {
        int length = sizeof(noteDurations_lose) / sizeof(int);
        buzzer.playMelody(melody_lose, noteDurations_lose, length);
      }
    }
  }

  // Check if the wrong button was pressed and play the disapproval sound
  if (play_songs == false && pressed_wrong == true ) {
    pauze_buzzer = true;
    buzzer.stop();
  }

  // Count the time to pause the disapproval sound
  if (pauze_buzzer == true)
    count_pause_buzzer++;

  // Play the disapproval sound
  if (count_pause_buzzer >= 100 && count_pause_buzzer <= 1000) {
    int length = sizeof(noteDurations_wrong) / sizeof(int);
    buzzer.playMelody(melody_wrong, noteDurations_wrong, length);
  }
  
  // Stop the disapproval sound
  if (count_pause_buzzer == 1000) {
    buzzer.stop();
  }

  // Replay the melody of the game
  if (count_pause_buzzer == 2000){
    play_songs = true;
    count_pause_buzzer = 0;
    pauze_buzzer = false;
    pressed_wrong = false;
  }

  // Check if it is time to light up the LEDs on the primary matrix
  if (light_one_led == true) {
    was_pressed_smth = false;
    displayPatternSolo();
    still_counting_time_solo = true;
    light_one_led = false;
  }

  // Check if the time to light up the LEDs on the primary matrix has passed
  if (count_time_solo == 5) {
    blank_matrix_uno();
    count_time_solo = 0;
    still_counting_time_solo = false;
    light_matrix = true;
  }
  
  // Check if it is time to light up the LEDs on the secondary matrix
  if (light_matrix == true) {
    displayPatternDuo();
    still_counting_time_duo = true;
    light_matrix = false;
    wait_DANU = true;
  }
  
  // Check if the time to light up the LEDs on the secondary matrix has passed
  if (count_time_duo == 5) {
    blank_matrix_duo();
    count_time_duo = 0;
    still_counting_time_duo = false;
  }

  // Check if a button was pressed
  if (was_pressed_smth == true) {
    blank_matrix_duo();
    light_one_led = true;
    count_time_duo = 0;
    still_counting_time_duo = false;
  }

  /*
   * Check if the number of lit LEDs is 5 and continue the game
   * by waiting for the buttons on the keypad to be pressed
   */
  if (count_leds_lit == 5 && was_pressed_smth == true) {
    wait_button_matrix = true;
    light_matrix = false;
    light_one_led = false;
    wait_DANU = false;
    was_pressed_smth = false;

    // Change the state of the buzzer and the song to be played
    buzzer.stop();
    play_song_game = false;
    play_song_keypad = true;
    play_victory = false;
    play_lose = false; 
  }

  // Check if the keypad is to be pressed
  if (wait_button_matrix == true) {
    if (nr_pressed < 5)
      check_keypad();
    
    // Check if the number of buttons pressed is 5
    if (nr_pressed == 5) {
      // Initialize the starting time for the servos
      startTimeServos = millis();

      // Continue to the next step of the game (display the score)
      wait_button_matrix = false;
      light_matrix = false;
      light_one_led = false;
      wait_DANU = false;
      game_final = true;

      // Check if the player won or lost
      if (nr_greseli == 0) {
        win = true;
      } else {
        win = false;
      }
      
      // Calculate the score
      scor = 10 - nr_greseli;
    } 
  }

  // Check if the game has ended
  if (game_final == true) {
    // Display the score
    if (display_score == false) {
      buzzer.stop();
      display_score = true;
      for (int i = 0; i < index_table[scor]; i++) {
        lc_duo.setLed(0, table[scor][i][0], table[scor][i][1], true);
      }
      for (int i = 0; i< 10; i++) {
        lc_duo.setLed(1, slash_table[i][0], slash_table[i][1], true);
      }
      for (int i = 0; i< index_table[10]; i++) {
        lc_solo.setLed(0, table[10][i][0], table[10][i][1], true);
      }
    }
    
    // If the player won and the countdown timer did not finish
    if (win == true && finish_timer == false) {
      // Rotate the servos
      rotate_servos();

      // Play the victory song
      play_song_game = false;
      play_song_keypad = false;
      play_victory = true;
      play_lose = false;
    } else {
      /*
       * If the player lost by score or the countdown timer finished
       * Play the lose song
       */
      play_song_game = false;
      play_song_keypad = false;
      play_victory = false;
      play_lose = true;
    } 
  }

  // End the game
  if (time_final_song == 30) {
    lc_solo.clearDisplay(0);
    lc_duo.clearDisplay(0);
    lc_duo.clearDisplay(1);
    buzzer.stop();
    countdown.clear();
    exit(0);
  }
}