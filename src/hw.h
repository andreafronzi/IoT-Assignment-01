#ifndef HW_H
#define HW_H

#include <Arduino.h>

//definizione dei pin corrispondenti ai bottoni
#define B1 8
#define B2 9
#define B3 10
#define B4 11

//definizione dei pin corrispondente ai led VERDI
#define L1 2
#define L2 3
#define L3 4
#define L4 5

//definizione del pin corrispondente al pin rosso
#define LR 6

/*definizione del pin corrispondente al potenziometro*/
#define POT_PIN A0

/*initialization of harware component*/
void initHardware();

/*read Pot value*/
int readPOT();

/*read which button is pressed*/
int readButton();
void ledsOff();
void ledOn(int idx);
void ledOff(int idx);

void startFading();

/*show initial message on LCD: "Welcome to TOS! Press B1 to start"*/
void showLCDInitialMessage();



#endif