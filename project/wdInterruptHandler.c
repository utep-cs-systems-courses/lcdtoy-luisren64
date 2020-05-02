#include <msp430.h>
#include "stateMachines.h"

void __interrupt_vec(WDT_VECTOR) WDT(){
  static char blink_count = 0;
  if (++blink_count == 125){ //every 1/10th of a second
    state_advance();
    blink_count = 0;
  }
  else if(blink_count == 4 && state ==2){
    state_advance();
    blink_count = 0;
  }
}
