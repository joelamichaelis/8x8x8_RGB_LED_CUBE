#include <xc.h>
#include <limits.h>
#include "DELAY.h"


void DELAY_Init(void)
{
    T1CONbits.RD16 = 1; // Put the TIMER1 Reg into 16bit write mode
    T1CONbits.T1RUN = 0;
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1OSCEN = 0;
    //T1CONbits.NOT_T1SYNC = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 0;
}



void DelayMicroseconds(unsigned short delayTime)
{
    T1CONbits.TMR1ON = 0;
    TMR1 = (unsigned short) (USHRT_MAX - delayTime);
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 1;
    while (!PIR1bits.TMR1IF);
    T1CONbits.TMR1ON = 0;
}


void DelayMilliseconds(unsigned short delayTime)
{
    T1CONbits.TMR1ON = 0;
    for (unsigned short x = 0; x < delayTime; x++)
    {
        TMR1 = (unsigned short) (USHRT_MAX - 1000);
        PIR1bits.TMR1IF = 0;
        T1CONbits.TMR1ON = 1;
        while (!PIR1bits.TMR1IF);
        T1CONbits.TMR1ON = 0;
    }
}
