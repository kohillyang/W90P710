/******************************************************************************/
/* IRQ.C: IRQ Handlers                                                        */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2008 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include "710defs.h"               /* Winbond W90P710 definitions        */
#include "../system/rtc/rtc.h"

unsigned long ticks = 0;
unsigned char Clock100ms;
unsigned char Clock1s;
uint32_t tick_time = 0;
/* Common interrupt handler, handles all interrupts                           */
__attribute__ ((interrupt ("IRQ")))
void IRQ_Handler(void) {
	volatile int x = REG_AIC_IPER;   
	switch (REG_AIC_ISNR & 0x1F) {
	case IRQ_TIMER1: /* Timer 0 interrupt index            */
		if (!((ticks++ ^ 9) & 0x0F)) { /* Set Clock100ms to 1 every 100 ms   */
			ticks &= ~0x0F;
			ticks += 0x10;
			Clock100ms = 1;
		}
		if (ticks >= (10 << 4)) { /* Set Clock1s to 1 every 1 second    */
			ticks = 0;
			Clock1s = 1;
			tick_time ++;
		}
		REG_TISR = 2; /* Clear Timer 1 interrupt status     */
		REG_AIC_SCCR = 1<<IRQ_TIMER1;
		break;
	case 29:
		key_exec();
		REG_AIC_SCCR = 1<<29;
		break;
	case IRQ_RTC:
		REG_AIC_SCCR = 1<<IRQ_RTC;
		REG_RTC_RIIR = 0x00;
;
		break;
	default:
	break;
	}
	REG_RTC_RIER = 0x0;
	REG_AIC_EOSCR = 0; /* End of interrupt service routine   */
}
#include <time.h>

time_t time(time_t *t){
	if(t!=0){
		*t = tick_time;
	}
	return  tick_time;
}
void setTime_t(time_t tm){
	tick_time = tm;
}

