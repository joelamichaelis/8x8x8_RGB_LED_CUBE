/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F46K22
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SCK1 aliases
#define SCK1_TRIS               TRISC3
#define SCK1_LAT                LATC3
#define SCK1_PORT               PORTCbits.RC3
#define SCK1_ANS                ANSC3
#define SCK1_SetHigh()    do { LATC3 = 1; } while(0)
#define SCK1_SetLow()   do { LATC3 = 0; } while(0)
#define SCK1_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCK1_GetValue()         PORTCbits.RC3
#define SCK1_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCK1_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define SCK1_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define SCK1_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set SDI1 aliases
#define SDI1_TRIS               TRISC4
#define SDI1_LAT                LATC4
#define SDI1_PORT               PORTCbits.RC4
#define SDI1_ANS                ANSC4
#define SDI1_SetHigh()    do { LATC4 = 1; } while(0)
#define SDI1_SetLow()   do { LATC4 = 0; } while(0)
#define SDI1_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDI1_GetValue()         PORTCbits.RC4
#define SDI1_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDI1_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define SDI1_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define SDI1_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set SDO1 aliases
#define SDO1_TRIS               TRISC5
#define SDO1_LAT                LATC5
#define SDO1_PORT               PORTCbits.RC5
#define SDO1_ANS                ANSC5
#define SDO1_SetHigh()    do { LATC5 = 1; } while(0)
#define SDO1_SetLow()   do { LATC5 = 0; } while(0)
#define SDO1_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define SDO1_GetValue()         PORTCbits.RC5
#define SDO1_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define SDO1_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define SDO1_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define SDO1_SetDigitalMode()   do { ANSC5 = 0; } while(0)
// get/set SCK2 aliases
#define SCK2_TRIS               TRISD0
#define SCK2_LAT                LATD0
#define SCK2_PORT               PORTDbits.RD0
#define SCK2_ANS                ANSD0
#define SCK2_SetHigh()    do { LATD0 = 1; } while(0)
#define SCK2_SetLow()   do { LATD0 = 0; } while(0)
#define SCK2_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define SCK2_GetValue()         PORTDbits.RD0
#define SCK2_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define SCK2_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define SCK2_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define SCK2_SetDigitalMode()   do { ANSD0 = 0; } while(0)
// get/set SDI2 aliases
#define SDI2_TRIS               TRISD1
#define SDI2_LAT                LATD1
#define SDI2_PORT               PORTDbits.RD1
#define SDI2_ANS                ANSD1
#define SDI2_SetHigh()    do { LATD1 = 1; } while(0)
#define SDI2_SetLow()   do { LATD1 = 0; } while(0)
#define SDI2_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define SDI2_GetValue()         PORTDbits.RD1
#define SDI2_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define SDI2_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

#define SDI2_SetAnalogMode()   do { ANSD1 = 1; } while(0)
#define SDI2_SetDigitalMode()   do { ANSD1 = 0; } while(0)
// get/set SDO2 aliases
#define SDO2_TRIS               TRISD4
#define SDO2_LAT                LATD4
#define SDO2_PORT               PORTDbits.RD4
#define SDO2_ANS                ANSD4
#define SDO2_SetHigh()    do { LATD4 = 1; } while(0)
#define SDO2_SetLow()   do { LATD4 = 0; } while(0)
#define SDO2_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define SDO2_GetValue()         PORTDbits.RD4
#define SDO2_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define SDO2_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

#define SDO2_SetAnalogMode()   do { ANSD4 = 1; } while(0)
#define SDO2_SetDigitalMode()   do { ANSD4 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/