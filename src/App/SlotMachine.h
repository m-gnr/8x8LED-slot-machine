#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H

#include <Arduino.h>

#include "../../Types.h"
#include "../../config/GameConfig.h"

#include "../Hardware/ButtonManager.h"
#include "../Hardware/Buzzer.h"
#include "../Hardware/LedMatrix.h"
#include "../Hardware/LcdDisplay.h"

#include "../Effects/LedEffects.h"

#include "../Game/ReelManager.h"
#include "../Game/RewardSystem.h"

class SlotMachine {
public:
  SlotMachine();

  void begin();
  void update();

private:
  void resetGame();

  void handleResetCombo();

  void handleIdle(ButtonType button);
  void handleSpinning(ButtonType button);
  void handleResult();
  void handleWin();
  void handleLose();
  void handleGameOver();
  void handleGameComplete();

  void renderReels();
  void updateLcdForState();
  void clampBetToBank();

#if DEBUG_REWARD_LOGS
  void logRewardDebug() const;
  const char* slotColorName(SlotColor color) const;
#endif

  uint8_t getResetSecondsLeft() const;

  GameState _state;

  ButtonManager _buttons;
  LedMatrix _matrix;
  Buzzer _buzzer;
  LedEffects _effects;
  LcdDisplay _lcd;
  ReelManager _reels;
  RewardSystem _rewardSystem;

  int _bank;
  int _bet;

  SpinResult _lastResult;

  unsigned long _stateStartTime;
};

#endif
