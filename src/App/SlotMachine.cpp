#include "SlotMachine.h"


#include "../../config/GameConfig.h"
#include "../../config/InputConfig.h"
#include "../../config/MatrixConfig.h"

#include "../../config/PinConfig.h"

SlotMachine::SlotMachine()
  : _state(GameState::IDLE),
    _bank(START_BANK),
    _bet(MIN_BET),
    _stateStartTime(0),
    _soundManager(BUZZER_PIN) {}

void SlotMachine::begin() {
  randomSeed(analogRead(0));

  _buttons.begin();
  _matrix.begin();
  _lcd.begin();
  _reels.begin();

  _soundManager.init();      
  _soundManager.playStartMusic();

  resetGame();
}

void SlotMachine::update() {
  _buttons.update();
  _soundManager.update();

  if (_buttons.isResetComboPressed()) {
    handleResetCombo();
    return;
  }

  ButtonType button = _buttons.getPressedButton();

  switch (_state) {
    case GameState::IDLE:
      handleIdle(button);
      break;

    case GameState::SPINNING:
    case GameState::STOPPING:
      handleSpinning(button);
      break;

    case GameState::RESULT:
      handleResult();
      break;

    case GameState::WIN:
      handleWin();
      break;

    case GameState::LOSE:
      handleLose();
      break;

    case GameState::GAME_OVER:
      handleGameOver();
      break;

    case GameState::GAME_COMPLETE:
      handleGameComplete();
      break;
  }
}

void SlotMachine::resetGame() {
  _state = GameState::IDLE;
  _bank = START_BANK;
  _bet = MIN_BET;
  _stateStartTime = millis();

  _reels.begin();

  _matrix.clear();
  _matrix.showDefaultSeparators();
  _matrix.show();

  _lcd.showIdle(_bank, _bet);
}

void SlotMachine::handleResetCombo() {
  uint8_t secondsLeft = getResetSecondsLeft();
  _lcd.showResetCountdown(secondsLeft);

  if (_buttons.getResetComboHoldTime() >= RESET_HOLD_MS) {
    resetGame();
  }
}

void SlotMachine::handleIdle(ButtonType button) {
  if (button == ButtonType::GREEN) {
    if (_bet < MAX_BET && _bet < _bank) {
      _bet++;
    }

    _lcd.showIdle(_bank, _bet);
  }

  else if (button == ButtonType::RED) {
    if (_bet > MIN_BET) {
      _bet--;
    }

    _lcd.showIdle(_bank, _bet);
  }

  else if (button == ButtonType::BLUE) {
    _bank -= _bet;

    _reels.startSpin();

    _state = GameState::SPINNING;
    _stateStartTime = millis();

    _soundManager.playSpinMusic();

    _lcd.showSpinning(_reels.getStoppedColumnCount());
  }
}

void SlotMachine::handleSpinning(ButtonType button) {
  _reels.update();
  renderReels();

  if (button == ButtonType::BLUE) {
    _reels.stopNextColumn();

    _lcd.showSpinning(_reels.getStoppedColumnCount());

    if (_reels.isFinished()) {
      _state = GameState::RESULT;
      _stateStartTime = millis();
      _lastResult = _rewardSystem.evaluate(_reels.getGrid(), _bet);
      _lcd.showResult(_lastResult);
    }
  }
}

void SlotMachine::handleResult() {
  if (millis() - _stateStartTime < RESULT_SCREEN_MS) {
    return;
  }

  if (_lastResult.totalReward > 0) {
    _bank += _lastResult.totalReward;

    if (_bank >= TARGET_BANK) {
      _state = GameState::GAME_COMPLETE;
      _stateStartTime = millis();
      _matrix.showWinSeparators();
      _matrix.show();
      _lcd.showGameComplete();
      _soundManager.playGameWonMusic(); 
      return;
    }

    _state = GameState::WIN;
    _stateStartTime = millis();
    _matrix.showWinSeparators();
    _matrix.show();
    _lcd.showWin(_lastResult.totalReward, _bank);
    return;
  }

  if (_bank <= 0) {
    _state = GameState::GAME_OVER;
    _stateStartTime = millis();
    _matrix.showLoseSeparators();
    _matrix.show();
    _lcd.showGameOver();
    _soundManager.playGameOverMusic(); 
    return;
  }

  _state = GameState::LOSE;
  _stateStartTime = millis();
  _matrix.showLoseSeparators();
  _matrix.show();
  _lcd.showLose(_bank);
}

void SlotMachine::handleWin() {
  if (millis() - _stateStartTime < RESULT_SCREEN_MS) {
    return;
  }

  _state = GameState::IDLE;
  _stateStartTime = millis();

  _matrix.showDefaultSeparators();
  _matrix.show();

  _lcd.showIdle(_bank, _bet);
}

void SlotMachine::handleLose() {
  if (millis() - _stateStartTime < RESULT_SCREEN_MS) {
    return;
  }

  _state = GameState::IDLE;
  _stateStartTime = millis();

  _matrix.showDefaultSeparators();
  _matrix.show();

  _lcd.showIdle(_bank, _bet);
}

void SlotMachine::handleGameOver() {
  // Stay here until reset combo is held.
}

void SlotMachine::handleGameComplete() {
  // Stay here until reset combo is held.
}

void SlotMachine::renderReels() {
  _matrix.clear();

  for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
    for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
      _matrix.drawBlock(col, row, _reels.getGridColor(row, col));
    }
  }

  _matrix.showDefaultSeparators();
  _matrix.show();
}

void SlotMachine::updateLcdForState() {
  switch (_state) {
    case GameState::IDLE:
      _lcd.showIdle(_bank, _bet);
      break;

    case GameState::SPINNING:
    case GameState::STOPPING:
      _lcd.showSpinning(_reels.getStoppedColumnCount());
      break;

    case GameState::RESULT:
      _lcd.showResult(_lastResult);
      break;

    case GameState::WIN:
      _lcd.showWin(_lastResult.totalReward, _bank);
      break;

    case GameState::LOSE:
      _lcd.showLose(_bank);
      break;

    case GameState::GAME_OVER:
      _lcd.showGameOver();
      break;

    case GameState::GAME_COMPLETE:
      _lcd.showGameComplete();
      break;
  }
}


uint8_t SlotMachine::getResetSecondsLeft() const {
  unsigned long holdTime = _buttons.getResetComboHoldTime();

  if (holdTime >= RESET_HOLD_MS) {
    return 0;
  }

  return (RESET_HOLD_MS - holdTime + 999) / 1000;
}

