#include <xc.h>
#include "I2C_UTILS.h"
#include <i2c.h>
#include <pic18f2685.h>

#define SCL_TRI TRISCbits.RC3  // I2C bus
#define SDA_TRI TRISCbits.RC4  //
#define SCL_IN  PORTCbits.SCL  //
#define SDA_IN  PORTCbits.SDA  //

#define I2C_WRITE   0b11111110
#define I2C_READ    0b00000001

//SSPADD Calc : Baud = F_OSC/(4 * (SSPADD + 1))

void I2C_Init(void)
{
    SDA_TRI = 1;
    SCL_TRI = 1;
    SCL_IN = 0;
    SDA_IN = 0;

    OpenI2C(MASTER, SLEW_OFF);
    SSPADD=0x09;  // Set 100khz I2C for 4MHz clock
}



void I2C_Write_Byte_Single_Reg(unsigned char device, unsigned char info)
{
    IdleI2C();
    StartI2C();
    WriteI2C(device & I2C_WRITE);
    IdleI2C();
    WriteI2C(info);
    StopI2C();
}

unsigned char I2C_Read_Byte_Single_Reg(unsigned char device)
{
    unsigned char b = 0;

    IdleI2C();
    StartI2C();
    WriteI2C(device | I2C_READ);
    b = ReadI2C();
    //AckI2C();
    //NotAckI2C();
    StopI2C();
    return b;
}



