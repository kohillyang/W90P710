/*
 ============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C
 ============================================================================
 */

#include <stdio.h>
#include "GLCD.h"
/*
 *
 * Print a greeting message on standard output and exit.
 *
 * On embedded platforms this might require semi-hosting or similar.
 *
 * For example, for toolchains derived from GNU Tools for Embedded,
 * to enable semi-hosting, the following was added to the linker:
 *
 * --specs=rdimon.specs -Wl,--start-group -lgcc -lc -lc -lm -lrdimon -Wl,--end-group
 *
 * Adjust it for other toolchains.
 *
 */

void Set_EBILED(int x){
	return;
}
/*
 * COPYRIGHT:       BSD, see COPYING.ARM in the top level directory
 * PROJECT:         ReactOS crt library
 * FILE:            lib/sdk/crt/math/arm/__rt_udiv.c
 * PURPOSE:         Implementation of __rt_udiv
 * PROGRAMMER:      Timo Kreuzer
 * REFERENCE:       http://research.microsoft.com/en-us/um/redmond/projects/invisible/src/crt/md/arm/_div10.s.htm
 *                  http://research.microsoft.com/en-us/um/redmond/projects/invisible/src/crt/md/arm/_udiv.c.htm
 */

typedef struct _ARM_UDIVRESULT
{
    unsigned int quotient; /* to be returned in R0 */
    unsigned int modulus;  /* to be returned in R1 */
} ARM_UDIVRESULT;

//__forceinline
//void
//__brkdiv0(void)
//{
//    __emit(0xDEF9);
//}

//void __rt_udiv(){
//	register unsigned int  r0 asm("r0");
//	register unsigned int  r1 asm("r1");
//	r0 = r1/r0;
//	r1 = r1%r0;
//}

void Delay (int x){
	for(int xx = 0;xx<x;xx++);
}
void Audio_Test(void);
#include "GLCD.h"
#define LED_NUM     8                   /* Number of user LEDs                */
#define LED8        (1 << 0)            /* LED8                               */
#define LED9        (1 << 1)            /* LED9                               */
#define LED10       (1 << 2)            /* LED8                               */
#define LED11       (1 << 3)            /* LED8                               */
#define LED12       (1 << 4)            /* LED8                               */
#define LED13       (1 << 5)            /* LED8                               */
#define LED14       (1 << 6)            /* LED8                               */
#define LED15       (1 << 7)            /* LED8                               */
#define LED_ALL     (LED8  |LED9  |     /* Mask of all LEDs                  */\
                     LED10 |LED11 |\
                     LED12 |LED13 |\
                     LED14 |LED15 )
extern const unsigned char gImage_pic4[153600];
#include <GUI.h>
#include <WM.h>
#include <time.h>
#include "W90P710.h"
static const int keytable[16] = {
		'+', '-', 'x', '0',
		'2','5', '8', GUI_KEY_ENTER,
		'3', '6', '9',' ',
		'1', '4', '7',GUI_KEY_BACKSPACE
};
#include "../system/rtc/rtc.h"
void user_init(void){
	GUI_Init();
	GUI_Clear();
	WM_HWIN CreateFramewin(void);
	CreateFramewin();
	m_rtc_init();
	KPIInit();
	REG_AIC_MECR = 1<<29;
	REG_AIC_MECR = 1<<IRQ_RTC;
}
void user_exec(void){
	GUI_Exec();
	WM_Exec();
	extern int key_flag;
	LineEditSetText(m_rtc_read());
	if(key_flag & (1<<5)){
		GUI_SendKeyMsg(keytable[(key_flag & 0x0f)],1);
		key_flag = 0;
	}
}



int main(){
#define Reg8(adr)  (*((volatile unsigned char  *) (adr)))

	Reg8(0x78000000) = LED_ALL;
	REG_TCR1  = 0xAC000000 + (15-1);      /* Dbg, IE, period mode, rst, prsc=80 */
	REG_TCR1  = 0xA8000000 + (15-1);      /* Dbg, IE, period mode,      prsc=80 */
	REG_TICR1 = (15000000 / (15 * 100));  /* Reload value=15MHz/(prescaler*100) */
	REG_TCR1 |= (1 << 30);                /* Start Timer 1                      */

	/* Setup AIC for Timer1 interrupt                                           */
	REG_AIC_SCR14 = (1 << 6) | 1;         /* Int trig on high level, priority 1 */
	REG_AIC_TEST  =  1;                   /* Enable Debugging of AIC            */
	REG_AIC_MECR  = (1 << IRQ_TIMER1);    /* Enable Timer 1 interrupt           */
	GLCD_init();
	GLCD_bitmap(0,0,320,240,gImage_pic4);
	user_init();
	int RTC_Test(int rtctest);
	RTC_Test(0);
	while(1){
		user_exec();
	}
}
