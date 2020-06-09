/* 
 * File:   DELAY.h
 * Author: Win 7
 *
 * Created on 30 September 2014, 22:05
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif


void DELAY_Init(void);
void DelayMicroseconds(unsigned short delayTime);
void DelayMilliseconds(unsigned short delayTime);


#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

