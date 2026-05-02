#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "../../Types.h"

class LcdDisplay {
public:
  LcdDisplay();

  void begin();
  void clear();

  void showIdle(int bank, int bet);
  void showSpinning(uint8_t stoppedColumnCount);
  void showResult(const SpinResult& result);
  void showWin(int reward, int bank);
  void showLose(int bank);
  void showGameOver();
  void showGameComplete();
  void showResetCountdown(uint8_t secondsLeft);

private:
  LiquidCrystal_I2C _lcd;
};

#endif