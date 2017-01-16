/*
 * fastconfig.h
 *
 *  Created on: 2015年9月5日
 *      Author: kohill
 */

#ifndef KOHILL_FASTCONFIG_H_
#define KOHILL_FASTCONFIG_H_
#include <stm32f4xx.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#else
# define UNUSED(x) x
#endif

int k_TIM_Fast_Config(TIM_TypeDef * tim,u16 PSC,u16 ARR,bool EnableUpdateIrq);
float k_DAC_Ch2_Sin_Fast_Config(u32 fclk,u16 amp,u16 dcCmp);
int ledWrite(uint8_t c);
int k_ADC_Ch12_DMA_Fast_Config(u16 ADC_SamplePoint,u8 buffer[]);
int k_ADC_Ch12_DMA_Fast_Config_12it(u16 ADC_SamplePoint,u16 buffer[]);
int led_Init(void);
int k_USART1_Fast_Confg(u32 baudrate);
int k_USART6_Fast_Confg(u32 baudrate);
void k_TIM2_PWM_Fast_Config(void);
void k_DAC_Fast_Config(void);
//define For ADC
extern uint16_t ADC1_CH12_Sample_Point;//采样点数
extern uint8_t* ADC1_CH12_buffer_pointer;//采样缓冲区指针
void pwm_init(void);


#endif /* KOHILL_FASTCONFIG_H_ */
