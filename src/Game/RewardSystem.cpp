#include "RewardSystem.h"

#include "../../config/GameConfig.h"

RewardSystem::RewardSystem() {}

SpinResult RewardSystem::evaluate(
  const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT],
  int bet
) const {
  SpinResult result;
  result.winningRowCount = 0;
  result.totalReward = 0;
  result.isJackpot = false;

  for (uint8_t row = 0; row < SLOT_ROW_COUNT; row++) {
    result.rows[row] = evaluateRow(grid[row], bet);

    if (result.rows[row].hasWin) {
      result.winningRowCount++;
      result.totalReward += result.rows[row].reward;
    }
  }

  result.isJackpot = isJackpot(result);

  if (result.isJackpot) {
    result.totalReward *= JACKPOT_MULTIPLIER;
  } else if (result.winningRowCount == 2) {
    result.totalReward =
      result.totalReward * BONUS_TWO_ROWS_MULTIPLIER / BONUS_MULTIPLIER_DIVISOR;
  } else if (result.winningRowCount == 3) {
    result.totalReward =
      result.totalReward * BONUS_THREE_ROWS_MULTIPLIER / BONUS_MULTIPLIER_DIVISOR;
  }

  return result;
}

RowResult RewardSystem::evaluateRow(
  const SlotColor row[SLOT_COLUMN_COUNT],
  int bet
) const {
  RowResult result;
  result.hasWin = false;
  result.color = SlotColor::EMPTY;
  result.matchCount = 0;
  result.reward = 0;

  SlotColor firstColor = row[0];

  if (firstColor == SlotColor::EMPTY) {
    return result;
  }

  uint8_t matchCount = 1;

  for (uint8_t col = 1; col < SLOT_COLUMN_COUNT; col++) {
    if (row[col] == firstColor) {
      matchCount++;
    } else {
      break;
    }
  }

  if (matchCount >= 3) {
    result.hasWin = true;
    result.color = firstColor;
    result.matchCount = matchCount;
    result.reward = bet * getMultiplier(firstColor, matchCount);
  }

  return result;
}

bool RewardSystem::isJackpot(const SpinResult& result) const {
  if (result.winningRowCount != SLOT_ROW_COUNT) {
    return false;
  }

  SlotColor jackpotColor = result.rows[0].color;

  if (jackpotColor == SlotColor::EMPTY) {
    return false;
  }

  for (uint8_t row = 1; row < SLOT_ROW_COUNT; row++) {
    if (!result.rows[row].hasWin || result.rows[row].color != jackpotColor) {
      return false;
    }
  }

  return true;
}

int RewardSystem::getMultiplier(SlotColor color, int matchCount) const {
  if (matchCount >= 4) {
    switch (color) {
      case SlotColor::RED:
        return MULTIPLIER_4_RED;
      case SlotColor::GREEN:
        return MULTIPLIER_4_GREEN;
      case SlotColor::BLUE:
        return MULTIPLIER_4_BLUE;
      case SlotColor::YELLOW:
        return MULTIPLIER_4_YELLOW;
      case SlotColor::PURPLE:
        return MULTIPLIER_4_PURPLE;
      default:
        return 0;
    }
  }

  if (matchCount >= 3) {
    switch (color) {
      case SlotColor::RED:
        return MULTIPLIER_3_RED;
      case SlotColor::GREEN:
        return MULTIPLIER_3_GREEN;
      case SlotColor::BLUE:
        return MULTIPLIER_3_BLUE;
      case SlotColor::YELLOW:
        return MULTIPLIER_3_YELLOW;
      case SlotColor::PURPLE:
        return MULTIPLIER_3_PURPLE;
      default:
        return 0;
    }
  }

  return 0;
<<<<<<< HEAD
=======

const SlotColor (*ReelManager::getGrid() const)[SLOT_COLUMN_COUNT] {
  return _grid;
}

>>>>>>> 9b0574246a65be3cbc8d62ab38c12e229cd0a0a2
}