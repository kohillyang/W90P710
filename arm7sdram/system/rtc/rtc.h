/*
 * rtc.h
 *
 *  Created on: 2016Äê10ÔÂ22ÈÕ
 *      Author: kohill
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_
#define    RTC_BA	 0xFFF84000 /* Real Time Clock Control */
/******************************************************************************
*
* RTC Control Registers
*
******************************************************************************/
#define REG_RTC_INIR		(VPint(RTC_BA+0x0000))	/* Product RTC RTC INITIALION Register  */
#define REG_RTC_AER			(VPint(RTC_BA+0x0004))	/* Product RTC RTC ACCESS ENABLE Register  */
#define REG_RTC_FCR			(VPint(RTC_BA+0x0008))	/* Product RTC RTC FREQUENCY COMPENSATION Register  */
#define REG_RTC_TLR			(VPint(RTC_BA+0x000C))	/* Product RTC TIME LOADING Register  */
#define REG_RTC_CLR			(VPint(RTC_BA+0x0010))	/* Product RTC CALENDAR LOADING Register  */
#define REG_RTC_TSSR		(VPint(RTC_BA+0x0014))	/* Product RTC TIME SCAL SELECTION Register  */
#define REG_RTC_DWR			(VPint(RTC_BA+0x0018))	/* Product RTC DAY OF THE WEEK Register  */
#define REG_RTC_TAR			(VPint(RTC_BA+0x001C))	/* Product RTC TIME ALARM Register  */
#define REG_RTC_CAR			(VPint(RTC_BA+0x0020))	/* Product RTC CALENDAR ALARM Register  */
#define REG_RTC_LIR			(VPint(RTC_BA+0x0024))	/* Product RTC LEAP YEAR INDICATOR Register  */
#define REG_RTC_RIER		(VPint(RTC_BA+0x0028))	/* Product RTC RTC INTERRUPT ENABLE Register  */
#define REG_RTC_RIIR		(VPint(RTC_BA+0x002C))	/* Product RTC RTC INTERRUPT INDICATOR Register  */
#define REG_RTC_TTR			(VPint(RTC_BA+0x0030))	/* Product RTC RTC TIME TICK Register  */
#define	SUNDAY		0
#define	MONDAY		1
#define	TUESDAY		2
#define	WEDNESDAY	3
#define	THURSDAY	4
#define	FRIDAY		5
#define	SATURDAY	6
typedef struct {
	unsigned int tm_year;
	unsigned int tm_mon;
	unsigned int tm_mday;
	unsigned int tm_hour;
	unsigned int tm_min;
	unsigned int tm_sec;
	unsigned int tm_week;
}RTC_TIME;

extern void m_rtc_init(void);
extern const char* m_rtc_read(void);
extern void LineEditSetText(const char* p);

extern void KPIInit(void);
extern unsigned int  key_exec(void);
extern const char* lua_exec(const char * in);
extern void rtcwrite(RTC_TIME rtc_data,int TSSR);;
extern int key_flag;// = 0
unsigned long my_mktime(const unsigned int year0, const unsigned int mon0,
		const unsigned int day, const unsigned int hour, const unsigned int min,
		const unsigned int sec);
#include <time.h>
#endif /* RTC_RTC_H_ */
