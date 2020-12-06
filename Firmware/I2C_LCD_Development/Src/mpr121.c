/**
 * MPR121 Library
 *
 * created on: 12/09/18
 * Version: 1.0
 *   
 * Copyright 2012 Waiman Zhao <Binpower@foxmail.com> 
 * Based on previous work by:
 *    Weibo: <http://weibo.com/binpower>
 *    QQ: <93242033>
 *		TaoBao: <http://waiman.taobao.com/>
*/




#include "mpr121.h"
#include "stm32f1xx_hal.h"


//------------------- WRITE register  -------------------------
void mpr121_write(I2C_HandleTypeDef *hi2c, uint8_t mpr121Address, uint8_t reg,uint8_t data)
{	
	uint8_t i2cData[2] = {reg,data};
	HAL_I2C_Master_Transmit(hi2c, mpr121Address, i2cData, 2, 10); //need to figure out what to do about timeout and mpr121Address.
}



/**
 * @brief read register data from mpr121
 * @param[in] mpr121Address - i2c address
 * @param[in] reg - starting register address to read from.
 * @param[in] length - how many bytes to read.
 * @param[in] ReturnData - points to the data location.
 */
void mpr121_read(I2C_HandleTypeDef *hi2c, uint8_t mpr121Address, uint8_t reg,uint8_t length,uint8_t *ReturnData)
{
	HAL_I2C_Mem_Read(hi2c, mpr121Address, reg, length, ReturnData, length, 10);
}


//------------------- read Touch  -------------------------
uint16_t mpr121_touch(I2C_HandleTypeDef *hi2c, uint8_t mpr121Address)
{
	uint8_t i2cTouchData[2] = {0x00, 0x00};
	uint8_t *pi2cData = &i2cTouchData[0];
	mpr121_read(hi2c, mpr121Address, 0x00, 2, pi2cData);
	uint16_t retVal = ((i2cTouchData[1]<<8) | i2cTouchData[0]);
	return retVal;
}


//------------------- MPR121 Config  -------------------------
void mpr121_init(I2C_HandleTypeDef *hi2c, uint8_t mpr121Address, I2C_HandleTypeDef *pI2cHandle){

	// STOP
	mpr121_write(hi2c, mpr121Address, ELE_CFG, 0x00);
  mpr121_write(hi2c, mpr121Address, RES_CF, 0X63);
  HAL_Delay(10);
	
	// Section A
	// This group controls filtering when data is > baseline.
	mpr121_write(hi2c, mpr121Address, MHD_R, 0x01);
	mpr121_write(hi2c, mpr121Address, NHD_R, 0x01);
	mpr121_write(hi2c, mpr121Address, NCL_R, 0x00);
	mpr121_write(hi2c, mpr121Address, FDL_R, 0x00);

	// Section B
	// This group controls filtering when data is < baseline.
	mpr121_write(hi2c, mpr121Address, MHD_F, 0x01);
	mpr121_write(hi2c, mpr121Address, NHD_F, 0x01);
	mpr121_write(hi2c, mpr121Address, NCL_F, 0xFF);
	mpr121_write(hi2c, mpr121Address, FDL_F, 0x02);

	// Section C
	// This group sets touch and release thresholds for each electrode
	mpr121_write(hi2c, mpr121Address, ELE0_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE0_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE1_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE1_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE2_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE2_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE3_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE3_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE4_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE4_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE5_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE5_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE6_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE6_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE7_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE7_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE8_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE8_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE9_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE9_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE10_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE10_R, REL_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE11_T, TOU_THRESH);
	mpr121_write(hi2c, mpr121Address, ELE11_R, REL_THRESH);

	// Section D
	// Set the Filter Configuration
	// Set ESI2
	mpr121_write(hi2c, mpr121Address, AFE1_CFG, 0x10);
	//AFE配置1 （默认=0x10）
	//	一级采样FFI:00-6次
	//	充放电电流CDC:100000 - 32uA
	mpr121_write(hi2c, mpr121Address, AFE2_CFG, 0x04);
	//AFE配置2	（默认=0x24）
	//	充电时间CDT:010 - 1us
	//	二级采样SFI:00 - 4次
	//	二级采样间隔ESI:100 - 16ms


	// Section E
	// Electrode Configuration
	// Enable 6 Electrodes and set to run mode
	// Set ELE_CFG to 0x00 to return to standby mode
	mpr121_write(hi2c, mpr121Address, ELE_CFG, 0x8C);	// Enables all 12 Electrodes

	//AFE配置1
	//	CL
	//	ELEPROX
	//	ELE:
	// Section F
	// Enable Auto Config and auto Reconfig
	/*mpr121_write(ATO_CFG0, 0x0B);
	mpr121_write(ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   mpr121_write(ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
	mpr121_write(ATO_CFGT, 0xB5);*/	// Target = 0.9*USL = 0xB5 @3.3V
}




char mpr121_wheel(I2C_HandleTypeDef *hi2c, uint8_t mpr121Address, char prevDir)
{
	uint16_t var = mpr121_touch(hi2c, mpr121Address);  
	
	if 			((var==0x0001)|(var==0x0003)|(var==0x0081)|(var==0x0083)) return 'S';	//South
	else if ((var==0x0004)|(var==0x0006)|(var==0x000C)|(var==0x000E)) return 'W';	//West
	else if ((var==0x0010)|(var==0x0018)|(var==0x0030)|(var==0x0038)) return 'N';	//North
	else if ((var==0x0040)|(var==0x0060)|(var==0x00C0)|(var==0x00E0)) return 'E';	//East
	return prevDir;
	
	/* previous methodology 
	if (var == 0x0001) return 0;	//pin 0, wheel #0
	if (var == 0x0002) return 1;	//pin 1, wheel #1
	if (var == 0x0004) return 2;	//pin 2, wheel #2
	if (var == 0x0008) return 3;	//pin 3, wheel #3
  if (var == 0x0010) return 4;	//pin 4, wheel #4
	if (var == 0x0020) return 5;	//pin 5, wheel #5
	if (var == 0x0040) return 6;	//pin 6, wheel #6
	if (var == 0x0080) return 7;	//pin 1, wheel #7
  if (var == 0x0100) return 8; 	//pin 8, wheel center
	if (var == 0x0000) return 9;	//arbitrary value. Indicates an valid combination.
	return 9;
	*/
}

//------------------- centigrade  -------------------------
uint8_t mpr121_keyPad(I2C_HandleTypeDef *hi2c, uint8_t mpr121Address)
{
  uint16_t var = mpr121_touch(hi2c, mpr121Address);
  
  if (var == 0x0001) return 1;
	if (var == 0x0002) return 4;
	if (var == 0x0004) return 7;
	if (var == 0x0008) return 10;		// '*' on keypad
	
  if (var == 0x0010) return 2;
	if (var == 0x0020) return 5;
	if (var == 0x0040) return 8;
	if (var == 0x0080) return 11;		// '0' on keypad
	
  if (var == 0x0100) return 3;
	if (var == 0x0200) return 6;
	if (var == 0x0400) return 9;
	if (var == 0x0800) return 12;		// '12' on keypad	

	if (var == 0x0000) return 0;	
	
	return 0;
}


