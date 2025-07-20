#include <msp430.h>
#include "statemachines.h"
#include "buzzer.h"
#include "led.h"
#include "switch.h"

enum SongState song_state = IDLE;

void police_siren_led(){
  police_led();
  police_siren();
}

void play_song() {
  char last_s2_state = 0;
  if(s2_state && !last_s2_state){
    reset_mary_had_a_little_lamb();
    song_state = PLAYING;
  }
  
  if(!s2_state && last_s2_state){
    buzzer_set_period(0);
    song_state = IDLE;
  }

  if (song_state == PLAYING && s2_state){
    mary_had_a_little_lamb();
  }
  last_s2_state = s2_state;
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
