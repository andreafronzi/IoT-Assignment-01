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
int round;

/*Notify the system to change state to START*/
void changeStateToStart();

/*update current sequence*/
void pushFirstButtonToSequence();
void pushSecondButtonToSequence();
void pushThirdButtonToSequence();
void pushFourthButtonToSequence();

/*inizializzo le variabili di gioco*/
void gameInit();

void gameLoop();

#endif