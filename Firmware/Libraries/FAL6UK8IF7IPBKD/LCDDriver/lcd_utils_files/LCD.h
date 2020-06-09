/* 
 * File:   LCD.h
 * Author: Win 7
 *
 * Created on 25 September 2014, 19:42
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
  void LCD_Init(void);
  void LCD_Write_Char(char message);
  void LCD_Write_Str(const char *message);
  
  void LCDclear(void);
  void LCDhome(void);

  void LCDnoDisplay(void);
  void LCDdisplay(void);
  void LCDnoBlink(void);
  void LCDblink(void);
  void LCDnoCursor(void);
  void LCDcursor(void);
  void LCDscrollDisplayLeft(void);
  void LCDscrollDisplayRight(void);
  void LCDscrollDisplay(void);
  void LCDscrollCursor(void);
  void LCDleftToRight(void);
  void LCDrightToLeft(void);
  void LCDautoscroll(void);
  void LCDnoAutoscroll(void);
  void LCDcreateChar(unsigned char, unsigned char[]);
  void LCDsetCursor(unsigned char, unsigned char);

  inline void LCDcommand(unsigned char);
  inline void LCDwrite(unsigned char);
  unsigned char LCDread(void);
  unsigned char LCDbusy(void);
  unsigned char LCDaddressCounter(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

