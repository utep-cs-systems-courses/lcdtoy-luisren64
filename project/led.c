#include <msp430.h>
#include "led.h"

unsigned char red_on = 0;
unsigned char green_on = 0;

static char redVal[] = {0, LED_RED};
static char greenVal[] = {0, LED_GREEN};

void led_init(){
  P1DIR |= LEDS;
  led_update();
}


int led_update(){
  char ledFlags = 0;

  ledFlags |= red_on ? LED_RED: 0;
  ledFlags |= green_on ? LED_GREEN: 0;
  
  P1OUT &= (0xff^LEDS) | ledFlags;
  P1OUT |= ledFlags;
}
