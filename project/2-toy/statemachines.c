#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "statemachines.h"

void police_siren_led(){
  police_led();
  police_siren();
}


void clear(){
  P1OUT &= ~LEDS;
  buzzer_set_period(0);
}

