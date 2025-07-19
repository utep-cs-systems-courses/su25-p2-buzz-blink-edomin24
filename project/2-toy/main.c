#include <msp430.h>
#include "switch.h"
#include "libTimer.h"
#include "led.h"

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;
  
  // Set P1.0 (Red LED) as output
  P1DIR |= LED_RED;
  P1OUT &= ~LED_RED;  
  switch_init();
  or_sr(0x18);

  while(1){
    if(switch_state_changed){
      switch_state_changed = 0;

      if(switch1_state || switch2_state || switch3_state || switch4_state){
	P1OUT |= LED_RED;
      }
      else{
	P1OUT &= ~LED_RED;
      }
    }
  }
}
