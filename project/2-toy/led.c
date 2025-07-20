#include <msp430.h>
#include "led.h"

void police_led(){
  char phase = 0;
  char phase_counter = 0;
  char stutter_counter = 0;
  char stutter = 0;

  phase_counter ++;

  if (phase == 0){               /*regular led blink logic */
    if(phase_counter >= 124){
      phase = 1;
    }

    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  }

  else{                      /* led stutter control logic */
    if (phase >= 124){
      phase = 0;
    }

    stutter_counter ++;

    if(stutter_counter >= 5){
      stutter ^= 1;
      stutter_counter = 0;
    }

    if (stutter){
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    }

    else{
      P1OUT |= LED_RED;
      P1OUT &= LED_GREEN;
    }
  }
}
    
