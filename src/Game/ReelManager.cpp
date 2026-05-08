#include "ReelManager.h"

#include "../../config/GameConfig.h"

ReelManager::ReelManager()
  : _spinning(false),
    _stoppedColumnCount(0),
    _lastSpinUpdateTime(0) {}

void ReelManager::begin() {
  _spinning = false;
  _stoppedColumnCount = 0;
  _lastSpinUpdateTime = 0;

  for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
    _columnStopped[col] = false;

    for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
      _grid[row][col] = SlotColor::EMPTY;
    }
  }
}

void ReelManager::startSpin() {
  _spinning = true;
  _stoppedColumnCount = 0;
  _lastSpinUpdateTime = millis();

  for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
    _columnStopped[col] = false;
  }

  for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
    for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
      _grid[row][col] = getRandomColor();
    }
  }
}

void ReelManager::update() {
  if (!_spinning) {
    return;
  }

  if (millis() - _lastSpinUpdateTime < SPIN_UPDATE_MS) {
    return;
  }

  _lastSpinUpdateTime = millis();

  for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
    if (_columnStopped[col]) {
      continue;
    }

    for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
      _grid[row][col] = getRandomColor();
    }
  }
}

void ReelManager::stopNextColumn() {
  if (!_spinning || _stoppedColumnCount >= SLOT_COLUMN_COUNT) {
    return;
  }

  _columnStopped[_stoppedColumnCount] = true;
  _stoppedColumnCount++;

  if (_stoppedColumnCount >= SLOT_COLUMN_COUNT) {
    _spinning = false;
  }
}

bool ReelManager::isSpinning() const {
  return _spinning;
}

bool ReelManager::isFinished() const {
  return !_spinning && _stoppedColumnCount >= SLOT_COLUMN_COUNT;
}

uint8_t ReelManager::getStoppedColumnCount() const {
  return _stoppedColumnCount;
}

SlotColor ReelManager::getGridColor(uint8_t row, uint8_t col) const {
  if (row >= SLOT_ROW_COUNT || col >= SLOT_COLUMN_COUNT) {
    return SlotColor::EMPTY;
  }

  return _grid[row][col];
}

SlotColor ReelManager::getRandomColor() const {
  int randomValue = random(100);

  if (randomValue < PROB_RED) {
    return SlotColor::RED;
  }

  randomValue -= PROB_RED;

  if (randomValue < PROB_GREEN) {
    return SlotColor::GREEN;
  }

  randomValue -= PROB_GREEN;

  if (randomValue < PROB_BLUE) {
    return SlotColor::BLUE;
  }

  randomValue -= PROB_BLUE;

  if (randomValue < PROB_YELLOW) {
    return SlotColor::YELLOW;
  }

  return SlotColor::PURPLE;
}

const SlotColor (*ReelManager::getGrid() const)[SLOT_COLUMN_COUNT] {

  return _grid;

}
