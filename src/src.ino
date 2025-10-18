#include "lib.h"

#define POTENZIOMETER_PIN A0;

int level = 1;
float T1 = 0;
float F = 0;
int8_t buttonSequence[4] = {0, 0, 0, 0};


void setup() {
    Serial.begin(9600);
    T1 = 24;
    int potenziometerValue = analogRead(POTENZIOMETER_PIN);
    level = map(potenziometerValue, 0, 1023, 1, 4);
    switch (level)
    {
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
        break;
    }
  begin();
}