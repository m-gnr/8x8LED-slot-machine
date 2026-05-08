#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <Arduino.h>
#include "../../Types.h"

class ButtonManager {
public:
  ButtonManager();

  void begin();
  void update();

  ButtonType getPressedButton() const;
  bool areAllButtonsPressed() const;
  bool isResetComboPressed() const;
  unsigned long getResetComboHoldTime() const;

private:
  struct ButtonState {
    uint8_t pin;
    bool pressed;
    bool lastReading;
    bool stable;
    unsigned long lastDebounceTime;
  };

  ButtonState _buttons[3];

  bool readButton(uint8_t index) const;

  ButtonType pressedButton;
  unsigned long resetComboStartTime;
};

#endif