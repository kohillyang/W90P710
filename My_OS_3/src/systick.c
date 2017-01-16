/*
 * systick.c
 *
 *  Created on: 2015Äê1ÔÂ16ÈÕ
 *      Author: kohill
 */
#include "systick.h"
void SystickInit(uint32_t count,bool openInterrupt,bool openSystemInterrupt){
    SysTickPeriodSet(count);
    if(openInterrupt){
    	SysTickIntEnable();
    }
    if(openSystemInterrupt){
        IntMasterEnable();
    }
    SysTickEnable();
}

