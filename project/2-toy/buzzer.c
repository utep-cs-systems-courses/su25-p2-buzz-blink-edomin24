#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "led.h"
#include "statemachines.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 4;		/* one half cycle */
}

void police_siren(){
  static int counter = 0;
  static int pitch = 4000;

  counter += 75;

  if (counter > 250){
    pitch -= 10;
    if(pitch <= 2000){
      pitch = 4000;
    }
    buzzer_set_period(pitch);
    counter = 0;
  }
}
int note_index = 0;
int note_duration = 0;
char song_finished = 0;

void mary_had_a_little_lamb() {

  static int melody[] = {
    E4, D4, C4, D4, E4, E4, E4,
    D4, D4, D4,
    E4, G4, G4,
    E4, D4, C4, D4, E4, E4, E4,
    E4, D4, D4,
    E4, D4, C4
  };

  static int num_notes = sizeof(melody) / sizeof(melody[0]);
  if (song_finished) {
    return;
  }

  if (note_duration == 0) {
    if (note_index < num_notes) {
      buzzer_set_period(melody[note_index]);
      note_duration = 80;
      note_index++;
    } else {
     
      song_finished = 1;
    }
  } else {
    note_duration--;
  }
}

void reset_mary_had_a_little_lamb(){
  note_index = 0;
  note_duration = 0;
  song_finished = 0;
  buzzer_set_period(0);
}
