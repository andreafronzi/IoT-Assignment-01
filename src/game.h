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

void handlerInit();
void handlerWaitStart();
void handlerSleep();
void handlerStart();
void handlerPlayRound();
void handlerWaitInput();
void handlerPassedRound();
void handlerGameOv();


/*Led verdi spenti
  Led rosso lampeggiante
  LCD scritta "Welcome to TOS/n press b1 to start".
  Se non viene premuto niente in 10 sec, il sistema entra in deep sleep;
  altrimenti, se viene premuto b1, il gioco inizia*/
void begin();

void sleep();

/* Tutti i led spenti
   LCD compare la scritta: "Go!"
   punteggio = 0*/
void startRound();

void correctSequence();

void wrongSequence();

void stop();


/*se sono trascorsi 10 sec cambia lo stato del gioco*/
bool offTimer();

#endif