#include <msp430.h>
#include "switch.h"
#include "libTimer.h"
#include "led.h"

void main(void) {
  // Set P1.0 (Red LED) as output
  P1DIR |= BIT0;
  P1OUT |= BIT0;                 // Start with LED off
  
  or_sr(0x18);
}

