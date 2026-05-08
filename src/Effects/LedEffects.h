#ifndef LED_EFFECTS_H
#define LED_EFFECTS_H

#include <Arduino.h>

#include "../Hardware/LedMatrix.h"

class LedEffects {
private:
  enum class EffectType {
    NONE,
    WIN,
    LOSE,
    RESET,
    GAME_OVER,
    GAME_COMPLETE
  };

public:
  LedEffects(LedMatrix& matrix);

  void update();
  void stop();

  void playWin(const SpinResult& result, const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT]);
  void playLose();
  void playReset(uint8_t secondsLeft);
  void playGameOver();
  void playGameComplete();

private:
  LedMatrix& _matrix;

  EffectType _currentEffect;
  uint8_t _resetSecondsLeft;

  bool _active;
  unsigned long _lastUpdateTime;
  bool _blinkState;

  bool _winningBlocks[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT];
  SlotColor _blockColors[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT];
};

#endif
