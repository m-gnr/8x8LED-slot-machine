#ifndef REEL_MANAGER_H
#define REEL_MANAGER_H

#include <Arduino.h>

#include "../../Types.h"
#include "../../config/MatrixConfig.h"

class ReelManager {
public:
  ReelManager();

  void begin();

  void startSpin();
  void update();
  void stopNextColumn();

  bool isSpinning() const;
  bool isFinished() const;

  uint8_t getStoppedColumnCount() const;
  SlotColor getGridColor(uint8_t row, uint8_t col) const;
  const SlotColor (*getGrid() const)[SLOT_COLUMN_COUNT];

private:
  SlotColor getRandomColor() const;

  SlotColor _grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT];

  bool _columnStopped[SLOT_COLUMN_COUNT];
  bool _spinning;

  uint8_t _stoppedColumnCount;
  unsigned long _lastSpinUpdateTime;
};

#endif