#include "LcdDisplay.h"

#include "../../config/LcdConfig.h"

LcdDisplay::LcdDisplay()
  : _lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS) {}

void LcdDisplay::begin() {
  _lcd.init();
  _lcd.backlight();
  _lcd.clear();
}

void LcdDisplay::clear() {
  _lcd.clear();
}

void LcdDisplay::showIdle(int bank, int bet) {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_BANK);
  _lcd.print("$");
  _lcd.print(bank);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_BET);
  _lcd.print("$");
  _lcd.print(bet);
}

void LcdDisplay::showSpinning(uint8_t stoppedColumnCount) {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_SPINNING);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_STOPPED);
  _lcd.print(stoppedColumnCount);
}

void LcdDisplay::showResult(const SpinResult& result) {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_ROWS);
  _lcd.print(result.winningRowCount);
  _lcd.print(" Col:");
  _lcd.print(result.winningColumnCount);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_REWARD);
  _lcd.print("$");
  _lcd.print(result.totalReward);
}

void LcdDisplay::showWin(int reward, int bank) {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_YOU_WIN);
  _lcd.print("$");
  _lcd.print(reward);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_BANK);
  _lcd.print("$");
  _lcd.print(bank);
}

void LcdDisplay::showLose(int bank) {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_TRY_AGAIN);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_BANK);
  _lcd.print("$");
  _lcd.print(bank);
}

void LcdDisplay::showGameOver() {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_GAME_OVER);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_PRESS_RESET);
}

void LcdDisplay::showGameComplete() {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_GAME_COMPLETE);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_CONGRATS);
}

void LcdDisplay::showResetCountdown(uint8_t secondsLeft) {
  _lcd.clear();

  _lcd.setCursor(0, 0);
  _lcd.print(LCD_MSG_RESETTING);

  _lcd.setCursor(0, 1);
  _lcd.print(LCD_MSG_RESET_IN);
  _lcd.print(secondsLeft);
}
