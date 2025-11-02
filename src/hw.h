#ifndef HW_H
#define HW_H

#include "game.h"
#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>

//definizione dei pin corrispondenti ai bottoni
#define B1 2
#define B2 9
#define B3 10
#define B4 11

//definizione dei pin corrispondente ai led VERDI
#define L1 8
#define L2 3
#define L3 4
#define L4 5

//definizione del pin corrispondente al pin rosso
#define LR 6

#define CURRISPONDENT_LED(button) ((button) == 1 ? L1 : (button) == 2 ? L2 : (button) == 3 ? L3 :  (button) == 4 ? L4 : LR)

/*definizione del pin corrispondente al potenziometro*/
#define POT_PIN A0

/*lcd monitor definition (defined in hw.cpp)
	define as extern here to avoid multiple definitions */
extern LiquidCrystal_I2C lcd;

/*initialization of harware component*/
void initHardware();

/*read Pot value*/
int readPOT();

/*read which button is pressed. Return 0 if no button is pressed or 1,2,3,4 if button 1,2,3,4 is pressed respectively*/
int readButton();

/*enable interrupts for buttons b1 to start game*/
void enableStartButtonInterrupt();

/*disabled actual interrupt of B1 and enable sleepInterrupt */
void enableSleepInterrupt();

void attachAllInterruptsForSequence();

/*disable all interrupts for sequence*/
void disableInterruptsForSequence();

/*put off all leds*/
void ledsOff();

/*turn on led idx*/
void ledOn(int idx);

/*turn off led idx*/
void ledOff(int idx);

/*avoid LR to start the fading*/
void startFading();

/*stop the fading of LR*/
void stopFading();

/*show initial message on LCD: "Welcome to TOS! Press B1 to start"*/
void showLCDInitialMessage();

/*show start message on LCD: "Go"*/
void showLCDStartMessage();

/*show sequence message on LCD: "XYWZ"*/
void showLCDSequenceMessage(uint8_t* seq);

/*show passed round message on LCD: "Good! Score XXX"*/
void showLCDScoreMessage(int score);

/*display the message "Game Over - Final Score XXX" for 10 seconds*/
void showLCDGameOverMessage(int score);

#endif