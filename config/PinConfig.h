#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// =====================
// Deneyap Kart 1A v2
// Pin Configuration
// =====================

// WS2812B 8x8 RGB LED Matrix
#define LED_MATRIX_PIN D8

// 2x16 I2C LCD
// Wire.begin() uses the default SDA/SCL pins on Deneyap Kart 1A v2.
// SDA = D10
// SCL = D11

// Physical Buttons
// Buttons use INPUT_PULLUP.
// One side of each button goes to the pin,
// the other side goes to GND.
#define BUTTON_GREEN_PIN D12   // Increase bet
#define BUTTON_RED_PIN   D13   // Decrease bet
#define BUTTON_BLUE_PIN  D14   // Spin / Stop columns

#endif