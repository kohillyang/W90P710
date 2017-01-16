/*
 * task.h
 *
 *  Created on: 2015年1月14日
 *      Author: kohill
 */

#ifndef TASK_H_
#define TASK_H_
#include "stdint.h"

#define STACK_SIZE 64



/*
 * 定义函数指针类型，指针内存放的是函数的地址，在首次进入任务时需要这个地址
 */
typedef void (*TaskFunction)(void);

/*
 * 在外部定义的三个数组，用于保存任务的寄存器
 */

extern uint32_t task1_stack[STACK_SIZE];
extern uint32_t task2_stack[STACK_SIZE];
extern uint32_t task3_stack[STACK_SIZE];
extern uint32_t task4_stack[STACK_SIZE];
extern uint32_t pui32Stack[64];
/*
 * @Function setTaskN
 * 初始化堆栈指针
 */
void setTask1(TaskFunction f);
void setTask2(TaskFunction f);
void setTask3(TaskFunction f);
void setTask4(TaskFunction f);

/*
 *任务函数
 */
void led1_task();
void led2_task();
void led3_task();

/*
 * 获取下一任务的sp的值
 */
extern uint32_t getNextSp(uint32_t currentSp);

#endif /* TASK_H_ */
