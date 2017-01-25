/*
 * tim1.c
 *
 *  Created on: 2017��1��25��
 *      Author: kohill
 */
#include <stm32f10x.h>
void tim1_init(){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
    TIM_DeInit(TIM1);
    RCC_ClocksTypeDef clock;
    RCC_GetClocksFreq(&clock);
    TIM_TimeBaseStructure.TIM_Period=clock.PCLK2_Frequency/72/1000-1;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
		//Ƶ�ʵ��޸Ļ�����һϵ�еı䶯
		//1.PID    //2.����
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= 71;				    /* ʱ��Ԥ��Ƶ�� 72M/72 */
    TIM_TimeBaseStructure.TIM_ClockDivision=0; 		/* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);							    		/* �������жϱ�־ */
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


