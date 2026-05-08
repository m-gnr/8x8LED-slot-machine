#ifndef MELODIES_H
#define MELODIES_H

#include "pitches.h"

// --- 1. Oyun Başlangıç Müziği ---
const int startThemeNotes[] = {
  NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_D5, 0,
  NOTE_C5, NOTE_AS4, NOTE_G4, 0,
  NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_F5, 0,
  NOTE_D5, NOTE_C5, NOTE_D5, 0
};
const int startThemeDurations[] = {
  8, 8, 8, 4, 16, 
  8, 8, 4, 8,
  8, 8, 8, 4, 16, 
  8, 8, 2, 4
};

// --- 2. OYUN İÇİ (SPIN) MELODİSİ ---
// Kolonlar dönerken arka planda sürekli tekrarlayacak (Loop) gerilimli ritim
const int spinMusicNotes[] = {
  NOTE_G3, 0, NOTE_AS3, 0, NOTE_C4, 0, NOTE_AS3, 0,
  NOTE_G3, 0, NOTE_F3,  0, NOTE_FS3, 0, NOTE_D3, 0
};
const int spinMusicDurations[] = {
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 16, 8, 16, 8, 16
};

// --- 3. KAZANMA (WIN / JACKPOT) MÜZİĞİ ---
// Giderek hızlanan, tatmin edici ve neşeli bir arcade kazanma sesi
const int winNotes[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, 
  NOTE_E5, NOTE_G5, NOTE_C6, 0, NOTE_C6
};
const int winDurations[] = {
  12, 12, 12, 12, 
  12, 12, 4, 16, 2
};

// --- 4. KAYBETME (GAME OVER) MÜZİĞİ ---
// Enerjisi tükenen, aşağı doğru çöken bir melodi
const int loseNotes[] = {
  NOTE_G4, NOTE_FS4, NOTE_F4, NOTE_E4, 0,
  NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_C4
};
const int loseDurations[] = {
  8, 8, 8, 4, 16,
  8, 8, 8, 2
};

#endif