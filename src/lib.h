#ifndef LIB_H
#define LIB_H
/*Led verdi spenti
  Led rosso lampeggiante
  LCD scritta "Welcome to TOS/n press b1 to start".
  Se non viene premuto niente in 10 sec, il sistema entra in deep sleep;
  altrimenti, se viene premuto b1, il gioco inizia*/
void begin();

void sleep();

/* Tutti i led spenti
   LCD compare la scritta: "Go!"
   punteggio = 0*/
void startRound();

void correctSequence();

void wrongSequence();

void stop();


/*se sono trascorsi 10 sec cambia lo stato del gioco*/
bool offTimer();

#endif