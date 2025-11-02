#include <Arduino.h>
#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include "hw.h"
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>


// define lcd instance (declared extern in hw.h)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

unsigned int fadeValue = 5;
unsigned int currIntensity = 0;



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

// verifyTimeToSleep() removed: use millis() check in game's handlerWaitStart
void verifyTimeToSleep() {
    Timer1.initialize(10000000);
    Timer1.attachInterrupt(changeStateToSleepMode);
}

/*Wake up the system from sleep mode*/
static void wakeUp() {
}

void sleepUntilB1() {
    disableInterrupt(B1);
	enableInterrupt(B1,wakeUp,RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    changeStateToStart();
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
    delay(20);
}

void stopFading() {
    fadeValue= 0;
}

/*LCD SECTION*/
void showLCDInitialMessage() {
    lcd.setCursor(0,0);
    lcd.print("Welcome to TOS!");
    lcd.setCursor(0, 1);
    lcd.print("Press B1 to start");
}

void showLCDStartMessage(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Go");
}

void showLCDSequenceMessage(uint8_t* seq){
    lcd.clear();
    lcd.setCursor(0,0);
    for (int i = 0; i < 4; i++) {
        lcd.print(seq[i]);
    }
}


void showLCDScoreMessage(int score){
    lcd.setCursor(0,0);
    lcd.print("GOOD! Score ");
    lcd.print(score);
}

void showLCDGameOverMessage(int score){
    lcd.setCursor(0,0);
    lcd.print("Game Over");
    lcd.setCursor(0,1);
    lcd.print("Final Score:");
    lcd.print(score);
}

