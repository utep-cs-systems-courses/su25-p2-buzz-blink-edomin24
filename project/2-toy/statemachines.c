#include <msp430.h>
#include "statemachines.h"
#include "buzzer.h"
#include "led.h"
#include "switch.h"

void police_siren_led(){
  police_led();
  police_siren();
}

void play_song(){
  static char playing = 0;

  if (s2_state && !playing){
    reset_mary_had_a_little_lamb();
    playing = 1;
  }

  if(!s2_state){
    playing = 0;
  }

  if(!song_finished){
    mary_had_a_little_lamb();
  }
}

void clear(){
  P1OUT &= ~LEDS;
  buzzer_set_period(0);
}

void state_advance(){
  switch (current_state){
  case 0:
    police_siren_led();
    break;
    
  case 1:
    play_song(); 
    break;
    
    default: clear(); break;
  }
}
