#include <msp430.h>
#include "led.h"
#include "buzzer.h"
#include "switches.h"

#ifndef stateMachine_included
#define stateMachine_included

extern int state;

void state_advance();

void button1();

void button2();

void button3();

void button4();
#endif
