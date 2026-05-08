#include "SoundManager.h"

SoundManager::SoundManager(uint8_t pin, uint8_t channel) 
  : buzzer(pin, channel), _isPlaying(false), _isResting(false) {}

void SoundManager::init() {
    buzzer.init();
}

void SoundManager::startMelody(const int* notes, const int* durations, int length, bool loop) {
    _currentNotes = notes;
    _currentDurations = durations;
    _melodyLength = length;
    _currentNoteIndex = 0;
    _isPlaying = true;
    _isLooping = loop; 
    _isResting = false;
    _noteStartTime = millis();
    
    _currentNoteDuration = 1000 / _currentDurations[0];
    buzzer.playTone(_currentNotes[0]);
}

void SoundManager::update() {
    if (!_isPlaying) return;

    unsigned long currentTime = millis();

    if (_isResting) {
        // Notalar arası 50ms sessizlik boşluğu bitti mi?
        if (currentTime - _noteStartTime >= 50) { 
            _isResting = false;
            _currentNoteIndex++;
            
            // Melodi bitti mi?
            if (_currentNoteIndex >= _melodyLength) {
                if (_isLooping) {
                    _currentNoteIndex = 0; 
                } else {
                    _isPlaying = false; 
                    buzzer.stopTone();
                    return;
                }
            }

            // Sıradaki notaya geç
            _noteStartTime = currentTime;
            _currentNoteDuration = 1000 / _currentDurations[_currentNoteIndex];
            buzzer.playTone(_currentNotes[_currentNoteIndex]);
        }
    } else {
        // Çalan notanın süresi doldu mu?
        if (currentTime - _noteStartTime >= _currentNoteDuration) {
            buzzer.stopTone(); 
            _isResting = true;
            _noteStartTime = currentTime; // Boşluk süresini başlat
        }
    }
}

void SoundManager::playStartMusic() {
    int size = sizeof(startThemeNotes) / sizeof(startThemeNotes[0]);
    startMelody(startThemeNotes, startThemeDurations, size);
}

void SoundManager::playGameWonMusic() { 
    int size = sizeof(winNotes) / sizeof(winNotes[0]);
    startMelody(winNotes, winDurations, size);
}

void SoundManager::playGameOverMusic() { 
    int size = sizeof(loseNotes) / sizeof(loseNotes[0]);
    startMelody(loseNotes, loseDurations, size);
}

void SoundManager::playSpinMusic() {
    int size = sizeof(spinMusicNotes) / sizeof(spinMusicNotes[0]);
    startMelody(spinMusicNotes, spinMusicDurations, size, true); 
}

void SoundManager::stopMusic() {
    _isPlaying = false;
    buzzer.stopTone();
}