#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

void buzzer_init() {
  timerAUpmode();           // Use libTimer function
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;            // Set P2.6 as output
  P2SEL |= BIT6;            // Enable PWM on P2.6
  P2DIR |= BIT6;
  buzzer_set_period(1000);  // Start with base pitch
}

void buzzer_set_period(short cycles) {
  CCR0 = cycles;
  CCR1 = cycles >> 1;       // 50% duty cycle
}
