// ===================================================================================
// Title:    3D 8x8x8 RGB LED CUBE by STEVE MANLEY
// Function: Burn-in Test for 8x8 Panels
// Board:    Arduino Uno R3
// Version:  1.0
// Author:   Steve Manley
// Date:     5th September 2014
// License:  The MIT License (See full license at the bottom of this file)
// Notes:    First experiments with dividing 8x8 RGB LED Panels using multiplexing
//           and interrupt timers. Starts of scrolling a message, then repeats a 
//           sequence of different routines for displaying patterns and fills.
// ===================================================================================

#include "SPI.h"

#define SPI_SCK         13                 // SPI clock    - must be pin 13
#define SPI_MOSI        11                 // SPI data out - must be pin 11
#define SR_LATCH         3                 // shift register latch         - any non SPI pin
#define SR_BLANK         2                 // shift register output enable - any non SPI pin
#define TD1            100                 // time delay 1 - 100ms
#define TD2           3000                 // time delay 2 -   3 seconds
#define TD3           1000                 // time delay 3 -   1 second
#define TD4             20                 // time delay 4 -  20ms
#define TD5            400                 // time delay 5 - 400ms



// =====================================================================================================
// variables used by Inturrupt Service Routine (ISR), must be volatile
// =====================================================================================================
volatile byte shiftRegisterRed[8];         // red   shift register data, 8 bytes, 1 byte per common anode
volatile byte shiftRegisterGrn[8];         // green shift register data, 8 bytes, 1 byte per common anode
volatile byte shiftRegisterBlu[8];         // blue  shift register data, 8 bytes, 1 byte per common anode
volatile byte anodeIndex   = 0;            // keeps track of which common anode is active
volatile byte anodeLevel[] = {             // used by 74HC595N shift register to control the anode multiplexing
              B11111110,                   // This is not an efficient use of variable memory, but what the heck!
              B11111101,                   // at least it shows how the anode multiplexing is done.
              B11111011, 
              B11110111, 
              B11101111, 
              B11011111, 
              B10111111,
              B01111111}; 



// =====================================================================================================
// font definition
// =====================================================================================================
char font8x8_basic[95][8] = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   // Ascii ( )
  {0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00},   // Ascii (!)
  {0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00},   // Ascii (")
  {0x14, 0x14, 0x3E, 0x14, 0x3E, 0x14, 0x14, 0x00},   // Ascii (#)
  {0x08, 0x3C, 0x0A, 0x1C, 0x28, 0x1E, 0x08, 0x00},   // Ascii ($)
  {0x06, 0x26, 0x10, 0x08, 0x04, 0x32, 0x30, 0x00},   // Ascii (%)
  {0x0C, 0x12, 0x0A, 0x04, 0x2A, 0x12, 0x2C, 0x00},   // Ascii (&)
  {0x0C, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00},   // Ascii (')
  {0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00},   // Ascii (()
  {0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02, 0x00},   // Ascii ())
  {0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, 0x00, 0x00},   // Ascii (*)
  {0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00},   // Ascii (+)
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0x02},   // Ascii (,)
  {0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00},   // Ascii (-)
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00},   // Ascii (.)
  {0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00},   // Ascii (/)
  {0x1C, 0x22, 0x32, 0x2A, 0x26, 0x22, 0x1C, 0x00},   // Ascii (0)
  {0x08, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00},   // Ascii (1)
  {0x1C, 0x22, 0x20, 0x18, 0x04, 0x02, 0x3E, 0x00},   // Ascii (2)
  {0x1C, 0x22, 0x20, 0x18, 0x20, 0x22, 0x1C, 0x00},   // Ascii (3)
  {0x10, 0x18, 0x14, 0x12, 0x3E, 0x10, 0x10, 0x00},   // Ascii (4)
  {0x3E, 0x02, 0x1E, 0x20, 0x20, 0x22, 0x1C, 0x00},   // Ascii (5)
  {0x18, 0x04, 0x02, 0x1E, 0x22, 0x22, 0x1C, 0x00},   // Ascii (6)
  {0x3E, 0x20, 0x10, 0x08, 0x04, 0x04, 0x04, 0x00},   // Ascii (7)
  {0x1C, 0x22, 0x22, 0x1C, 0x22, 0x22, 0x1C, 0x00},   // Ascii (8)
  {0x1C, 0x22, 0x22, 0x3C, 0x20, 0x10, 0x0C, 0x00},   // Ascii (9)
  {0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x00, 0x00},   // Ascii (:)
  {0x00, 0x00, 0x0C, 0x0C, 0x00, 0x0C, 0x08, 0x04},   // Ascii (;)
  {0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00},   // Ascii (<)
  {0x00, 0x00, 0x3E, 0x00, 0x3E, 0x00, 0x00, 0x00},   // Ascii (=)
  {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00},   // Ascii (>)
  {0x1C, 0x22, 0x20, 0x10, 0x08, 0x00, 0x08, 0x00},   // Ascii (?)
  {0x1C, 0x22, 0x20, 0x2C, 0x2A, 0x2A, 0x1C, 0x00},   // Ascii (@)
  {0x1C, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22, 0x00},   // Ascii (A)
  {0x1E, 0x22, 0x22, 0x1E, 0x22, 0x22, 0x1E, 0x00},   // Ascii (B)
  {0x1C, 0x22, 0x02, 0x02, 0x02, 0x22, 0x1C, 0x00},   // Ascii (C)
  {0x0E, 0x12, 0x22, 0x22, 0x22, 0x12, 0x0E, 0x00},   // Ascii (D)
  {0x3E, 0x02, 0x02, 0x1E, 0x02, 0x02, 0x3E, 0x00},   // Ascii (E)
  {0x3E, 0x02, 0x02, 0x1E, 0x02, 0x02, 0x02, 0x00},   // Ascii (F)
  {0x1C, 0x22, 0x02, 0x02, 0x32, 0x22, 0x3C, 0x00},   // Ascii (G)
  {0x22, 0x22, 0x22, 0x3E, 0x22, 0x22, 0x22, 0x00},   // Ascii (H)
  {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00},   // Ascii (I)
  {0x38, 0x10, 0x10, 0x10, 0x10, 0x12, 0x0C, 0x00},   // Ascii (J)
  {0x22, 0x12, 0x0A, 0x06, 0x0A, 0x12, 0x22, 0x00},   // Ascii (K)
  {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x3E, 0x00},   // Ascii (L)
  {0x22, 0x36, 0x2A, 0x2A, 0x22, 0x22, 0x22, 0x00},   // Ascii (M)
  {0x22, 0x22, 0x26, 0x2A, 0x32, 0x22, 0x22, 0x00},   // Ascii (N)
  {0x1C, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x00},   // Ascii (O)
  {0x1E, 0x22, 0x22, 0x1E, 0x02, 0x02, 0x02, 0x00},   // Ascii (P)
  {0x1C, 0x22, 0x22, 0x22, 0x2A, 0x12, 0x2C, 0x00},   // Ascii (Q)
  {0x1E, 0x22, 0x22, 0x1E, 0x0A, 0x12, 0x22, 0x00},   // Ascii (R)
  {0x1C, 0x22, 0x02, 0x1C, 0x20, 0x22, 0x1C, 0x00},   // Ascii (S)
  {0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00},   // Ascii (T)
  {0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1C, 0x00},   // Ascii (U)
  {0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x08, 0x00},   // Ascii (V)
  {0x22, 0x22, 0x22, 0x2A, 0x2A, 0x2A, 0x14, 0x00},   // Ascii (W)
  {0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22, 0x00},   // Ascii (X)
  {0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x00},   // Ascii (Y)
  {0x3E, 0x20, 0x10, 0x08, 0x04, 0x02, 0x3E, 0x00},   // Ascii (Z)
  {0x0E, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0E, 0x00},   // Ascii ([)
  {0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x00, 0x00},   // Ascii (\)
  {0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0E, 0x00},   // Ascii (])
  {0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00},   // Ascii (^)
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E},   // Ascii (_)
  {0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00},   // Ascii (`)
  {0x00, 0x00, 0x1C, 0x20, 0x3C, 0x22, 0x3C, 0x00},   // Ascii (a)
  {0x02, 0x02, 0x1A, 0x26, 0x22, 0x22, 0x1E, 0x00},   // Ascii (b)
  {0x00, 0x00, 0x0C, 0x12, 0x02, 0x12, 0x0C, 0x00},   // Ascii (c)
  {0x20, 0x20, 0x2C, 0x32, 0x22, 0x22, 0x3C, 0x00},   // Ascii (d)
  {0x00, 0x00, 0x1C, 0x22, 0x3E, 0x02, 0x1C, 0x00},   // Ascii (e)
  {0x08, 0x14, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x00},   // Ascii (f)
  {0x00, 0x00, 0x3C, 0x22, 0x22, 0x3C, 0x20, 0x1C},   // Ascii (g)
  {0x02, 0x02, 0x1A, 0x26, 0x22, 0x22, 0x22, 0x00},   // Ascii (h)
  {0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00},   // Ascii (i)
  {0x08, 0x00, 0x0C, 0x08, 0x08, 0x08, 0x08, 0x06},   // Ascii (j)
  {0x02, 0x02, 0x12, 0x0A, 0x06, 0x0A, 0x12, 0x00},   // Ascii (k)
  {0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E, 0x00},   // Ascii (l)
  {0x00, 0x00, 0x16, 0x2A, 0x2A, 0x22, 0x22, 0x00},   // Ascii (m)
  {0x00, 0x00, 0x1A, 0x16, 0x12, 0x12, 0x12, 0x00},   // Ascii (n)
  {0x00, 0x00, 0x0C, 0x12, 0x12, 0x12, 0x0C, 0x00},   // Ascii (o)
  {0x00, 0x00, 0x0E, 0x12, 0x12, 0x0E, 0x02, 0x02},   // Ascii (p)
  {0x00, 0x00, 0x1C, 0x12, 0x12, 0x1C, 0x10, 0x10},   // Ascii (q)
  {0x00, 0x00, 0x14, 0x0C, 0x04, 0x04, 0x04, 0x00},   // Ascii (r)
  {0x00, 0x00, 0x1C, 0x02, 0x0C, 0x10, 0x0E, 0x00},   // Ascii (s)
  {0x04, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x0C, 0x00},   // Ascii (t)
  {0x00, 0x00, 0x12, 0x12, 0x12, 0x12, 0x1C, 0x00},   // Ascii (u)
  {0x00, 0x00, 0x22, 0x22, 0x22, 0x14, 0x08, 0x00},   // Ascii (v)
  {0x00, 0x00, 0x22, 0x22, 0x2A, 0x2A, 0x14, 0x00},   // Ascii (w)
  {0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00},   // Ascii (x)
  {0x00, 0x00, 0x12, 0x12, 0x12, 0x1C, 0x10, 0x0C},   // Ascii (y)
  {0x00, 0x00, 0x3E, 0x10, 0x08, 0x04, 0x3E, 0x00},   // Ascii (z)
  {0x08, 0x04, 0x04, 0x02, 0x04, 0x04, 0x08, 0x00},   // Ascii ({)
  {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00},   // Ascii (|)
  {0x02, 0x04, 0x04, 0x08, 0x04, 0x04, 0x02, 0x00},   // Ascii (})
  {0x2C, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};  // Ascii (~)



// =====================================================================================================
// ~~~ START of SETUP ~~~
// =====================================================================================================
void setup() {

  // set up IO pins as outputs
  // -------------------------------------------------------------
  pinMode(SPI_SCK,  OUTPUT);
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(SR_LATCH, OUTPUT);
  pinMode(SR_BLANK, OUTPUT);

  digitalWrite(SR_BLANK, HIGH);              // temporarily disable all shift register outputs
  digitalWrite(SR_LATCH,  LOW);              // set shift register latch to initial state

  // set up Timer 2 for 8KHz (125uS) interrupt 
  // code example from Amanda Ghassaei 
  // http://www.instructables.com/id/Arduino-Timer-Interrupts/?ALLSTEPS
  // ------------------------------------------------------------------
    cli();                                   // stop interrupts
    TCCR2A  =   0;                           // set entire TCCR2A register to 0
    TCCR2B  =   0;                           // same for TCCR2B
    TCNT2   =   0;                           // initialize counter value to 0
    OCR2A   = 249;                           // Set compare match register for 16KHz. Increments calculated as follows:
                                             // Arduino clk frequency 16MHz / (required frequency * Prescaler of 8) - 1, Result must be < 256.
                                             // So for this instance we calculate 16,000,000 / (8,000 * 8) - 1 = 249
    TCCR2A |= (1 << WGM21);                  // turn on CTC mode
    TCCR2B |= (1 << CS21);                   // Set CS21 bit for 8 pre-scalar
    TIMSK2 |= (1 << OCIE2A);                 // enable timer compare interrupt
    sei();                                   // allow interrupts
  // end code example from Amanda Ghassaei
  // -------------------------------------------------------------
  
  // initialise SPI
  // -------------------------------------------------------------
  SPI.setDataMode    (SPI_MODE0     );       // mode 0 rising edge of data, keep clock low
  SPI.setBitOrder    (MSBFIRST      );       // most significant bit first
  SPI.setClockDivider(SPI_CLOCK_DIV2);       // run the data in at 16MHz/2 - 8MHz (max speed)
  SPI.begin();                               // start up SPI

  // initialise Serial Port for de-bugging
  // -------------------------------------------------------------
  Serial.begin  (115200 );                   // set up serial port for 115200 baud rate
  Serial.println("Start");                   // display Start in Terminal Window

  randomSeed(analogRead(0));                 // set random seed

  // display some text, only runs once
  // -------------------------------------------------------------
  displaySomeText("WELCOME TO THE 8x8 RGB LED PANEL TESTING... ", TD5);
}
// ====================
// ~~~ END of SETUP ~~~
// ====================




// =====================================================================================================
// ~~~ START of LOOP ~~~
// =====================================================================================================
void loop() {
  
  // zig zag fills from bottom to top
  // -------------------------------------------------------------
  zigZagFill(1, 0, 0, TD4);         // red
  zigZagFill(0, 1, 0, TD4);         // green
  zigZagFill(0, 0, 1, TD4);         // blue
  zigZagFill(1, 1, 1, TD4);         // white
  zigZagFill(1, 0, 1, TD4);         // magenta
  zigZagFill(1, 1, 0, TD4);         // yellow
  zigZagFill(0, 1, 1, TD4);         // turquoise


  // flood panel with single colour
  // -------------------------------------------------------------
  floodFill(1, 0, 0); delay(TD2);   // red
  floodFill(0, 1, 0); delay(TD2);   // green
  floodFill(0, 0, 1); delay(TD2);   // blue
  floodFill(1, 1, 1); delay(TD2);   // white
  floodFill(1, 0, 1); delay(TD2);   // magenta
  floodFill(1, 1, 0); delay(TD2);   // yellow
  floodFill(0, 1, 1); delay(TD2);   //turquoise
  

  // clear the panel
  // -------------------------------------------------------------
  floodFill(0, 0, 0); delay(TD3);   // clear display


  // move single columns left to right for each colour
  // -------------------------------------------------------------
  for(int i = 0; i < 8; i++){fillCol(i, 1, 0, 0); delay(TD1); fillCol(i, 0, 0, 0);}  // red
  for(int i = 0; i < 8; i++){fillCol(i, 0, 1, 0); delay(TD1); fillCol(i, 0, 0, 0);}  // green
  for(int i = 0; i < 8; i++){fillCol(i, 0, 0, 1); delay(TD1); fillCol(i, 0, 0, 0);}  //blue
  for(int i = 0; i < 8; i++){fillCol(i, 1, 1, 1); delay(TD1); fillCol(i, 0, 0, 0);}  //white
  for(int i = 0; i < 8; i++){fillCol(i, 1, 0, 1); delay(TD1); fillCol(i, 0, 0, 0);}  //magenta
  for(int i = 0; i < 8; i++){fillCol(i, 1, 1, 0); delay(TD1); fillCol(i, 0, 0, 0);}  //yellow
  for(int i = 0; i < 8; i++){fillCol(i, 0, 1, 1); delay(TD1); fillCol(i, 0, 0, 0);}  //turquoise


  // move single row bottom to top for each colour
  // -------------------------------------------------------------
  for(int i = 0; i < 8; i++){fillRow(i, 1, 0, 0); delay(TD1); fillRow(i, 0, 0, 0);}  // red
  for(int i = 0; i < 8; i++){fillRow(i, 0, 1, 0); delay(TD1); fillRow(i, 0, 0, 0);}  // green
  for(int i = 0; i < 8; i++){fillRow(i, 0, 0, 1); delay(TD1); fillRow(i, 0, 0, 0);}  // blue
  for(int i = 0; i < 8; i++){fillRow(i, 1, 1, 1); delay(TD1); fillRow(i, 0, 0, 0);}  // white
  for(int i = 0; i < 8; i++){fillRow(i, 1, 0, 1); delay(TD1); fillRow(i, 0, 0, 0);}  // magent
  for(int i = 0; i < 8; i++){fillRow(i, 1, 1, 0); delay(TD1); fillRow(i, 0, 0, 0);}  // yellow
  for(int i = 0; i < 8; i++){fillRow(i, 0, 1, 1); delay(TD1); fillRow(i, 0, 0, 0);}  // turquoise
 
 
  // 2 columns and 2 rows crossing over r, g, b & w
  // -------------------------------------------------------------
  for(int f = 0; f < 4; f++){
    for(int i = 0; i < 8; i++){ 
      fillRow(0 + i, 1, 0 ,0);
      fillRow(7 - i, 0, 1, 0);
      fillCol(0 + i, 0, 0, 1);
      fillCol(7 - i, 1, 1, 1);
      delay(TD1);
      fillRow(0 + i, 0, 0, 0);
      fillRow(7 - i, 0, 0, 0);
      fillCol(0 + i, 0, 0, 0);
      fillCol(7 - i, 0, 0, 0);
    }
  }
 
 
  // fill panel with random colours
  // -------------------------------------------------------------
  for(int i = 0; i < 20; i++){
    for(int y = 0; y < 8; y++){
      for(int x = 0; x < 8; x++){
        setPixel(x, y, random(2), random(2), random(2));\
      }
    }
    delay(TD1);
  }


  // clear the panel
  // -------------------------------------------------------------
  floodFill(0, 0, 0); delay(TD3);   // clear display
} 
// ===================
// ~~~ END of LOOP ~~~
// ===================



// =====================================================================================================
// ~~~ START of DISPLAY SOME TEXT ~~~
// ----------------------------------
//   takes a string of text and displays it one character at a time with each new word a random colour
// =====================================================================================================
void displaySomeText(String someText, int pauseTime) {
  byte aChar;                                 // grabs one character at a time from the message string
  int  stringLen;                             // length of text message
  byte myColour;                              // random colour
  
  uint16_t charScroll[8] = {0x0000, 0x0000,   // 8 row 16 bit display buffer
                            0x0000, 0x0000,   // 8x8 panel maps to the 8 MSB's
                            0x0000, 0x0000,   // aChar loads into 8 LSB's
                            0x0000, 0x0000};  // bit shifts to the left to scroll new char in and old char out
      
  stringLen = someText.length();              // find length of text message
  myColour = random(7) + 1;                   // select first random colour

  for(int i = 0; i < stringLen; i++){         // loop for as many characters in text message
    aChar = int(someText[i] - 0x20);          // get ascii value for each character and remove offset
    
    // load a character into buffers 8 Least Significant Bits
    for(int j = 0; j < 8; j++){
      charScroll[j] += font8x8_basic[aChar][7 - j] << 8;
    } 
    
    // shift buffer left one bit then load shift registers with the buffers 8 Most Significant Bits
    for(int j = 0; j < 7; j++){
      for(int k = 0; k < 8; k++){
        charScroll[k] = charScroll[k] >> 1;
        if(myColour & 0x01) {shiftRegisterRed[k] = 0x00ff & charScroll[k];} else {shiftRegisterRed[k] = 0;}
        if(myColour & 0x02) {shiftRegisterGrn[k] = 0x00ff & charScroll[k];} else {shiftRegisterGrn[k] = 0;}
        if(myColour & 0x04) {shiftRegisterBlu[k] = 0x00ff & charScroll[k];} else {shiftRegisterBlu[k] = 0;}
      }
      delay(60);
    }
    // if a space is detected chose a new random colour for the next word
    if(aChar == 0x00){ myColour = random(7) + 1; }
  }
delay(1000);
} 
// ================================
// ~~~ END of DISPLAY SOME TEXT ~~~
// ================================



// =====================================================================================================
// ~~~ Start of Zig Zag Fill ~~~
// -----------------------------
// fills entire panel bottom up one pixel at a time in a zig zag pattern left to right
// =====================================================================================================
void zigZagFill(boolean red, boolean grn, boolean blu, int pauseTime) {
  
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(i % 2 == 0){ setPixel(7 - j, i, red, grn, blu);} else {setPixel(j, i, red, grn, blu);}
      delay(pauseTime);
    }
  }
}
// ===========================
// ~~~ END of Zig Zag Fill ~~~
// ===========================



// =====================================================================================================
// ~~~ Start Flood Fill ~~~
// ------------------------
// fills entire panel with chosen colour via direct manipulation of the shift register arrays 
// (much faster than setting individual pixels)
// =====================================================================================================
void floodFill(boolean red, boolean grn, boolean blu) {

  for(int indexY = 0; indexY < 8; indexY++){
    if(red == 1) {shiftRegisterRed[indexY] = B11111111;} else {shiftRegisterRed[indexY] = B00000000;}
    if(grn == 1) {shiftRegisterGrn[indexY] = B11111111;} else {shiftRegisterGrn[indexY] = B00000000;}
    if(blu == 1) {shiftRegisterBlu[indexY] = B11111111;} else {shiftRegisterBlu[indexY] = B00000000;}
  }
}
// =========================
// ~~~ END of Flood Fill ~~~
// =========================



// =====================================================================================================
// ~~~ Start Fill Column ~~~
// -------------------------
// fills one column with single colour via direct manipulation of the register arrays 
// (has to do this one pixel at a time because columns span all bytes)
// =====================================================================================================
void fillCol(byte colIndex, boolean red, boolean grn, boolean blu) {

  // test column index is within boundary
  if(colIndex < 0) colIndex = 0;
  if(colIndex > 7) colIndex = 7;  
  
  // set the register arrays using bit manipulation
  for(int i = 0; i < 8; i++){
    if(red == 0) shiftRegisterRed[i] &= ~(1 << colIndex); else shiftRegisterRed[i] |=  (1 << colIndex);
    if(grn == 0) shiftRegisterGrn[i] &= ~(1 << colIndex); else shiftRegisterGrn[i] |=  (1 << colIndex);
    if(blu == 0) shiftRegisterBlu[i] &= ~(1 << colIndex); else shiftRegisterBlu[i] |=  (1 << colIndex);  
  }
}
// ==========================
// ~~~ END of Fill Column ~~~
// ==========================



// =====================================================================================================
// ~~~ Start Fill Row ~~~
// ----------------------
// fills 1 row with chosen colour via direct manipulation of the register arrays 
// (faster than setting individual pixels because rows span a single byte)
// =====================================================================================================
void fillRow(byte rowIndex, boolean red, boolean grn, boolean blu) {

  // test column index is within boundary
  if(rowIndex < 0) rowIndex = 0;
  if(rowIndex > 7) rowIndex = 7;  
  
  // set the register arrays using bit manipulation
  if(red == 0) {shiftRegisterRed[rowIndex] = 0;} else {shiftRegisterRed[rowIndex] = 255;}
  if(grn == 0) {shiftRegisterGrn[rowIndex] = 0;} else {shiftRegisterGrn[rowIndex] = 255;}
  if(blu == 0) {shiftRegisterBlu[rowIndex] = 0;} else {shiftRegisterBlu[rowIndex] = 255;} 
}
// =======================
// ~~~ END of Fill Row ~~~
// =======================



// =====================================================================================================
// ~~~ Start Set Pixel ~~~
// -----------------------
// take a pixels x & y co-ordinate, R, G & B binary values and assigns to appropriate shift register bit
// =====================================================================================================
void setPixel(byte pixelX, byte pixelY, boolean red, boolean grn, boolean blu) {

  // test pixel x & co-ordinates are within boundary
  if(pixelX < 0) pixelX = 0;
  if(pixelX > 7) pixelX = 7;
  if(pixelY < 0) pixelY = 0;
  if(pixelY > 7) pixelY = 7;
  
  // set appropriate registers using bit manipulation.
  // just Google 'bit shifting in c' 
  // to find tutorials and explanations of the following:  
  if(red == 1) shiftRegisterRed[pixelY] |=  (1 << pixelX);   // if red is 1 set appropriate bit within appropriate red byte to 1
    else       shiftRegisterRed[pixelY] &= ~(1 << pixelX);   //   otherwise set appropriate bit within appropriate red byte to 0
    
  if(grn == 1) shiftRegisterGrn[pixelY] |=  (1 << pixelX);   // if grn is 1 set appropriate bit within appropriate grn byte to 1 
    else       shiftRegisterGrn[pixelY] &= ~(1 << pixelX);   //   otherwise set appropriate bit within appropriate grn byte to 0
    
  if(blu == 1) shiftRegisterBlu[pixelY] |=  (1 << pixelX);   // if blu is 1 set appropriate bit within appropriate blu byte to 1
    else       shiftRegisterBlu[pixelY] &= ~(1 << pixelX);   //   otherwise set appropriate bit within appropriate blu byte to 0
}
// ======================
// ~~~ END Set Pixel  ~~~
// ======================



// =====================================================================================================
// ~~~ START 0f ISR ~~~
// --------------------
//   Updates the panel. Called every 125uS (8KHz), each row is lit for 1/8th of the time (1KHz)
// =====================================================================================================
ISR(TIMER2_COMPA_vect) {
  
  PORTD |= (1 << SR_BLANK);                      // temporarely disable the SR outputs
  SPI.transfer(shiftRegisterRed[anodeIndex]);    // send the red SR byte for the given anode level
  SPI.transfer(shiftRegisterGrn[anodeIndex]);    // send the grn SR byte for the given anode level
  SPI.transfer(shiftRegisterBlu[anodeIndex]);    // send the blu SR byte for the given anode level
  SPI.transfer(anodeLevel[anodeIndex]);          // send the anode multiplex byte
  anodeIndex = (anodeIndex + 1) % 8;             // incrument anode index ready for next ISR
  PORTD |=  (1 << SR_LATCH);                     // set latch pin LOW
  PORTD &= ~(1 << SR_LATCH);                     // set latch pin HIGH - SR outputs now have new data
  PORTD &= ~(1 << SR_BLANK);                     // re-enable the SR outputs
}
// ==================
// ~~~ END of ISR ~~~
// ==================



/*
* Copyright (c) 2014 Steve Manley
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHOR(S) OR COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

