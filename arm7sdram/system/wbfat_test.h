/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   wbfat_test.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of Winbond FAT test program
*
* HISTORY
*   2006-02-14  Ver 1.0 Created by NS21 WTLiu
*
* REMARK
*   None
****************************************************************************/
#ifndef _WB_FAT_TEST_H_
#define _WB_FAT_TEST_H_

#include "wbfat.h"

#ifdef SD_PATTERN
#define SD_DISK  (DISK_TYPE_SD_MMC)
#endif
#define USB_DISK (DISK_TYPE_DMA_MODE|DISK_TYPE_USB_DEVICE|DISK_TYPE_HARD_DISK)

extern CHAR Action_GetDriverNo(UINT32 DISK_TYPE);
extern VOID Action_RelessDisk(UINT32 DISK_TYPE);
extern INT Action_DIR(CHAR *suDirName);
#ifdef __WB_EVB__
#ifdef SD_PATTERN
extern VOID sd_inserted(VOID);
extern VOID sd_removed(VOID *ptr);
#endif
#endif

#endif
