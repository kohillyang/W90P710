/****************************************************************************
 * 
 * Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved. 
 *
 ****************************************************************************/
 
/****************************************************************************
 * 
 * FILENAME
 *     smartcard.h
 *
 * VERSION
 *     1.1
 *
 * DESCRIPTION
 *     Smart Card driver supported for Winbond ARM7 MCU.
 *
 * DATA STRUCTURES
 *     
 *
 * FUNCTIONS
 *     
 *
 * HISTORY
 *	2005/04/28		Ver 1.0 Created by PC34 QFu
 *      2005/09/14		Modified for simple implementation
 *	2005/12/19		Merge linux smartcard driver & library, removed POS-TAX related APIs, 
 *				                            port to Non-OS library  [yachen]
 *
 * REMARK
 *   
 *
 *************************************************************************/

#ifndef _WINBOND_SC_H_
#define _WINBOND_SC_H_

#include "wblib.h"

#define MAX_ATR_LEN					(33)
#define MAX_BUF_LEN					(500)
#define MAX_CMD_LEN					(262)	/* header : 5, data : 256(max), le : 1, plus all 262 */

#define SMARTCARD_NUM					2      // we have 2 interfaces

#define SC_IOC_ISCARDPRESENT				1		/* check card present */
#define SC_IOC_GETATR					2
#define SC_IOC_GETERRNO					3		/* get error number */


/* iso7816 operation class */
#define SC_ISO_OPERATIONCLASS_A				(0x01)
#define SC_ISO_OPERATIONCLASS_B				(0x02)

// Current card operation
#define SC_OP_NOP					(0x00)
#define SC_OP_READ					(0x01)
#define SC_OP_WRITE					(0x02)

// error code get from SC_IOC_GETERRNO
#define SC_ERR_CARD_REMOVED				-120
#define SC_ERR_OVER_RUN					-119
#define SC_ERR_PARITY_ERROR				-118
#define SC_ERR_NO_STOP					-117
#define SC_ERR_SILENT_BYTE				-116
#define SC_ERR_CMD						-115
#define SC_ERR_UNSUPPORTEDCARD			-114
#define SC_ERR_READ						-113
#define SC_ERR_WRITE					-112
#define SC_ERR_TIMEOUT             		-111

// These are the error code actually returns to user application
#define SC_EIO							(1| SMARTCARD_ERR_ID)
#define SC_ENODEV						(2| SMARTCARD_ERR_ID)
#define SC_ENOMEM						(3| SMARTCARD_ERR_ID)
#define SC_EBUSY						(4| SMARTCARD_ERR_ID)
#define SC_ENOTTY						(5| SMARTCARD_ERR_ID)




// Smartcard library APIs
extern INT32 scInit(VOID);
extern INT32 scOpen(PVOID param);
extern INT32 scClose(INT32 fd);
extern INT32 scRead(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 scWrite(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 scIoctl(INT32 fd, UINT32 cmd, UINT32 arg0, UINT32 arg1);
extern INT32 scExit(VOID);
//extern INT32 scProbe(PVOID dev);

#endif