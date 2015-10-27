#include "LPD8806.h"
#include <SPI.h>

const int dataPin = 11;   
const int clockPin = 13; 
const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
//const int numLEDs = 160;
const int numLEDs = 80;

// Set the first variable to the NUMBER of pixels. 32 = 32 pixels in a row
// The LED strips are 32 LEDs per meter but you can extend/cut the strip
//LPD8806 strip = LDPD8806(160)  // 5 meter strip
//LPD8806 strip = LPD8806(32, dataPin, clockPin);
LPD8806 strip = LPD8806(numLEDs, dataPin, clockPin);  // 3 meter strip

uint32_t Red, Green, Blue, Cyan, Yellow, Magenta, White, Black;

// segments - large star
//
//    L3 L4  
//  L2     L5
//  L1     L6
//    L8 L7

// for 5 meter strip - 160 LEDs
// large star:  8, 8, 14, 14, 8, 8, 21, 20
//            0-7, 8-15, 16-29, 30-43, 44-51, 52-59, 60-80, 81-100
// small star: 7, 6, 6, 6, 7, 6, 6, 6 
//       103-109, 110-115, 116-121, 122-127, 128-134, 135-140, 141-146, 147-152

// for 3 meter strip - 96 LEDs
// large star:  14, 6, 6, 14, 14, 6, 6, 14  
//            0-13, 14-19, 20-25, 26-39, 40-53, 54-59, 60-65, 66-79
// small star:  4, 5, 5, 4,  5, 4, 5, 5
//       59-62, 63-67, 68-72, 73-76,  77-81, 82-85, 86-90, 91-95

// large star - address of each segment, clockwise around the star
const int ls_1 = 0;
const int ls_2 = 14; 
const int ls_3 = 20; 
const int ls_4 = 26; 
const int ls_5 = 40; 
const int ls_6 = 54; 
const int ls_7 = 60; 
const int ls_8 = 66; 
const int ls_end = 80;  // last pixel in large star
// small star - clockwise
// const int ss_1 = 59; 
// const int ss_2 = 63; 
// const int ss_3 = 68; 
// const int ss_4 = 73; 
// const int ss_5 = 77; 
// const int ss_6 = 82; 
// const int ss_7 = 86;
// const int ss_8 = 91; 
// const int ss_end = 95;

void blink() {
// if the LED is off turn it on and vice-versa:
  if (ledState == LOW)
    ledState = HIGH;
  else
    ledState = LOW;
// set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
}

void setup() {
  Red = strip.Color(127,0,0);
  Green = strip.Color(0,127,0);
  Blue = strip.Color(0,0,127);
  Cyan = strip.Color(0,127,127);
  Yellow = strip.Color(127,127,0);
  Magenta = strip.Color(127,0,127);
  Black = strip.Color(0,0,0);
  White = strip.Color(127,127,127);
  pinMode(ledPin, OUTPUT);  // LED pin
  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();
}

void loop() {

  blink();
  
  
  chaseUpTheStar(Red,300);
  
  
  
// *****  RANDOM RED INNER, THEN TURN ON SLOWLY
//   randomSparkleUpSegment(Red,15,20,ss_1,ss_end); //color, density, delay, low point, high point
//   turnSegOn(Red,1000,ss_1,ss_end-ss_1); //color, delay, start, length
// *****  RANDOM GREEN OUTER, THEN TURN ON SLOWLY
  randomSparkleUpSegment(Green,15,20,ls_1,ls_end); //color, density, delay, low point, high point
  turnSegOn(Green,500,ls_1,ls_end-ls_1); //color, delay, start of segment, end of segment
// *****
  delay(1000);
//  turnOffAll;
  
// **** FILL UP RED  
  fillUpTheStar(Red,30); //color, delay
//   fillUpCenterStar(Red,30); //color, delay
// ***** FILL UP YELLOW
  fillUpTheStar(Yellow,30); //color, delay
//   fillUpCenterStar(Yellow,30); //color, delay
// *** FILL UP GREEN
  fillUpTheStar(Green,30); //color, delay
//   fillUpCenterStar(Green,30); //color, delay
// ***** FILL UP CYAN
  fillUpTheStar(Cyan,30); //color, delay
//   fillUpCenterStar(Cyan,30); //color, delay
// ***** FILL UP BLUE
  fillUpTheStar(Blue,30); //color, delay
//   fillUpCenterStar(Blue,30); //color, delay
// ***** FILL UP MAGENTA
  fillUpTheStar(Magenta,30); //color, delay
//   fillUpCenterStar(Magenta,30); //color, delay
// *** FILL UP WHITE
  fillUpTheStar(White,30); //color, delay
//   fillUpCenterStar(White,30); //color, delay 
  
// *** ALL RED, GREEN DITHER, FADE DOWN
  turnOnAll(Red,200); //color, delay - turn all pixels one color, slowly
  dither(Green, 15); // DITHER TO GREEN
  dither(Blue, 15);  // DITHER TO BLUE
  dither(Cyan, 15);  // DITHER TO CYAN
  dither(Yellow, 15);  // DITHER TO YELLOW
  dither(Magenta, 15);  // DITHER TO MAGENTA
  dither(White, 15);  // DITHER TO WHITE

// *** RED DITHER, FADE DOWN
  dither(Red, 20); //color, delay - random fills up the strip
//  fadeDown(127,0,0,30); //red, green, blue, delay - fade down all pixels one color

// *** FLASH RED, GREEN, RED, GREEN, etc,,,   
  turnOnAll(Red,400); //color, delay - turn all pixels one color 
  turnOnAll(Green,400); //color, delay - turn all pixels one color 
  turnOnAll(Red,400); //color, delay - turn all pixels one color 
  turnOnAll(Green,400); //color, delay - turn all pixels one color 
  turnOnAll(Red,400); //color, delay - turn all pixels one color 
  turnOnAll(Green,400); //color, delay - turn all pixels one color 
  turnOnAll(Red,400); //color, delay - turn all pixels one color 
  turnOnAll(Green,400); //color, delay - turn all pixels one color 
  turnOnAll(Red,400); //color, delay - turn all pixels one color 
  turnOnAll(Green,400); //color, delay - turn all pixels one color 
  turnOnAll(Red,400); //color, delay - turn all pixels one color 
  turnOnAll(Green,400); //color, delay - turn all pixels one color 

// *** CHASE TO BLACK (CODE SAYS WHITE??? )
  chaseBetweenUp(White,20,ls_1,ls_end); //color, delay, low, high - chase led between two locations progressing up the chain
//   chaseBetweenDown(White,20,ss_1,ss_end); //color, delay, low, high - chase led between two locations progressing down the chain
//  turnOffAll(); //turn all pixels off 

// *** FADE UP/DOWN RED, GREEN, BLUE, WHITE
  fadeUpAll(Red,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(Red,20); //red, green, blue, delay - fade down all pixels one color
  fadeUpAll(Green,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(Green,20); //red, green, blue, delay - fade down all pixels one color
  fadeUpAll(Blue,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(Blue,20); //red, green, blue, delay - fade down all pixels one color
  fadeUpAll(Cyan,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(Cyan,20); //red, green, blue, delay - fade down all pixels one color
  fadeUpAll(Yellow,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(Yellow,20); //red, green, blue, delay - fade down all pixels one color
  fadeUpAll(Magenta,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(Magenta,20); //red, green, blue, delay - fade down all pixels one color
  fadeUpAll(White,20); //red, green, blue, delay - fade up all pixels one color
  fadeDownAll(White,20); //red, green, blue, delay - fade down all pixels one color
//  turnOffAll();
  
// *** RANDOM SPARKLE RED, GREEN, RED/GREEN
//  randomSparkle(Red,80, 30); //color, density, delay - random sparkles in one color
//  randomSparkle(Green,80, 30); //color, density, delay - random sparkles in one color
//  twoColorSparkle(Red, Green, 30, 10); //color 1, color 2, density, delay - random sparkles in two colors
 
// *** RAINDBOW
  fadeUpAll(White,20);
  rainbow(20);
//  turnOffAll();
 
// *** RANDOM SPARKLE ALL COLORS
//  randomColorSparkle(10); //delay - random color sparkles

// *** ALL BLUE, CHASE BLACK, GREEN, RED, etc.
  turnOnAll(Blue,1000); //color, delay - turn all pixels one color 
  chaseBetweenUp(White,10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing up the chain
  chaseBetweenUp(Green,10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing up the chain
  chaseBetweenDown(Red,10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing down the chain
  chaseBetweenDown(Green,10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing down the chain
//  chaseToCenter(Red,25,1,0,lastLED); //color, number of leds in line, delay, low, high - chase lines to the center
//  chasePastCenter(Red,25,1,0,lastLED); //color, number of leds in line, delay, low, high - chase lines past the center
  chaseBetweenUp(strip.Color(50,50,127),10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing up the chain
  chaseBetweenUp(Red,10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing up the chain
  chaseBetweenUp(Green,10,0,ls_end); //color, delay, low, high - chase leds between two locations progressing up the chain
  chaseLineDown(Red,20,0,0,ls_end); //color, number of leds in line, delay, low, high - chase leds in a line progressing up the chain
  chaseLineUp(Green,20,0,0,ls_end); //color, delay, low, high - chase leds between two locations progressing up the chain

// *** RAINBOW CYCLE  
  fadeUpAll(White,20);
  rainbowCycle(20);  // make it go through the cycle fairly fast
//  turnOffAll();
  
// for 3 meter strip - 96 LEDs
// large star:  4, 5, 8, 7, 5, 5, 11, 12  
//            0-3, 4-8, 9-16, 17-23, 24-28, 29-33, 34-44, 45-56
// small star:  4, 5, 5, 4,  5, 4, 5, 5
//       59-62, 63-67, 68-72, 73-76,  77-81, 82-85, 86-90, 91-95

  // perimeter, clockwise from left point: 4, 5, 8, 7, 5, 5, 11, 12
  //     0-3, 4-8, 9-16, 17-23, 24-28, 29-33, 34-44, 45-56
  // 2 "in the gap"
  // center star:  37 LEDs starting at 59 to 95
  //       59-62, 63-67, 68-72, 73-76,  77-81, 82-85, 86-90, 91-95
  //red and green segments around perimeter, center blue
  
// *** SEGMENT BLINK  
  int i;
  for(i=1; i<=1; i++){
    turnSegOn(Blue,200, ls_1, ls_end-ls_1); // all on blue
    turnSegOn(Red,200, ls_8, ls_end-ls_8); // segment 8 red
    turnSegOn(Green,200, ls_1, ls_2-ls_1); // segment 1 green
    turnSegOn(Red,200, ls_2, ls_3-ls_2); // segment 2 red
    turnSegOn(Green,200, ls_3, ls_4-ls_3); // segment 3 green
    turnSegOn(Red,200, ls_4, ls_5-ls_4); // segment 4 red
    turnSegOn(Green,200, ls_5, ls_6-ls_5); // segment 5 green
    turnSegOn(Red,200, ls_6, ls_7-ls_6); // segment 6 red
    turnSegOn(Green,200, ls_7, ls_8-ls_7); // segment 7 green
    delay(1000);
    fadeDownAll(strip.Color(63,63,63),40); //red, green, blue, delay - fade down all pixels one color
    // now go the other direction
    turnSegOn(Blue,200, ls_1, ls_end-ls_1); // all on blue
    turnSegOn(Green,200, ls_7, ls_8-ls_7); // segment 7 green
    turnSegOn(Red,200, ls_6, ls_7-ls_6); // segment 6 red
    turnSegOn(Green,200, ls_5, ls_6-ls_5); // segment 5 green
    turnSegOn(Red,200, ls_4, ls_5-ls_4); // segment 4 red
    turnSegOn(Green,200, ls_3, ls_4-ls_3); // segment 3 green
    turnSegOn(Red,200, ls_2, ls_3-ls_2); // segment 2 red
    turnSegOn(Green,200, ls_1, ls_2-ls_1); // segment 1 green
    turnSegOn(Red,200, ls_8, ls_end-ls_8); // segment 8 red
    delay(1000);
    fadeDownAll(strip.Color(63,63,63),40); //red, green, blue, delay - fade down all pixels one color
  }

// *** ALL BLUE, DITHER RED, FADE DOWN
  fadeUpAll(White,200);  // FADEUP WHITE, SLOWLY
//  turnOnAll(Blue,200); 
  dither(Blue, 20); // DITHER TO BLUE
  dither(Green, 20); // DITHER TO GREEN
  dither(Red, 20); // DITHER TO RED
  fadeDownAll(Red,30); //red, green, blue, delay - fade down all pixels one color
// *** ALL RED, GREEN DITHER, FADE DOWN
  turnOnAll(Red,200); // all pixels red, slowly
  dither(Blue, 20);  // DITHER TO BLUE
  dither(Cyan, 20);  // DITHER TO CYAN
  dither(Yellow, 20);  // DITHER TO YELLOW
  dither(Magenta, 20);  // DITHER TO MAGENTA
  dither(White, 20);  // DITHER TO WHITE
  
// *** OUTER BLUE, INNER BLUE, THEN CHASE TO BLACK
//  turnSegOn(Blue,10,ss_1,ss_end-ss_1); //color, delay, start of segment, end of segment
  turnSegOn(Blue,10,ls_1,ls_end-ls_1); //color, delay, start of segment, end of segment
  chaseUpTheStar(Red,30); //color, delay
//   chaseUpCenterStar(Red,30); //color, delay
//  turnSegOn(Green,10,ls_1,ss_end-ls_1); // all segments to green
  chaseUpTheStar(Green,30); // chase up the star
//  turnOffAll();
 
 // *** FILL UP FROM BOTTOM OUTER RED, INNER GREEN, OUTER GREEN, INNER RED, OUTER WHITE, INNER WHITE
  fillUpTheStar(Red,30); //color, delay
//   fillUpCenterStar(Green, 30); //color, delay
  fillUpTheStar(Green,30); //color, delay
//   fillUpCenterStar(Red,30); //color, delay
  fillUpTheStar(White,30); //color, delay 
//   fillUpCenterStar(White,30); //color, delay
//  turnOffAll();

// *** DITHER TO CYAN, FADE
  dither(Cyan, 10); //color, delay - random fills up the strip
  fadeDownAll(Cyan,20); //red, green, blue, delay - fade down all pixels one color
//  turnOffAll();
  
// *** SCANNER RED (ugly)
//  scanner(127,0,0,0); //red, green, blue, delay
//  turnOffAll();

// *** WAVE RED, FADE, WAVE GREEN
  wave(Red,5,0,200); //color, cycles, delay, repetitions
  fadeDownAll(Red,20); //red, green, blue, delay - fade down all pixels one color
  wave(Green,5,0,200); //color, cycles, delay, repetitions
//  turnOffAll();
  

// *** RANDOM SPARKLE UP WHITE, FADE
//  randomSparkleUpStrip(White,15,10); //color, density, wait
//  turnOnAll(White,500);
//  fadeDownAll(127,127,127,20); //red, green, blue, delay - fade down all pixels one color
// *** RANDOM SPARKLE UP BLUE, FADE
//  randomSparkleUpStrip(strip.Color(20,20,127),15,10);
//  turnOnAll(strip.Color(20,20,127),500);
//  fadeDownAll(20,20,127,20); //red, green, blue, delay - fade down all pixels one color
// *** RANDOM SPARKLE UP MAGENTA, FADE
//  randomSparkleUpStrip(strip.Color(127,50,127),15,10);
//  turnOnAll(strip.Color(127,50,127),500);
//  fadeDownAll(127,50,127,20); //red, green, blue, delay - fade down all pixels one color
// *** RANDOM SPARKLE UP GREEN, FADE
//  randomSparkleUpStrip(strip.Color(20,127,39),15,10);
//  turnOnAll(strip.Color(20,127,39),500);
//  fadeDownAll(20,127,39,20); //red, green, blue, delay - fade down all pixels one color
// *** RANDOM SPARKLE UP BLUE, FADE
//  randomSparkleUpStrip(strip.Color(10,10,127),15,10);
//  turnOnAll(strip.Color(10,10,127),500);
//  fadeDownAll(10,10,127,20); //red, green, blue, delay - fade down all pixels one color

// *** ALL GREEN< CHASE TO BLACK
  turnOnAll(Green,400);
  chaseBetweenUp(Red,20,ls_1,ls_end); //color, delay, low, high - chase led between two locations progressing up the chain
//  chaseBetweenDown(Red,20,ss_end,ss_1); //color, delay, low, high - chase led between two locations progressing down the chain

// *** WAVES - GREEN, etc
  wave(Green,5,0,100); //color, cycles, delay, repetitions
  wave(strip.Color(20,127,0),10,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(40,127,0),15,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(80,127,0),20,0,50); //color, cycles, delay, repetitions
  wave(Yellow,25,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(127,80,0),35,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(127,40,0),45,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(127,20,0),55,0,50); //color, cycles, delay, repetitions
  wave(Red,65,0,100); //color, cycles, delay, repetitions
  wave(Red,65,0,50); //color, cycles, delay, repetitions
//  turnOffAll();
 
  wave(Green,60,0,100); //color, cycles, delay, repetitions
  wave(strip.Color(20,107,0),50,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(40,87,0),40,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(80,47,0),30,0,50); //color, cycles, delay, repetitions
  wave(strip.Color(107,27,0),20,0,100); //color, cycles, delay, repetitions
  wave(Red,5,0,200); //color, cycles, delay, repetitions
  
// for 3 meter strip - 96 LEDs
// large star:  4, 5, 8, 7, 5, 5, 11, 12  
//            0-3, 4-8, 9-16, 17-23, 24-28, 29-33, 34-44, 45-56
// small star:  4, 5, 5, 4,  5, 4, 5, 5
//       59-62, 63-67, 68-72, 73-76,  77-81, 82-85, 86-90, 91-95
  // 3 meter star = 96 LEDs
  // perimeter, clockwise from left point: 4, 5, 8, 7, 5, 5, 11, 12
  //       0-3, 4-8, 9-16, 17-23, 24-28, 29-33, 34-44, 45-56
  // 3 "in the gap"
  // center star:  37 LEDs starting at 59 to 95
  //       59-62, 63-67, 68-72, 73-76,  77-81, 82-85, 86-90, 91-95

// *** SIDES ROTATING AROUND STAR COUNTER CLOCKWISE - VERY BLINKY
//  int j;
//  for(j=1; j<=15; j++){ 
//    turnSegmentOn(Blue,0, 34, 56);//red 1 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,0, 86, 90); //blue 1 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,200, 59, 62); //blue 1 on - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 24, 33); //red 4 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 63, 72); //blue 4 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,0, 0, 8); //red 2 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,200, 82, 90); //blue 2 on - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 34, 56); //red 1 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 91, 95); // blue 1 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 59, 62); //blue 1 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,0, 9, 23); //red 3 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,200, 73, 81); //blue 3 on - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 0, 8); //red 2 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 82, 90); //blue 2 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,0, 24, 33); //red 4 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,200, 63, 72); //blue 4 on - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 9, 23); //red 3 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 73, 81); //blue 3 off - color, delay, start of segment, end of segment
//  }
  
// *** SIDES ROTATING AROUND STAR CLOCKWISE - VERY BLINKY
//  int k;
//  for(k=1; k<=15; k++){ 
//    turnSegmentOn(Red,0, 34, 56);//blue 1 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,0, 86, 90); //red 1 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,200, 59, 62); //red 1 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 24, 33); //blue 4 off - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 63, 72); //red 4 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,0, 0, 8); //blue 2 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,200, 82, 90); //red 2 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 34, 56); //blue 1 off - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 91, 95); // red 1 off - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 59, 62); //red 1 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,0, 9, 23); //blue 3 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,200, 73, 81); //red 3 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 0, 8); //blue 2 off - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 82, 90); //red 2 off - color, delay, start of segment, end of segment
//    turnSegmentOn(Red,0, 24, 33); //blue 4 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Blue,200, 63, 72); //red 4 on - color, delay, start of segment, end of segment
//    turnSegmentOn(Green,0, 9, 23); //blue 3 off - color, delay, start of segment, end of segment
//    turnSegmentOn(strip.Color(50,50,0),0, 73, 81); //red 3 off - color, delay, start of segment, end of segment
//  }

// *** FADE UP RED INNER, GREEN OUTER, FADE DOWN INNER, INNER
//   fadeUp(Red,200,ss_1,ss_end-ss_1); // inner star fade up red
  fadeUp(Green,200,ls_1,ls_end-ls_1); // outer star fade up green
//   fadeDown(Green,200,ss_1,ss_end-ss_1); // inner star fade down green
  fadeDown(Red,200,ls_1,ls_end-ls_1); // outer star fade down red

// *** FADE UP GREEN INNER, RED OUTER, FADE DOWN INNER, OUTER
//   fadeUp(Green,200,ss_1,ss_end-ss_1);
  fadeUp(Red,200,ls_1,ls_end-ls_1); 
//   fadeDown(Green,200,ss_1,ss_end-ss_1); 
  fadeDown(Red,200,ls_1,ls_end-ls_1); 
  
// *** FADE UP BLUE INNER, GREEN OUTER, FADE DOWN INNER, OUTER
//   fadeUp(Blue,200,ss_1,ss_end-ss_1); 
  fadeUp(Green,200,ls_1,ls_end-ls_1); 
//   fadeDown(Blue,200,ss_1,ss_end-ss_1); 
  fadeDown(Green,200,ls_1,ls_end-ls_1); 
  
// *** FADE UP GREEN INNER, BLUE OUTER, FADE DOWN INNER, OUTER
//   fadeUp(Green,200,ss_1,ss_end-ss_1); 
  fadeUp(Blue,200,ls_1,ls_end-ls_1); 
//   fadeDown(Green,200,ss_1,ss_end-ss_1); 
  fadeDown(Blue,200,ls_1,ls_end-ls_1); 

// *** FADE UP WHITE INNER, BLUE OUTER, FADE DOWN INNER, OUTER
//   fadeUp(White,200,ss_1,ss_end-ss_1); 
  fadeUp(strip.Color(20,20,127),200,ls_1,ls_end-ls_1); 
//   fadeDown(White,200,ss_1,ss_end-ss_1); //
  fadeDown(strip.Color(20,20,127),200,ls_1,ls_end-ls_1); 

// *** CHASE CLOCKWISE ALL COLORS 6 LED SEGMENTS  
  chaseMultipleLinesLToH(6,20,ls_1,ls_end); //

}

// An "ordered dither" fills_ every pixel in a sequence that looks
// sparkly and almost random, but actually follows a specific order.
void dither(uint32_t c, uint8_t wait) {
  // Determine highest bit needed to represent pixel index
  int hiBit = 0;
  int n = strip.numPixels() - 1;
  for(int bit=1; bit < 0x8000; bit <<= 1) {
    if(n & bit) hiBit = bit;
  }
  int bit, reverse;
  for(int i=0; i<(hiBit << 1); i++) {
    // Reverse the bits in i to create ordered dither:
    reverse = 0;
    for(bit=1; bit <= hiBit; bit <<= 1) {
      reverse <<= 1;
      if(i & bit) reverse |= 1;
    }
    strip.setPixelColor(reverse, c);
    strip.show();
    delay(wait);
  }
  delay(250); // Hold image for 1/4 sec
}

// "Larson scanner" = Cylon/KITT bouncing light effect
void scanner(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  int i, j, pos, dir;
  pos = 0;
  dir = 1;
  for(i=0; i<((strip.numPixels()-1) * 8); i++) {
    // Draw 5 pixels centered on pos. setPixelColor() will clip
    // any pixels off the ends of the strip, no worries there.
    // we'll make the colors dimmer at the edges for a nice pulse
    // look
    strip.setPixelColor(pos - 2, strip.Color(r/4, g/4, b/4));
    strip.setPixelColor(pos - 1, strip.Color(r/2, g/2, b/2));
    strip.setPixelColor(pos, strip.Color(r, g, b));
    strip.setPixelColor(pos + 1, strip.Color(r/2, g/2, b/2));
    strip.setPixelColor(pos + 2, strip.Color(r/4, g/4, b/4));

    strip.show();
    delay(wait);
    // If we wanted to be sneaky we could erase just the tail end
    // pixel, but it's much easier just to erase the whole thing
    // and draw a new one next time.
    for(j=-2; j<= 2; j++)
        strip.setPixelColor(pos+j, Black);
    // Bounce off ends of strip
    pos += dir;
    if(pos < 0) {
      pos = 1;
      dir = -dir;
    } else if(pos >= strip.numPixels()) {
      pos = strip.numPixels() - 2;
      dir = -dir;
    }
  }
}

// Sine wave effect
#define PI 3.14159265
void wave(uint32_t c, int cycles, uint8_t wait, int repetitions) {
  blink();
  float y;
  byte r, g, b, r2, g2, b2;
  // Need to decompose color into its r, g, b elements
  g = (c >> 16) & 0x7f;
  r = (c >> 8) & 0x7f;
  b = c & 0x7f;
  for(int x=0; x<repetitions; x++) {
    for(int i=0; i<strip.numPixels(); i++) {
      y = sin(PI * (float)cycles * (float)(x + i) / (float)strip.numPixels());
        y = 1.0 - y; // Translate Y to 0.0 (top) to 1.0 (center)
        r2 = (byte)((float)r * y);
        g2 = (byte)((float)g * y);
        b2 = (byte)((float)b * y);
      
      strip.setPixelColor(i, r2, g2, b2);
    }
    strip.show();
    delay(wait);
  }
}

void chaseUpTheStar(uint32_t c, uint8_t wait) {
blink();
int i,j;
strip.setPixelColor(44, c);
delay(wait);
strip.setPixelColor(40, Black);
for (i = 1; i <= 12; i++) {
strip.setPixelColor(40+i, c);
strip.setPixelColor(40-i, c);
strip.show(); // write all the pixels out
delay(wait);
strip.setPixelColor(40+i, Black);
strip.setPixelColor(40-i, Black);
strip.show(); // write all the pixels out
}
for (j=0; j<=16; j++) {
strip.setPixelColor(j, c);
strip.setPixelColor(33-j, c);
strip.show(); // write all the pixels out
delay(wait);
strip.setPixelColor(j, Black);
strip.setPixelColor(33-j, Black);
strip.show(); // write all the pixels out
}
}


// void chaseUpCenterStar(uint32_t c, uint8_t wait) {
//   blink();
//   int i,j;
//   for (i = 1; i <= 5; i++) {
//     strip.setPixelColor(90+i, c);
//     strip.setPixelColor(91-i, c);
//     strip.show();   // write all the pixels out
//     delay(wait);
//     strip.setPixelColor(90+i, Black);
//     strip.setPixelColor(91-i, Black);
//     strip.show();   // write all the pixels out
//   }
//   for (j=0; j<=15; j++) {
//     strip.setPixelColor(59+j, c);
//     strip.setPixelColor(85-j, c);
//     strip.show();   // write all the pixels out
//     delay(wait);
//     strip.setPixelColor(59+j, Black);
//     strip.setPixelColor(85-j, Black);
//     strip.show();   // write all the pixels out
//   }  
// }

void fillUpTheStar(uint32_t c, uint8_t wait) {
  blink();
  int i,j;
  strip.setPixelColor(79, c);
  delay(wait);
  for (i = 1; i <= 0; i++) {
    strip.setPixelColor(79+i, c);
    strip.setPixelColor(79-i, c);
    strip.show();   // write all the pixels out
    delay(wait);
  }
  for (j=0; j<=39; j++) {
    strip.setPixelColor(j, c);
    strip.setPixelColor(79-j, c);
    strip.show();   // write all the pixels out
    delay(wait);
  }  
}

// void fillUpCenterStar(uint32_t c, uint8_t wait) {
//   blink();
//   int i,j;
//   for (i = 1; i <= 5; i++) {
//     strip.setPixelColor(90+i, c);
//     strip.setPixelColor(91-i, c);
//     strip.show();   // write all the pixels out
//     delay(wait);
//   }
//   for (j=0; j<=15; j++) {
//     strip.setPixelColor(59+j, c);
//     strip.setPixelColor(85-j, c);
//     strip.show();   // write all the pixels out
//     delay(wait);
//   }  
// }

void chaseBetweenUp(uint32_t c, uint8_t wait, uint8_t point1, uint8_t point2) {
  blink();
  int i;
  for (i = point1; i <= point2; i++) {
    strip.setPixelColor(i, c);
    strip.show();   // write all the pixels out
    delay(wait);
    strip.setPixelColor(i, Black);
    strip.show();   // write all the pixels out
    }  
}

void chaseBetweenDown(uint32_t c, uint8_t wait, uint8_t point1, uint8_t point2) {
  blink();
  int i;
  for (i = point2; i >= point1; i--) {
    strip.setPixelColor(i, c);
    strip.show();   // write all the pixels out
    delay(wait);
    strip.setPixelColor(i, Black);
    strip.show();   // write all the pixels out
  }  
}

void chaseLineUp(uint32_t c, uint8_t lineNumber, uint8_t wait, uint8_t point1, uint8_t point2) {
  blink();
  int i, j;
  for(i = point1; i < point2+lineNumber; i++) {
    for(j = 0; j < lineNumber; j++) {
      strip.setPixelColor(i-j, c);
      }
  strip.show();   // write all the pixels out
  delay(wait);
  turnOffAll();
  }  
}

void chaseLineDown(uint32_t c, uint8_t lineNumber, uint8_t wait, uint8_t point1, uint8_t point2) {
  blink();
  int i, j;
  for(i = point2; i > point1; i--) {
    for(j = 0; j<lineNumber; j++){
      strip.setPixelColor(i+j, c);
    }
  strip.show();   // write all the pixels out
  delay(wait);
  turnOffAll();
  }  
}

// void chaseToCenter(uint32_t c, uint8_t lineNumber, uint8_t wait, uint8_t pointL, uint8_t pointH) {
//   blink();
//   int i, j, k;
//   i = pointL;
//   k = pointH;
//   while(i < k && k > i) {
//            for(j = 0; j < lineNumber; j++) {
//              strip.setPixelColor(i-j, c);
//              strip.setPixelColor(k+j, c);
//            }
//   strip.show();   // write all the pixels out
//   delay(wait);
//   i++;
//   k--;
//   turnOffAll();
//   }
// }

// void chasePastCenter(uint32_t c, uint8_t lineNumber, uint8_t wait, uint8_t pointL, uint8_t pointH) {
//   blink();
//   int i, j, k;
//   i = pointL;
//   k = pointH;
//   while(i < pointH && k > pointL) {
//            for(j = 0; j < lineNumber; j++) {
//              strip.setPixelColor(i-j, c);
//              strip.setPixelColor(k+j, c);
//            }
//   strip.show();   // write all the pixels out
//   delay(wait);
//   i++;
//   k--;
//   turnOffAll();
//   }
// }

void turnOnAll(uint32_t c, uint32_t wait) {
  blink();
  int i;  
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);  // turn all pixels on
  }
  strip.show();   // write all the pixels out
  delay(wait); 
}

void turnSegOn(uint32_t c, uint32_t wait, uint8_t seg_start, uint8_t seg_length) {
  blink();
  int i;  
  for (i=seg_start; i < seg_start+seg_length; i++) {
    strip.setPixelColor(i, c);  // turn all pixels on
  }
  strip.show();   // write all the pixels out
  delay(wait); 
}

void fadeUp(uint32_t c, uint32_t wait, uint8_t seg_start, uint8_t seg_length) {
  blink();
  int i, j;
  uint8_t r, g, b;
  r = (c >> 16) & 0x7F;
  g = (c >>  8) & 0x7F;
  b =  c        & 0x7F;
  for (j=0; j <= 100; j++) {
    for (i=seg_start; i<seg_start+seg_length; i++) {
      strip.setPixelColor(i, strip.Color((r*j)/100,(g*j)/100,(b*j)/100));
    }
    strip.show();
    delay(wait);
  }
}

void fadeDown(uint32_t c, uint32_t wait, uint8_t seg_start, uint8_t seg_length) {
  blink();
  int i, j;
  uint8_t r, g, b;
  r = (c >> 16) & 0x7F;
  g = (c >>  8) & 0x7F;
  b =  c        & 0x7F;
  for (j=100; j >= 0; j--) {
    for (i=seg_start; i<seg_start+seg_length; i++) {
      strip.setPixelColor(i, strip.Color((r*j)/100,(g*j)/100,(b*j)/100));  // turn all pixels on
    }
    strip.show();
    delay(wait);
  }
}

void fadeUpAll(uint32_t c, uint32_t wait) {
  fadeUp(c, wait, 0, strip.numPixels());
}

void fadeDownAll(uint32_t c, uint32_t wait) {
  fadeDown(c, wait, 0, strip.numPixels());
}

void chaseMultipleLinesLToH(uint8_t lineNumber, uint8_t wait, uint8_t point1, uint8_t point2) {
  blink();
  int i, j;
  for(i = point1; i <= point2; i++) {
    for(j = 0; j < lineNumber; j++) {
      strip.setPixelColor(i, Blue);
      strip.setPixelColor(i+j+(2*lineNumber), Red);
      strip.setPixelColor(i+j+(3*lineNumber), Green);
      strip.setPixelColor(i+j+(4*lineNumber), Yellow);
      strip.setPixelColor(i+j+(5*lineNumber), Cyan);
      strip.setPixelColor(i+j+(6*lineNumber), Magenta);
      strip.setPixelColor(i+j+(7*lineNumber), Blue);
      strip.setPixelColor(i+j+(8*lineNumber), Red);
      strip.setPixelColor(i+j+(9*lineNumber), Black);
    }
  strip.show();   // write all the pixels out
  delay(wait);
  }  
}

void turnOffAll() {
  blink();
  int i;  
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);  // turn all pixels off
  }
  strip.show();   // write all the pixels out 
}

void randomSparkleUpSegment(uint32_t c, uint32_t density, uint8_t wait, uint8_t pointL, uint8_t pointH) {
  blink();
  int i,j,location;
    for (j=pointL; j<=pointH; j++) {
      for (i=0; i <= density; i++) {
      location = random(pointL,j);
      strip.setPixelColor(location, c);
      }
    strip.show();   // write all the pixels out
    delay(wait);
    turnOffAll();
    strip.show();   // write all the pixels out
    }  
}

void randomSparkleUpStrip(uint32_t c, uint32_t density, uint8_t wait) {
  blink();
  int i,j,location;
    for (j=density; j<strip.numPixels(); j++) {
      for (i=0; i <= density; i++) {
      location = random(0,j);
      strip.setPixelColor(location, c);
      }
    strip.show();   // write all the pixels out
    delay(wait);
    turnOffAll();
    strip.show();   // write all the pixels out
    }  
}

void randomSparkle(uint32_t c, uint32_t density, uint8_t wait) {
  blink();
  int i,j,location;
  for (j=0; j < 200; j++) {
      for (i=0; i <= density; i++) {
         location = random(0,strip.numPixels()); //random location in first 5th of strip
         strip.setPixelColor(location, c);
      }
    strip.show();   // write all the pixels out
    delay(wait);
    turnOffAll();
    strip.show();   // write all the pixels out
         }
}

void randomColorSparkle(uint8_t wait) {
  blink();
  int i;
  int location1, location2, location3, location4, location5;
  int color1, color2, color3;
  for (i=0; i < 200; i++) {
    location1 = random(0,15); //random location in first 5th of strip
    location2 = random(16,31); //random location in 2nd 5th of strip
    location3 = random(32,47); //random location in 3rd 5th of strip
    location4 = random(48,63); //random location in 4th 5th of strip
    location5 = random(64,79); //randon location in last 5th of strip
    
    color1 = random(127);
    color2 = random(127);
    color3 = random(127);
    
    strip.setPixelColor(location1, strip.Color(color1,color2,0));
    strip.setPixelColor(location2, strip.Color(color3,0,color1));
    strip.setPixelColor(location3, strip.Color(0,color2,color3));
    strip.setPixelColor(location4, strip.Color(color1,color2,0));
    strip.setPixelColor(location5, strip.Color(color3,0,color1));
    strip.show();   // write all the pixels out
    delay(wait);
    strip.setPixelColor(location1, Black);
    strip.setPixelColor(location2, Black);
    strip.setPixelColor(location3, Black);
    strip.setPixelColor(location4, Black);
    strip.setPixelColor(location5, Black);
    strip.show();   // write all the pixels out
  }
}

void twoColorSparkle(uint32_t c1, uint32_t c2, uint32_t density, uint8_t wait) {
  blink();
  int i,j,location1,location2;
  for (j=0; j < 200; j++) {
    for (i=0; i <= density; i++) {
      location1 = random(0,strip.numPixels()); //random location number 1
      location2 = random(0,strip.numPixels()); //random location number 2
      strip.setPixelColor(location1, c1);
      strip.setPixelColor(location2, c2);
    }
    strip.show();   // write all the pixels out
    delay(wait);
    turnOffAll();
    strip.show();   // write all the pixels out
  }
}

void rainbow(uint8_t wait) {
  blink();
  int i, j;
  for (j=0; j < 384 * 3; j++) {     // 3 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  blink();
  uint16_t i, j;
  for (j=0; j < 384 * 5; j++) {     // 5 cycles of all 384 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 384-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 384 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 384 / strip.numPixels()) + j) % 384) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(uint32_t c, uint8_t wait) {
  blink();
  int i;
  
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

// Chase a dot down the strip
// good for testing purposes
void colorChase(uint32_t c, uint8_t wait) {
  blink();
  int i;
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);  // turn all pixels off
  } 
  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    if (i == 0) { 
      strip.setPixelColor(strip.numPixels()-1, 0);
    } else {
      strip.setPixelColor(i-1, 0);
    }
    strip.show();
    delay(wait);
  }
}

/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g - b - back to r
uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch(WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break; 
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break; 
    case 2:
      b = 127 - WheelPos % 128;  //blue down 
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break; 
  }
  return(strip.Color(r,g,b));
}
