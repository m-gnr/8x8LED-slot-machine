#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin, uint8_t channel) {
    this->pin = pin;
}

void Buzzer::init() {
    pinMode(pin, OUTPUT);
}

void Buzzer::playTone(unsigned int frequency) {
    if (frequency == 0) {
        stopTone();
    } else {
        tone(pin, frequency); // delay yok! Sadece sesi başlatıp anında çıkıyoruz.
    }
}

void Buzzer::stopTone() {
    noTone(pin);
}