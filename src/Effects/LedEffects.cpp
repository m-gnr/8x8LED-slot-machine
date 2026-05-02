#include "LedEffects.h"

#include "../../config/GameConfig.h"

LedEffects::LedEffects(LedMatrix& matrix)
  : _matrix(matrix),
    _currentEffect(EffectType::NONE),
    _resetSecondsLeft(0),
    _active(false),
    _lastUpdateTime(0),
    _blinkState(false) {}

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
      if (_blinkState) {
        _matrix.showWinSeparators();
      } else {
        _matrix.showDefaultSeparators();
      }
      break;

    case EffectType::LOSE:
      if (_blinkState) {
        _matrix.showLoseSeparators();
      } else {
        _matrix.showDefaultSeparators();
      }
      break;

    case EffectType::RESET:
      if (_resetSecondsLeft % 2 == 0) {
        _matrix.showLoseSeparators();
      } else {
        _matrix.showDefaultSeparators();
      }
      break;

    case EffectType::GAME_OVER:
      if (_blinkState) {
        _matrix.showLoseSeparators();
      } else {
        _matrix.clear();
      }
      break;

    case EffectType::GAME_COMPLETE:
      if (_blinkState) {
        _matrix.showWinSeparators();
      } else {
        _matrix.showDefaultSeparators();
      }
      break;

    case EffectType::NONE:
    default:
      break;
  }

  _matrix.show();
}

void LedEffects::playWin() {
  _currentEffect = EffectType::WIN;
  _active = true;
}

void LedEffects::playLose() {
  _currentEffect = EffectType::LOSE;
  _active = true;
}

void LedEffects::playReset(uint8_t secondsLeft) {
  _currentEffect = EffectType::RESET;
  _resetSecondsLeft = secondsLeft;
  _active = true;
}

void LedEffects::playGameOver() {
  _currentEffect = EffectType::GAME_OVER;
  _active = true;
}

void LedEffects::playGameComplete() {
  _currentEffect = EffectType::GAME_COMPLETE;
  _active = true;
}