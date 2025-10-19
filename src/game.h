#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

typedef enum {
  STATE_INIT,
  STATE_WAIT_START,
  STATE_SLEEP,
  STATE_START,
  STATE_PLAY_ROUND,
  STATE_WAIT_INPUT,
  STATE_PASSED_ROUND,
  STATE_GAME_OVER
} GameState;

extern int round;
extern float T1;
extern float F;
extern GameState state;
extern int score;

/*inizializzo le variabili di gioco*/
void gameInit();

void gameLoop();

#endif