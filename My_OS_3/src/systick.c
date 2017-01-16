/*
 * systick.c
 *
 *  Created on: 2015��1��16��
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

