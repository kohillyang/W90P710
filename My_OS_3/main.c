//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2022-2024 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.2.0.22573 of the EK-TM4C223GXL Firmware Package.
//
//*****************************************************************************

#include "public_header.h"
#include "led.h"
#include "task.h"
#include "systick.h"

void Led_handler() {
	static bool isOpen = false;
	if (!isOpen) {
//		ledOpen(green);
		isOpen = true;
	} else {
		ledClose(green);
		isOpen = false;
	}
}
int main(void) {
	led_init();
	setTask1(led1_task);
	setTask2(led2_task);
	setTask3(led3_task);
	IntMasterEnable();
	SystickInit(SysCtlClockGet()*2, true, true);
	while (1)
	;
}
