/*
 * getNextSp.c
 *
 *  Created on: 2015年1月17日
 *      Author: kohill
 */
#include "task.h"
#include <tm4c123gh6pm.h>
extern void taskSwitchAsm(void);


uint32_t getAddress(){
	volatile uint32_t a = (*((volatile uint32_t *)(0xE000E000+0x10)));
	return (uint32_t)taskSwitchAsm;
}

uint32_t getNextSp(uint32_t currentSp) {

//读取systick标志位：
	volatile uint32_t a = NVIC_ST_CTRL_R;
	if ((currentSp > (uint32_t)task1_stack)
			&& (currentSp <(uint32_t) (task1_stack + STACK_SIZE - 1))) {
		task1_stack[STACK_SIZE - 1] = currentSp;
		return task2_stack[STACK_SIZE - 1];
	}
	else if ((currentSp > (uint32_t)task2_stack)
			&& (currentSp < (uint32_t)(task2_stack + STACK_SIZE - 1))) {
		task2_stack[STACK_SIZE - 1] = currentSp;
		return task3_stack[STACK_SIZE - 1];
	}
	else if ((currentSp > (uint32_t)task3_stack)
			&& (currentSp < (uint32_t)(task3_stack + STACK_SIZE - 1))) {
		task3_stack[STACK_SIZE - 1] = currentSp;
		return task1_stack[STACK_SIZE - 1];
	}
	else {
		pui32Stack[63] = currentSp;
		return task1_stack[STACK_SIZE-1];
	}
}
