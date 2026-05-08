#include "Buzzer.h"

#include "../../config/SoundConfig.h"

Buzzer::Buzzer(uint8_t pin, uint8_t channel)
  : _pin(pin),
    _channel(channel),
    _notes(nullptr),
    _durations(nullptr),
    _length(0),
    _noteIndex(0),
    _noteStartTime(0),
    _playing(false),
    _resting(false),
    _looping(false),
    _spinLoopActive(false) {
}

void Buzzer::init() {
  pinMode(_pin, OUTPUT);
  stopTone();
}

void Buzzer::update() {
  if (!_playing || _notes == nullptr || _durations == nullptr) {
    return;
  }

  unsigned long now = millis();

  if (_resting) {
    if (now - _noteStartTime < BUZZER_NOTE_GAP_MS) {
      return;
    }

    _resting = false;
    _noteIndex++;

    if (_noteIndex >= _length) {
      if (_looping) {
        _noteIndex = 0;
        startCurrentNote();
      } else if (_spinLoopActive) {
        startSpinLoopMelody();
      } else {
        stopMelody();
      }
      return;
    }

    startCurrentNote();
    return;
  }

  if (now - _noteStartTime >= _durations[_noteIndex]) {
    stopTone();
    _resting = true;
    _noteStartTime = now;
  }
}

void Buzzer::playTone(unsigned int frequency) {
  if (frequency == SOUND_REST) {
    stopTone();
    return;
  }

  tone(_pin, frequency);
}

void Buzzer::stopTone() {
  noTone(_pin);
}

void Buzzer::stopMelody() {
  _playing = false;
  _resting = false;
  _looping = false;
  _spinLoopActive = false;
  _notes = nullptr;
  _durations = nullptr;
  _length = 0;
  _noteIndex = 0;
  stopTone();
}

void Buzzer::playBetChange() {
  playMelody(BET_CHANGE_NOTES, BET_CHANGE_DURATIONS, 2);
}

void Buzzer::playSpinStart() {
  playMelody(SPIN_START_NOTES, SPIN_START_DURATIONS, 3);
}

void Buzzer::playSpinLoop() {
  _spinLoopActive = true;

  if (!_playing) {
    startSpinLoopMelody();
  }
}

void Buzzer::stopSpinLoop() {
  _spinLoopActive = false;

  if (_looping) {
    stopMelody();
  }
}

void Buzzer::playColumnStop() {
  playMelody(COLUMN_STOP_NOTES, COLUMN_STOP_DURATIONS, 1);
}

void Buzzer::playWin() {
  _spinLoopActive = false;
  playMelody(WIN_NOTES, WIN_DURATIONS, sizeof(WIN_NOTES) / sizeof(WIN_NOTES[0]));
}

void Buzzer::playLose() {
  _spinLoopActive = false;
  playMelody(LOSE_NOTES, LOSE_DURATIONS, sizeof(LOSE_NOTES) / sizeof(LOSE_NOTES[0]));
}

void Buzzer::playFinalVictory() {
  _spinLoopActive = false;
  playMelody(
    FINAL_VICTORY_NOTES,
    FINAL_VICTORY_DURATIONS,
    sizeof(FINAL_VICTORY_NOTES) / sizeof(FINAL_VICTORY_NOTES[0])
  );
}

void Buzzer::playFinalGameOver() {
  _spinLoopActive = false;
  playMelody(
    FINAL_GAME_OVER_NOTES,
    FINAL_GAME_OVER_DURATIONS,
    sizeof(FINAL_GAME_OVER_NOTES) / sizeof(FINAL_GAME_OVER_NOTES[0])
  );
}

void Buzzer::playMelody(
  const unsigned int* notes,
  const unsigned int* durations,
  uint8_t length,
  bool looping
) {
  _notes = notes;
  _durations = durations;
  _length = length;
  _noteIndex = 0;
  _playing = length > 0;
  _resting = false;
  _looping = looping;

  if (!_playing) {
    stopTone();
    return;
  }

  startCurrentNote();
}

void Buzzer::startSpinLoopMelody() {
  playMelody(
    SPIN_LOOP_NOTES,
    SPIN_LOOP_DURATIONS,
    sizeof(SPIN_LOOP_NOTES) / sizeof(SPIN_LOOP_NOTES[0]),
    true
  );
}

void Buzzer::startCurrentNote() {
  _noteStartTime = millis();
  playTone(_notes[_noteIndex]);
}
