#include <ezBuzzer.h> // ezBuzzer library
#include "pitches.h"
#include "music_game.h"
#include "music_keypad.h"
#include "music_victory.h"
#include "music_lose.h"

// Define the pin for BUZZER
#define BUZZER_PIN 7

/* 
 * Define a boolean to check if the buzzer is playing
 * a song or it should play a sound that indicates a mistake
 */
bool play_songs = true;

// Define the boolean for each song
bool play_song_game = true;
bool play_song_keypad = false;
bool play_victory = false;
bool play_lose = false;

// Initialize the ezBuzzer
ezBuzzer buzzer(BUZZER_PIN);

// Define the sound for a mistake
int melody_wrong[] = {NOTE_D5};
int noteDurations_wrong[] = {8};

// Define a time to pause the buzzer
bool pauze_buzzer = false;
int count_pause_buzzer = 0;
