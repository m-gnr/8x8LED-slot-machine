#include "LedEffects.h"

#include "../../config/GameConfig.h"

LedEffects::LedEffects(LedMatrix& matrix)
  : _matrix(matrix),
    _currentEffect(EffectType::NONE),
    _resetSecondsLeft(0),
    _active(false),
    _lastUpdateTime(0),
    _blinkState(false) {
  for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
    for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
      _winningBlocks[row][col] = false;
      _blockColors[row][col] = SlotColor::EMPTY;
    }
  }
}

void LedEffects::update() {
  if (!_active) {
    return;
  }

  if (millis() - _lastUpdateTime < EFFECT_UPDATE_MS) {
    return;
  }

  _lastUpdateTime = millis();
  _blinkState = !_blinkState;

  switch (_currentEffect) {
    case EffectType::WIN:
      for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
        for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
          if (_winningBlocks[row][col]) {
            _matrix.drawBlock(col, row, _blinkState ? _blockColors[row][col] : SlotColor::EMPTY);
          }
        }
      }
      break;

    case EffectType::LOSE:
      break;

    case EffectType::RESET:
      break;

    case EffectType::GAME_OVER:
      if (!_blinkState) {
        _matrix.clear();
      }
      break;

    case EffectType::GAME_COMPLETE:
      if (!_blinkState) {
        _matrix.clear();
      }
      break;

    case EffectType::NONE:
    default:
      break;
  }

  _matrix.showDefaultSeparators();
  _matrix.show();
}

void LedEffects::stop() {
  _currentEffect = EffectType::NONE;
  _active = false;
  _blinkState = false;
}

void LedEffects::playWin(
  const SpinResult& result,
  const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT]
) {
  for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
    for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
      _winningBlocks[row][col] =
        result.rows[row].hasWin &&
        col >= result.rows[row].startColumn &&
        col < result.rows[row].startColumn + result.rows[row].matchCount;
      _blockColors[row][col] = grid[row][col];
    }
  }

  for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
    if (!result.columns[col].hasWin) {
      continue;
    }

    for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
      _winningBlocks[row][col] = true;
      _blockColors[row][col] = grid[row][col];
    }
  }

  _currentEffect = EffectType::WIN;
  _active = true;
  _lastUpdateTime = millis();
  _blinkState = true;
  _matrix.showDefaultSeparators();
  _matrix.show();
}

void LedEffects::playLose() {
  _currentEffect = EffectType::LOSE;
  _active = true;
  _lastUpdateTime = millis();
  _blinkState = true;
}

void LedEffects::playReset(uint8_t secondsLeft) {
  _currentEffect = EffectType::RESET;
  _resetSecondsLeft = secondsLeft;
  _active = true;
  _lastUpdateTime = millis();
}

void LedEffects::playGameOver() {
  _currentEffect = EffectType::GAME_OVER;
  _active = true;
  _lastUpdateTime = millis();
  _blinkState = true;
}

void LedEffects::playGameComplete() {
  _currentEffect = EffectType::GAME_COMPLETE;
  _active = true;
  _lastUpdateTime = millis();
  _blinkState = true;
}
