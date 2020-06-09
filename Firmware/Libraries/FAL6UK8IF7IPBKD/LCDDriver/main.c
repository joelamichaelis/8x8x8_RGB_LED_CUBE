/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F2685
        Driver Version    :  2.00
        Compiler          :  XC8 v1.35
        MPLAB             :  MPLAB X v2.15
*/


// Includes

#include "mcc_generated_files/mcc.h"
#include "I2C_UTILS.h"
#include "LCD_I2C_PCF8574.h"
#include "DELAY.h"
#include <stdio.h>
#include <stdlib.h>
#include <pic18f2685.h>


// Defines

#define FALSE 0
#define TRUE ~FALSE



unsigned char x = 0;

unsigned char hex[]        = {"0123456789ABCDEF"};
unsigned char bell[8]      = {0x04,0x0e,0x0e,0x0e,0x1f,0x00,0x04};
unsigned char note[8]      = {0x02,0x03,0x02,0x0e,0x1e,0x0c,0x00};
unsigned char clock[8]     = {0x00,0x0e,0x15,0x17,0x11,0x0e,0x00};
unsigned char heart[8]     = {0x00,0x0a,0x1f,0x1f,0x0e,0x04,0x00};
unsigned char duck[8]      = {0x00,0x0c,0x1d,0x0f,0x0f,0x06,0x00};
unsigned char check[8]     = {0x00,0x01,0x03,0x16,0x1c,0x08,0x00};
unsigned char cross[8]     = {0x00,0x1b,0x0e,0x04,0x0e,0x1b,0x00};
unsigned char retarrow[8]  = {0x01,0x01,0x05,0x09,0x1f,0x08,0x04};
unsigned char * charmap[8] = {bell, note, clock, heart, duck, check, cross, retarrow};

void exerciseDisplay(void);
void displayLeftRightScroll(void);
void autoIncrement(void);
void displayOnOff(void);
void backLightControl(void);
void printAt(void);
void cursorControl(void);
void printLeftAndRight(void);
void controlMemoryReading(void);
void dataMemoryReading(void);
void updateSwitches(void);
void updateNavButtons(void);
void updateEncoder(void);
void updateButton(void);
void putHexString(unsigned char c, unsigned char r, unsigned char hexval);



/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    while (TRUE)
        exerciseDisplay();
}




void exerciseDisplay(void)
{
    autoIncrement();
    displayLeftRightScroll();
    displayOnOff();
    backLightControl();
    printAt();
    cursorControl();
    printLeftAndRight();
    controlMemoryReading();
    dataMemoryReading();
}




void autoIncrement(void)
{
  char Autoscroll[] = "Autoscroll";
  char NoAutoscroll[] = "No Autoscroll";
  unsigned char * p;

  LCDclear();
  LCDcursorOff();
  LCDblinkOff();
  LCDautoscroll();
  p = Autoscroll;
  LCDsetCursor(15,1);
  while (*p)
  {
      LCD_Write_Char((char) *p++);
      DelayMilliseconds(400);
  }
  DelayMilliseconds(5000);

  LCDclear();
  LCDnoAutoscroll();
  p = NoAutoscroll;
  LCDsetCursor(3,1);
  while (*p)
  {
      LCD_Write_Char((char) *p++);
      DelayMilliseconds(400);
  }
  DelayMilliseconds(5000);
}


void displayLeftRightScroll(void)
{
  LCDclear();
  LCDcursorOff();
  LCDblinkOff();
  LCDsetCursor(0,0);
  LCD_Write_Str("Scroll Right");
  LCDsetCursor(0,1);
  LCD_Write_Str("---->");
  for (unsigned char x = 0; x< 8; x++)
  {
    LCDscrollDisplayRight();
    DelayMilliseconds(500);
  }

  LCDclear();
  LCDsetCursor(8,0);
  LCD_Write_Str("Scroll Left ");
  LCDsetCursor(8,1);
  LCD_Write_Str("<----");
  for (unsigned char x = 0; x< 8; x++)
  {
    LCDscrollDisplayLeft();
    DelayMilliseconds(500);
  }

  DelayMilliseconds(5000);
}



void displayOnOff(void)
{
  LCDclear();
  LCDcursorOff();
  LCDblinkOff();
  for (unsigned char x = 0; x < 6; x++)
  {
      if (x%2) {
        LCDhome();
        LCD_Write_Str("           ");
        LCDhome();
        LCD_Write_Str("Display On ");
        LCDdisplayOn();
      } else {
        LCDsetCursor(0,0);
        LCD_Write_Str("           ");
        LCDsetCursor(0,0);
        LCD_Write_Str("Display Off");
        LCDdisplayOff();
      }
      DelayMilliseconds(750);
  }
}

void backLightControl(void)
{
  LCDclear();
  LCDcursorOff();
  LCDbacklight();
  LCD_Write_Str("Backlight On");
  DelayMilliseconds(1000);
  LCDclear();
  //LCDsetCursor(0,0);
  LCDnoBacklight();
  LCD_Write_Str("Backlight Off");
  DelayMilliseconds(1000);
  LCDclear();
  //LCDsetCursor(0,0);
  LCDbacklight();
  LCD_Write_Str("Backlight On");
  DelayMilliseconds(1000);
  for (unsigned char x = 0; x < 6; x++)
  {
      if (x%2) {
        LCDsetCursor(0,0);
        LCD_Write_Str("             ");
        LCDsetCursor(0,0);
        LCD_Write_Str("Backlight On ");
        LCDbacklight();
      } else {
        LCDclear();
        LCD_Write_Str("Backlight Off");
        LCDnoBacklight();
      }
      DelayMilliseconds(750);
  }
}

void printAt(void)
{
  LCDclear();
  LCDcursorOff();
  //LCDsetCursor(0,0);
  LCD_Write_Str("@:0,0");
  LCDsetCursor(1,1);
  LCD_Write_Str("@:1,1");
  LCDsetCursor(2,2);
  LCD_Write_Str("@:2,2");
  LCDsetCursor(3,3);
  LCD_Write_Str("@:3,3");
  LCDsetCursor(12,0);
  LCD_Write_Str("Print at");
  DelayMilliseconds(3000);
}


void cursorControl(void)
{
  LCDclear();
  LCDcursorOff();
  LCD_Write_Str("Cursor Off");
  DelayMilliseconds(1500);
  LCDclear();
  LCDcursorOn();
  LCD_Write_Str("Cursor On");
  DelayMilliseconds(1500);
  LCDclear();
  LCDblinkOn();
  LCD_Write_Str("Blink On");
  DelayMilliseconds(1500);
  LCDclear();
  LCDblinkOff();
  LCD_Write_Str("Blink Off");
  DelayMilliseconds(1500);
  LCDclear();
  LCD_Write_Str("Cursor Home");
  LCDhome();
  DelayMilliseconds(1500);
  LCDclear();
  LCD_Write_Str("Cursor Home & Blink");
  LCDhome();
  LCDblinkOn();
  DelayMilliseconds(3000);
}


void printLeftAndRight(void)
{
  LCDclear();
  LCDcursorOff();
  LCDblinkOff();
  //LCDsetCursor(0,0);
  LCDleftToRight();
  LCD_Write_Str("Print left to right");
  LCDsetCursor(0,1);
  LCD_Write_Str("0123456789ABCDEFGHIJ");
  LCDsetCursor(0,2);
  LCD_Write_Str("Print right to left");
  LCDrightToLeft();
  LCDsetCursor(19,4);
  LCD_Write_Str("0123456789ABCDEFGHIJ");
  LCDleftToRight();
  DelayMilliseconds(5000);
}

void controlMemoryReading(void)
{
    unsigned char x = 0;

    LCDclear();
    LCDcursorOn();
    LCDblinkOn();
    LCDsetCursor(1,1); // At position 1,1 the Address Counter will read 0x41
    DelayMilliseconds(2000);
    x = LCDaddressCounter();
    LCDcursorOff();
    LCDblinkOff();
    LCDsetCursor(0,2);
    LCD_Write_Str("Addr Counter : ");
    LCDsetCursor(15,2);
    LCD_Write_Str("0x");
    LCDsetCursor(17,2);
    LCD_Write_Char((char) hex[(x>>4)& 0x0f]);
    LCDsetCursor(18,2);
    LCD_Write_Char((char) hex[x & 0x0f]);
    //DelayMilliseconds(5000);

    x = LCDbusy();
    LCDsetCursor(0,3);
    LCD_Write_Str("Busy Flag : ");
    LCDsetCursor(12,3);
    LCD_Write_Str("0x");
    LCDsetCursor(14,3);
    LCD_Write_Char((char) hex[(x>>4)& 0x0f]);
    LCDsetCursor(15,3);
    LCD_Write_Char((char) hex[x & 0x0f]);
    DelayMilliseconds(5000);
}


void dataMemoryReading(void)
{
    unsigned char x = 0;

    LCDclear();
    LCDcursorOff();
    LCDblinkOff();
    //for (unsigned char p = 0; p < (sizeof(charmap)/sizeof(unsigned char *)) ; p++)
    for (unsigned char p = 0; p < 8 ; p++)
        LCDcreateChar(p, charmap[p]);
    LCDhome();

    LCDsetCursor(0,0);
    LCD_Write_Str("Q = ");

    x = LCDreadDDRam(0x00);
    LCDsetCursor(4,0);
    LCD_Write_Str("0x");
    LCDsetCursor(6,0);
    LCD_Write_Char((char) hex[(x>>4)& 0x0f]);
    LCDsetCursor(7,0);
    LCD_Write_Char((char) hex[x & 0x0f]);
    LCDsetCursor(8,0);
    LCD_Write_Char(',');

    for (unsigned char i = 0; i < 8; i++)
    {
        LCDsetCursor(i+10,0);
        LCD_Write_Char(i);
    }

    LCDsetCursor(0,1);
    LCD_Write_Str("Bell char Hex rep;");

    x = 0;
    for (unsigned char r = 0; r < 2; r++)
        for (unsigned char c = 0; c < 4; c++)
            putHexString(c, r, LCDreadCGRam(x++));
  DelayMilliseconds(5000);
}



void putHexString(unsigned char c, unsigned char r, unsigned char hexval)
{
    LCDsetCursor(0+(5*c),2+(2*r));
    LCD_Write_Str("0x");
    LCDsetCursor(2+(5*c),2+(2*r));
    LCD_Write_Char((char) hex[(hexval>>4)& 0x0f]);
    LCDsetCursor(3+(5*c),2+(2*r));
    LCD_Write_Char((char) hex[hexval & 0x0f]);
}


/**
 End of File
*/