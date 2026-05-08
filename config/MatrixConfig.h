#ifndef MATRIX_CONFIG_H
#define MATRIX_CONFIG_H

// =====================
// MATRIX SIZE
// =====================
#define LED_MATRIX_WIDTH  8
#define LED_MATRIX_HEIGHT 8
#define LED_MATRIX_COUNT  (LED_MATRIX_WIDTH * LED_MATRIX_HEIGHT)

// =====================
// WIRING MODE
// =====================
// true  = zigzag / serpentine
// false = normal / progressive
#define MATRIX_SERPENTINE true

// =====================
// BRIGHTNESS
// =====================
#define MATRIX_BRIGHTNESS 40

// =====================
// SLOT LAYOUT
// =====================
#define SLOT_ROW_COUNT    3
#define SLOT_COLUMN_COUNT 4
#define SLOT_BLOCK_SIZE   2

#define SEPARATOR_ROW_1 2
#define SEPARATOR_ROW_2 5

// =====================
// SLOT COLORS (RGB)
// =====================
#define COLOR_RED_R     255
#define COLOR_RED_G     0
#define COLOR_RED_B     0

#define COLOR_GREEN_R   0
#define COLOR_GREEN_G   255
#define COLOR_GREEN_B   0

#define COLOR_BLUE_R    0
#define COLOR_BLUE_G    0
#define COLOR_BLUE_B    255

#define COLOR_YELLOW_R  255
#define COLOR_YELLOW_G  180
#define COLOR_YELLOW_B  0

#define COLOR_PURPLE_R  160
#define COLOR_PURPLE_G  0
#define COLOR_PURPLE_B  255

#define COLOR_EMPTY_R   0
#define COLOR_EMPTY_G   0
#define COLOR_EMPTY_B   0

// =====================
// SEPARATOR COLORS (RGB)
// =====================
#define SEPARATOR_DEFAULT_R 255
#define SEPARATOR_DEFAULT_G 180
#define SEPARATOR_DEFAULT_B 0

#define SEPARATOR_WIN_R     0
#define SEPARATOR_WIN_G     255
#define SEPARATOR_WIN_B     0

#define SEPARATOR_LOSE_R    255
#define SEPARATOR_LOSE_G    0
#define SEPARATOR_LOSE_B    0

#endif