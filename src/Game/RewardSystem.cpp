#include "RewardSystem.h"

#include "../../config/GameConfig.h"

RewardSystem::RewardSystem() {}

SpinResult RewardSystem::evaluate(
  const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT],
  int bet
) const {
  SpinResult result;
  result.winningRowCount = 0;
  result.winningColumnCount = 0;
  result.verticalReward = 0;
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

  for (uint8_t col = 0; col < SLOT_COLUMN_COUNT; col++) {
    result.columns[col] = evaluateColumn(grid, col, bet);

    if (result.columns[col].hasWin) {
      result.winningColumnCount++;
      result.verticalReward += result.columns[col].reward;
    }
  }

  result.totalReward += result.verticalReward;

  return result;
}

RowResult RewardSystem::evaluateRow(
  const SlotColor row[SLOT_COLUMN_COUNT],
  int bet
) const {
  RowResult result;
  result.hasWin = false;
  result.color = SlotColor::EMPTY;
  result.startColumn = 0;
  result.matchCount = 0;
  result.reward = 0;

  uint8_t col = 0;

  while (col < SLOT_COLUMN_COUNT) {
    SlotColor currentColor = row[col];

    if (currentColor == SlotColor::EMPTY) {
      col++;
      continue;
    }

    uint8_t startColumn = col;
    uint8_t matchCount = 1;

    while (
      col + matchCount < SLOT_COLUMN_COUNT &&
      row[col + matchCount] == currentColor
    ) {
      matchCount++;
    }

    if (matchCount >= 3 && matchCount > result.matchCount) {
      result.hasWin = true;
      result.color = currentColor;
      result.startColumn = startColumn;
      result.matchCount = matchCount;
      result.reward = bet * getMultiplier(currentColor, matchCount);
    }

    col += matchCount;
  }

  return result;
}

ColumnResult RewardSystem::evaluateColumn(
  const SlotColor grid[SLOT_ROW_COUNT][SLOT_COLUMN_COUNT],
  uint8_t col,
  int bet
) const {
  ColumnResult result;
  result.hasWin = false;
  result.color = SlotColor::EMPTY;
  result.columnIndex = col;
  result.reward = 0;

  if (col >= SLOT_COLUMN_COUNT) {
    return result;
  }

  SlotColor firstColor = grid[0][col];

  if (firstColor == SlotColor::EMPTY) {
    return result;
  }

  for (uint8_t row = 1; row < SLOT_ROW_COUNT; row++) {
    if (grid[row][col] != firstColor) {
      return result;
    }
  }

  result.hasWin = true;
  result.color = firstColor;
  result.reward = bet * getVerticalMultiplier(firstColor);

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
}

int RewardSystem::getVerticalMultiplier(SlotColor color) const {
  switch (color) {
    case SlotColor::RED:
      return VERTICAL_MULTIPLIER_RED;
    case SlotColor::GREEN:
      return VERTICAL_MULTIPLIER_GREEN;
    case SlotColor::BLUE:
      return VERTICAL_MULTIPLIER_BLUE;
    case SlotColor::YELLOW:
      return VERTICAL_MULTIPLIER_YELLOW;
    case SlotColor::PURPLE:
      return VERTICAL_MULTIPLIER_PURPLE;
    default:
      return 0;
  }
}
