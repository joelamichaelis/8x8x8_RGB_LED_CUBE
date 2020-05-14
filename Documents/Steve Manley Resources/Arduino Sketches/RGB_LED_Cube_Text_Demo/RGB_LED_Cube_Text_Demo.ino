// ===================================================================================
// Title:    3D 8x8x8 RGB LED CUBE by STEVE MANLEY
// Function: Draws text Right to Left and Back to Front
// Board:    Arduino Uno R3
// Version:  1.0
// Author:   Steve Manley
// Date:     7th SMarch 2016
// License:  The MIT License (See full license at the bottom of this file)
// Notes:    Basic demonstration of drawing text on the cube 
//           from right to left and from back to front.
// ===================================================================================

#include "SPI.h"

#define SPI_SCK         13                 // SPI clock    - must be pin 13
#define SPI_MOSI        11                 // SPI data out - must be pin 11
#define SR_LATCH         3                 // shift register latch         - any non SPI pin
#define SR_BLANK         2                 // shift register output enable - any non SPI pin
#define TD1             80                 // time delay 1 - 100ms
#define TD2           3000                 // time delay 2 -   3 seconds
#define TD3           1000                 // time delay 3 -   1 second
#define TD4             20                 // time delay 4 -  20ms
#define TD5            400                 // time delay 5 - 400ms
#define TD6            120                 // time delay 5 - 400ms
#define TD7            100                 // time delay 5 - 400ms


// =====================================================================================================
// variables used by Inturrupt Service Routine (ISR), must be volatile
// =====================================================================================================
volatile byte shiftRegisterRed[64];         // red   shift register data, 8 bytes, 1 byte per common anode
volatile byte shiftRegisterGrn[64];         // green shift register data, 8 bytes, 1 byte per common anode
volatile byte shiftRegisterBlu[64];         // blue  shift register data, 8 bytes, 1 byte per common anode
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
         byte colours[] = { 1, 2, 4, 3, 6, 5, 7 };

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
  //displaySomeText("WELCOME TO THE 8x8 RGB LED PANEL TESTING... ", TD5);
}
// ====================
// ~~~ END of SETUP ~~~
// ====================




// =====================================================================================================
// ~~~ START of LOOP ~~~
// =====================================================================================================
void loop() {
 
//                   Text         , Z Plane  , Colour       , Speed (lower = faster scroll)
//                   ---------------------------------------------------------------------- 
    textRightToLeft("Hello World ", random(8), random(7) + 1, 80);

//                   Text            , Colour       , Speed (lower = faster scroll)
//                   -------------------------------------------------------------- 
    textBackToFront("By Steve Manley", random(7) + 1, 100);


} 
// ===================
// ~~~ END of LOOP ~~~
// ===================



// =====================================================================================================
// ~~~ START of TEXT BACK TO FRONT ~~~
// -----------------------------------
//   takes a string of text and displays one character at a time from front to back
// =====================================================================================================
void textBackToFront(String someText, byte colour, int pauseTime) {
  byte aChar;                                 // grabs one character at a time from the message string
  int  stringLen;                             // length of text message
  int  index;                                 // indexes each line that makes up a character
  uint8_t charBuffer[8];                      // character buffer 8 bytes per char
      
  stringLen = someText.length();              // find length of text message

  for(int i = 0; i < stringLen; i++){         // loop for as many characters in text message
    aChar = int(someText[i] - 0x20);          // get ascii value for each character and remove offset
    
   
    // load a character into buffer and invert (else the text is upside down)
    for(int j = 0; j < 8; j++){
      charBuffer[j] = font8x8_basic[aChar][7 - j];
    } 

    // draw, pause, erase each character from front to back
    for(int zPlane = 0; zPlane < 8; zPlane++) {
      
      // draw
      for(int k = 0; k < 8; k++) {
        index = zPlane + (8 * k);
        if(colour & 0x01) {shiftRegisterRed[index] = 0x00ff & charBuffer[k];} else {shiftRegisterRed[index] = 0;}
        if(colour & 0x02) {shiftRegisterGrn[index] = 0x00ff & charBuffer[k];} else {shiftRegisterGrn[index] = 0;}
        if(colour & 0x04) {shiftRegisterBlu[index] = 0x00ff & charBuffer[k];} else {shiftRegisterBlu[index] = 0;}
      }
      
      // pause
      delay(pauseTime);
      
      // erase 
      for(int k = 0; k < 8; k++) {
        index = zPlane + (8 * k);
        if(colour & 0x01) {shiftRegisterRed[index] = 0;}
        if(colour & 0x02) {shiftRegisterGrn[index] = 0;}
        if(colour & 0x04) {shiftRegisterBlu[index] = 0;}
      }
    }
  }
} 

// =================================
// ~~~ END of TEXT BACK TO FRONT ~~~
// =================================





// =====================================================================================================
// ~~~ START of TEXT LEFT TO RIGHT ~~~
// -----------------------------------
//   takes a string of text and scrolles the characters from right to left
// =====================================================================================================
void textRightToLeft(String someText, byte zPlane, byte colour, int pauseTime) {
  byte aChar;                                 // grabs one character at a time from the message string
  int  stringLen;                             // length of text message
  int  index;                                 // indexes each line that makes up a character
  uint16_t charScroll[8] = {0x0000, 0x0000,   // 8 row 16 bit display buffer
                            0x0000, 0x0000,   // 8x8 panel maps to the 8 MSB's
                            0x0000, 0x0000,   // aChar loads into 8 LSB's
                            0x0000, 0x0000};  // bit shifts to the left to scroll new char in and old char out
      
  stringLen = someText.length();              // find length of text message

  for(int i = 0; i < stringLen; i++){         // loop for as many characters in text message
    aChar = int(someText[i] - 0x20);          // get ascii value for each character and remove offset
    
    // load a character into buffers 8 Least Significant Bits and invert (else the text is upside down)
    for(int j = 0; j < 8; j++){
      charScroll[j] += font8x8_basic[aChar][7 - j] << 8;
    } 
    
    // shift buffer left one bit then load shift registers with the buffers 8 Most Significant Bits
    for(int j = 0; j < 7; j++){
      for(int k = 0; k < 8; k++){
        charScroll[k] = charScroll[k] >> 1;
        index =zPlane + (8 * k);
        if(colour & 0x01) {shiftRegisterRed[index] = 0x00ff & charScroll[k];}
        if(colour & 0x02) {shiftRegisterGrn[index] = 0x00ff & charScroll[k];}
        if(colour & 0x04) {shiftRegisterBlu[index] = 0x00ff & charScroll[k];}
      }
      delay(pauseTime);
    }
  }
} 

// =================================
// ~~~ END of TEXT LEFT TO RIGHT ~~~
// =================================





// =====================================================================================================
// ~~~ START Draw Rectanle Outline ~~~
// -----------------------------------
// draw a 3d wireframe rectangle 
// =====================================================================================================
void drawRectangleOutline(int xMin, int yMin , int zMin, int xMax, int yMax, int zMax, boolean red, boolean grn, boolean blu) {

  for (int x = xMin; x < xMax + 1; x++) {
    setPixel( x, yMin, zMin, red, grn, blu);
    setPixel( x, yMin, zMax, red, grn, blu);
    setPixel( x, yMax, zMax, red, grn, blu);
    setPixel( x, yMax, zMin, red, grn, blu);
  }
  for (int y = yMin; y < yMax + 1; y++) {
    setPixel( xMin, y, zMin, red, grn, blu);
    setPixel( xMin, y, zMax, red, grn, blu);
    setPixel( xMax, y, zMax, red, grn, blu);
    setPixel( xMax, y, zMin, red, grn, blu);
  }
  for (int z = zMin; z < zMax + 1; z++) {
    setPixel( xMin, yMin, z, red, grn, blu);
    setPixel( xMin, yMax, z, red, grn, blu);
    setPixel( xMax, yMax, z, red, grn, blu);
    setPixel( xMax, yMin, z, red, grn, blu);
  }
}
// =================================
// ~~~ END Draw Rectanle Outline ~~~
// =================================



// =====================================================================================================
// ~~~ START Draw Rectanle Sides ~~~
// ---------------------------------
// draw a 3d rectangle filled sides 
// =====================================================================================================
void drawRectangleSides(int xMin, int yMin , int zMin, int xMax, int yMax, int zMax, boolean red, boolean grn, boolean blu) {

  for (int x = xMin; x < xMax + 1; x++) {
    for (int y = yMin; y < yMax + 1; y++) {
      setPixel( x, y, zMin, red, grn, blu);
      setPixel( x, y, zMax, red, grn, blu);
    }
  }
  for (int y = yMin; y < yMax + 1; y++) {
    for (int z = zMin; z < zMax + 1; z++) {
      setPixel( xMin, y, z, red, grn, blu);
      setPixel( xMax, y, z, red, grn, blu);
    }
  }
  for (int x = xMin; x < xMax + 1; x++) {
    for (int z = zMin; z < zMax + 1; z++) {
      setPixel( x, yMin, z, red, grn, blu);
      setPixel( x, yMax, z, red, grn, blu);
    }
  }
}
// ===============================
// ~~~ END Draw Rectanle Sides ~~~
// ===============================



// =====================================================================================================
// ~~~ START Draw Rectanle Filled ~~~
// ----------------------------------
// draw a 3d rectangle filled 
// =====================================================================================================
void drawRectangleFilled(int xMin, int yMin , int zMin, int xMax, int yMax, int zMax, boolean red, boolean grn, boolean blu) {

  for (int x = xMin; x < xMax + 1; x++) {
    for (int y = yMin; y < yMax + 1; y++) {
      for (int z = zMin; z < zMax + 1; z++) {
        setPixel(x, y, z, red, grn, blu);
      }
    }
  }
}
// ================================
// ~~~ END Draw Rectanle Filled ~~~
// ================================



// =====================================================================================================
// ~~~ Start Flood Fill ~~~
// ------------------------
// fills entire panel with chosen colour via direct manipulation of the shift register arrays 
// (much faster than setting individual pixels)
// =====================================================================================================
void floodFillCube(boolean red, boolean grn, boolean blu) {

  for ( int indexY = 0; indexY < 64; indexY++ ) {
    if(red == 1) {shiftRegisterRed[indexY] = B11111111;} else {shiftRegisterRed[indexY] = B00000000;}
    if(grn == 1) {shiftRegisterGrn[indexY] = B11111111;} else {shiftRegisterGrn[indexY] = B00000000;}
    if(blu == 1) {shiftRegisterBlu[indexY] = B11111111;} else {shiftRegisterBlu[indexY] = B00000000;}
  }
}
// =========================
// ~~~ END of Flood Fill ~~~
// =========================



// =====================================================================================================
// ~~~ Start Fill YZ Axis Plane ~~~
// --------------------------------
// 
// 
// =====================================================================================================
void yzPlaneFill(byte xIndex, byte colour) {
  
  boolean red = colour & B00000001; 
  boolean grn = colour & B00000010; 
  boolean blu = colour & B00000100;
  Serial.print("red = ");
  Serial.print(red);
  
  // test column index is within boundary
  if ( xIndex < 0) xIndex = 0;
  if ( xIndex > 7) xIndex = 7;  
  
  // set the register arrays using bit manipulation
  for ( int i = 0; i < 8; i++ ) {
    for ( int j = 0; j < 8; j++ ) {
      if ( red == 0 ) shiftRegisterRed[i + (j * 8)] &= ~(1 << xIndex); else shiftRegisterRed[i + (j * 8)] |=  (1 << xIndex);
      if ( grn == 0 ) shiftRegisterGrn[i + (j * 8)] &= ~(1 << xIndex); else shiftRegisterGrn[i + (j * 8)] |=  (1 << xIndex);
      if ( blu == 0 ) shiftRegisterBlu[i + (j * 8)] &= ~(1 << xIndex); else shiftRegisterBlu[i + (j * 8)] |=  (1 << xIndex);  
    }
  }
}
// ==============================
// ~~~ END Fill YZ Axis Plane ~~~
// ==============================



// =====================================================================================================
// ~~~ Start Fill XZ Axis Plane ~~~
// --------------------------------
// 
// 
// =====================================================================================================
void xzPlaneFill(byte yIndex, byte colour) {
  
  boolean red = colour & B00000001; 
  boolean grn = colour & B00000010; 
  boolean blu = colour & B00000100;
  Serial.print("red = ");
  Serial.print(red);
  
  // test column index is within boundary
  if ( yIndex < 0 ) yIndex = 0;
  if ( yIndex > 7 ) yIndex = 7;  
  
  // set the register arrays using bit manipulation
  for (int i = 0; i < 8; i++) {
    if(red == 0) {shiftRegisterRed[i + (yIndex * 8)] = 0;} else {shiftRegisterRed[i + (yIndex * 8)] = 255;}
    if(grn == 0) {shiftRegisterGrn[i + (yIndex * 8)] = 0;} else {shiftRegisterGrn[i + (yIndex * 8)] = 255;}
    if(blu == 0) {shiftRegisterBlu[i + (yIndex * 8)] = 0;} else {shiftRegisterBlu[i + (yIndex * 8)] = 255;} 
  }
}
// ==============================
// ~~~ END Fill XZ Axis Plane ~~~
// ==============================



// =====================================================================================================
// ~~~ Start Fill XZ Axis Plane ~~~
// --------------------------------
// 
// 
// =====================================================================================================
void xyPlaneFill(byte zIndex, byte colour) {
  
  boolean red = colour & B00000001; 
  boolean grn = colour & B00000010; 
  boolean blu = colour & B00000100;
  
  // test column index is within boundary
  if ( zIndex < 0 ) zIndex = 0;
  if ( zIndex > 7 ) zIndex = 7;  
  
  // set the register arrays using bit manipulation
  for ( int i = 0; i < 8; i++ ) {
    if ( red == 0 ) {shiftRegisterRed[zIndex + ( 8 * i)] = 0;} else {shiftRegisterRed[zIndex + ( 8 * i)] = 255;}
    if ( grn == 0 ) {shiftRegisterGrn[zIndex + ( 8 * i)] = 0;} else {shiftRegisterGrn[zIndex + ( 8 * i)] = 255;}
    if ( blu == 0 ) {shiftRegisterBlu[zIndex + ( 8 * i)] = 0;} else {shiftRegisterBlu[zIndex + ( 8 * i)] = 255;} 
  }
}
// =======================
// ~~~ END of Fill Row ~~~
// =======================



// =====================================================================================================
// ~~~ Start Set Pixel ~~~
// -----------------------
// take a pixels x & y co-ordinate, R, G & B binary values and assigns to appropriate shift register bit
// =====================================================================================================
void setPixel(byte pixelX, byte pixelY, byte pixelZ, boolean red, boolean grn, boolean blu) {

  // test pixel x & co-ordinates are within boundary
  if(pixelX < 0) pixelX = 0;
  if(pixelX > 7) pixelX = 7;
  if(pixelY < 0) pixelY = 0;
  if(pixelY > 7) pixelY = 7;
  if(pixelZ < 0) pixelZ = 0;
  if(pixelZ > 7) pixelZ = 7;
  
  // set appropriate registers using bit manipulation.
  // just Google 'bit shifting in c' 
  // to find tutorials and explanations of the following:  
  if(red == 1) shiftRegisterRed[(8 * pixelY) + (7 - pixelZ)] |=  (1 << pixelX);   // if red is 1 set appropriate bit within appropriate red byte to 1
    else       shiftRegisterRed[(8 * pixelY) + (7 - pixelZ)] &= ~(1 << pixelX);   //   otherwise set appropriate bit within appropriate red byte to 0
    
  if(grn == 1) shiftRegisterGrn[(8 * pixelY) + (7 - pixelZ)] |=  (1 << pixelX);   // if grn is 1 set appropriate bit within appropriate grn byte to 1 
    else       shiftRegisterGrn[(8 * pixelY) + (7 - pixelZ)] &= ~(1 << pixelX);   //   otherwise set appropriate bit within appropriate grn byte to 0
    
  if(blu == 1) shiftRegisterBlu[(8 * pixelY) + (7 - pixelZ)] |=  (1 << pixelX);   // if blu is 1 set appropriate bit within appropriate blu byte to 1
    else       shiftRegisterBlu[(8 * pixelY) + (7 - pixelZ)] &= ~(1 << pixelX);   //   otherwise set appropriate bit within appropriate blu byte to 0
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
  for (int i = 0; i < 8; i++) {
    SPI.transfer(shiftRegisterRed[i + anodeIndex * 8]);    // send the red SR byte for the given anode level
    SPI.transfer(shiftRegisterGrn[i + anodeIndex * 8]);    // send the grn SR byte for the given anode level
    SPI.transfer(shiftRegisterBlu[i + anodeIndex * 8]);    // send the blu SR byte for the given anode level
  }
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

