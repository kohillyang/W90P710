/*
 * tim1.c
 *
 *  Created on: 2017年1月25日
 *      Author: kohill
 */
#include <stm32f10x.h>
void tim1_init(){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
    TIM_DeInit(TIM1);
    RCC_ClocksTypeDef clock;
    RCC_GetClocksFreq(&clock);
    TIM_TimeBaseStructure.TIM_Period=clock.PCLK2_Frequency/72/1000-1;		 								/* 自动重装载寄存器周期的值(计数值) */
		//频率的修改会引发一系列的变动
		//1.PID    //2.按键
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= 71;				    /* 时钟预分频数 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=0; 		/* 采样分频 */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);							    		/* 清除溢出中断标志 */
    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM1, ENABLE);

    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = TIM1_UP_IRQn;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&nvic);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}
#include <NRF24L01.h>
#include "cqueue.h"
void TIM1_UP_IRQHandler(){
	unsigned char buf[32];
	nrf_send_buf_deque32(buf);
	NRF_TxPacket(buf,32);
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
}


