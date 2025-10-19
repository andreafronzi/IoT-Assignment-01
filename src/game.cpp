#include <assert.h>
#include "game.h"
#include "hw.h"
#include <LiquidCrystal_I2C.h>

/*sequence to be reproduced*/
int currentSequence[4];
/*user's try*/
int trySequence[4];
int seqIndex;
float initilTime;
float currentRoundTime;

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
        case STATE_SLEEP:
            //entrare in deep_sleep
            handlerSleep();
            break;
        case STATE_START;
            if(/*sistema in deep sleep*/) {
                /*lo si sveglia*/
            }
            handlerStart();
            break;
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
static void handlerSleep() {
    if(readButton() == 1) {
        state = STATE_START;
    }
}

/*All leds are turned off, LCD displays the message "Go!" and the score is set to 0*/
static void handlerStart() {
    ledsOff();
    showLCDStartMessage();
    score = 0;
    state = STATE_PLAY_ROUND;
}

/**/
void handlerPlayRound() {
    seqIndex = 0;
    ledsOff();
    round += 1;
    initSequence();
    showLCDSequenceMessage(/*trasforma la sequenza in stringa*/);
    currentRoundTime = millis();
}

void handlerWaitInput() {
    if(millis() - currentRoundTime >= T1) {
        state = STATE_GAME_OVER;
    } else {
        int buttonPressed = readButton();
        assert(buttonPressed != 0);
        int corrispondentLed = getCorrispondentLed(buttonPressed);
        ledOn(corrispondentLed);
        delay(30)
        ledOff(corrispondentLed);
        trySequence[seqIndex] = buttonPressed;
        seqIndex += 1;
        if(seqIndex == 4) {
            if(SequenceAreEqual())  {
                state = STATE_PASSED_ROUND;
            } else {
                state = STATE_GAME_OVER;
        }
    }
}

/*increase the score and display it on the LCD. New roung begin and try time decreases */
void handlerPassedRound() {
    score += 1;
    showLCDScoreMessage(score);
    delay(3000);
    T1 = T1 - F;
    state = STATE_PLAY_ROUND;
}

/*Turno on red led for 2 seconds and display the message "Game Over - Final Score XXX"*/
void handlerGameOv() {
    ledOn(LR);
    delay(2000);
    ledOff(LR);
    showLCDGameOverMessage(score);
    state = STATE_WAIT_START;
}


static void initSequence() {
    int i = 0;
    while(i < 4) {
        int random = random(1, 5);
        int j;
        for(j = 0; j <= i; j++) {
            if(currentSequence[j] == random) {
                break;
            } else {
                currentSequence[i] = random;
            }
    }
}

static int getCorrispondentLed(int buttonPressed) {
    switch(buttonPressed) {
        case 1: return L1;
        case 2: return L2;
        case 3: return L3;
        case 4: return L4;
    }
}

static boll SequenceAreEqual() {
    int i;
    for(i = 0; i < 4; i++) {
        if(currentSequence[i] != trySequence[i]) {
            return false;
        }
    }
    return true;
}
