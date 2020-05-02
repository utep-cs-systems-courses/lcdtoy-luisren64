#include <msp430.h>
#include "switches.h"
#include "stateMachines.h"

char switch1, switch2, switch3, switch4;

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  //
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init(){
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
}

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  switch1 = (p2val & SW1) ? 0 : 1;
  switch2 = (p2val & SW2) ? 0 : 1;
  switch3 = (p2val & SW3) ? 0 : 1;
  switch4 = (p2val & SW4) ? 0 : 1;
  
  if (switch1){
    state = 1;
  }
  else if (switch2){
    state =2;
  }
  else if (switch3){
    state = 3;
  }
  else if (switch4){
    state = 4;
  }
}
