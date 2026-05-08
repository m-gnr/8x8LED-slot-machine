#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
private:
    uint8_t pin;
    uint8_t channel;
    
public:
    Buzzer(uint8_t pin, uint8_t channel = 0);
    void init();
    void playTone(unsigned int frequency); 
    void stopTone();
};

#endif