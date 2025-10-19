#include <Arduino.h>
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
    }
}

void ledOn(int idx) {
    switch (idx) {
        case 1: digitalWrite(L1, LOW); break;
        case 2: digitalWrite(L2, LOW); break;
        case 3: digitalWrite(L3, LOW); break;
        case 4: digitalWrite(L4, LOW); break;
    }
}

void startFading() {
    analogWrite(LED_PIN, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
        fadeAmount = -fadeAmount ;
    }
}

void stopFading() {
    fadeAmount = 0;
}


