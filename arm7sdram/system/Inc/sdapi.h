/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   sdapi.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   Wrapper functions for FMI library. Create a unified interface with other non-os library
*
* DATA STRUCTURES
*   None
*
* FUNCTIONS
*
* HISTORY
*
* REMARK
*   None
****************************************************************************/
#ifndef __SCAPI_H__
#define __SCAPI_H__

#define SD_IOC_SETCALLBACK				1		/* install card insert/remove callback function */
#define SD_IOC_SETSECTOR				2		/* set read/write sector */



extern INT32 sdInit(VOID);
extern INT32 sdOpen(PVOID param);
extern INT32 sdClose(INT32 fd);
extern INT32 sdRead(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 sdWrite(INT32 fd, PUINT8 buf, UINT32 len);
extern INT32 sdIoctl(INT32 fd, UINT32 cmd, UINT32 arg0, UINT32 arg1);
extern INT32 sdExit(VOID);


#endif