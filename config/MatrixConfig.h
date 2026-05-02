#ifndef MATRIX_CONFIG_H
#define MATRIX_CONFIG_H

#define LED_MATRIX_WIDTH 8
#define LED_MATRIX_HEIGHT 8
#define LED_MATRIX_COUNT (LED_MATRIX_WIDTH * LED_MATRIX_HEIGHT)


// true  = zigzag / serpentine
// false = normal / progressive
#define MATRIX_SERPENTINE true

#define SLOT_ROW_COUNT 3
#define SLOT_COLUMN_COUNT 4
#define SLOT_BLOCK_SIZE 2

#define SEPARATOR_ROW_1 2
#define SEPARATOR_ROW_2 5

#endif