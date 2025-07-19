#include <msp430.h>
#include "switch.h"
#include "led.h"

char switch1_state, switch2_state, switch3_state, switch4_state;
char switch_state_changed = 0;
char switch_state = 0;

static char
switch_update_interrupt_sense(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void
switch_init()
{
  // Setup P1 buttons
  P2REN |= SWITCHES;
  P2IE  |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler()
{
  P1OUT ^= LED_RED;

}
