#include "LCD.h"
#include "DELAY.h"
#include "MCP23017.h"
#include <xc.h>
#include <i2c.h>
#include "I2C_UTILS.h"



#define LCD_CLEAR_DISPLAY           0x01    // Mode : Clears display

#define LCD_RETURN_HOME             0x02    // Mode : Returns cursor to home posn.

// Entry Mode
#define LCD_ENTRY_MODE_SET          0x04    // Mode : Entry Mode Set, Sets the cursor move dir and specs whether or not to shift the display
#define LCD_INCREMENT               0x02        // Sub Mode of ENTRY_MODE_SET : Increment DDRAM (I/D), Entry Left
#define LCD_DECREMENT               0x00        // Sub Mode of ENTRY_MODE_SET : Decrement DDRAM (I/D), Entry Right
#define LCD_SHIFT_ON                0x01        // Sub Mode of ENTRY_MODE_SET : Shift On  (S), Shift Display when byte written
#define LCD_SHIFT_OFF               0x00        // Sub Mode of ENTRY_MODE_SET : Shift Off (S), Don't shift display when byte written

// Display Function
#define LCD_DISPLAY_ON_OFF          0x08    // Mode : Display On/Off, Sets on/off of all display, Cursor on/off, Cursor Blink on/off
#define LCD_DISPLAY_ON              0x04        // Sub Mode of DISPLAY_ON_OFF : Puts display on  (D)
#define LCD_DISPLAY_OFF             0x00        // Sub Mode of DISPLAY_ON_OFF : Puts display off (D)
#define LCD_CURSOR_ON               0x02        // Sub Mode of DISPLAY_ON_OFF : Puts cursor on   (C)
#define LCD_CURSOR_OFF              0x00        // Sub Mode of DISPLAY_ON_OFF : Puts cursor off  (C)
#define LCD_BLINKING_ON             0x01        // Sub Mode of DISPLAY_ON_OFF : Blinking cursor  (B)
#define LCD_BLINKING_OFF            0x00        // Sub Mode of DISPLAY_ON_OFF : Solid cursor     (B)

// Display Control
#define LCD_MV_CUR_SHIFT_DISPLAY    0x10    // Mode : Move the cursor and shifts the display
#define LCD_DISPLAY_SHIFT           0x08        // Sub Mode of CURSOR_SHFT_DIS : Display shifts after char print   (SC)
#define LCD_CURSOR_SHIFT            0x00        // Sub Mode of CURSOR_SHFT_DIS : Cursor shifts after char print    (SC)
#define LCD_SHIFT_RIGHT             0x04        // Sub Mode of CURSOR_SHFT_DIS : Cursor or Display shifts to right (RL)
#define LCD_SHIFT_LEFT              0x00        // Sub Mode of CURSOR_SHFT_DIS : Cursor or Display shifts to left  (RL)

// Display Mode
#define LCD_FUNCTION_SET            0x20    // Mode : Set the type of interface that the display will use
#define LCD_INTF8BITS               0x10        // Sub Mode of FUNCTION_SET : Select 8 bit interface         (DL)
#define LCD_INTF4BITS               0x00        // Sub Mode of FUNCTION_SET : Select 4 bit interface         (DL)
#define LCD_TWO_LINES               0x08        // Sub Mode of FUNCTION_SET : Selects two char line display  (N)
#define LCD_ONE_LINE                0x00        // Sub Mode of FUNCTION_SET : Selects one char line display  (N)
#define LCD_FONT_5_10               0x04        // Sub Mode of FUNCTION_SET : Selects 5 x 10 Dot Matrix Font (F)
#define LCD_FONT_5_7                0x00        // Sub Mode of FUNCTION_SET : Selects 5 x 7 Dot Matrix Font  (F)

#define LCD_CG_RAM_ADDRESS          0x40    // Mode : Enables the setting of the Char Gen (CG) Ram Address, to be or'ed with require address

#define LCD_DD_RAM_ADDRESS          0x80    // Mode : Enables the setting of the Display Data (DD) Ram Address, to be or'ed with require address




/*
 Assumes the following;
 *
 * Connection to the LCD Display is via an I2C MCP23017 which is preconfigured with IOCON.BANK = 1
 * at I2C address 0x40. ie A0..2 = 0. Note : 4 Bit Mode Port I/O is not supported.
 *
 * Port A is used for the display data. Assumes that Port A is initialised as input
 * 
 *  Pin#  bit#  LCD bit#  LCD Data Mode   Data Dir
 *  28     7     7 (3)      8/4             R/W    (Input/Output) Data bit 7
 *  27     6     6 (2)      8/4             R/W    (Input/Output) Data bit 6
 *  26     5     5 (1)      8/4             R/W    (Input/Output) Data bit 5
 *  25     4     4 (0)      8/4             R/W    (Input/Output) Data bit 4
 *  24     3     3          8               R/W    (Input/Output) Data bit 3
 *  23     2     2          8               R/W    (Input/Output) Data bit 2
 *  22     1     1          8               R/W    (Input/Output) Data bit 1
 *  21     0     0          8               R/W    (Input/Output) Data bit 0
 *
 * Port B is used for the control lines to the LCD
 *
 *  Pin#  bit# LCD Name  Data Dir
 *  4      3     E          W     (Output) Enable. Used as read/write enable signal.
 *  5      4     R/~W       W     (Output) Read/~Write
 *  6      5     RS         W     (Output) Register Select. High = Data Register, Low = Instruction Register
 *
 */

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x7 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//

#define LCD_LINE1	0x00		// Constant used to point to start of LCD Line 1
#define LCD_LINE2	0x40		// Constant used to point to start of LCD Line 2
#define LCD_LINE3	0x14		// Constant used to point to start of LCD Line 3
#define LCD_LINE4	0x54		// Constant used to point to start of LCD Line 4

// DDRAM address:
// Display position
// 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20
// 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10 11 12 13
// 40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F 50 51 52 53
// 14 15 16 17 18 19 1A 1B 1C 1D 1E 1F 20 21 22 23 24 25 26 27
// 54 55 56 57 58 59 5A 5B 5C 5D 5E 5F 60 61 62 63 64 65 66 67


static unsigned char _displaymode;
static unsigned char _entrymodeset;
static unsigned char _displaycontrol;
static unsigned char _displayfunction;
static unsigned char _numlines,_currline;


static void LCDsend(unsigned char value, unsigned char mode);
static unsigned char LCDrecieve(unsigned char mode);
static void LCDSetRegisterSelect(unsigned char RS);
static void LCDSetReadWriteMode(unsigned char DataDirection);
static void LCDpulseEnable(void);
static void LCDenableLow(void);
static void LCDwrite8bits(unsigned char value);
static unsigned char LCDread8bits(void);
static void LCDdataPortAllInputs(void);
static void LCDSetControlLines(void);



#define LCD_MCP23017_ADDR        0x40
#define LCD_E_MASK               0b11011111
#define LCD_RnW_MASK             0b11101111
#define LCD_RS_MASK              0b11110111
#define LCD_BUSY_FLAG_MASK       0b01111111
#define LCD_ADDRESS_COUNTER_MASK 0b10000000
#define LCD_READ                 0xFF
#define LCD_WRITE                0x00
#define LCD_SELECT_REGISTER      0xFF
#define LCD_SELECT_INSTRUCTION   0x00
#define LCD_MAX_COLS             20
#define LCD_MAX_ROWS             4


/********** high level commands, for the user! */
void LCD_Init(void)
{
    LCDSetControlLines(); // Programs the E, R/~W and RS as Outputs
    // E O/P = Low, R/~W O/P = Low, RS O/P = Low, Port A : D0-D7 = Low
    LCDSetReadWriteMode(LCD_WRITE); // R/~W = Low
    LCDSetRegisterSelect(LCD_SELECT_INSTRUCTION); // RS = Low
    LCDdataPortAllInputs(); // Port A all inputs
    LCDenableLow(); // E = Low

    _numlines = LCD_MAX_ROWS;
    _currline = 0;

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
  DelayMicroseconds(50000);

  // Send function set command sequence
  _displaymode = LCD_FUNCTION_SET | LCD_INTF8BITS; // This is for first initialisation as described in Hitachi Manual
  LCDcommand(_displaymode);
  DelayMicroseconds(4500);  // wait more than 4.1ms

  // second try
  LCDcommand(_displaymode);
  DelayMicroseconds(150);

  // third go
  LCDcommand(_displaymode);
  
  _displaymode = LCD_FUNCTION_SET | LCD_INTF8BITS | LCD_TWO_LINES | LCD_FONT_5_7;
  // finally, set # lines, font size, etc.
  LCDcommand(_displaymode);

  // Initialize to default text direction (for romance languages)
  _entrymodeset = LCD_ENTRY_MODE_SET | LCD_INCREMENT | LCD_SHIFT_OFF;
  // set the entry mode
  LCDcommand(_entrymodeset);


  // set cursor to move right on entry
  _displaycontrol =  LCD_MV_CUR_SHIFT_DISPLAY | LCD_DISPLAY_SHIFT | LCD_SHIFT_RIGHT;
  // Set display control
  LCDcommand(_displaycontrol);

// turn the display on with no cursor or blinking default
  _displayfunction =  LCD_DISPLAY_ON_OFF | LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINKING_ON;
  // Set display fucntion
  LCDcommand(_displayfunction);
    
}

void LCD_Write_Char(char message)
{
    LCDwrite((unsigned char) message);
}

void LCD_Write_Str(const char *message)
{
    unsigned char *message_ptr = (unsigned char *) message;

    while (*message_ptr)
    {
        LCDwrite((unsigned char) (*message_ptr++));
    }
}


void LCDclear(void)
{
  LCDcommand(LCD_CLEAR_DISPLAY);  // clear display, set cursor position to zero
  while(LCDbusy());
  //DelayMicroseconds(2000);  // this command takes a long time!
}

void LCDhome(void)
{
  LCDcommand(LCD_RETURN_HOME);  // set cursor position to zero
  while(LCDbusy());
  //DelayMicroseconds(2000);  // this command takes a long time!
}

void LCDsetCursor(unsigned char col, unsigned char row)
{
  int row_offsets[] = { LCD_LINE1, LCD_LINE2, LCD_LINE3, LCD_LINE4 };
  //int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  if ( row >= _numlines ) {
    row = _numlines-1;    // we count rows starting w/0
  }

  LCDcommand(LCD_DD_RAM_ADDRESS | (col + row_offsets[row]));
}

// Turn the display on/off (quickly)
void LCDnoDisplay(void) {
  _displayfunction &= ~LCD_DISPLAY_ON;
  LCDcommand(_displayfunction);
}
void LCDdisplay(void) {
  _displayfunction |= LCD_DISPLAY_ON;
  LCDcommand(_displayfunction);
}

// Turns the underline cursor on/off
void LCDnoCursor(void) {
  _displayfunction &= ~LCD_CURSOR_ON;
  LCDcommand(_displayfunction);
}
void LCDcursor(void) {
  _displayfunction |= LCD_CURSOR_ON;
  LCDcommand(_displayfunction);
}

// Turn on and off the blinking cursor
void LCDnoBlink(void) {
  _displayfunction &= ~LCD_BLINKING_ON;
  LCDcommand(_displayfunction);
}
void LCDblink(void) {
  _displayfunction |= LCD_BLINKING_ON;
  LCDcommand(_displayfunction);
}

// These commands scroll the display without changing the RAM
void LCDscrollDisplayLeft(void) {
  _displaycontrol &= ~LCD_SHIFT_RIGHT;
  LCDcommand(_displaycontrol);
}
void LCDscrollDisplayRight(void) {
  _displaycontrol |= LCD_SHIFT_RIGHT;
  LCDcommand(_displaycontrol);
}


void LCDscrollDisplay(void) {
  _displaycontrol |= LCD_DISPLAY_SHIFT;
  LCDcommand(_displaycontrol);
}
void LCDscrollCursor(void) {
  _displaycontrol &= ~LCD_DISPLAY_SHIFT;
  LCDcommand(_displaycontrol);
}


// This is for text that flows Left to Right
void LCDleftToRight(void) {
  _entrymodeset |= LCD_SHIFT_ON;
  LCDcommand(_entrymodeset);
}

// This is for text that flows Right to Left
void LCDrightToLeft(void) {
  _entrymodeset &= ~LCD_SHIFT_ON;
  LCDcommand(_entrymodeset);
}

// This will 'right justify' text from the cursor
void LCDautoscroll(void) {
  _entrymodeset |= LCD_INCREMENT;
  LCDcommand(_entrymodeset);
}

// This will 'left justify' text from the cursor
void LCDnoAutoscroll(void) {
  _entrymodeset &= ~LCD_INCREMENT;
  LCDcommand(_entrymodeset);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LCDcreateChar(unsigned char location, unsigned char charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  LCDcommand(LCD_CG_RAM_ADDRESS | (location << 3));
  for (int i=0; i<8; i++) {
    LCDwrite(charmap[i]);
  }
}

/*********** mid level commands, for sending data/cmds */

inline void LCDcommand(unsigned char value) {
  LCDsend(value, LCD_SELECT_INSTRUCTION);
}

inline void LCDwrite(unsigned char value) {
  LCDsend(value, LCD_SELECT_REGISTER);
}

unsigned char LCDread(void) { // Read LCD. Read the ASCII Character value on the Display at the Current Cursor Position
    unsigned char b;

    b = LCDrecieve(LCD_SELECT_REGISTER);
    return  b;
}

unsigned char LCDbusy(void) { // Read busy flag
    unsigned char b;

    b = LCDrecieve(LCD_SELECT_INSTRUCTION) & (unsigned char)~LCD_BUSY_FLAG_MASK;
    return  b;
}

unsigned char LCDaddressCounter(void) { // Read address counter
    unsigned char b;

    b = LCDrecieve(LCD_SELECT_INSTRUCTION) & (unsigned char)~LCD_ADDRESS_COUNTER_MASK;
    return  b;
}

/************ low level data pushing commands **********/

// write either command or data byte. mode = LCD_SELECT_REGISTER / LCD_SELECT_INSTRUCTION
static void LCDsend(unsigned char value, unsigned char mode) {
    LCDSetRegisterSelect(mode);
    //LCDSetReadWriteMode(LCD_WRITE);
    LCDwrite8bits(value);
}


// read either command or data byte. mode = LCD_SELECT_REGISTER / LCD_SELECT_INSTRUCTION
static unsigned char LCDrecieve(unsigned char mode) {
    unsigned char b = 0;

    LCDSetRegisterSelect(mode);
    //LCDSetReadWriteMode(LCD_READ);
    b = LCDread8bits();
    return b;
}


static void LCDSetRegisterSelect(unsigned char RS) {
    unsigned char b;

    b = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_OLATB);
    switch (RS) {
        case LCD_SELECT_REGISTER :
            b |= (unsigned char)~LCD_RS_MASK; // Set RS, High
            break;
        case LCD_SELECT_INSTRUCTION :
        default :
            b &= LCD_RS_MASK; // Clear RS, Low
            break;
    }
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, b);
}

static void LCDSetReadWriteMode(unsigned char DataDirection) {
    unsigned char b;

    b = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_OLATB);
    switch (DataDirection) {
        case LCD_READ :
            b |= (unsigned char)~LCD_RnW_MASK; // Set R/~W, High
            break;
        case LCD_WRITE :
        default :
            b &= LCD_RnW_MASK; // Clear R/~W, Low
            break;
    }
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, b);
}

static void LCDpulseEnable(void) {
    unsigned char b;

    b = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_OLATB);
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, b & LCD_E_MASK); // E = Low, for 1uS
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, b | (unsigned char)~LCD_E_MASK); // E = High, for >450nS
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, b & LCD_E_MASK); // E = Low, for >37uS
}

static void LCDenableLow(void) {
    unsigned char b;

    b = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_OLATB);
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, b & LCD_E_MASK); // E = Low, for 1uS
}

static void LCDwrite8bits(unsigned char value) {
  LCDSetReadWriteMode(LCD_WRITE);
  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_IODIRA, MCP23017_ALL_OUT); // Set port A to all outputs
  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATA, value);
  LCDpulseEnable();
}


static unsigned char LCDread8bits(void) {
  unsigned char b = 0;
  unsigned char c = 0;

  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_IODIRA, MCP23017_ALL_IN); // Set port A to all inputs
  LCDSetReadWriteMode(LCD_READ);
  //LCDpulseEnable();

  c = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_OLATB);
  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, c & LCD_E_MASK); // E = Low, for 1uS
  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, c | (unsigned char)~LCD_E_MASK); // E = High, for >450nS

  b = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_GPIOA); // read the data

  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_OLATB, c & LCD_E_MASK); // E = Low, for >37uS
  return b;
}

static void LCDdataPortAllInputs(void)
{
  I2C_Write_Byte(LCD_MCP23017_ADDR, B1_IODIRA, MCP23017_ALL_IN); // Set port A to all inputs
}

static void LCDSetControlLines(void)
{
    unsigned char b = 0;
    b = I2C_Read_Byte(LCD_MCP23017_ADDR, B1_IODIRB);
    I2C_Write_Byte(LCD_MCP23017_ADDR, B1_IODIRB, b & LCD_E_MASK & LCD_RnW_MASK & LCD_RS_MASK); // IODIRB = XXOOOXXX, Bits 2, 3 and 4 O/Ps
}