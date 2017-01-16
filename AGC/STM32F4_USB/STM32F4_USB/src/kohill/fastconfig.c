/*
 * fastconfig.c
 *
 *  Created on: 2015年9月5日
 *      Author: kohill
 */
#include "fastconfig.h"

static int getMostNearMul(u32 mul,u32 *x,u32 *y){
	long mmin=65536;
	for(long i=1;i<65536;i++){
		long _mul = (long)mul;
		long div = _mul/i;
		if(labs(_mul-div) < mmin && div <65566){
			*x =(u32) i;
			*y = (u32)div;
			mmin = labs(_mul-div);
		}
	}


}
/*
 * Note:适用于”一键“打开时基单元
 * 函数功能：设置定时器：开启时钟，设置周期，打开update中断
 * 参数：tim 可以为TIM1-TIM14
 * 		period ，周期，从0-0xffffffff,注意TIM1和TIM8与其他定时器的时钟不相同
 * 		EnableUpdateIrq ，置false则不开启update中断
 * 返回值：正常返回0，参数不对时返回-1
 */
int k_TIM_Fast_Config(TIM_TypeDef * tim,u16 PSC,u16 ARR,bool EnableUpdateIrq){
	IRQn_Type irq = 0;
	TIM_DeInit(tim);
	switch((u32)tim){
		case (u32)TIM1:RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);irq = TIM1_UP_TIM10_IRQn;break;
		case (u32)TIM2:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);irq = TIM2_IRQn;break;
		case (u32)TIM3:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);irq = TIM3_IRQn;break;
		case (u32)TIM4:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);irq= TIM4_IRQn;break;
		case (u32)TIM5:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);irq = TIM5_IRQn;break;
		case (u32)TIM6:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);irq = TIM6_DAC_IRQn;break;
		case (u32)TIM7:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);irq = TIM7_IRQn;break;
		case (u32)TIM8:RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);irq = TIM8_UP_TIM13_IRQn;break;
		case (u32)TIM9:RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);irq = TIM1_BRK_TIM9_IRQn;break;
		case (u32)TIM10:RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);irq = TIM1_UP_TIM10_IRQn;break;
		case (u32)TIM11:RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);irq = TIM1_TRG_COM_TIM11_IRQn;break;
		case (u32)TIM12:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);irq = TIM8_BRK_TIM12_IRQn;break;
		case (u32)TIM13:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);irq = TIM8_UP_TIM13_IRQn;break;
		case (u32)TIM14:RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);break;
		default:assert_param(IS_TIM_ALL_PERIPH(tim));return -1;
	}
	TIM_TimeBaseInitTypeDef timBase = {
		.TIM_ClockDivision = TIM_CKD_DIV1,
		.TIM_CounterMode = TIM_CounterMode_Up,
		.TIM_Period = ARR,
		.TIM_Prescaler = PSC,
		.TIM_RepetitionCounter = 0
	};
	TIM_TimeBaseInit(tim,&timBase);
	if(EnableUpdateIrq){
		NVIC_InitTypeDef nvic= {
				.NVIC_IRQChannel = irq,
				.NVIC_IRQChannelCmd = ENABLE,
				.NVIC_IRQChannelPreemptionPriority = 0,
				.NVIC_IRQChannelSubPriority = 0
		};
		NVIC_Init(&nvic);
		TIM_ITConfig(tim,TIM_IT_Update,ENABLE);
	}
	return 0;
}

/*
 * Note：适用于从PA5（DAC CH2）快速产生指定频率，指定幅度，指定直流分量的正弦波
 * Note:DAC会占用DAC_Trigger_T8_TRGO，定时器8的时钟频率要与系统时钟一致
 * 函数功能：通过DAC通道产生正弦波
 * 参数：freq，输出的正弦波频率，频率变高的时候点数会减少，范围为1HZ-50kHZ
 * 		fclkActual:存储设置频率的实际值，在高频的时候由于时钟的关系，频率会有误差，误差值可由fclk-fclkActual算出
 * Todo:DAC的转换速率最高也就300多k，依据负载不同有所变化，这里设置的定时器的最高触发频率为512KHZ，保证在10kHZ的时候点数有512个点
 */

float k_DAC_Ch2_Sin_Fast_Config(u32 fclk,u16 amp,u16 dcCmp){
	uint32_t DAC_DHR12R2_ADDRESS  = 0x40007414;
	static u16 sine12bit[4096];

	DMA_InitTypeDef DMA_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_ClocksTypeDef rccf;
	RCC_GetClocksFreq(&rccf);
	/*计算点数与触发周期*/
	int points = 0;
	int triggerPeriod = 0;
	points = 512000/fclk;
	if(points ==0){
		return -1;
	}

	if(points>4096)	points = 4096;
//	points = (points<rccf.HCLK_Frequency/256000)?(rccf.HCLK_Frequency/256000):points;//确保不超出DAC转换最大速率
	triggerPeriod =rccf.SYSCLK_Frequency/points/fclk-1;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*设置GPIO，PA5，模拟引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T8_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude =DAC_TriangleAmplitude_4095;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	/* DMA1_Stream6 channel7 configuration **************************************/
	DMA_DeInit(DMA1_Stream6);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) DAC_DHR12R2_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) &sine12bit;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = points;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);

	/* Enable DMA1_Stream6 */
	DMA_Cmd(DMA1_Stream6, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = triggerPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

	/* TIM6 TRGO selection */
	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Update);
#include <math.h>
	for (int i = 0; i < points; i++) {
		float val = sin(1.0f * i / points * 2 * 3.141592654f)*amp + dcCmp;
		sine12bit[i] = (u16)(val>0?val:0);
	}
	TIM_Cmd(TIM8, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);
	DAC_DMACmd(DAC_Channel_2, ENABLE);
	return 1.0f*rccf.HCLK_Frequency/(TIM8->ARR+1);
}


/*
 * ADC1，通道13，定时器3触发，8位，默认采样率2MHZ,DMA2 Stream0中断，需要从外部打开定时器
 * GPIO口为GPIOC PC2
 * 参数说明：ADC_SamplePoint采样点数
 * 			buffer：用于存储ADC采样的数据,buffer长度需要大于ADC_SamplePoint+4
 */
//供外部访问的变量
uint16_t ADC1_CH12_Sample_Point = 0;//采样点数
uint8_t* ADC1_CH12_buffer_pointer = NULL;//采样缓冲区指针
int k_ADC_Ch12_DMA_Fast_Config(u16 ADC_SamplePoint,u8 buffer[]) {
	ADC1_CH12_Sample_Point = ADC_SamplePoint;
	ADC1_CH12_buffer_pointer = &buffer[0];
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Configure ADC Channel 12 pin as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* DMA2 Stream0 channel0 configuration */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) &(ADC1->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr =
			(uint32_t) &buffer[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = ADC_SamplePoint+4;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
	NVIC_InitTypeDef nvic = { .NVIC_IRQChannel = DMA2_Stream0_IRQn,
			.NVIC_IRQChannelCmd = ENABLE,
			.NVIC_IRQChannelPreemptionPriority = 0,
			.NVIC_IRQChannelSubPriority = 0 };
	NVIC_Init(&nvic);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_6Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge =ADC_ExternalTrigConvEdge_Falling;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	TIM_TimeBaseInitTypeDef time;
	time.TIM_ClockDivision = TIM_CKD_DIV1;
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_Period = ((u16)144/3) - 1;
	time.TIM_Prescaler = 0;
	time.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &time);
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	return  0;
}
uint16_t ADC1_CH12_Sample_Point_12bit = 0;//采样点数
uint16_t* ADC1_CH12_buffer_pointer_12bit = NULL;//采样缓冲区指针

int k_ADC_Ch12_DMA_Fast_Config_12it(u16 ADC_SamplePoint,u16 buffer[]) {
	ADC1_CH12_Sample_Point_12bit = ADC_SamplePoint;
	ADC1_CH12_buffer_pointer_12bit = &buffer[0];
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* Configure ADC Channel 12 pin as analog input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* DMA2 Stream0 channel0 configuration */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) &(ADC1->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr =
			(uint32_t) &buffer[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = ADC_SamplePoint;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
	NVIC_InitTypeDef nvic = { .NVIC_IRQChannel = DMA2_Stream0_IRQn,
			.NVIC_IRQChannelCmd = ENABLE,
			.NVIC_IRQChannelPreemptionPriority = 3,
			.NVIC_IRQChannelSubPriority = 3 };
	NVIC_Init(&nvic);
	nvic.NVIC_IRQChannel = SysTick_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0;
	nvic.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic);

	DMA_Cmd(DMA2_Stream0, ENABLE);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge =ADC_ExternalTrigConvEdge_Falling;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	TIM_TimeBaseInitTypeDef time;
	time.TIM_ClockDivision = TIM_CKD_DIV1;
	time.TIM_CounterMode = TIM_CounterMode_Up;
	time.TIM_Period = 1;
	time.TIM_Prescaler = SystemCoreClock/200000-1;
	time.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &time);
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);


	ADC_Cmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	return  0;
}

/*
 * Function:LED灯GPIO初始化
 */
int  led_Init() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &gpio);
	return 0;
}
int ledWrite(uint8_t c) {
	if (c) {
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
	} else {
		GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
	}
	return c;
}
/*
 * Note:适用于”一键“ 开启USART1
 * 返回值：始终为0
 */
int k_USART1_Fast_Confg(u32 baudrate){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&gpio);
	USART_InitTypeDef usart;
	usart.USART_BaudRate =baudrate;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx |  USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_DeInit(USART1);
	USART_Init(USART1,&usart);
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = USART1_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvic);
	return 0;
}
//PC6 :Tx
//PC7: RX
int k_USART6_Fast_Confg(u32 baudrate){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&gpio);
	USART_InitTypeDef usart;
	usart.USART_BaudRate =baudrate;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart.USART_Mode = USART_Mode_Rx |  USART_Mode_Tx;
	usart.USART_Parity = USART_Parity_No;
	usart.USART_StopBits = USART_StopBits_1;
	usart.USART_WordLength = USART_WordLength_8b;
	USART_DeInit(USART6);
	USART_Init(USART6,&usart);
	USART_Cmd(USART6,ENABLE);
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = USART6_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvic);
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
//	DMA_InitTypeDef dma;
//	dma.DMA_BufferSize = 1;
//	dma.DMA_Channel = DMA_Channel_5;
//	dma.DMA_DIR = DMA_DIR_MemoryToMemory;
//	dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
//	dma.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//	dma.DMA_Memory0BaseAddr = (uint32_t)&(USART6->DR);
//	dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
//	dma.DMA_MemoryInc = DMA_MemoryInc_Disable;
//	dma.DMA_Mode = DMA_Mode_Circular;
//	dma.DMA_PeripheralBaseAddr = (uint32_t)(&(USART1->DR));
//	dma.DMA_PeripheralBurst = DMA_PeripheralBurst_INC16;
//	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	dma.DMA_Priority = DMA_Priority_High;
//	DMA_Init(DMA2_Stream2,&dma);
//	DMA_Cmd(DMA2_Stream2,ENABLE);
//	USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE);

	return 0;
}
void k_TIM2_PWM_Fast_Config(void){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_OD;
	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);

	k_TIM_Fast_Config(TIM2, 0,1680, false);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	uint16_t CCR1_Val = 0;
	uint16_t CCR2_Val = 0;
	uint16_t CCR3_Val = 1550;
	uint16_t CCR4_Val = 1550;
	uint16_t PrescalerValue = 0;

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel4 */
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);

	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM2, ENABLE);

	/* TIM3 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}
void k_DAC_Fast_Config(){

	DAC_InitTypeDef DAC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/*计算点数与触发周期*/

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*设置GPIO，PA5，模拟引脚*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude =DAC_TriangleAmplitude_4095;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	/* TIM6 TRGO selection */
	DAC_Cmd(DAC_Channel_2, ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);

}

