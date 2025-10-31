#include <Arduino.h>
//#include <urs/sleep.h>
#include <EnableInterrupt.h>
#include "hw.h"
#include <LiquidCrystal_I2C.h>

// define lcd instance (declared extern in hw.h)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

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

    //inzializing lcd
    lcd.init();
    lcd.backlight();
}

/*POTENZIOMETER SECTION*/
int readPOT() {
    return analogRead(POT_PIN);
}

/*BUTTONS SECTION*/
void notifyStartButtonPressed() {
    changeStateToStart();
}

void enableStartButtonInterrupt() {
    disableInterrupt(B1);
	enableInterrupt(B1, notifyStartButtonPressed, RISING);
}

/*Wake up the system from sleep mode*/
static void wakeUp() {
    changeStateToStart();
}

void enableSleepInterrupt() {
    disableInterrupt(B1);
	enableInterrupt(B1,wakeUp,RISING);
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

/*LEDS SECTION*/
void ledsOff() {
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
    digitalWrite(LR, LOW);
}

void ledOn(int idx) {
    digitalWrite(CURRISPONDENT_LED(idx), HIGH);
}

void ledOff(int idx) {
    digitalWrite(CURRISPONDENT_LED(idx), LOW);
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
void showLCDInitialMessage() {
    lcd.setCursor(0,0);
    lcd.print("Welcome to TOS! Press B1 to start");
}

void showLCDStartMessage(){
    lcd.setCursor(0,0);
    lcd.print("Go");
}

static void transferSequenceToString(uint8_t* currentSequence) {
    // Build a simple string representation like "1234" and display on LCD
    String seqStr = "";
    for (int i = 0; i < 4; ++i) {
        seqStr += String(currentSequence[i]);
    }
    // show on lcd (caller may also use it differently)
    lcd.setCursor(0,0);
    lcd.print(seqStr);
}

void showLCDSequenceMessage(const char* seq){
    lcd.setCursor(0,0);
    lcd.print(seq);
}


void showLCDScoreMessage(int score){
    lcd.setCursor(0,0);
    lcd.print("Good! Score ");
    lcd.print(score);
}

void showLCDGameOverMessage(int score){
    lcd.setCursor(0,0);
    lcd.print("Game Over - Final Score ");
    lcd.print(score);
}

