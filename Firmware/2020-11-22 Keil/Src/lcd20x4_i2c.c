/*
 * lcd20x4_i2c.c
 *
 *  Created on: Mar 28, 2020
 *      Original Author: Mohamed Yaqoob
 *			Revised By: Joel Michaelis
 *
 */

#include "lcd20x4_i2c.h"


extern bool Keypad_IRQ;
extern bool Wheel_IRQ;



/* Private functions */
static void lcd20x4_i2c_sendCommand(uint8_t command)
{
  const uint8_t command_0_3 = (0xF0 & (command<<4));
  const uint8_t command_4_7 = (0xF0 & command);
  uint8_t i2cData[4] =
  {
      command_4_7 | LCD_EN | LCD_BK_LIGHT,
      command_4_7 | LCD_BK_LIGHT,
      command_0_3 | LCD_EN | LCD_BK_LIGHT,
      command_0_3 | LCD_BK_LIGHT,
  };
  HAL_I2C_Master_Transmit(lcd20x4_i2cHandle, LCD_I2C_SLAVE_ADDRESS, i2cData, 4, 200);
}

static void lcd20x4_i2c_sendData(uint8_t data)
{
  const uint8_t data_0_3 = (0xF0 & (data<<4));
  const uint8_t data_4_7 = (0xF0 & data);
  uint8_t i2cData[4] =
  {
      data_4_7 | LCD_EN | LCD_BK_LIGHT | LCD_RS,
      data_4_7 | LCD_BK_LIGHT | LCD_RS,
      data_0_3 | LCD_EN | LCD_BK_LIGHT | LCD_RS,
      data_0_3 | LCD_BK_LIGHT | LCD_RS,
  };
  HAL_I2C_Master_Transmit(lcd20x4_i2cHandle, LCD_I2C_SLAVE_ADDRESS, i2cData, 4, 200);
}


/**
 * @brief Initialise LCD20x4
 * @param[in] *pI2cHandle - pointer to HAL I2C handle
 */
bool lcd20x4_i2c_init(I2C_HandleTypeDef *pI2cHandle)
{
  HAL_Delay(50);
  lcd20x4_i2cHandle = pI2cHandle;
  if(HAL_I2C_IsDeviceReady(lcd20x4_i2cHandle, LCD_I2C_SLAVE_ADDRESS_0, 5, 500) != HAL_OK)
  {
    if(HAL_I2C_IsDeviceReady(lcd20x4_i2cHandle, LCD_I2C_SLAVE_ADDRESS_1, 5, 500) != HAL_OK)
    {
      return false;
    }
    else
    {
      LCD_I2C_SLAVE_ADDRESS = LCD_I2C_SLAVE_ADDRESS_1;
    }
  }
  else
  {
    LCD_I2C_SLAVE_ADDRESS = LCD_I2C_SLAVE_ADDRESS_0;
  }
  //Initialise LCD for 4-bit operation
  //1. Wait at least 15ms
  HAL_Delay(45);
  //2. Attentions sequence
  lcd20x4_i2c_sendCommand(0x30);
  HAL_Delay(5);
  lcd20x4_i2c_sendCommand(0x30);
  HAL_Delay(1);
  lcd20x4_i2c_sendCommand(0x30);
  HAL_Delay(8);
  lcd20x4_i2c_sendCommand(0x20);
  HAL_Delay(8);

  lcd20x4_i2c_sendCommand(LCD_FUNCTIONSET | LCD_FUNCTION_N);
  HAL_Delay(1);
  lcd20x4_i2c_sendCommand(LCD_DISPLAYCONTROL);
  HAL_Delay(1);
  lcd20x4_i2c_sendCommand(LCD_CLEARDISPLAY);
  HAL_Delay(3);
  lcd20x4_i2c_sendCommand(0x04 | LCD_ENTRY_ID);
  HAL_Delay(1);
  lcd20x4_i2c_sendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAY_D);
  HAL_Delay(3);

  return true;
}

/**
 * @brief Set cursor position
 * @param[in] row - 0 - 3 (4 row LCD)
 * @param[in] col - 0 - 19 (20 column LCD)
 */
void lcd20x4_i2c_setCursor(uint8_t row, uint8_t col)
{
  uint8_t maskData;
  maskData = (col)&0x0F;
  if(row==0)
  {
    maskData |= (0x80);
    lcd20x4_i2c_sendCommand(maskData);
  }
  if(row==1)
  {
    maskData |= (0xC0);
    lcd20x4_i2c_sendCommand(maskData);
  }
  if(row==2)
  {
    maskData |= (0x94);
    lcd20x4_i2c_sendCommand(maskData);
  }
  if(row==3)
  {
    maskData |= (0xD4);
    lcd20x4_i2c_sendCommand(maskData);
  }
}

/**
 * @brief Move to beginning of 1st line
 */
void lcd20x4_i2c_1stLine(void)
{
  lcd20x4_i2c_setCursor(0,0);
}
/**
 * @brief Move to beginning of 2nd line
 */
void lcd20x4_i2c_2ndLine(void)
{
  lcd20x4_i2c_setCursor(1,0);
}
/**
 * @brief Move to beginning of 3rd line
 */
void lcd20x4_i2c_3rdLine(void)
{
  lcd20x4_i2c_setCursor(2,0);
}
/**
 * @brief Move to beginning of 4th line
 */
void lcd20x4_i2c_4thLine(void)
{
  lcd20x4_i2c_setCursor(3,0);
}

/**
 * @brief Select LCD Number of lines mode
 */
void lcd20x4_i2c_TwoLines(void)
{
  lcd20x4_i2c_sendCommand(LCD_FUNCTIONSET | LCD_FUNCTION_N);
}
void lcd20x4_i2c_OneLine(void)
{
  lcd20x4_i2c_sendCommand(LCD_FUNCTIONSET);
}

/**
 * @brief Cursor ON/OFF
 */
void lcd20x4_i2c_cursorShow(bool state)
{
  if(state)
  {
    lcd20x4_i2c_sendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C | LCD_DISPLAY_D);
  }
  else
  {
    lcd20x4_i2c_sendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAY_D);
  }
}

/**
 * @brief Display clear
 */
void lcd20x4_i2c_clear(void)
{
  lcd20x4_i2c_sendCommand(LCD_CLEARDISPLAY);
  HAL_Delay(3);
}

/**
 * @brief Display ON/OFF, to hide all characters, but not clear
 */
void lcd20x4_i2c_display(bool state)
{
  if(state)
  {
    lcd20x4_i2c_sendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C | LCD_DISPLAY_D);
  }
  else
  {
    lcd20x4_i2c_sendCommand(LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C);
  }
}

/**
 * @brief Shift content to right
 */
void lcd20x4_i2c_shiftRight(uint8_t offset)
{
  for(uint8_t i=0; i<offset;i++)
  {
    lcd20x4_i2c_sendCommand(0x1c);
  }
}

/**
 * @brief Shift content to left
 */
void lcd20x4_i2c_shiftLeft(uint8_t offset)
{
  for(uint8_t i=0; i<offset;i++)
  {
    lcd20x4_i2c_sendCommand(0x18);
  }
}

/**
 * @brief Print to display
 */
void lcd20x4_i2c_printf(const char* str, ...)
{
  char stringArray[20];
  va_list args;
  va_start(args, str);
  vsprintf(stringArray, str, args);
  va_end(args);
  for(uint8_t i=0;  i<strlen(stringArray) && i<20; i++)
  {
    lcd20x4_i2c_sendData((uint8_t)stringArray[i]);
  }
}
