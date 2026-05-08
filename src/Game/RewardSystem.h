#ifndef REWARD_SYSTEM_H
#define REWARD_SYSTEM_H

#include <Arduino.h>

#include "../../Types.h"
#include "../../config/MatrixConfig.h"

class RewardSystem {
public:
  RewardSystem();

  SpinResult evaluate(const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT], int bet) const;

private:
  RowResult evaluateRow(const SlotColor row[SLOT_COLUMN_COUNT], int bet) const;
  ColumnResult evaluateColumn(
    const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT],
    uint8_t col,
    int bet
  ) const;

  bool isJackpot(const SpinResult& result) const;
  int getMultiplier(SlotColor color, int matchCount) const;
  int getVerticalMultiplier(SlotColor color) const;
};

#endif
