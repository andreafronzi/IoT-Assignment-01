#include <Arduino.h>
#include <urs/sleep.h>
#include "hw.h"

static unsigned int fadeValue = 5;
static unsigned int currIntensity = 0;



void initHardware() {
    //inizializzazione bottoni
    pinMode(B1, INPUT);
    pinMode(B2, INPUT);
    pinMode(B3, INPUT);
    pinMode(B4, INPUT);

    //inizializzazione led verdi
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(L3, OUTPUT);
    pinMode(L4, OUTPUT);

    //inizializzazione led rosso
    pinMode(LR, OUTPUT);
}

int readPOT() {
    return analogRead(POT_PIN);
}

int readButton() {
    if(digitalRead(B1) == HIGH) return 1;
    if(digitalRead(B2) == HIGH) return 2;
    if(digitalRead(B3) == HIGH) return 3;
    if(digitalRead(B4) == HIGH) return 4;
    return 0;
}

/*enable interrupts for buttons b1 to start game*/
void enableStartButtonInterrupt() {
    disableInterrupt(B1);
	enableInterrupt(B1, notifyStartButtonPressed, RISING);
}

/*enable interrupt for weaking up sistem from sleep_mode */
void enableSleepInterrupt() {
    disableInterrupt(B1);
	enableInterrupt(B1,wakeUp,RISING);
}

/*Wake up the system from sleep mode*/
static void wakeUp() {
    changeStateToStart();
}

void attachAllInterruptsForSequence() {
    /*enable all Interrupts for buttons*/
    enableInterrupt(B1,notifyPressedButton1ForSequence,RISING);
	enableInterrupt(B2,notifyPressedButton2ForSequence,RISING);
	enableInterrupt(B3,notifyPressedButton3ForSequence,RISING);
	enableInterrupt(B4,notifyPressedButton4ForSequence,RISING);
}

void disableInterruptsForSequence() {
    /*disable all Interrupts for buttons*/
    disableInterrupt(B1);
    disableInterrupt(B2);
    disableInterrupt(B3);
    disableInterrupt(B4);
}

/*Notify wich button was pressed during the round */
void notifyPressedButton1ForSequence() {
	pushFirstButtonToSequence();
}

void notifyPressedButton2ForSequence() {
	pushSecondButtonToSequence();
}

void notifyPressedButton3ForSequence() {
	pushThirdButtonToSequence();
}

void notifyPressedButton4ForSequence() {
	pushFourthButtonToSequence();
}

/*Notify if b1 is pressed for starting the game*/
void notifyStartButtonPressed() {
    changeStateToStart();
}


void ledsOff() {
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
    digitalWrite(LR, LOW);
}

void ledOn(int idx) {
    switch (idx) {
        case 1: digitalWrite(L1, HIGH); break;
        case 2: digitalWrite(L2, HIGH); break;
        case 3: digitalWrite(L3, HIGH); break;
        case 4: digitalWrite(L4, HIGH); break;
        case 6: digitalWrite(LR, HIGH); break;
    }
}

void ledOff(int idx) {
    switch (idx) {
        case 1: digitalWrite(L1, LOW); break;
        case 2: digitalWrite(L2, LOW); break;
        case 3: digitalWrite(L3, LOW); break;
        case 4: digitalWrite(L4, LOW); break;
        case 6: digitalWrite(LR, LOW); break;
    }
}

void startFading() {
    analogWrite(LR, currIntensity);
    currIntensity = currIntensity + fadeValue;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeValue = -fadeValue;
    }
}

void stopFading() {
    fadeValue= 0;
}


