#include "game.h"
#include "hw.h"
#include <LiquidCrystal_I2C.h>

int currentSequence[4];
int seqIndex;
int initilTime;

void gameInit() {
    /*inizializzo lo stato del gioco*/
    state = STATE_INIT;
    /*inizializzo il valore del tempo iniziale*/
    T1 = 1000;
    /*inizializzo il valore del round*/
    round = 0;
    /*inizializzo il punteggio*/
    score = 0;
    /*set difficulty*/
    int difficulty = readPOT();
    //mappo il valore letto in 4 livelli di difficoltà
    int level = map(difficulty, 0, 1023, 1, 4);
    switch (level) {
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
            F = 1.0;
            break;
    }
    ledsOff();
    startFading();
    showLCDInitialMessage();
    /*Set initial timer to verify if the MCU should enter in sleep mode*/
    initilTime = millis();
}

void gameLoop() {
    switch (state) {
        case STATE_INIT: handlerInit(); break;
        case STATE_WAIT_START: handlerWaitStart(); break;
        case STATE_SLEEP handlerSleep(); break;
        case STATE_START; handlerStart(); break;
        case STATE_PLAY_ROUND: handlerPlayRound(); break;
        case STATE_WAIT_INPUT: handlerWaitInput(); break;
        case STATE_PASSED_ROUND: handlerPassedRound(); break;
        case STATE_GAME_OVER: handlerGameOv(); break;
    }
}

/*after the initialization, the system go in WAIT_START mode*/
static void handlerInit() {state = STATE_WAIT_START;}

/* If the B1 button is not pressed within 10 seconds, the system must go into deep sleeping. If the B1 button is pressed within, the game starts*/
static void handlerWaitStart(); {
if (readButton() == 1) {
        state = STATE_START;
    } else if (millis() - initilTime >= 10000) {
        state = STATE_SLEEP;
    }
}

/*If the system is in sleep mode, it must wake up and go into START mode*/
void handlerSleep() {
    
}
void handlerStart();
void handlerPlayRound();
void handlerWaitInput();
void handlerPassedRound();
void handlerGameOv();