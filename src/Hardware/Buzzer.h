#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
  Buzzer(uint8_t pin, uint8_t channel = 0);

  void init();
  void update();

  void playTone(unsigned int frequency);
  void stopTone();
  void stopMelody();

  void playBetChange();
  void playSpinStart();
  void playColumnStop();
  void playWin();
  void playLose();

private:
  void playMelody(const unsigned int* notes, const unsigned int* durations, uint8_t length);
  void startCurrentNote();

  uint8_t _pin;
  uint8_t _channel;

  const unsigned int* _notes;
  const unsigned int* _durations;
  uint8_t _length;
  uint8_t _noteIndex;

  unsigned long _noteStartTime;
  bool _playing;
  bool _resting;
};

#endif
