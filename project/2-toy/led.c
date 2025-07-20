#include <msp430.h>
#include "led.h"

void led_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}

void police_led(){
  static char phase = 0;
  static char phase_counter = 0;
  static char stutter_counter = 0;
  static char stutter = 0;

  phase_counter ++;

  switch(phase){
  case 0:
    if (phase_counter <= 124){
      if (phase_counter <= 62){
	P1OUT |= LED_RED;
	P1OUT &= ~LED_GREEN;
      } else {
	P1OUT |= LED_GREEN;
	P1OUT &= ~LED_RED;
      }
    } else {
      phase = 1;
      phase_counter = 0;
    }

    break;

  case 1:     /*stutter logic */
    stutter_counter ++;

    if (stutter_counter >= 5){
      stutter ^= 1;
      stutter_counter = 0;
    }

    if (stutter){
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    } else {
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    }

    if (phase_counter >= 124){
      phase = 0;
      phase_counter = 0;
    }

    break;
  }
}
