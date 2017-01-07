/*
 * rtc.c
 *
 *  Created on: 2016年10月22日
 *      Author: kohill
 */




#include <stdio.h>
#include "../rtc/rtc.h"
#include "710defs.h"











void rtcread(RTC_TIME *p);
void Timing_Value(void);
void RTCInit(void);
static unsigned int L;

void m_rtc_init(void)
{
    RTC_TIME rtc_data;
    REG_RTC_INIR = 0xa5eb1357;
	RTCInit();
    rtc_data.tm_year = 1998;
	rtc_data.tm_mon = 2;
	rtc_data.tm_mday = 28;
	rtc_data.tm_hour = 23;
	rtc_data.tm_min = 59;
	rtc_data.tm_sec = 49;
	rtc_data.tm_week = THURSDAY;


	L=rtc_data.tm_year;
	for(int i =100;i>=0;i--){
		rtcwrite(rtc_data,1);
	}
	//Timing_Value();
}
//static char buf[64];
const char* m_rtc_read(void){
//    Delay(5900000);
//	RTC_TIME rtc_data2;
//	rtcread(&rtc_data2);
//	sprintf(buf,"%u %u %u %u %u %u",
//			rtc_data2.tm_year,rtc_data2.tm_mon,rtc_data2.tm_mday,rtc_data2.tm_hour,rtc_data2.tm_min,rtc_data2.tm_sec);
//	return buf;
	time_t m;
	time(&m);
	return ctime(&m);
}
/*******************************************************************************
* Function Name  : Delay
* Description    : 用于不精确延时
* Input          : 延时时间
* Output         : None
* Return         : None
*******************************************************************************/


/*******************************************************************************
* Function Name  : rtcwrite
* Description    : 写入时间信息
* Input          : 对应内容结构体及显示方式（12/24）
* Output         : None
* Return         : None
*******************************************************************************/
void rtcwrite(RTC_TIME rtc_data,int TSSR)
{
	 U32 temp=0,TLR = 0,CLR = 0,DWR = 0;

	 TLR= 0;
	 CLR = 0;

	 CLR |= rtc_data.tm_year/10 << 20;
	 CLR |= rtc_data.tm_year%10 << 16;

	 CLR |= rtc_data.tm_mon/10 << 12;
	 CLR |= rtc_data.tm_mon%10 << 8;

	 CLR |= rtc_data.tm_mday/10 << 4;
	 CLR |= rtc_data.tm_mday%10 << 0;

	 TLR |= rtc_data.tm_hour/10 <<20;
	 TLR |= rtc_data.tm_hour%10 <<16;
	 TLR |= rtc_data.tm_min/10 <<12;
	 TLR |= rtc_data.tm_min%10 <<8;
	 TLR |= rtc_data.tm_hour/10 <<4;
	 TLR |= rtc_data.tm_hour%10 <<0;

	 DWR = rtc_data.tm_week;

	do
    {   REG_RTC_AER = 0xa965;
		temp=(REG_RTC_AER&0x10000);
		if(temp==0x10000)
		{
			REG_RTC_FCR = 0x00000734;
			REG_RTC_TLR = TLR;
			REG_RTC_CLR = CLR;
			REG_RTC_TSSR = TSSR;
			REG_RTC_DWR = DWR;
   			REG_RTC_RIER = 0x2;

   		 	break;
    	}
    }while(1);
}
/*******************************************************************************
* Function Name  : rtcread
* Description    : 读取显示信息
* Input          : 要显示内容对应结构体的地址
* Output         : None
* Return         : None
*******************************************************************************/
void rtcread(RTC_TIME *p)
{
	U32 YearH;
	uint32_t vreg_tlr =REG_RTC_TLR;
	YearH=((L/1000)<<12)+(((L/100)%10)<<8);
	p->tm_hour = ((vreg_tlr >>20)&0x03) *10 + (vreg_tlr >>16)&0x0f;
	p->tm_min = ((vreg_tlr >>12)&0x07) *10 + (vreg_tlr >>8)&0x0f ;
	p->tm_sec = ((vreg_tlr & 0x70) >> 4 ) * 10 + (vreg_tlr&0x0f);

	(*p).tm_year = YearH+((REG_RTC_CLR&0x00ff0000) >> 16);
	(*p).tm_mon = ((REG_RTC_CLR&0x0000ff00) >> 8);
	(*p).tm_mday = (REG_RTC_CLR&0xff);
	(*p).tm_week = REG_RTC_DWR;
#define BCD(x) (x = x&0x0f + ((x&0xf0) >>4)*10)

	BCD(p->tm_year);
	BCD(p->tm_mon);
	unsigned int x = p->tm_mday;
	p->tm_mday = ((x &0xf0)>>4)*10  + (x & 0x0f) ;
}
/*******************************************************************************
* Function Name  : Timing_Value
* Description    : 定时设置
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timing_Value(void)
{
	REG_RTC_CAR = 0x980301;
	REG_RTC_TAR = 0x0;
	REG_RTC_RIER |= 0x1;
}

/*******************************************************************************
* Function Name  : RTCInit
* Description    : RTC中断初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCInit(void)
{
    REG_AIC_SCR8 = 0x00000045;
	REG_AIC_MECR = 0x100;
	REG_RTC_RIER = 0x03;
	REG_RTC_TTR = 0;
}






