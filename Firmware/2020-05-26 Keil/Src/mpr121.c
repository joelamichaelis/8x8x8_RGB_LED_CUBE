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

//------------------- WRITE register  -------------------------
void mpr121_write(uint8_t reg,uint8_t data)
{	
	uint8_t i2cData[2] = {reg,data};
	HAL_I2C_Master_Transmit(mpr121_i2cHandle, MPR121_ADDRESS, i2cData, 2, 10); //need to figure out what to do about timeout and MPR121_ADDRESS.
}


//------------------- Read register  -------------------------
void mpr121_read(uint8_t reg,uint8_t length,uint8_t *ReturnData)
{
	
	HAL_I2C_Master_Transmit(mpr121_i2cHandle, MPR121_ADDRESS, reg, length, 10);
	//HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
	HAL_I2C_Master_Receive(mpr121_i2cHandle, MPR121_ADDRESS, *ReturnData, length, 10)
}


//------------------- read Touch  -------------------------
uint16_t mpr121_touch(void)
{
	unit8_t i2cData[2];
	uint8_t *pi2cData = &i2cData[0];
	mpr121_read(0x00, 2, pi2cData);
	return ((i2cData[1]<<8) && i2cData[0])
}


//------------------- MPR121 Config  -------------------------
void mpr121_init(I2C_HandleTypeDef *pI2cHandle){
	mpr121_i2cHandle = pI2cHandle;
	// STOP
	mpr121_write(ELE_CFG, 0x00);
    mpr121_write(RES_CF, 0X63);
    delay(10);
	// Section A
	// This group controls filtering when data is > baseline.
	mpr121_write(MHD_R, 0x01);
	mpr121_write(NHD_R, 0x01);
	mpr121_write(NCL_R, 0x00);
	mpr121_write(FDL_R, 0x00);

	// Section B
	// This group controls filtering when data is < baseline.
	mpr121_write(MHD_F, 0x01);
	mpr121_write(NHD_F, 0x01);
	mpr121_write(NCL_F, 0xFF);
	mpr121_write(FDL_F, 0x02);

	// Section C
	// This group sets touch and release thresholds for each electrode
	mpr121_write(ELE0_T, TOU_THRESH);
	mpr121_write(ELE0_R, REL_THRESH);
	mpr121_write(ELE1_T, TOU_THRESH);
	mpr121_write(ELE1_R, REL_THRESH);
	mpr121_write(ELE2_T, TOU_THRESH);
	mpr121_write(ELE2_R, REL_THRESH);
	mpr121_write(ELE3_T, TOU_THRESH);
	mpr121_write(ELE3_R, REL_THRESH);
	mpr121_write(ELE4_T, TOU_THRESH);
	mpr121_write(ELE4_R, REL_THRESH);
	mpr121_write(ELE5_T, TOU_THRESH);
	mpr121_write(ELE5_R, REL_THRESH);
	mpr121_write(ELE6_T, TOU_THRESH);
	mpr121_write(ELE6_R, REL_THRESH);
	mpr121_write(ELE7_T, TOU_THRESH);
	mpr121_write(ELE7_R, REL_THRESH);
	mpr121_write(ELE8_T, TOU_THRESH);
	mpr121_write(ELE8_R, REL_THRESH);
	mpr121_write(ELE9_T, TOU_THRESH);
	mpr121_write(ELE9_R, REL_THRESH);
	mpr121_write(ELE10_T, TOU_THRESH);
	mpr121_write(ELE10_R, REL_THRESH);
	mpr121_write(ELE11_T, TOU_THRESH);
	mpr121_write(ELE11_R, REL_THRESH);

	// Section D
	// Set the Filter Configuration
	// Set ESI2
	mpr121_write(AFE1_CFG, 0x10);
	//AFE配置1 （默认=0x10）
	//	一级采样FFI:00-6次
	//	充放电电流CDC:100000 - 32uA
	mpr121_write(AFE2_CFG, 0x04);
	//AFE配置2	（默认=0x24）
	//	充电时间CDT:010 - 1us
	//	二级采样SFI:00 - 4次
	//	二级采样间隔ESI:100 - 16ms


	// Section E
	// Electrode Configuration
	// Enable 6 Electrodes and set to run mode
	// Set ELE_CFG to 0x00 to return to standby mode
	mpr121_write(ELE_CFG, 0x8C);	// Enables all 12 Electrodes

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




//------------------- centigrade  -------------------------
int8_t mpr121_wheelKey(void)
{
      switch(touch())
      {
		case 0x0001:
			return 1;  // Electrode 0
		break;
		case 0x0003:
			return 2;  // Electrode 0 and 1
		break;
		case 0x0002:
			return 3;  // Electrode 1
		break;
		case 0x0006:
			return 4;  // Electrode 1 and 2
		break;
		case 0x0004:
			return 5;  // Electrode 2 
		break;
		case 0x000C:
			return 6;  // Electrode 2 and 3
		break;
		case 0x0008:
			return 7;  // Electrode 3 
		break;
		case 0x0018:
			return 8;  // Electrode 3 and 4
		break;
		case 0x0010:
			return 9;  // Electrode 4 
		break;
		case 0x0030:
			return 10;  // Electrode 4 and 5
		break;
		case 0x0020:
			return 11;  // Electrode 5
		break;
		case 0x0060:
			return 12;  // Electrode 5 and 6
		break;
		case 0x0040:
			return 13;  // Electrode 6
		break;
		case 0x00C0:
			return 14;  // Electrode 6 and 7
		break;
		case 0x0080:
			return 15;  // Electrode 7
		break;
		case 0x0081:
			return 16;  // Electrode 7 and 0
		break;
		case 0x0100:
			return 20;  // Electrode 8 :centre button
		break;
		default:
			return -1;  // Release
		break;		
      }
}

//------------------- centigrade  -------------------------
int8_t mpr121_keyPad(void)
{
  int var = touch();
  //Serial.println(var,HEX);
  if ((var&0x0001) >0) return 1;
  if ((var&0x0002) >0) return 4;
  if ((var&0x0004) >0) return 7;
  if ((var&0x0008) >0) return 11; // '*' key
  
  if ((var&0x0010) >0) return 2;
  if ((var&0x0020) >0) return 5;
  if ((var&0x0040) >0) return 8;
  if ((var&0x0080) >0) return 0;
  
  if ((var&0x0100) >0) return 3;
  if ((var&0x0200) >0) return 6;
  if ((var&0x0400) >0) return 9;
  if ((var&0x0800) >0) return 12; // '#' key
  
  return -1; // Release or other state
}


