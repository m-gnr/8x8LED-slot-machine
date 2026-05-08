#ifndef SOUND_CONFIG_H
#define SOUND_CONFIG_H

// =====================
// BUZZER TIMING (ms)
// =====================
#define BUZZER_NOTE_GAP_MS 20

// =====================
// SHORT MELODIES
// =====================
#define SOUND_REST 0

static const unsigned int BET_CHANGE_NOTES[] = { 880, 1175 };
static const unsigned int BET_CHANGE_DURATIONS[] = { 40, 55 };

static const unsigned int SPIN_START_NOTES[] = { 330, 494, 659 };
static const unsigned int SPIN_START_DURATIONS[] = { 45, 45, 70 };

static const unsigned int SPIN_LOOP_NOTES[] = {
  196, SOUND_REST, 233, 247, 277, SOUND_REST,
  262, 233, 208, SOUND_REST, 247, 277
};
static const unsigned int SPIN_LOOP_DURATIONS[] = {
  90, 35, 70, 70, 95, 35,
  80, 70, 110, 35, 70, 120
};

static const unsigned int COLUMN_STOP_NOTES[] = { 784 };
static const unsigned int COLUMN_STOP_DURATIONS[] = { 45 };

static const unsigned int WIN_NOTES[] = {
  523, 659, 740, 784, 932,
  880, 1047, SOUND_REST, 1175, 1047
};
static const unsigned int WIN_DURATIONS[] = {
  55, 55, 40, 70, 55,
  40, 80, 35, 65, 160
};

static const unsigned int LOSE_NOTES[] = {
  784, 740, 698, 659, SOUND_REST,
  622, 587, 554, 523
};
static const unsigned int LOSE_DURATIONS[] = {
  45, 45, 60, 75, 35,
  60, 75, 85, 180
};

static const unsigned int FINAL_VICTORY_NOTES[] = {
  523, 659, 784, 932, SOUND_REST,
  880, 1047, 1175, 1319, SOUND_REST,
  1175, 1047, 932, 1047, 1319, 1568, SOUND_REST,
  1760, 1568
};
static const unsigned int FINAL_VICTORY_DURATIONS[] = {
  90, 90, 110, 140, 60,
  90, 100, 120, 180, 70,
  90, 90, 110, 120, 150, 260, 80,
  180, 420
};

static const unsigned int FINAL_GAME_OVER_NOTES[] = {
  784, 740, 698, 659, SOUND_REST,
  622, 587, 554, 523, SOUND_REST,
  494, 466, 440, 415, 392, SOUND_REST,
  330, 262
};
static const unsigned int FINAL_GAME_OVER_DURATIONS[] = {
  90, 90, 110, 150, 70,
  100, 110, 130, 180, 80,
  110, 120, 140, 160, 230, 90,
  260, 520
};

#endif
