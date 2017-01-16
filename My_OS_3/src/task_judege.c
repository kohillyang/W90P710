/*
 * task_judege.c
 *
 *  Created on: 2015Äê1ÔÂ14ÈÕ
 *      Author: kohill
 */

#include <stdint.h>
#include <tm4c123gh6pm.h>
#include "task.h"
#include "led.h"
static uint32_t currentTask = 0;

void task_judge() {
//	ledOpen(led1);
	uint32_t next = 0;
	switch (currentTask) {
	case 0:
		currentTask = 1;
		__asm("ldr r1,=task1_sp\n"
				"ldr sp,[r1]\n"
				"mov pc,lr\n");
		break;
	case 1:
		__asm("ldr r1, =task1_sp\n");
		next = 2;
		break;
	case 2:
		__asm("ldr r1, =task2_sp\n");
		next = 3;
		break;
	case 3:
		__asm("ldr r1, =task3_sp\n");
		next = 4;
		break;
	case 4:
		__asm("ldr r1, =task4_sp\n");
		next = 1;
		break;
	}
	__asm("str r0,[r1]");
	switch (next) {
	case 1:
		currentTask = 1;
		__asm("ldr r1 ,=task1_sp\n");
		break;
	case 2:
		currentTask = 2;
		__asm("ldr r1 ,=task2_sp\n");
		break;
	case 3:
		currentTask = 3;
		__asm("ldr r1 ,=task3_sp\n");
		break;
	case 4:
		currentTask = 4;
		__asm("ldr r1 ,=task4_sp\n");
		break;
	}
	__asm(
			"ldr sp,[r1]\n"
			"mov pc,lr\n"
	);
}
;
