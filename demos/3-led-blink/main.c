//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);			/* CPU off, GIE on */
}

// global state var to count time
int secondCount = 0;

void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  secondCount += 10;
  if (secondCount <= 124) { 	/* once each sec... */
    P1OUT |= LED_GREEN;		/* toggle green LED */
    P1OUT &= ~LED_RED;
  }

  else{
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
    secondCount = 0;
  }
}

