#include "touch.h" 
#include "lcd.h"
#include "spi.h"
static void delay_us(unsigned int d){
	for(volatile int i=0;i<0xff;i++);;
}

u16 ADS_Read(u8 CMD)	  
{ 	 	  
	u16 Num=0,temp;  	 
	TCS_LOW; 
	SPI1_RWByte(CMD);
	delay_us(6);	 
	temp=SPI1_RWByte(0x00); 
	Num=temp<<8; 
	delay_us(1); 
	temp=SPI1_RWByte(0x00); 
	Num|=temp;  	
	Num>>=4;
	TCS_HIGH; 
	return(Num);  
} 

u16 Read_XY(u8 CMD)
{
	if (PEN_int==RESET) {
		u16 i, j;
		u16 buf[10];
		u16 sum=0;
		u16 temp;
		for(i=0;i<10;i++)buf[i]=ADS_Read(CMD);
		for(i=0;i<9; i++)
		{
			for(j=i+1;j<10;j++)
			{
				if(buf[i]>buf[j])
				{
					temp=buf[i];
					buf[i]=buf[j];
					buf[j]=temp;
				}
			}
		}
		for(i=3;i<7;i++)sum+=buf[i];
		temp=sum/(4);
		return temp;
	}
	else return 0xffff;
} 

void Touch_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//pen_int:PD3   
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_Init(GPIOG, &GPIO_InitStructure);		   
	SPI1_Init();
	CSPin_init();
}

