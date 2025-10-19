#include <TimerOne.h>
#include <util/atomic.h
#include "lib.h"


#define POTENZIOMETER_PIN A0;

int round = 1;
float T1;
float F;

int8_t[4] buttonSequence = {0, 0, 0, 0};
int8_t[4] led = {0, 0, 0, 0};

void setup() {
    Serial.begin(9600);
    //impostazione di T1 per il tempo iniziale
    T1 = 24;
    //setting F exploited for game's difficulty
    int potenziometerValue = analogRead(POTENZIOMETER_PIN);
    int difficultyOfLevel = map(potenziometerValue, 0, 1023, 1, 4);
    switch (difficultyOfLevel) {
    case 1:
        F = 0.5;
        break;
    case 2:
        F = 1.0;
        break;
    case 3:
        F = 1.5;
        break;
    case 4:
        F = 2.0;
        break;
    default:
        break;
    }
}

void loop() {
    switch(state) {
        case INIT:
            long current = millis();
            Timer1.initialize(10,000,000);
            Timer1.attachInterrupt(offTimer);
            if()
            break;
        case DEEP_SLEEP:
            Timer1.detachInterrupt();

    }

}

 INIT, 
    WAIT_START,
    DEEP_SLEEP,
    SHOW_SEQUENCE,
    WAIT_INPUT,
    GOOD,
    GAME_OVER