#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

int state = 0; 

void state_advance(){
  switch(state){
  case 1: red_on =1; green_on =0;
    button1();
    led_update();
    break;
  case 2:
    button2();
    break;
  case 3:
    clearScreen(COLOR_WHITE);
    drawChar11x16(10,10,'H',COLOR_RED,COLOR_BLUE);
    drawChar11x16(21,10,'e',COLOR_RED,COLOR_BLUE);
    drawChar11x16(32,10,'y',COLOR_RED,COLOR_BLUE);
    button3();
    break;
  case 4: red_on =0; green_on =0;
    buzzer_set_period(5405); led_update();
    break;
  default:
    red_on = 1; green_on = 1;
    clearScreen(COLOR_BLACK);
    buzzer_set_period(6000); led_update();
    break;
  }
}

  void button1(){
    static int note = 1;
    switch(note++){
    case 1: buzzer_set_period(7664);
      clearScreen(COLOR_BLUE);
      break;
    case 2: buzzer_set_period(5102);
      //clearScreen(COLOR_WHITE);
      break;
    case 3: buzzer_set_period(4049);
      break;
    case 4: buzzer_set_period(5405);
      note = 1;
      break;
    }
  }

void button2(){
  static int dim = 1;
  switch(dim++){
  case 1:case 2:
    red_on=1; green_on=1;
    led_update();
    break;
  case 3: red_on=0; green_on=0;
    led_update();
    dim = 1;
    break;
  }
}

void button3(){
  static int x = 50;
  static int y =50;
  static int size = 5;
  for (int j =  size;j > 0;j--){
    drawPixel(x-j,y-j+size, COLOR_RED);//bottom left
    drawPixel(x+j,y-j+size, COLOR_RED);//bottom right
    drawPixel(x-j+size,y-j, COLOR_RED);//top right
    drawPixel(x+j-size,y-j, COLOR_RED);//top left
  }
  if (size > 20){
    size = 5;
  }
  else{
    size++;
  }
}

  

  
