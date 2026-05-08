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

#endif
