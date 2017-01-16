/*
 * board.c
 *
 *  Created on: 2016年1月12日
 *      Author: kohill
 */


/*
 * 	PB10:SCL PB11:SDA
 */
#include "myiic.h"
#include "board.h"
static int uart0_put_string(const char *p);
int k_INA226_Fast_Config(void){

	IIC_Init();
	return 0;
}
//FEH
#define SLAVE_ADDR (0x40<<1)
int k_INA226_SetRegPointer(u8 p){
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDR | 0x00);
	if(IIC_Wait_Ack()){
		while(1);
	};
	IIC_Send_Byte(p);
	if(IIC_Wait_Ack()){
		while(1);
	};
	IIC_Stop();
	return 0;
}
u16 k_INA226_ReadReg(){


	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDR | 0x01);
	if(IIC_Wait_Ack()){
		while(1);
	};
	u16 M = IIC_Read_Byte(1);
	u16 L = IIC_Read_Byte(0);
	IIC_Stop();
	return  (0xFF00 &(M<<8))|L;
}
int k_INA226_WriteReg(u8 regAddr,u16 data){
	IIC_Start();
	IIC_Send_Byte(SLAVE_ADDR | 0x00);
	if(IIC_Wait_Ack()){
		while(1);
	};
	IIC_Send_Byte(regAddr);
	if(IIC_Wait_Ack()){
		while(1);
	};
	IIC_Send_Byte((u8)(data >> 8));
	if(IIC_Wait_Ack()){
		while(1);
	};
	IIC_Send_Byte((u8)(data));
	if(IIC_Wait_Ack()){
		while(1);
	};
	IIC_Stop();
	return  0;
}
//单位：mA
float k_read_current(void){
	k_INA226_SetRegPointer(0x01);
	return 2.5f*(s16)k_INA226_ReadReg()/10;
}
//单位mV
float k_read_Voltage(void){
	k_INA226_SetRegPointer(0x02);
	return 1.25f*k_INA226_ReadReg();
}
#include <string.h>
static int uart0_put_string(const char *p){
	int n_byte = strlen(p);
	for(int i = 0;i<n_byte;i++){
		while(!(USART1->SR & USART_FLAG_TXE));
			USART1->DR = p[i];
	}
	return n_byte;
}
#define WIFI_AT uart0_put_string
#include <GUI.h>
void k_wifi_init(void);
void k_wifi_init(void){
	GUI_Delay(100);
	WIFI_AT("AT+CWMODE=1\r\n");//Statin Mode.
	GUI_Delay(100);
	WIFI_AT("AT+CWJAP=\"lie\",\"1234567890\"\r\n");
	GUI_Delay(1000);


}
void pwm_init(void){
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;
	gpio.GPIO_Speed =GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio);

}

