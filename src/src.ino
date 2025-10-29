#include <TimerOne.h>
#include <util/atomic.h>
#include "game.h"
#include "hw.h"

void setup() {
    InitHardware();
    gameInit();
}

void loop() {
  gameLoop();
}