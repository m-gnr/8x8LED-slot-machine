#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "../Hardware/Buzzer.h"
#include "Melodies.h"

class SoundManager {
private:
    Buzzer buzzer;

    // Asenkron (Non-blocking) değişkenler
    const int* _currentNotes;
    const int* _currentDurations;
    int _melodyLength;
    int _currentNoteIndex;
    
    unsigned long _noteStartTime;
    int _currentNoteDuration;
    bool _isPlaying;
    bool _isResting; // Notalar arası kısa boşluk (50ms) için
    bool _isLooping;

    void startMelody(const int* notes, const int* durations, int length, bool loop = false);

public:
    SoundManager(uint8_t pin, uint8_t channel = 0);
    void init();
    
    void update(); // ANA DÖNGÜDE SÜREKLİ ÇAĞRILACAK

    void playStartMusic();
    void playGameWonMusic();
    void playGameOverMusic();
    void playSpinMusic();
    void stopMusic();
};

#endif