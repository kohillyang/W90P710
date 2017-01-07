/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   rtc.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of Winbond ARM7 MCU RTC device library
*
* HISTORY
*   12/22/05    Ver 1.0 Created by YCChang
*
* REMARK
*
****************************************************************************/

#ifndef _RTC_H
#define _RTC_H

//#define OLD_RTC
#include "wblib.h"

/********************************************************************/
/* ==========================INIR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT inir:16,inir_ack:1,unused:15;
          }INIR_field;
} INIR_union;

#define INIR_0_15       	(INIR_REG.INIR_field.inir)
#define INIR_16         	(INIR_REG.INIR_field.inir_ack)

/********************************************************************/
/* ==========================AER register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT aer:16,aer_ack:1,unused:15;
          }AER_field;
} AER_union;

#define AER_0_15        	(AER_REG.AER_field.aer)
#define AER_16          	(AER_REG.AER_field.aer_ack)

/********************************************************************/
/* ==========================FCR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT fcr_0_5:6,unused1:2,fcr_8_11:4,unused2:20;
          }FCR_field;
} FCR_union;

#define FCR_0_5         	(FCR_REG.FCR_field.fcr_0_5)
#define FCR_8_11        	(FCR_REG.FCR_field.fcr_8_11)

/********************************************************************/
/* ==========================TLR register========================== */
typedef union
{
    UINT value;
    struct{
        UINT tlr_0_3:4,tlr_4_6:3,unused1:1,tlr_8_11:4,tlr_12_14:3
           ,unused2:1,tlr_16_19:4,tlr_20_21:2,unused:10;
          }TLR_field;
} TLR_union;

#define TLR_0_3         	(TLR_REG.TLR_field.tlr_0_3)
#define TLR_4_6         	(TLR_REG.TLR_field.tlr_4_6)
#define TLR_8_11        	(TLR_REG.TLR_field.tlr_8_11)
#define TLR_12_14       	(TLR_REG.TLR_field.tlr_12_14)
#define TLR_16_19       	(TLR_REG.TLR_field.tlr_16_19)
#define TLR_20_21       	(TLR_REG.TLR_field.tlr_20_21)

/********************************************************************/
/* ==========================CLR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT clr_0_3:4,clr_4_5:2,unused1:2,clr_8_11:4,clr_12:1,unused2:3,
            clr_16_19:4,clr_20_23:4,unused:8;
          }CLR_field;
} CLR_union;

#define CLR_0_3         	(CLR_REG.CLR_field.clr_0_3)
#define CLR_4_5         	(CLR_REG.CLR_field.clr_4_5)
#define CLR_8_11        	(CLR_REG.CLR_field.clr_8_11)
#define CLR_12          	(CLR_REG.CLR_field.clr_12)
#define CLR_16_19       	(CLR_REG.CLR_field.clr_16_19)
#define CLR_20_23       	(CLR_REG.CLR_field.clr_20_23)
/********************************************************************/
/* ==========================TSSR register ==========================*/
typedef union
{
    UINT value;
    struct{
        	UINT tssr_0:1,unused:31;
          }TSSR_field;
} TSSR_union;
#define TSSR_0      		(TSSR_REG.TSSR_field.tssr_0)

/********************************************************************/
/* ==========================DWR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT dwr_0_2:3,unused:29;
          }DWR_field;
} DWR_union;
#define DWR_0_2         	(DWR_REG.DWR_field.dwr_0_2)

/********************************************************************/
/* ==========================TAR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT tar_0_3:4,tar_4_6:3,unused1:1,tar_8_11:4,tar_12_14:3,
            unused2:1,tar_16_19:4,tar_20_21:2,unused:10;
          }TAR_field;
} TAR_union;

#define TAR_0_3         	(TAR_REG.TAR_field.tar_0_3)
#define TAR_4_6         	(TAR_REG.TAR_field.tar_4_6)
#define TAR_8_11        	(TAR_REG.TAR_field.tar_8_11)
#define TAR_12_14       	(TAR_REG.TAR_field.tar_12_14)
#define TAR_16_19       	(TAR_REG.TAR_field.tar_16_19)
#define TAR_20_21       	(TAR_REG.TAR_field.tar_20_21)
/********************************************************************/
/* ==========================CAR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT car_0_3:4,car_4_5:2,un1:2,car_8_11:4,car_12:1,un2:3,
            car_16_19:4,car_20_23:4,un:8;
          }CAR_field;
} CAR_union;
#define CAR_0_3         	(CAR_REG.CAR_field.car_0_3)
#define CAR_4_5         	(CAR_REG.CAR_field.car_4_5)
#define CAR_8_11       		(CAR_REG.CAR_field.car_8_11)
#define CAR_12          	(CAR_REG.CAR_field.car_12)
#define CAR_16_19       	(CAR_REG.CAR_field.car_16_19)
#define CAR_20_23       	(CAR_REG.CAR_field.car_20_23)
/********************************************************************/
/* ==========================LIR registe==========================r */
typedef union
{
    UINT value;
    struct{
        	UINT lir_0:1,un:31;
          }LIR_field;
} LIR_union;
#define LIR_0       		(LIR_REG.LIR_field.lir_0)
/********************************************************************/
/* ==========================RIER register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT rier_0:1,rier_1:1,un:30;
          }RIER_field;
} RIER_union;
#define RIER_0      		(RIER_REG.RIER_field.rier_0)
#define RIER_1      		(RIER_REG.RIER_field.rier_1)
/********************************************************************/
/* ==========================RIIR register========================== */
typedef union
{
    UINT value;
    struct{
        	UINT riir_0:1,riir_1:1,un:30;
          }RIIR_field;
} RIIR_union;
#define RIIR_0      		(RIIR_REG.RIIR_field.riir_0)
#define RIIR_1      		(RIIR_REG.RIIR_field.riir_1)
/********************************************************************/
/* ==========================TTR register========================== */

#ifdef OLD_RTC
typedef union
{
    UINT value;
    struct{
        	UINT ttr_0_6:7,ttr_7:1,un:24;
          }TTR_field;
} TTR_union;
#define TTR_0_6         	(TTR_REG.TTR_field.ttr_0_6)
#define TTR_7           	(TTR_REG.TTR_field.ttr_7)
#else
typedef union
{
    UINT value;
    struct{
        	UINT ttr_0_2:3,un:29;
          }TTR_field;
} TTR_union;
#define TTR_0_2				(TTR_REG.TTR_field.ttr_0_2)
#endif

#define YEAR2000			2000

#define SET_RTC_AIE				1
#define RTC_RD_TIME_SCALE		2
#define RTC_SET_TIME_SCALE		3
#define RTC_ALM_READ			4
#define RTC_ALM_SET				5
#define RTC_TICK_READ			6
#define RTC_TICK_SET			7
#define RTC_RD_TIME				8
#define RTC_SET_TIME			9
#define RTC_RD_LEAP				10
#define RTC_RD_TICK_INTERRUPT_REG 		11
#define RTC_CLEAR_TICK_INTERRUPT_REG 	12
#define RTC_SET_FREQUENCY_COMPENSATION	13
#define	RTC_RD_FREQUENCY_COMPENSATION	14
#define SET_RTC_TIE				15
#define	RTC_SET_TTR_ENABLE		16
#define NO_COMMAND				17

#define RTC_TICK			0
#define RTC_ALARM			1
#define TIMESCALE12			0
#define TIMESCALE24			1

#define WAITCOUNT			100000

#ifdef OLD_RTC
#define INIKEY				0x00001357
#else
#define INIKEY				0xa5eb1357
#endif

#define RWKEY				0x0000a965

#define FCR_VALUE           0x00000734  //32768.87


#define RTC_INIT_ERR      (1|RTC_ERR_ID)
#define RTC_SETALARM_ERR  (2|RTC_ERR_ID)
#define RTC_SETTICK_ERR	  (3|RTC_ERR_ID)
#define RTC_COMMAND_ERR   (4|RTC_ERR_ID)
#define RTC_NOpen		  (5|RTC_ERR_ID)




struct rtc_time {
	UINT tm_sec;
	UINT tm_min;
	UINT tm_hour;
	UINT tm_mday;
	UINT tm_mon;
	UINT tm_year;
	UINT tm_wday;
	UINT tm_yday;
	UINT tm_week;
  	UINT tm_isdst;
};

#define	SUNDAY		0
#define	MONDAY		1
#define	TUESDAY		2
#define	WEDNESDAY	3
#define	THURSDAY	4
#define	FRIDAY		5
#define	SATURDAY	6

extern INT rtcWrite(INT option,UINT32 time_data,PUCHAR warg);
extern INT rtcRead(INT option,UINT32 time_data,PUCHAR rarg);
extern INT rtcInit(void);
extern INT rtcIoctl(INT32 rev_arg1,INT cmd,UINT32 arg,INT32 rev_arg2);
extern INT rtcOpen(void);
extern INT rtcClose(INT arg);
#endif
