#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "../../Types.h"

class LedMatrix {
public:
  LedMatrix();

  void begin();
  void clear();
  void show();

  void setBrightness(uint8_t brightness);

  void setPixel(uint8_t x, uint8_t y, uint32_t color);
  uint32_t getPixel(uint8_t x, uint8_t y) const;

  void drawBlock(uint8_t slotColumn, uint8_t slotRow, SlotColor color);
  void drawSeparators(uint32_t color);

  void showWinSeparators();
  void showLoseSeparators();
  void showDefaultSeparators();

  uint32_t colorFromSlotColor(SlotColor color) const;

private:
  uint16_t getIndex(uint8_t x, uint8_t y) const;

  Adafruit_NeoPixel _matrix;
};

#endif