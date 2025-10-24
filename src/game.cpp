#include "game.h"
#include "hw.h
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h>

#define CURRISPONDENT_LED(button) ((button) == 1 ? L1 : (button) == 2 ? L2 : (button) == 3 ? L3 : L4)

/*sequence to be reproduced*/
int currentSequence[4];
/*user's try*/
uint8_t trySequence[4];
uint8_t seqIndex;
int seqIndex;
float initilTime;
float currentRoundTime;

void gameInit() {

	/*set initial index of the sequence*/
	seqIndex = 0;
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
}

void gameLoop() {
    switch (state) {
        case STATE_INIT: handlerInit(); break;
        case STATE_WAIT_START: handlerWaitStart(); break;
        case STATE_SLEEP:
            //entrare in deep_sleep
            handlerSleep();
            break;
        case STATE_START:
            if(/*sistema in deep sleep*/) {
                /*lo si sveglia*/
            }
            handlerStart();
            break;
        case STATE_PLAY_ROUND: handlerPlayRound(); break;
        case STATE_WAIT_INPUT: handlerWaitInput(); break;
        case STATE_PASSED_ROUND: handlerPassedRound(); break;
        case STATE_GAME_OVER: handlerGameOv(); break;}
}

/*after the initialization, the system go in WAIT_START mode*/
static void handlerInit() {
    showLCDInitialMessage();
    delay(3000);
    state = STATE_WAIT_START;
    initilTime = millis();
}

/* If the B1 button is not pressed within 10 seconds, the system must go into deep sleeping. If the B1 button is pressed within 10s, the game starts*/
static void handlerWaitStart() {
    startFading();
    putButton1InInitialMode();
	if(millis() - initialTime >= 10000) {
		state = STATE_SLEEP;
		return;
	}
}


/*If the system is in sleep mode, it must wake up and go into START mode*/
static void handlerSleep() {
    enableSleepInterrupt();
}

/*All leds are turno off, LCD displays the message "Go!" and the score is set to 0*/
static void handlerStart() {
    ledsOff();
    showLCDStartMessage();
    resetScore();
    state = STATE_PLAY_ROUND;
}

/**/
void handlerPlayRound() {
    resetSequenceIndex();
    ledsOff();
    updateRound();
    initSequence();
    showLCDSequenceMessage(/*trasforma la sequenza in stringa*/);
    currentRoundTime = millis();
    disableInterruptsForSequence();
    state = STATE_WAIT_INPUT;
}

void handlerWaitInput() {
    enableInterruptsForSequence();
    if(millis() - currentRoundTime >= T1) {
        state = STATE_GAME_OVER;
    } else {
        if(seqIndex == 4) {
            if(SequenceAreEqual())  {
                state = STATE_PASSED_ROUND;
            } else {
                state = STATE_GAME_OVER;
        }
    }
    }
}

/*increase the score and display it on the LCD. New roung begin and try time decreases */
static void handlerPassedRound() {
    increaseScore();
    showLCDScoreMessage(score);
    delay(3000);
    T1 = T1 - F;
    state = STATE_PLAY_ROUND;
}

/*Turno on red led for 2 seconds and display the message "Game Over - Final Score XXX"*/
static void handlerGameOv() {
    disableInterruptsForSequence();
    ledOn(LR);
    delay(2000);
    ledOff(LR);
    showLCDGameOverMessage(score);
    state = STATE_WAIT_START;
}


static void initSequence() {
	randomSeed(analogRead(A1));  //inizializzo il generatore di numeri casuali
	int i = 0;
  	while (i < 4) {
    	int r = random(1, 5); // 1..4 (5 escluso)
    // controlla se r è già presente tra gli elementi 0..i-1
    	bool exists = false;
    	for (int j = 0; j < i; j++) {
      		if (currentSequence[j] == r) { exists = true; break; }
    	}
    	if (!exists) {
      	currentSequence[i] = r;
      	i++;
    }
    // se exists==true, viene tentato un nuovo r
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

static bool SequenceAreEqual() {
    uint8_t i;
    for(i = 0; i < 4; i++) {
        if(currentSequence[i] != trySequence[i]) {
            return false;
        }
    }
    return true;
}

static void putButton1InInitialMode() {
    enableStartButtonInterrupt();
}

void pushFirstButtonToSequence() {
	if(state == STATE_WAIT_INPUT && seqIndex < 4) {
        uint8_t buttonPressed = 1;
		trySequence[seqIndex] = buttonPressed;
        ledOn(CURRISPONDENT_LED(buttonPressed));
        delay(30);
        ledOff(CURRISPONDENT_LED(buttonPressed));
		seqIndex++;
	}
}

void pushSecondButtonToSequence() {
	if(state == STATE_WAIT_INPUT && seqIndex < 4) {
        uint8_t buttonPressed = 2;
		trySequence[seqIndex] = buttonPressed;
        ledOn(CURRISPONDENT_LED(buttonPressed));
        delay(30);
        ledOff(CURRISPONDENT_LED(buttonPressed));
		seqIndex++;
	}
}

void pushThirdButtonToSequence() {
	if(state == STATE_WAIT_INPUT && seqIndex < 4) {
        uint8_t buttonPressed = 3;
		trySequence[seqIndex] = buttonPressed;
        ledOn(CURRISPONDENT_LED(buttonPressed));
        delay(30);
        ledOff(CURRISPONDENT_LED(buttonPressed));
		seqIndex++;
	}
}
void pushFourthButtonToSequence() {
    if(state == STATE_WAIT_INPUT && seqIndex < 4) {
        uint8_t buttonPressed = 4;
        trySequence[seqIndex] = buttonPressed;
        ledOn(CURRISPONDENT_LED(buttonPressed));
        delay(30);
        ledOff(CURRISPONDENT_LED(buttonPressed));
        seqIndex++;
    }
}

void changeStateToStart() {
    if(state == STATE_WAIT_START || state == STATE_SLEEP) {
        state = STATE_START;
    }
}

/*Reset the score*/
static void resetScore() {
    score = 0;
}

/*increase the score*/
static void increaseScore() {
    score += 1;
}

/*Reset the sequence index*/
static void resetSequenceIndex() {
    seqIndex = 0;
}

/*Update round's number*/
static void updateRound() {
    round += 1;
}