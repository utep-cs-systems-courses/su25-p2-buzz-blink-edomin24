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

  /* checks if s2 is pressed */
  if(s2_state != 0){
    mary_had_a_little_lamb();
    if(song_finished){                /*reset and wait for next play */
      reset_mary_had_a_little_lamb();
      s2_state = 0;
    }

  }
}

static char s3_phase = 0;
void red_green() {
  if (s3_state){
    switch(s3_phase){
    case 0: red_green(0); s3_phase = 1; break;
    case 1: red_green(1); s3_phase = 2; break;
    case 2: red_green(2); s3_phase = 0; break;
    }
  }

  s3_state = 0;
}

void clear(){
  P1OUT &= ~LEDS;
  buzzer_set_period(0);
}

void state_advance(){
  switch (current_state){
  case 0: police_siren_led(); break;
  case 1: play_song(); break;
  case 2: red_green(); break;
  default: clear(); break;
    
  }
}
