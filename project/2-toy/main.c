#include <msp430.h>
#include "switch.h"

void main(void) {
  WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer

  // Set P1.0 (Red LED) as output
  P1DIR |= BIT0;
  P1OUT &= ~BIT0;                 // Start with LED off
  switch_init();                  // Initialize switches
  __enable_interrupt();           // Enable global interrupts

  while (1) {
    // Check global state set in switch_interrupt_handler
    if (switch_state_changed) {
      switch_state_changed = 0;
      if (switch1_state || switch2_state || switch3_state || switch4_state) {
	P1OUT |= BIT0;      // Turn ON LED if any switch is pressed
      } else {
	P1OUT &= ~BIT0;     // Turn OFF LED otherwise
      }
    }
  }
}

