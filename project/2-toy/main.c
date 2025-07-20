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
  switch (current_state){
  case 0: police_siren_led(); break;
  default: clear(); break;
  }
}
