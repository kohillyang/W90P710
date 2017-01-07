/****************************************************************************
 * 
 * Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved. 
 *
 ****************************************************************************/
 
/****************************************************************************
 * 
 * FILENAME
 *     i2c.h
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *	Winbond ARM7 I2C Driver header
 *
 * DATA STRUCTURES
 *		None
 *
 * FUNCTIONS
 *		None
 *
 * HISTORY
 *	2005/05/20		Ver 1.0 Created by PC34 QFu
 *     03/13/2006			 Port to Non-OS library 
 *
 * REMARK
 *     None
 *************************************************************************/
#ifndef _WINBOND_I2C_H_
#define _WINBOND_I2C_H_


#include "wblib.h"



#define I2C_NUMBER				2
#define I2C_MAX_BUF_LEN			450


#define I2C_INPUT_CLOCK			80000		/* 80 000 KHz */

/* bit map in CMDR */
#define I2C_CMD_START			0x10
#define I2C_CMD_STOP			0x08
#define I2C_CMD_READ			0x04
#define I2C_CMD_WRITE			0x02
#define I2C_CMD_NACK			0x01

/* for transfer use */
#define I2C_WRITE				0x00
#define I2C_READ				0x01


#define I2C_STATE_NOP			0x00
#define I2C_STATE_READ			0x01
#define I2C_STATE_WRITE		0x02
#define I2C_STATE_PROBE		0x03




//typedef struct{
//	CHAR len;
//	UINT addr;
//}sub_addr;


/* error code */
#define I2C_ERR_NOERROR				(0x00)
#define I2C_ERR_LOSTARBITRATION			(0x01 | I2C_ERR_ID)
#define I2C_ERR_BUSBUSY				(0x02 | I2C_ERR_ID)
#define I2C_ERR_NACK				(0x03 | I2C_ERR_ID)	/* data transfer error */
#define I2C_ERR_SLAVENACK			(0x04 | I2C_ERR_ID)	/* slave not respond after address */
#define I2C_ERR_NODEV				(0x05 | I2C_ERR_ID)
#define I2C_ERR_BUSY				(0x06 | I2C_ERR_ID)
#define I2C_ERR_IO				(0x07 | I2C_ERR_ID)
#define I2C_ERR_NOTTY				(0x08 | I2C_ERR_ID)

/*ioctl commands */

#define I2C_IOC_SET_DEV_ADDRESS		0
#define I2C_IOC_SET_SUB_ADDRESS		1
#define I2C_IOC_SET_SPEED		2
//#define I2C_IOC_GET_LAST_ERROR		3


// I2C library APIs
extern INT32 i2cInit(VOID);
extern INT32 i2cOpen(PVOID param);
extern INT32 i2cClose(INT32 fd);
extern INT32 i2cRead(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 i2cWrite(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 i2cIoctl(INT32 fd, UINT32 cmd, UINT32 arg0, UINT32 arg1);
extern INT32 i2cExit(VOID);




#endif

