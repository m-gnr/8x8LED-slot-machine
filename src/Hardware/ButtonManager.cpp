#include "ButtonManager.h"

#include "../../config/PinConfig.h"
#include "../../config/InputConfig.h"

ButtonManager::ButtonManager()
  : _buttons{
      {BUTTON_GREEN_PIN, false, false, false, 0},
      {BUTTON_RED_PIN,   false, false, false, 0},
      {BUTTON_BLUE_PIN,  false, false, false, 0}
    },
    pressedButton(ButtonType::NONE),
    resetComboStartTime(0) {}

void ButtonManager::begin() {
  for (uint8_t i = 0; i < 3; i++) {
    pinMode(_buttons[i].pin, INPUT_PULLDOWN);

    bool reading = readButton(i);

    _buttons[i].pressed = reading;
    _buttons[i].lastReading = reading;
    _buttons[i].stable = reading;
    _buttons[i].lastDebounceTime = 0;
  }

  resetComboStartTime = 0;
}

void ButtonManager::update() {
  static const ButtonType buttonTypes[3] = {
    ButtonType::GREEN,
    ButtonType::RED,
    ButtonType::BLUE
  };

  pressedButton = ButtonType::NONE;

  for (uint8_t i = 0; i < 3; i++) {
    bool reading = readButton(i);

    if (reading != _buttons[i].lastReading) {
      _buttons[i].lastDebounceTime = millis();
      _buttons[i].lastReading = reading;
    }

    if ((millis() - _buttons[i].lastDebounceTime) >= DEBOUNCE_MS) {
      if (reading != _buttons[i].stable) {
        _buttons[i].stable = reading;

        if (_buttons[i].stable) {
          _buttons[i].pressed = true;
          pressedButton = buttonTypes[i];
        } else {
          _buttons[i].pressed = false;
        }
      }
    }
  }

  if (isResetComboPressed()) {
    if (resetComboStartTime == 0) {
      resetComboStartTime = millis();
    }
  } else {
    resetComboStartTime = 0;
  }
}

ButtonType ButtonManager::getPressedButton() const {
  return pressedButton;
}

bool ButtonManager::areAllButtonsPressed() const {
  return _buttons[0].stable &&
         _buttons[1].stable &&
         _buttons[2].stable;
}

bool ButtonManager::isResetComboPressed() const {
  return areAllButtonsPressed();
}

unsigned long ButtonManager::getResetComboHoldTime() const {
  if (!isResetComboPressed() || resetComboStartTime == 0) {
    return 0;
  }

  return millis() - resetComboStartTime;
}

bool ButtonManager::readButton(uint8_t index) const {
  // INPUT_PULLUP -> LOW = pressed
  return digitalRead(_buttons[index].pin) == HIGH;
}