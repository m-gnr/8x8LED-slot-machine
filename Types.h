#ifndef TYPES_H
#define TYPES_H

#include "config/MatrixConfig.h"

// =====================
// Game States
// =====================
enum class GameState {
  IDLE,
  SPINNING,
  STOPPING,
  RESULT,
  WIN,
  LOSE,
  GAME_OVER,
  GAME_COMPLETE
};

// =====================
// Buttons
// =====================
enum class ButtonType {
  NONE,
  GREEN,
  RED,
  BLUE
};

// =====================
// Slot Colors
// =====================
enum class SlotColor {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  PURPLE,
  EMPTY
};

// =====================
// Row Result
// =====================
struct RowResult {
  bool hasWin;
  SlotColor color;
  int startColumn;
  int matchCount;
  int reward;
};

// =====================
// Column Result
// =====================
struct ColumnResult {
  bool hasWin;
  SlotColor color;
  int columnIndex;
  int reward;
};

// =====================
// Spin Result
// =====================
struct SpinResult {
  RowResult rows[SLOT_ROW_COUNT];
  ColumnResult columns[SLOT_COLUMN_COUNT];
  int winningRowCount;
  int winningColumnCount;
  int verticalReward;
  int totalReward;
  bool isJackpot;
};

#endif
