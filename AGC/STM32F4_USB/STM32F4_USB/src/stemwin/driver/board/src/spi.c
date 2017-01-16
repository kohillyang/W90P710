#include "spi.h"

void SPI1_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB ,ENABLE);
  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI1);
  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI1);
  	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI1);
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	SPI_I2S_DeInit(SPI2);
  	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//ȫ˫��
  	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//8λ����ģʽ
  	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//����ģʽ��SCKΪ1
  	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//���ݲ����ӵ�2��ʱ����ؿ�ʼ
  	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//NSS�������
  	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//������
  	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ģʽ
  	SPI_InitStructure.SPI_CRCPolynomial = 7;//CRC����ʽ
  	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;//����ģʽ
  	SPI_Init(SPI2, &SPI_InitStructure);
  	SPI_Cmd(SPI2, ENABLE);
}

void CSPin_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//MMACS:PD12
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_SetBits(GPIOD, GPIO_Pin_12);//��ѡ��
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//TPCS:PB14
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
  	GPIO_SetBits(GPIOB, GPIO_Pin_12);//��ѡ��
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//FLCS:PD13
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOD, &GPIO_InitStructure);
  	GPIO_SetBits(GPIOD, GPIO_Pin_13);//��ѡ��
}

u8 SPI1_RWByte(u8 byte)
{
 	while((SPI2->SR&SPI_I2S_FLAG_TXE)==RESET);
 	SPI2->DR = byte;
 	while((SPI2->SR&SPI_I2S_FLAG_RXNE)==RESET);
 	return(SPI2->DR);
}

