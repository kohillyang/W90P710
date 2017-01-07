/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   wbfmi.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   Original fmi APIs
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
#ifndef _FMILIB_H_
#define _FMILIB_H_

#include "wberrcode.h"

//#define DEBUG

#define _WB_FAT_

#define FMI_SD_CARD		0
//#define SD_POWER_CTRL
//#define SD_WRITE_PROTECTION

// device type
#define FMI_DEVICE_SD		0
#define FMI_DEVICE_MMC		1
#define FMI_DEVICE_SDIO		2

/* FMI Library Error Numbers */
//#define FMI_ERR_ID				0xffffff00
#define FMI_NO_ERR				0					/* No error */
#define FMI_TIMEOUT				(FMI_ERR_ID|0x01)	/* device time-out */

/* SD host error code */
#define FMI_NO_SD_CARD			(FMI_ERR_ID|0x10)	/* No SD card */
#define FMI_SD_WRITE_PROTECT	(FMI_ERR_ID|0x11)	/* SD card write protect*/
#define FMI_SD_INIT_ERROR		(FMI_ERR_ID|0x12)	/* SD card init fail */
#define FMI_SD_SELECTCARD_ERROR	(FMI_ERR_ID|0x13)	/* SD select card error */
#define FMI_SD_CRC_ERROR		(FMI_ERR_ID|0x14)	/* SD card send data error */
#define FMI_SD_CRC7_ERROR		(FMI_ERR_ID|0x15)	/* SD card CMD crc7 error */
#define FMI_SD_R2_ERROR			(FMI_ERR_ID|0x16)	/* SD card R2 error */
#define FMI_SD_R2CRC7_ERROR		(FMI_ERR_ID|0x17)	/* SD card R2 crc7 error */
#define FMI_SD_CRC16_ERROR		(FMI_ERR_ID|0x18)	/* SD card get data error */
#define FMI_SDIO_READ_ERROR		(FMI_ERR_ID|0x19)	/* SDIO read fail */
#define FMI_SDIO_WRITE_ERROR	(FMI_ERR_ID|0x1a)	/* SDIO write fail */
#define FMI_SD_INIT_TIMEOUT		(FMI_ERR_ID|0x1b)	/* CMD1, CMD5, ACMD41 timeout */
#define FMI_SD_TIMEOUT			(FMI_ERR_ID|0x1c)	/* timeout */
#define FMI_SD_PARA_ERROR		(FMI_ERR_ID|0x1d)   // wrong parameter to api
#define FMI_SD_NOT_INIT			(FMI_ERR_ID|0x1e)	// call read/write... functions before a success open()


// CMD52 -> IO read / write
typedef struct sdio_data_t
{
	UINT32	regAddr;
	UINT8	funNo;
	UINT8	WriteData;
	BOOL	IsReadAfterWrite;
} SDIO_DATA_T;


// SDIO definitiion
#define FMI_SDIO_SINGLE			0
#define FMI_SDIO_MULTIPLE		1
#define FMI_SDIO_FIX_ADDRESS	2
#define FMI_SDIO_INC_ADDRESS	3


// CMD53 -> IO read / write
typedef struct sdio_multidata_t
{
	UINT32	regAddr;
	UINT32	bufAddr;
	UINT16	Count;
	UINT8	funNo;
	UINT8	OpCode;
	UINT8	BlockMode;
} SDIO_MULTIDATA_T;


// function prototype
VOID fmiInitDevice(VOID);
VOID fmiSetFMIReferenceClock(UINT32 uClock);
INT  fmiInitSD(VOID);

// for mass storage
INT  fmiSDCmdAndRsp(UINT8 ucCmd, UINT32 uArg);
INT  fmiSDDeviceInit(VOID);				// return total sector count

INT  fmiSD_Read(UINT32 uSector, UINT32 uBufcnt, UINT32 uDAddr);
INT  fmiSD_Write(UINT32 uSector, UINT32 uBufcnt, UINT32 uSAddr);
INT  fmiSDIO_Read(SDIO_DATA_T *sdio);
INT  fmiSDIO_Write(SDIO_DATA_T *sdio);
INT  fmiSDIO_BlockRead(SDIO_MULTIDATA_T *sdio);
INT  fmiSDIO_BlockWrite(SDIO_MULTIDATA_T *sdio);


// for file system

INT  fmiInitSDDevice(VOID);

// callback function
VOID fmiSetCallBack(UINT32 uCard, PVOID pvRemove, PVOID pvInsert);

#endif //_FMILIB_H_