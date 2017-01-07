/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   wblib.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of W90P710 system library
*
* HISTORY
*   2002-06-06  Ver 1.0 Created by PC30 HPChen
*
* REMARK
*   None
****************************************************************************/
#ifndef _WBLIB_H_
#define _WBLIB_H_

#include "W90P710_reg.h"
#include "wberrcode.h"
#include "wbio.h"

//-- function return value
#define	   Successful  0
#define	   Fail        1

#define APB_SYSTEM_CLOCK  15000000  /* 15MHz */

#define WB_PM_IDLE		1
#define WB_PM_PD		2
#define WB_PM_MIDLE	3

#define WB_PM_PD_IRQ_Fail			-1
#define WB_PM_Type_Fail			    -2
#define WB_PM_INVALID_IRQ_NUM		-3

/* Define constants for use external IO in service parameters.  */
#define EXT0			0
#define EXT1			1
#define EXT2			2
#define EXT3			3

#define SIZE_256K		4
#define SIZE_512K		5
#define SIZE_1M			6
#define SIZE_2M			7
#define SIZE_4M			8
#define SIZE_8M			9
#define SIZE_16M		10
#define SIZE_32M		11

#define BUS_DISABLE		12
#define BUS_BIT_8		13
#define BUS_BIT_16		14
#define BUS_BIT_32		15

/* Define constants for use timer in service parameters.  */
#define TIMER0            0
#define TIMER1            1

#define ONE_SHOT_MODE     0
#define PERIODIC_MODE     1
#define TOGGLE_MODE       2

#define HALF_MINUTES      0
#define ONE_MINUTES       1
#define TWO_MINUTES       2
#define FOUR_MINUTES      3

/* Define constants for use UART in service parameters.  */
#define WB_DATA_BITS_5    0x00
#define WB_DATA_BITS_6    0x01
#define WB_DATA_BITS_7    0x02
#define WB_DATA_BITS_8    0x03

#define WB_STOP_BITS_1    0x00
#define WB_STOP_BITS_2    0x04

#define WB_PARITY_NONE    0x00
#define WB_PARITY_ODD     0x00
#define WB_PARITY_EVEN    0x10

//#define WB_DTR_Low        0x01
//#define WB_RTS_Low        0x02
//#define WB_MODEM_En       0x08

#define LEVEL_1_BYTE      0x01
#define LEVEL_4_BYTES     0x41
#define LEVEL_8_BYTES     0x81
#define LEVEL_14_BYTES    0xC1

/* Define constants for use AIC in service parameters.  */
#define WB_SWI                     0
#define WB_D_ABORT                 1
#define WB_I_ABORT                 2
#define WB_UNDEFINE                3

/* The parameters of WB_SetInterruptPriorityLevel() and WB_InstallISR() */
#define FIQ_LEVEL_0                0
#define IRQ_LEVEL_1                1
#define IRQ_LEVEL_2                2
#define IRQ_LEVEL_3                3
#define IRQ_LEVEL_4                4
#define IRQ_LEVEL_5                5
#define IRQ_LEVEL_6                6
#define IRQ_LEVEL_7                7

/* The parameters of WB_SetGlobalInterrupt() */
#define ENABLE_ALL_INTERRUPTS      0
#define DISABLE_ALL_INTERRUPTS     1

/* The parameters of WB_SetInterruptType() and WB_InstallISR() */
#define LOW_LEVEL_SENSITIVE        0x00
#define HIGH_LEVEL_SENSITIVE       0x40
#define NEGATIVE_EDGE_TRIGGER      0x80
#define POSITIVE_EDGE_TRIGGER      0xC0

/* The parameters of WB_SetLocalInterrupt() */
#define ENABLE_IRQ                 0x7F
#define ENABLE_FIQ                 0xBF
#define ENABLE_FIQ_IRQ             0x3F
#define DISABLE_IRQ                0x80
#define DISABLE_FIQ                0x40
#define DISABLE_FIQ_IRQ            0xC0

/* Define constants for use Cache in service parameters.  */
#define I_CACHE			0
#define D_CACHE			1
#define I_D_CACHE		2


typedef struct datetime_t
{
	UINT32	year;
	UINT32	mon;
	UINT32	day;
	UINT32	hour;
	UINT32	min;
	UINT32	sec;
} DateTime_T;


/* Define UART initialization data structure */
typedef struct UART_INIT_STRUCT
{
    UINT32		uiFreq;
    UINT32		uiBaudrate;
    UINT8		uiDataBits;
    UINT8		uiStopBits;
    UINT8		uiParity;
    UINT8		uiRxTriggerLevel;
} WB_UART_T;


/* UART return value */
#define WB_INVALID_PARITY       -1
#define WB_INVALID_DATA_BITS    -2
#define WB_INVALID_STOP_BITS    -3
#define WB_INVALID_BAUD         -4


/* Interrupt Source */
#define 	IRQ_WDT			1 	/* Watch Dog Timer Interrupt */
#define 	IRQ_nIRQ0		2 	/* External Interrupt 0 */
#define 	IRQ_nIRQ1		3 	/* External Interrupt 1 */
#define 	IRQ_nIRQ2		4 	/* External Interrupt 2 */
#define 	IRQ_nIRQ3		5 	/* External Interrupt 3 */
#define 	IRQ_AC97		6 	/* AC97 Interrupt */
#define 	IRQ_LCD			7 	/* LCD Controller Interrupt */
#define 	IRQ_RTC			8 	/* RTC Controller Interrupt */
#define 	IRQ_UART0		9 	/* UART 0 Interrupt */
#define 	IRQ_UART1		10 	/* UART 1 Interrupt */
#define 	IRQ_UART2		11	/* UART 2 Interrupt */
#define 	IRQ_UART3		12 	/* UART 3 Interrupt */
#define 	IRQ_TIMER0		13 	/* Timer Interrupt 0 */
#define 	IRQ_TIMER1		14	/* Timer Interrupt 1 */
#define 	IRQ_USBH0		15 	/* USB Host Interrupt 0 */
#define 	IRQ_USBH1		16 	/* USB Host Interrupt 1 */
#define 	IRQ_EMCTX		17	/* EMC TX Interrupt */
#define 	IRQ_EMCRX		18	/* EMC RX Interrupt */
#define 	IRQ_GDMA0		19	/* GDMA Channel Interrupt 0 */
#define 	IRQ_GDMA1		20	/* GDMA Channel Interrupt 1 */
#define 	IRQ_SDIO		21 	/* SDIO Interrupt */
#define 	IRQ_USBD		22 	/* USB Device Interrupt */
#define 	IRQ_SC0			23 	/* SmartCard Interrupt 0 */
#define 	IRQ_SC1			24 	/* SmartCard Interrupt 1 */
#define 	IRQ_I2C0		25 	/* I2C Interrupt 0 */
#define 	IRQ_I2C1		26 	/* I2C Interrupt 1 */
#define 	IRQ_SSP			27 	/* SSP Interrupt */
#define 	IRQ_PWM			28 	/* PWM Timer Interrupt */
#define 	IRQ_KEYPAD		29 	/* keypad Interrupt */
#define 	IRQ_PS2			30 	/* PS/2 Interrupt */
#define 	IRQ_nIRQ45	    31 	/* reserved Interrupt */

/* Define system library Timer functions */
UINT32	sysGetTicks (INT32 timeNo);
INT32	sysResetTicks (INT32 timeNo);
INT32	sysUpdateTickCount(INT32 nTimeNo, UINT32 uCount);
INT32	sysSetTimerReferenceClock (UINT32 timeNo, UINT32 clockRate);
INT32	sysStartTimer (INT32 timeNo, UINT32 ticksPerSecond, INT32 opMode);
INT32	sysStopTimer (INT32 timeNo);
VOID	sysClearWatchDogTimerCount (VOID);
VOID	sysClearWatchDogTimerInterruptStatus(VOID);
VOID	sysDisableWatchDogTimer (VOID);
VOID	sysDisableWatchDogTimerReset(VOID);
VOID	sysEnableWatchDogTimer (VOID);
VOID	sysEnableWatchDogTimerReset(VOID);
PVOID	sysInstallWatchDogTimerISR (INT32 intTypeLevel, PVOID pNewISR);
INT32	sysSetWatchDogTimerInterval (INT32 wdtInterval);
INT32	sysSetTimerEvent(UINT32 timeNo, UINT32 timeTick, PVOID pFun);
VOID	sysClearTimerEvent(UINT32 timeNo, UINT32 timeEventNo);
VOID	sysSetLocalTime(DateTime_T ltime);
VOID	sysGetCurrentTime(DateTime_T *curTime);
VOID	sysDelay(UINT32 uTicks);

/* Define system library UART functions */
INT8	sysGetChar(VOID);
INT32	sysInitializeUART(WB_UART_T *uart);
VOID	sysPrintf(PINT8 pcStr,...);
VOID	sysprintf(PINT8 pcStr,...);
VOID	sysPutChar(UINT8 ch);

/* Define system library AIC functions */
INT32	sysDisableInterrupt (UINT32 intNo);
INT32	sysEnableInterrupt (UINT32 intNo);
PVOID	sysInstallExceptionHandler (INT32 exceptType, PVOID pNewHandler);
PVOID	sysInstallFiqHandler (PVOID pNewISR);
PVOID	sysInstallIrqHandler (PVOID pNewISR);
PVOID	sysInstallISR (INT32 intTypeLevel, INT32 intNo, PVOID pNewISR, PVOID pParam);
INT32	sysSetGlobalInterrupt (INT32 intState);
INT32	sysSetInterruptPriorityLevel (UINT32 intNo, UINT32 intLevel);
INT32	sysSetInterruptType (UINT32 intNo, UINT32 intSourceType);
INT32	sysSetLocalInterrupt (INT32 intState);
INT32	sysSetAIC2SWMode(VOID);
UINT32	sysGetInterruptEnableStatus(VOID);

/* Define system library Cache functions */
VOID	sysEnableCache(VOID);
VOID	sysDisableCache(VOID);
VOID	sysFlushCache(INT32 nCacheType);

/* Define system library External IO functions */
VOID	sysSetExternalIO(INT extNo, UINT32 extBaseAddr, UINT32 extSize, INT extBusWidth);
VOID	sysSetExternalIOTiming1(INT extNo, INT tACC, INT tACS);
VOID	sysSetExternalIOTiming2(INT extNo, INT tCOH, INT tCOS);

/* Define system library power management functions */
INT		sysEnablePM_IRQ(INT irq_no);
VOID    sysDisableAllPM_IRQ(VOID);
INT     sysPMStart(INT pd_type);

#endif  /* _WBLIB_H */
