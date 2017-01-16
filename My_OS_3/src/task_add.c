/*
 * task_add.c
 *
 *  Created on: 2015Äê1ÔÂ14ÈÕ
 *      Author: kohill
 */
#include <stdint.h>
#include <stdlib.h>
#include "task.h"
typedef struct {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t pc;
} InitialStack;

uint32_t task1_stack[STACK_SIZE];
uint32_t task2_stack[STACK_SIZE];
uint32_t task3_stack[STACK_SIZE];


void setTask1(TaskFunction f) {
	task1_stack[STACK_SIZE - 1] = task1_stack + STACK_SIZE - 13;
	task1_stack[STACK_SIZE - 2]=0x1000000;
	task1_stack[STACK_SIZE - 3] = f;
}

void setTask2(TaskFunction f) {
	task2_stack[STACK_SIZE - 1] = task2_stack + STACK_SIZE - 13;
	task2_stack[STACK_SIZE - 2]=0x1000000;
	task2_stack[STACK_SIZE - 3] = f;
}

void setTask3(TaskFunction f) {
	task3_stack[STACK_SIZE - 1] = task3_stack + STACK_SIZE - 13;
	task3_stack[STACK_SIZE - 2]=0x1000000;
	task3_stack[STACK_SIZE - 3] = f;
}

