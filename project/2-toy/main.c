#include <msp430.h>
#include "switch.h"
#include "buzzer.h"
#include "statemachines.h"
#include "libTimer.h"
#include "led.h"

int main(void) {
  configureClocks();
  switch_init();
  buzzer_init();
  led_init();
  enableWDTInterrupts();
  or_sr(0x18);
}

void __interrupt_vec(WDT_VECTOR) WDT(){
  state_advance(); //initalize state machine
}
