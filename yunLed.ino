/*
*     
  Modified by Moheeb Zara to include some serial stuff to run different effects based on skynet input



 * arduino serial-i2c-gateway, Copyright (C) 2011 michael vogt <michu@neophob.com>
 *  
 * This file is part of neorainbowduino.
 *
 * neorainbowduino is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * neorainbowduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Iwnc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 	
 */

#include <TimerOne.h>
#include "LPD6803.h"

#define PIXELS 49

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
int dataPin = 2;       // 'green' wire
int clockPin = 3;      // 'blue' wire
// Don't forget to connect 'blue' to ground and 'red' to +5V

byte kr=0;
byte krDirection=0;

//initialize strip with 20 leds
LPD6803 strip = LPD6803(PIXELS, dataPin, clockPin);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  randomSeed(analogRead(0));

  strip.setCPUmax(50);  // start with 50% CPU usage. up this if the strand flickers or is slow

  // Start up the LED counter
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}

 
// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b) {
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)r & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)g & 0x1F);
}


void knightRider(int ces) {
  for (byte i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }

  if (kr<PIXELS-1) {
    if(ces == 0){
    strip.setPixelColor(kr+1, Color(10, 0, 0));
    }else if(ces == 1){
      strip.setPixelColor(kr+1, Color(0, 10, 0));
    }else if(ces == 2){
      strip.setPixelColor(kr+1, Color(0, 0, 10));
    }
  }
  
  if(ces == 0){
    strip.setPixelColor(kr, Color(31, 0, 0));
    }else if(ces == 1){
     strip.setPixelColor(kr, Color(0, 31, 0));
    }else if(ces == 2){
      strip.setPixelColor(kr, Color(0, 0, 31));
    }
  if (kr>1) {
    
    if(ces == 0){
    strip.setPixelColor(kr-1, Color(10, 0, 0));
    }else if(ces == 1){
      strip.setPixelColor(kr-1, Color(0, 10, 0));
    }else if(ces == 2){
      strip.setPixelColor(kr-1, Color(0, 0, 10));
    }
  }
 
  //swap buffers asap, all 20 pixels
  strip.doSwapBuffersAsap(PIXELS);

  delay(30);

  if (krDirection==0) {
    kr++;
  } else {
    kr--;
  }
  
  if (kr>PIXELS-1) {
    krDirection = 1;
    kr = PIXELS;
  }
  
  if (kr==0) {
   krDirection = 0;
   kr = 0; 
  }
}

void rainbow(uint8_t wait) {
  int i, j;
   
  for (j=0; j < 96 * 3; j++) {     // 3 cycles of all 96 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 96));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  
  for (j=0; j < 96 * 5; j++) {     // 5 cycles of all 96 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 96 / strip.numPixels()) + j) % 96) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint16_t c, uint8_t wait) {
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 15 bit color value from R,G,B

//Input a value 0 to 127 to get a color value.
//The colours are a transition r - g -b - back to r
unsigned int Wheel(byte WheelPos)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r=31- WheelPos % 32;   //Red down
      g=WheelPos % 32;      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g=31- WheelPos % 32;  //green down
      b=WheelPos % 32;      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b=31- WheelPos % 32;  //blue down 
      r=WheelPos % 32;      //red up
      g=0;                  //green off
      break; 
  }
  return(Color(r,g,b));
}


int ind;
void loop() {
   while (Serial1.available()) {
   ind = Serial1.read();
   Serial.println(ind);
   
  }
  
  if(ind == 48){
    colorWipe(Color(63, 0, 0), 50);
  }else if(ind == 49){
    
     colorWipe(Color(0, 63, 0), 50);
    
  }else if(ind == 50){
     knightRider(2);
    
  }else if(ind == 51){
     knightRider(0);
    
  }

}

