#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

// =====================
// BANK & BET
// =====================
#define START_BANK  10
#define TARGET_BANK 100000
#define VICTORY_MILESTONE_AMOUNT 100
#define MIN_BET     1

// =====================
// GAME TIMING (ms)
// =====================
#define SPIN_UPDATE_MS   120
#define STOP_DELAY_MS    150
#define RESULT_SCREEN_MS 1500
#define EFFECT_UPDATE_MS 80

// =====================
// DEBUG
// =====================
#define DEBUG_REWARD_LOGS 0

// =====================
// COLOR PROBABILITIES (%)
// Total must be 100
// =====================
#define PROB_RED    30
#define PROB_GREEN  25
#define PROB_BLUE   20
#define PROB_YELLOW 15
#define PROB_PURPLE 10

// =====================

// REWARD MULTIPLIERS

// =====================

// 3 matches
#define MULTIPLIER_3_RED    2
#define MULTIPLIER_3_GREEN  3
#define MULTIPLIER_3_BLUE   4
#define MULTIPLIER_3_YELLOW 5
#define MULTIPLIER_3_PURPLE 6

// 4 matches
#define MULTIPLIER_4_RED    5
#define MULTIPLIER_4_GREEN  6
#define MULTIPLIER_4_BLUE   8
#define MULTIPLIER_4_YELLOW 10
#define MULTIPLIER_4_PURPLE 15

// Vertical 3-row column bonus
#define VERTICAL_MULTIPLIER_RED    1
#define VERTICAL_MULTIPLIER_GREEN  2
#define VERTICAL_MULTIPLIER_BLUE   3
#define VERTICAL_MULTIPLIER_YELLOW 4
#define VERTICAL_MULTIPLIER_PURPLE 5

// =====================
// BONUS SYSTEM
// Integer-based multipliers
// Example: 15 / 10 = 1.5x
// =====================
#define BONUS_TWO_ROWS_MULTIPLIER   15
#define BONUS_THREE_ROWS_MULTIPLIER 20
#define BONUS_MULTIPLIER_DIVISOR    10
#define JACKPOT_MULTIPLIER          10

#endif
