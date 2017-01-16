

/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "LCDDriver.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"



#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>

extern void screenpage(char page,unsigned char *p,int l);
bool push=0;

unsigned char a1[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0};
unsigned char b1[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0};
unsigned char c1[]={255,255,255,255,255,255,255,255,127,31,15,15,15,143,15,15,143,207,255,255,255,127,15,15,15,15,15,63,127,255,255,31,15,15,15,63,255,255,127,31,15,15,15,255,255,255,15,15,15,15,143,143,143,143,143,159,255,255,255,255,255,255,255,255,255,255,255,255,255,255,127,15,15,15,143,143,143,15,15,63,127,255,15,15,15,15,255,255,255,255,31,15,15,15,255,255,255,15,15,15,15,143,143,143,143,143,223,255,15,15,15,15,143,143,143,143,15,15,63,255,255,255,255,255,255,255,255,0};
unsigned char d1[]={255,255,255,255,255,255,3,1,0,0,252,255,223,207,15,7,15,15,255,1,0,0,48,60,63,62,60,0,0,1,207,199,0,0,0,128,0,1,128,128,0,0,0,255,255,255,0,0,0,135,207,199,207,207,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,0,255,255,255,255,63,0,0,0,255,192,128,0,0,7,15,63,15,0,0,128,192,255,255,255,0,0,0,0,199,199,199,207,255,255,255,0,0,0,12,63,63,15,15,128,192,192,199,255,255,255,255,255,255,255,0};
unsigned char e1[]={255,255,255,255,255,255,254,252,240,192,193,231,231,231,224,192,192,226,247,224,192,224,248,254,254,254,254,224,192,192,231,226,192,192,224,255,254,254,255,224,192,192,224,255,255,255,192,192,192,231,231,231,231,199,231,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,240,224,192,199,199,231,199,231,192,224,240,255,255,255,254,248,240,224,192,240,248,254,255,255,255,255,255,192,192,192,195,199,231,231,239,239,255,255,192,224,192,228,252,240,224,192,192,193,239,255,255,255,255,255,255,255,255,0};
unsigned char f1[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0};
unsigned char g1[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0};
unsigned char h1[]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0};

	
	
unsigned char a2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char b2[]={0,0,0,0,0,0,128,192,96,32,48,16,48,48,48,48,16,240,240,240,48,16,48,48,240,240,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,128,128,0,0,0,0,0,128,128,0,128,240,240,48,16,48,48,48,48,16,48,48,96,64,192,128,128,0,128,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,240,48,48,16,48,240,240,0,0,0,0,0,0};
unsigned char c2[]={0,0,0,0,0,0,255,255,0,0,0,0,195,227,227,99,227,255,255,254,0,0,0,0,255,255,4,6,2,3,227,227,195,3,3,3,3,255,255,3,3,3,3,227,243,227,6,6,6,12,254,255,3,3,3,3,227,227,227,6,6,6,12,255,255,1,1,1,1,127,127,59,1,1,1,1,255,255,0,0,0,0,135,199,130,0,0,0,0,255,255,17,17,17,17,255,255,236,6,6,3,3,195,227,115,99,99,255,255,12,6,2,3,227,243,225,0,0,0,0,255,255,0,0,0,0,0,0};
unsigned char d2[]={0,0,0,0,0,0,63,63,56,56,56,56,63,31,0,0,0,0,63,60,56,56,56,56,63,31,12,28,56,56,56,57,56,56,56,56,56,255,255,128,128,128,128,241,249,56,56,24,28,12,255,255,128,128,128,128,240,249,56,56,24,28,12,7,7,7,6,254,252,140,140,132,128,192,192,96,127,63,56,56,56,56,56,57,56,56,24,28,12,63,63,56,56,56,56,63,63,63,56,56,56,56,63,31,0,0,0,7,7,12,28,24,56,56,57,56,56,56,56,56,63,31,0,0,0,0,0,0};
unsigned char e2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char f2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,112,240,216,152,156,156,152,254,254,254,254,254,246,226,194,210,252,220,248,240,192,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char g2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,7,7,7,7,7,7,7,7,7,7,7,3,7,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char h2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
	
	union screen {
	char a;
	struct {
		char bit1 :1;
		char bit2 :1;
		char bit3 :1;
		char bit4 :1;
		char bit5 :1;
		char bit6 :1;
		char bit7 :1;
		char bit8 :1;
	};
};


enum
{
	LINE_ONE,
	LINE_TWO,
	LINE_THREE,
	LINE_FOUR,

	LINE_NUM
}line_define;

//#define CHAR_WIDTH			8
#define WORD_WIDTH			16

#ifndef TARGET_IS_BLIZZARD_RA1
#define TARGET_IS_BLIZZARD_RA1
#endif

/***************************************************************
 * @brief	LCD模块按键响应中断 PC7 对应的为按键S1
 * @param	null
 * @return  null
***************************************************************/
extern uint8_t VCA_BUTTON_UP_DOWM;
char cur_Col = 0;
//中断处理子函数
void Int_GPIO_D_Handler(void)
{
		static bool thefirst = true;
	unsigned long ulStatus;
	// 读取中断状态
	ulStatus = GPIOIntStatus(GPIO_PORTD_BASE, true);
	// 清除中断状态
	GPIOIntClear(GPIO_PORTD_BASE, ulStatus);
	if (thefirst){
		SysTickIntEnable();          //  使能SysTick中断
		thefirst = !thefirst;
	}
	// 如果KEY的中断状态有效
	if (ulStatus & GPIO_PIN_7)
	{
		// 延时约10ms，消除按键抖动
		// 等待KEY抬起
		// 延时约10ms，消除松键抖动
		//TODO 逻辑处理
		push = 1;

	}

	if (ulStatus & GPIO_PIN_6)// 如果KEY的中断状态有效
	{
		// 延时约10ms，消除按键抖动
		SysCtlDelay(10 * (SysCtlClockGet() / 3000));
		// 等待KEY抬起
		// 延时约10ms，消除松键抖动
		//TODO 逻辑处理

	}

}
/***************************************************************
 * @brief  	初始化ADC获取滚轮电压值
 * 		————————|
//		TIVA	    |
//		M4	PE0|<--ADC		模数转换信号源
//		________|
***************************************************************/
#define ADC_BASE		ADC0_BASE			// 使用ADC0
#define SequenceNum 	3				// 使用序列3
void Init_ADCWheel(){
	// 使能ADC0外设
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	// 使能外设端口E
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	// 选择PE0为外部模拟数字转换功能
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
	// 使能采样序列号为触发处理获取模式
	ADCSequenceConfigure(ADC_BASE, SequenceNum, ADC_TRIGGER_PROCESSOR, 0);
	// ADC配置

	ADCSequenceStepConfigure(ADC_BASE, SequenceNum, 0, ADC_CTL_CH3 | ADC_CTL_IE |ADC_CTL_END);
	// 使能ADC配置
	ADCSequenceEnable(ADC_BASE, SequenceNum);
	// 清除ADC中断标志位
	ADCIntClear(ADC_BASE, SequenceNum);
}


/***************************************************************
 * @brief   获取特定ADC的模数转化采样值。
 * @param   ui32Base            ADC采样基地址
 * @param   ui32Peripheral   ADC启动的外设端口
 * @return                        ADC采样值
***************************************************************/
unsigned long ADC_ValueGet(uint32_t ui32Base, uint32_t ui32SequenceNum)
{
    unsigned long value = 0;
// 保存ADC采样值
    uint32_t ADCValue[1];
    // 触发获取端口采样
    ADCProcessorTrigger(ui32Base, ui32SequenceNum);
    //等待采样结束
    while(!ADCIntStatus(ui32Base, ui32SequenceNum, false))
    {
    }
    // 清除ADC采样中断标志
    ADCIntClear(ui32Base, ui32SequenceNum);
    // 读取ADC采样值
    ADCSequenceDataGet(ui32Base, ui32SequenceNum, ADCValue);
    value = ADCValue[0];
    return value;
}




/***************************************************************
 * @brief   刷屏函数
 * @param   二进制矩阵
 * @return   NULL                   
***************************************************************/

void screen_wape(bool pos[64][128]) {
	int m, n, i;
	unsigned char k[8][128];
	union screen a;
	for (n = 0; n < 7; n++) {
		for (m = 0; m < 128; m++) {
			a.bit1 = pos[8 * n-7+ 8][m];
			a.bit2 = pos[8 * n - 6 + 8][m];
			a.bit3 = pos[8 * n - 5 + 8][m];
			a.bit4 = pos[8 * n - 4 + 8][m];
			a.bit5 = pos[8 * n - 3 + 8][m];
			a.bit6 = pos[8 * n - 2 + 8][m];
			a.bit7 = pos[8 * n - 1 + 8][m];
			a.bit8 = pos[8 * n - 0 + 8][m];
			k[n][m] = a.a;
			

		}
		
		
	}

	screenpage(0,k[0], 128);
	screenpage(1,k[1], 128);
	screenpage(2, k[2], 128);
	screenpage(3,k[3], 128);
	screenpage(4,k[4], 128);
	screenpage(5, k[5], 128);
	screenpage(6,k[6], 128);
 //screenpage(7,k[7], 128);

}





/************************************************************
 * @brief  	对端口C、D进行按键中断初始化
 * @param	none
 * @param	none
 ***********************************************************/
void Init_Int_Key() {
	
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

	HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK)  |= GPIO_LOCK_KEY;

	HWREG(GPIO_PORTD_BASE+GPIO_O_CR)   |= (1<<7);

	HWREG(GPIO_PORTD_BASE+GPIO_O_DEN)  &=(~(1<<7));

	 HWREG(GPIO_PORTD_BASE+GPIO_O_PDR)  &= (~(1<<7));

	HWREG(GPIO_PORTD_BASE+GPIO_O_PUR)  &= (~(1<<7));

	HWREG(GPIO_PORTD_BASE+GPIO_O_AFSEL) &=(~(1<<7));

	// Make PD6/7 an output.
	
	GPIODirModeSet(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_DIR_MODE_IN);

	GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA,
			GPIO_PIN_TYPE_STD_WPU);

	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7, GPIO_LOW_LEVEL);

	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

	//IntEnable(INT_GPIOD_TM4C123);
	IntEnable(INT_GPIOD);

	IntMasterEnable();

	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
}

unsigned char director = 0;				// 当前的移动方向

extern void screenpage(char page,unsigned char *p,int l);

/************************************************************
 * @brief  	计时器中断初始化
 * @param	none
 * @param	none
 ***********************************************************/
void Int_Systick_Frequency(void) {
	
	
	SysTickPeriodSet(3000000UL);     //   设置SysTick计数器的周期值
	IntMasterEnable();          //  使能处理器中断
	SysTickEnable();          //  使能SysTick计数器
	SysTickPeriodGet();      //计时器返回值

}




static bool point[64][128];
static bool bird[64][128];
static bool terminator[64][128];
	
int main(void) {
	
	void Int_Systick_Frequency(void);
	Int_Systick_Frequency();           
	

	unsigned char old_Raw, old_Col;		// 保留上一次的位置

	unsigned char cur_Raw; 	// 记录光标当前的横坐标，纵坐标
	
	unsigned long sample;
		


	cur_Raw = 0;
	cur_Col = 0;

	// 设置系统主频
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN
							| SYSCTL_XTAL_16MHZ);

	Init_ADCWheel();

	Init_Int_Key();

	LCD_Enable();						// 使能LCD
	LCD_Init();							// 初始化LCD
	LCD_ScreenClr();					// 清屏
	IntPrioritySet(INT_GPIOD_TM4C123 , 0);
	
	screenpage(1,b2, 128);
	screenpage(2, c2, 128);
	screenpage(3,d2, 128);
	screenpage(4,e2, 128);
	screenpage(5, f2, 128);
	screenpage(6,g2, 128);
 screenpage(7,h2, 128);
 

	uint32_t i,j;
/*	for(i=0;i<=64;i++){
		for(j=0;j<=128;j++){
			point[i][j]=0;
		}
	}
	for(i=0;i<=64;i++){
		for(j=0;j<=64;j++){
			bird[i][j]=0;
		}
	}
	for(i=0;i<=64;i++){
		for(j=0;j<=64;j++){
			terminator[i][j]=0;
		}
	}*/
	
	
    *((unsigned int *)0xE000E40c) |=(1<<31)|(1<<30)|(1<<29);
	
	
		while (1)
		{
	};
}



#define BLACK 1
#define WHITE 0
#define STEP 2				
#define VACANCY 24		
#define WELL 12				
#define HIGH 50				
#define LOW 20				
#define WIETH 20			
#define JUMP 10			
uint32_t SPEED=1;				
#define BIRDY 40			


/************************************************************
 * @brief	 计时器中断函数
 *
 *@param
 *@return
 * ************************************************************/
 uint32_t record = 0,score = 0;
 int birdx=32,high,low,flag=0;over = 0,score0=-2;
 
 
void SysTick_Handler(void) {
	
	uint32_t pui32ADC0Value[1];			// 保存ADC采样值
	ADCProcessorTrigger(ADC_BASE, SequenceNum);
	// Wait for conversion to be completed.
		while(!ADCIntStatus(ADC_BASE, SequenceNum, false))
		{
		}

		// Clear the ADC interrupt flag.
		ADCIntClear(ADC_BASE, SequenceNum);

		// Read ADC Value.
		ADCSequenceDataGet(ADC_BASE, SequenceNum, pui32ADC0Value);
unsigned long sample = pui32ADC0Value[0];
		SPEED=(LCD_MAX_COL * sample) / (4096*3);
	
	
	if(over==0){
int i,j;
	 
	
	srand( (unsigned)flag );
	for(i = 0; i<=64; i++){
		for(j = 0; j<128-STEP; j++){
			point[i][j] = point[i][j+STEP];
		}
	}
	record = record%(VACANCY + WELL);
	if(record == 0){						
		high = rand()%(HIGH-LOW)+LOW;
		low = high - WIETH;
		for(i = 0;i<low-3;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
		for(i = low-3;i<low;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = BLACK;
		for(i = low;i<high;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
		for(i = high;i<=high+3;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = BLACK;
		for(i = high+3;i<=56;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;

	}
	else if(record<WELL){					
	if(record<WELL-STEP){
		for(i = 0;i<low;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = BLACK;
		for(i = low;i<high;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
		for(i = high;i<=56;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = BLACK;
	}
	else{
		for(i = 0;i<low-3;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
		for(i = low-3;i<low;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = BLACK;
		for(i = low;i<high;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
		for(i = high;i<=high+3;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = BLACK;
		for(i = high+3;i<=56;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
	}
	}
	else if(record>=WELL){
			if(record==WELL+(VACANCY-WELL)){
				score0++;
				if(score0<0)
					score=0;
				else score=score0;
			}
		for(i = 0;i<=64;i++)
			for(j=128-STEP;j<128;j++)
				point[i][j] = WHITE;
	}
	for(i = birdx-1;i<=birdx+1;i++)
		for(j = BIRDY-1;j<=BIRDY+1;j++)
			bird[i][j] = WHITE;
	if(push == 1)		{					
		birdx -= JUMP;
		push = 0;
	}
	else birdx += SPEED;
	for(i = birdx-1;i<=birdx+1;i++)
		for(j = BIRDY-1;j<=BIRDY+1;j++)
			bird[i][j] = BLACK;

	for(i=0;i<=64;i++){
		for(j=0;j<=128;j++){
			terminator[i][j]=bird[i][j]+point[i][j];
		}
	}
	record += STEP;
	flag++;
	screen_wape(terminator);
	if(point[birdx][BIRDY]==1){

		SysTickIntDisable();
		SysTickDisable();
		screenpage(0,a1, 128);
	screenpage(1,b1, 128);
	screenpage(2, c1, 128);
	screenpage(3,d1, 128);
	screenpage(4,e1, 128);
	screenpage(5, f1, 128);
	screenpage(6,g1, 128);
 screenpage(7,h1, 128);
		
	LCD_Draw_Char_8x8('S', 7, 1,1);
	LCD_Draw_Char_8x8('c', 7, 2,1);
	LCD_Draw_Char_8x8('o', 7, 3,1);
	LCD_Draw_Char_8x8('r', 7, 4,1);
	LCD_Draw_Char_8x8('e', 7, 5,1);
	LCD_Draw_Char_8x8(':', 7, 6,1);
  LCD_Draw_Num((float)(score), 0, 7,7, 1);
		return;
		
	//	over = 1;
	}
}



	
	
	LCD_Draw_Char_8x8('S', 7, 1,0);
	LCD_Draw_Char_8x8('c', 7, 2,0);
	LCD_Draw_Char_8x8('o', 7, 3,0);
	LCD_Draw_Char_8x8('r', 7, 4,0);
	LCD_Draw_Char_8x8('e', 7, 5,0);
LCD_Draw_Char_8x8(':', 7, 6,0);
 LCD_Draw_Num((float)(score), 0, 7,7, 0);
	

}
