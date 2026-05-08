#include "src/App/SlotMachine.h"

SlotMachine game;

void setup() {
  game.begin();
}

void loop() {
  game.update();
}