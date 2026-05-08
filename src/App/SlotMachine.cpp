#include "SlotMachine.h"

#include "../../config/GameConfig.h"
#include "../../config/InputConfig.h"
#include "../../config/MatrixConfig.h"
#include "../../config/PinConfig.h"

SlotMachine::SlotMachine()
  : _state(GameState::IDLE),
    _buzzer(BUZZER_PIN),
    _effects(_matrix),
    _bank(START_BANK),
    _bet(MIN_BET),
    _stateStartTime(0) {}

void SlotMachine::begin() {
#if DEBUG_REWARD_LOGS
  Serial.begin(115200);
#endif

  randomSeed(analogRead(0));

  _buttons.begin();
  _matrix.begin();
  _buzzer.init();
  _lcd.begin();
  _reels.begin();

  resetGame();
}

void SlotMachine::update() {
  _buttons.update();

  if (_buttons.isResetComboPressed()) {
    handleResetCombo();
    _buzzer.update();
    _effects.update();
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

  _buzzer.update();
  _effects.update();
}

void SlotMachine::resetGame() {
  _state = GameState::IDLE;
  _bank = START_BANK;
  _bet = MIN_BET;
  _stateStartTime = millis();

  _effects.stop();
  _buzzer.stopMelody();
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
    if (_bet < _bank) {
      _bet++;
      _buzzer.playBetChange();
    }

    clampBetToBank();
    _lcd.showIdle(_bank, _bet);
  }

  else if (button == ButtonType::RED) {
    if (_bet > MIN_BET) {
      _bet--;
      _buzzer.playBetChange();
    }

    clampBetToBank();
    _lcd.showIdle(_bank, _bet);
  }

  else if (button == ButtonType::BLUE) {
    if (_bank < MIN_BET || _bet > _bank) {
      clampBetToBank();
      _lcd.showIdle(_bank, _bet);
      return;
    }

    _effects.stop();
    _bank -= _bet;
    clampBetToBank();

    _reels.startSpin();

    _state = GameState::SPINNING;
    _stateStartTime = millis();

    _buzzer.playSpinStart();
    _buzzer.playSpinLoop();
    _lcd.showSpinning(_reels.getStoppedColumnCount());
  }
}

void SlotMachine::handleSpinning(ButtonType button) {
  _reels.update();
  renderReels();

  if (button == ButtonType::BLUE) {
    _reels.stopNextColumn();
    _buzzer.playColumnStop();

    _lcd.showSpinning(_reels.getStoppedColumnCount());

    if (_reels.isFinished()) {
      _buzzer.stopSpinLoop();
      _state = GameState::RESULT;
      _stateStartTime = millis();
      _lastResult = _rewardSystem.evaluate(_reels.getGrid(), _bet);
#if DEBUG_REWARD_LOGS
      logRewardDebug();
#endif
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
    clampBetToBank();

    if (_bank >= TARGET_BANK) {
      _state = GameState::GAME_COMPLETE;
      _stateStartTime = millis();
      _buzzer.stopSpinLoop();
      _effects.playWin(_lastResult, _reels.getGrid());
      _lcd.showGameComplete();
      _buzzer.playFinalVictory();
      return;
    }

    _state = GameState::WIN;
    _stateStartTime = millis();
    _effects.playWin(_lastResult, _reels.getGrid());
    _lcd.showWin(_lastResult.totalReward, _bank);
    _buzzer.playWin();
    return;
  }

  if (_bank <= 0) {
    _state = GameState::GAME_OVER;
    _stateStartTime = millis();
    clampBetToBank();
    _buzzer.stopSpinLoop();
    _effects.playGameOver();
    _lcd.showGameOver();
    _buzzer.playFinalGameOver();
    return;
  }

  _state = GameState::LOSE;
  _stateStartTime = millis();
  clampBetToBank();
  _effects.playLose();
  _matrix.showDefaultSeparators();
  _matrix.show();
  _lcd.showLose(_bank);
  _buzzer.playLose();
}

void SlotMachine::handleWin() {
  if (millis() - _stateStartTime < RESULT_SCREEN_MS) {
    return;
  }

  _state = GameState::IDLE;
  _stateStartTime = millis();
  _effects.stop();
  clampBetToBank();

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
  _effects.stop();
  clampBetToBank();

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

void SlotMachine::clampBetToBank() {
  if (_bank < MIN_BET) {
    _bet = _bank;
    return;
  }

  if (_bet < MIN_BET) {
    _bet = MIN_BET;
  }

  if (_bet > _bank) {
    _bet = _bank;
  }
}

#if DEBUG_REWARD_LOGS
void SlotMachine::logRewardDebug() const {
  Serial.println("=== REWARD DEBUG ===");

  const SlotColor (*grid)[SLOT_COLUMN_COUNT] = _reels.getGrid();

  for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
    Serial.print("Row ");
    Serial.print(row);
    Serial.print(": ");

    for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
      Serial.print(slotColorName(grid[row][col]));

      if (col < SLOT_COLUMN_COUNT - 1) {
        Serial.print(" ");
      }
    }

    Serial.print(" | hasWin=");
    Serial.print(_lastResult.rows[row].hasWin ? "YES" : "NO");
    Serial.print(" startColumn=");
    Serial.print(_lastResult.rows[row].startColumn);
    Serial.print(" matchCount=");
    Serial.print(_lastResult.rows[row].matchCount);
    Serial.print(" color=");
    Serial.print(slotColorName(_lastResult.rows[row].color));
    Serial.print(" reward=");
    Serial.println(_lastResult.rows[row].reward);
  }

  Serial.print("winningRowCount=");
  Serial.print(_lastResult.winningRowCount);
  Serial.print(" winningColumnCount=");
  Serial.print(_lastResult.winningColumnCount);
  Serial.print(" verticalReward=");
  Serial.print(_lastResult.verticalReward);
  Serial.print(" totalReward=");
  Serial.print(_lastResult.totalReward);
  Serial.print(" jackpot=");
  Serial.println(_lastResult.isJackpot ? "YES" : "NO");

  for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
    Serial.print("Column ");
    Serial.print(col);
    Serial.print(": hasWin=");
    Serial.print(_lastResult.columns[col].hasWin ? "YES" : "NO");
    Serial.print(" color=");
    Serial.print(slotColorName(_lastResult.columns[col].color));
    Serial.print(" reward=");
    Serial.println(_lastResult.columns[col].reward);
  }

  Serial.println("====================");
}

const char* SlotMachine::slotColorName(SlotColor color) const {
  switch (color) {
    case SlotColor::RED:
      return "RED";
    case SlotColor::GREEN:
      return "GREEN";
    case SlotColor::BLUE:
      return "BLUE";
    case SlotColor::YELLOW:
      return "YELLOW";
    case SlotColor::PURPLE:
      return "PURPLE";
    case SlotColor::EMPTY:
    default:
      return "EMPTY";
  }
}
#endif

uint8_t SlotMachine::getResetSecondsLeft() const {
  unsigned long holdTime = _buttons.getResetComboHoldTime();

  if (holdTime >= RESET_HOLD_MS) {
    return 0;
  }

  return (RESET_HOLD_MS - holdTime + 999) / 1000;
}
