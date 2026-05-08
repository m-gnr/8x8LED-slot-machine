#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H

#include <Arduino.h>

#include "../../Types.h"

#include "../Hardware/ButtonManager.h"
#include "../Hardware/LedMatrix.h"
#include "../Hardware/LcdDisplay.h"

#include "../Game/ReelManager.h"
#include "../Game/RewardSystem.h"

<<<<<<< HEAD
#include "../Effects/SoundManager.h"

=======
>>>>>>> 9b0574246a65be3cbc8d62ab38c12e229cd0a0a2
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

  uint8_t getResetSecondsLeft() const;

  GameState _state;

  ButtonManager _buttons;
  LedMatrix _matrix;
  LcdDisplay _lcd;
  ReelManager _reels;
  RewardSystem _rewardSystem;

  int _bank;
  int _bet;

  SpinResult _lastResult;

  unsigned long _stateStartTime;
<<<<<<< HEAD

  SoundManager _soundManager;
=======
>>>>>>> 9b0574246a65be3cbc8d62ab38c12e229cd0a0a2
};

#endif