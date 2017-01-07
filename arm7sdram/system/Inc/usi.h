/****************************************************************************
 * 
 * Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved. 
 *
 ****************************************************************************/
 
/****************************************************************************
 * 
 * FILENAME
 *     usi.h
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *     USI driver supported for ARM7 MCU.
 *
 * FUNCTIONS
 *	all functions, if they has return value, return 0 if they success, others failed.
 *
 * HISTORY
 *	2006/01/10		Created by QFu
 *  2006/03/20      Ported to non-OS library
 *
 * REMARK
 *     None
 *************************************************************************/
#ifndef _WINBOND_USI_H_
#define _WINBOND_USI_H_

#include "wblib.h"



//#define USI_IOC_SET_BIT		0  
#define USI_IOC_SET_LSB		1
//#define USI_IOC_SET_SLEEP	2
#define USI_IOC_SET_NEG		3
#define USI_IOC_SET_DIVIDER	4
#define USI_IOC_SET_ACT_LEVEL	5
#define USI_IOC_ACTIVE		6
#define USI_IOC_DEACTIVE	7

#define USI_ERR_IO				(SPI_ERR_ID | 0x01)
#define USI_ERR_NOTTY			(SPI_ERR_ID | 0x02)
#define USI_ERR_BUSY			(SPI_ERR_ID | 0x03)

extern INT32 usiInit(VOID);
extern INT32 usiOpen(PVOID param);
extern INT32 usiClose(INT32 fd);
extern INT32 usiRead(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 usiWrite(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 usiIoctl(INT32 fd, UINT32 cmd, UINT32 arg0, UINT32 arg1);
extern INT32 usiExit(VOID);



typedef struct {	

	UINT16 divider;
	UINT8 act_level;	
	UINT8 tx_neg;
	UINT8 rx_neg;
	UINT8 lsb;	
	
}usiPara;


#endif /* _WINBOND_USI_H_ */

