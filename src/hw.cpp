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

/*POTENZIOMETER SECTION*/
int readPOT() {
    return analogRead(POT_PIN);
}

/*BUTTONS SECTION*/
void enableStartButtonInterrupt() {
    disableInterrupt(B1);
	enableInterrupt(B1, notifyStartButtonPressed, RISING);
}

void enableSleepInterrupt() {
    disableInterrupt(B1);
	enableInterrupt(B1,wakeUp,RISING);
}

/*Wake up the system from sleep mode*/
static void wakeUp() {
    changeStateToStart();
}

void attachAllInterruptsForSequence() {
    enableInterrupt(B1,notifyPressedButton1ForSequence,RISING);
	enableInterrupt(B2,notifyPressedButton2ForSequence,RISING);
	enableInterrupt(B3,notifyPressedButton3ForSequence,RISING);
	enableInterrupt(B4,notifyPressedButton4ForSequence,RISING);
}

void disableInterruptsForSequence() {
    disableInterrupt(B1);
    disableInterrupt(B2);
    disableInterrupt(B3);
    disableInterrupt(B4);
}

/*Notify wich button was pressed during the round in order to be inserted into the sequence*/
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

/*LEDS SECTION*/
void ledsOff() {
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
    digitalWrite(LR, LOW);
}

void ledOn(int idx) {
    digitalWrite(idx, HIGH);
}

void ledOff(int idx) {
    digitalWrite(idx, LOW);
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

/*LCD SECTION*/
void showLCDInitialMessage() {}

void showLCDStartMessage(){}

void showLCDSequenceMessage(const char* seq){}

void showLCDScoreMessage(int score){}

void showLCDGameOverMessage(int score){}

