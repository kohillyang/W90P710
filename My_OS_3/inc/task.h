/*
 * task.h
 *
 *  Created on: 2015��1��14��
 *      Author: kohill
 */

#ifndef TASK_H_
#define TASK_H_
#include "stdint.h"

#define STACK_SIZE 64



/*
 * ���庯��ָ�����ͣ�ָ���ڴ�ŵ��Ǻ����ĵ�ַ�����״ν�������ʱ��Ҫ�����ַ
 */
typedef void (*TaskFunction)(void);

/*
 * ���ⲿ������������飬���ڱ�������ļĴ���
 */

extern uint32_t task1_stack[STACK_SIZE];
extern uint32_t task2_stack[STACK_SIZE];
extern uint32_t task3_stack[STACK_SIZE];
extern uint32_t task4_stack[STACK_SIZE];
extern uint32_t pui32Stack[64];
/*
 * @Function setTaskN
 * ��ʼ����ջָ��
 */
void setTask1(TaskFunction f);
void setTask2(TaskFunction f);
void setTask3(TaskFunction f);
void setTask4(TaskFunction f);

/*
 *������
 */
void led1_task();
void led2_task();
void led3_task();

/*
 * ��ȡ��һ�����sp��ֵ
 */
extern uint32_t getNextSp(uint32_t currentSp);

#endif /* TASK_H_ */
