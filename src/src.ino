#include "lib.h"

#define POTENZIOMETER_PIN A0;

enum GameState { 
    INIT, 
    WAIT_START,
    DEEP_SLEEP,
    SHOW_SEQUENCE,
    WAIT_INPUT,
    GOOD,
    GAME_OVER
};

GameState state = INIT;

int level = 1;
float T1 = 0;
float F = 0;
int8_t buttonSequence[4] = {0, 0, 0, 0};


void setup() {
    Serial.begin(9600);
    //impostazione di T1 per il tempo iniziale
    T1 = 24;
    //setting F exploited for game's difficulty
    int potenziometerValue = analogRead(POTENZIOMETER_PIN);
    level = map(potenziometerValue, 0, 1023, 1, 4);
    switch (level)
    {
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

  begin();
}

void loop() {
    

}