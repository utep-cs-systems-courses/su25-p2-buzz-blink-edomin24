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
  switch(song_state){
  case IDLE:
    buzzer_set_period(0);
    reset_mary_had_a_little_lamb();
    
    if(s2_state == 1){
      song_state = PLAYING;
    }
    
    break;
    
  case PLAYING:
    mary_had_a_little_lamb();
    if(s2_state == 0){
      song_state = IDLE;
    }
    else if (song_finished){
      song_state = SWITCH_RELEASE;
    }

    break;

  case SWITCH_RELEASE:
    buzzer_set_period(0);
    if(s2_state == 0){
      song_state = IDLE;
    }
    break;
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
