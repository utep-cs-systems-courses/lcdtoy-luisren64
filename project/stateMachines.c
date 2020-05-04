#include <msp430.h>
#include "stateMachines.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

int state = 0; 

void state_advance(){
  //The following variables keep track of whether or not this is the first time a state is entered.
  //Used to stop clearScreen from being called every time.
  static int first = 0;
  static int first1=0;
  static int first2 =0;
  static int first3 = 0;
  static int first4 = 0;
  
  switch(state){
  case 1:
    if (first1 == 0){
      clearScreen(COLOR_BLACK);
      first1++;
      first2 = 0;
      first3 = 0;
      first4 = 0;
    }
    button1();
    break;
    
  case 2:
    if(first2 == 0){
      clearScreen(COLOR_GOLDENROD);
      first2++;
      first1 = 0;
      first3 = 0;
      first4 = 0;
      buzzer_set_period(0);
    }
    button2();
    break;
    
  case 3:
    if (first3 == 0){
      clearScreen(COLOR_WHITE);
      first3++;
      first1 = 0;
      first2 = 0;
      first4 = 0;
      buzzer_set_period(0);
    }
    button3();
    break;
    
  case 4:
    if (first4 == 0){
      first4++;
      first1 = 0;
      first2 = 0;
      first3 = 0;
      buzzer_set_period(0);
    }
    button4();
    break;
    
  default:
    if (first == 0){
      first++;
      clearScreen(COLOR_GOLDENROD);
    }
    drawChar11x16(30,50,'R',COLOR_WHITE,COLOR_GOLDENROD);
    drawChar11x16(41,50,'e',COLOR_WHITE,COLOR_GOLDENROD);
    drawChar11x16(52,50,'a',COLOR_WHITE,COLOR_GOLDENROD);
    drawChar11x16(63,50,'d',COLOR_WHITE,COLOR_GOLDENROD);
    drawChar11x16(74,50,'y',COLOR_WHITE,COLOR_GOLDENROD);
    drawChar11x16(85,50,'!',COLOR_WHITE,COLOR_GOLDENROD);
    break;
  }
}

//Writes out 'Lavender Town' and plays the little tune associated with it.
void button1(){
  static int note = 1;
  switch(note++){
  case 1: buzzer_set_period(7664);
    drawChar11x16(20,20,'L',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(31,20,'a',COLOR_VIOLET,COLOR_BLACK);
    break;
  case 2: buzzer_set_period(5102);
    drawChar11x16(42,20,'v',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(53,20,'e',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(64,20,'n',COLOR_VIOLET,COLOR_BLACK);
    break;
  case 3: buzzer_set_period(4049);
    drawChar11x16(75,20,'d',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(86,20,'e',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(97,20,'r',COLOR_VIOLET,COLOR_BLACK);
    break;
  case 4: buzzer_set_period(5405);
    drawChar11x16(40,37,'T',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(51,37,'o',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(62,37,'w',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(73,37,'n',COLOR_VIOLET,COLOR_BLACK);
    note = 1;
    break;
  }
}

//Dimming lights. Does not use the screen
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

//Draws a diamond that appears to grow in size.
void button3(){
  static int x = 60;
  static int y =60;
  static int size = 5;
  fillRectangle(35,35,50,50,COLOR_WHITE);
  //Drawing a diamond
  for (int j =  size;j >= 0;j--){
    drawPixel(x-j,y-j+size, COLOR_NAVY);//bottom left
    drawPixel(x+j,y-j+size, COLOR_NAVY);//bottom right
    drawPixel(x-j+size,y-j, COLOR_NAVY);//top right
    drawPixel(x+j-size,y-j, COLOR_NAVY);//top left
  }
  if (size > 20){
    size = 5;
  }
  else{
    size++;
  }
}

//Draws a square that moves up-right then down-left in a diagonal line.
void button4(){
  static int movement = 0;
  static int x = 15;
  static int y = 120;
  static int size = 10;
  clearScreen(COLOR_WHITE);
  //drawing a square
  for(int j =size*2; j > 0; j--){
    drawPixel(x-j+size,y-size, COLOR_SEA_GREEN);//Top line
    drawPixel(x-j+size,y+size, COLOR_SEA_GREEN);//Bottom line
    drawPixel(x-size,y-j+size, COLOR_SEA_GREEN);//Left Line
    drawPixel(x+size,y-j+size, COLOR_SEA_GREEN);//Right Line
  }

  //move up-right until a certain point, then down left.
  switch(movement){
  case 0:
    x=x+2;
    y=y-2;
    if (x > 116){
      movement = 1;
    }
    break;
  case 1:
    x=x-2;
    y=y+2;
    if (x < 10){
      movement = 0;
    }
  }
}

  
