/*
 * Right Here Waiting
 * melody played when the player loses
 */
int melody_lose[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4,
  NOTE_E4, NOTE_C4, NOTE_C4, NOTE_G4,
  REST,

  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G3,

  NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_C4,
  REST,

  NOTE_B3, NOTE_C4, REST,
  NOTE_B3, NOTE_C4, REST,
};

int noteDurations_lose[] = {
  4, 4, 4, 2,
  4, 2, 2, 4,
  1,

  4, 4, 4, 4, 1,
  4, 4, 4, 4, 1,
  4, 2, 2, 2, 2, 2, 4, 4, 1,

  4, 4, 4, 4, 1,
  4, 4, 4, 4, 1,
  4, 2, 2, 2, 2, 2, 4, 4, 2,
  2,

  2, 1, 4,
  2, 1, 4,
};