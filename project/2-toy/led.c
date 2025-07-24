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


void red_green_dim_to_bright() {
  static char brightness = 0;
  static char direction = 1;     // 1 = brighten, 0 = dim
  static char phase = 0;         // 0 = red, 1 = green

  static int phase_counter = 0;
  static int fade_counter = 0;

  P1OUT &= ~LEDS; /*initially leds are off */

  phase_counter++;
  if(phase_counter >= 4){
    phase_counter = 0;
  } 

  if (brightness > 0 && phase_counter < brightness){
    if (phase == 0) {
      P1OUT |= LED_RED;
      P1OUT &= ~LED_GREEN;
    } else {
      P1OUT |= LED_GREEN;
      P1OUT &= ~LED_RED;
    }
  } else {
    P1OUT &= ~LEDS;
  }
  
  fade_counter ++;          //fade timining logic, update brightness every 32 ticks
  if (fade_counter >=32){
    fade_counter = 0;
    
    if (direction) {           //brightness up, dim when peaked
      brightness++;
      if (brightness >= 4) {
	brightness = 3;
	direction = 0;
      }
    }
    else{
      if(brightness > 0){  //dimming to 0 restart brightness
	brightness --;
      }
      else{
	direction = 1;
	if(phase == 0){
	  phase = 1;
	}
	else{
	  phase = 0;
	}
      }
    }
  }
}
