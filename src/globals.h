#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

enum GameState { 
    INIT, 
    WAIT_START,
    DEEP_SLEEP,
    SHOW_SEQUENCE,
    WAIT_INPUT,
    GOOD,
    GAME_OVER
};

// variabili globali visibili in più file
extern volatile GameState state = INIT; // volatile perché modificata da ISR
extern volatile bool tickFlag;

#endif // GLOBALS_H