#include <msp430.h>
#include "../timerLib/libTimer.h"
#include "buzzer.h"

int main() {
  configureClocks();
  buzzer_init();
  enableWDTInterrupts(); // Enable periodic interrupt
  or_sr(0x18); // CPU off, GIE on
}
int counter= 0;
int pitch = 4000;

void __interrupt_vec(WDT_VECTOR) WDT()
{
  counter += 50;
  if (counter > 250) {  
    pitch -= 10;           
    if (pitch <= 2000){   //reset
      pitch = 4000;
    }
    buzzer_set_period(pitch);
    counter = 0;
  }
}
