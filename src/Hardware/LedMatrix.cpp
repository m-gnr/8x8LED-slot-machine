#include "LedMatrix.h"

#include "../../config/PinConfig.h"
#include "../../config/MatrixConfig.h"

LedMatrix::LedMatrix()
  : _matrix(LED_MATRIX_COUNT, LED_MATRIX_PIN, NEO_GRB + NEO_KHZ800) {}

void LedMatrix::begin() {
  _matrix.begin();
  _matrix.clear();
  _matrix.setBrightness(MATRIX_BRIGHTNESS);
  _matrix.show();
}

void LedMatrix::clear() {
  _matrix.clear();
}

void LedMatrix::show() {
  _matrix.show();
}

void LedMatrix::setBrightness(uint8_t brightness) {
  _matrix.setBrightness(brightness);
}

void LedMatrix::setPixel(uint8_t x, uint8_t y, uint32_t color) {
  if (x >= LED_MATRIX_WIDTH || y >= LED_MATRIX_HEIGHT) {
    return;
  }

  _matrix.setPixelColor(getIndex(x, y), color);
}

uint32_t LedMatrix::getPixel(uint8_t x, uint8_t y) const {
  if (x >= LED_MATRIX_WIDTH || y >= LED_MATRIX_HEIGHT) {
    return 0;
  }

  return _matrix.getPixelColor(getIndex(x, y));
}

void LedMatrix::drawBlock(uint8_t slotColumn, uint8_t slotRow, SlotColor color) {
  if (slotColumn >= SLOT_COLUMN_COUNT || slotRow >= SLOT_ROW_COUNT) {
    return;
  }

  uint8_t startX = slotColumn * SLOT_BLOCK_SIZE;
  uint8_t startY;

  if (slotRow == 0) {
    startY = 0;
  } else if (slotRow == 1) {
    startY = SEPARATOR_ROW_1 + 1;
  } else {
    startY = SEPARATOR_ROW_2 + 1;
  }

  uint32_t ledColor = colorFromSlotColor(color);

  for (uint8_t y = startY; y < startY + SLOT_BLOCK_SIZE; y++) {
    for (uint8_t x = startX; x < startX + SLOT_BLOCK_SIZE; x++) {
      setPixel(x, y, ledColor);
    }
  }
}

void LedMatrix::drawSeparators(uint32_t color) {
  for (uint8_t x = 0; x < LED_MATRIX_WIDTH; x++) {
    setPixel(x, SEPARATOR_ROW_1, color);
    setPixel(x, SEPARATOR_ROW_2, color);
  }
}

void LedMatrix::showDefaultSeparators() {
  drawSeparators(_matrix.Color(
    SEPARATOR_DEFAULT_R,
    SEPARATOR_DEFAULT_G,
    SEPARATOR_DEFAULT_B
  ));
}

uint32_t LedMatrix::colorFromSlotColor(SlotColor color) const {
  switch (color) {
    case SlotColor::RED:
      return _matrix.Color(COLOR_RED_R, COLOR_RED_G, COLOR_RED_B);

    case SlotColor::GREEN:
      return _matrix.Color(COLOR_GREEN_R, COLOR_GREEN_G, COLOR_GREEN_B);

    case SlotColor::BLUE:
      return _matrix.Color(COLOR_BLUE_R, COLOR_BLUE_G, COLOR_BLUE_B);

    case SlotColor::YELLOW:
      return _matrix.Color(COLOR_YELLOW_R, COLOR_YELLOW_G, COLOR_YELLOW_B);

    case SlotColor::PURPLE:
      return _matrix.Color(COLOR_PURPLE_R, COLOR_PURPLE_G, COLOR_PURPLE_B);

    case SlotColor::EMPTY:
    default:
      return _matrix.Color(COLOR_EMPTY_R, COLOR_EMPTY_G, COLOR_EMPTY_B);
  }
}

uint16_t LedMatrix::getIndex(uint8_t x, uint8_t y) const {
  if (MATRIX_SERPENTINE && (y % 2 == 1)) {
    return y * LED_MATRIX_WIDTH + (LED_MATRIX_WIDTH - 1 - x);
  }

  return y * LED_MATRIX_WIDTH + x;
}
