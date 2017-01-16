/*
 * stm32f4xx_it.c
 *
 *  Created on: 2015Äê9ÔÂ10ÈÕ
 *      Author: kohill
 */

#include "stm32f4xx_it.h"
#include "kohill/fastconfig.h"


void TIM4_IRQHandler(){
	TIM_Cmd(TIM3,ENABLE);
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}
void TIM5_IRQHandler(){
	TIM_Cmd(TIM3,ENABLE);
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
}
void USART6_IRQHandler(){
	u8 c = (USART6->DR & (uint16_t)0x01FF);
	while(!(USART1->SR & USART_FLAG_TXE));
	USART1->DR = c;
	USART_ClearITPendingBit(USART6,USART_IT_RXNE);
}
void USART1_IRQHandler(){
	u8 c = (USART1->DR & (uint16_t)0x01FF);
	while(!(USART6->SR & USART_FLAG_TXE));
	USART6->DR = c;
//	while(!(USART1->SR & USART_FLAG_TXE));
//	USART1->DR = c;
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}
