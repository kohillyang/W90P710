/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   ebi_led.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of EBI LED control
*
* HISTORY
*   2006-02-08  Ver 1.0 Created by NS21 WTLiu
*
* REMARK
*   None
****************************************************************************/
#ifndef _EBI_LED_H_
#define _EBI_LED_H_

#define EBI_EXT0_VALUE  0xF0078001
#define EBILED_ADDRESS  0x78000000

#define LED0    (1<<0)
#define LED1    (1<<1)
#define LED2    (1<<2)
#define LED3    (1<<3)
#define LED4    (1<<4)
#define LED5    (1<<5)
#define LED6    (1<<6)
#define LED7    (1<<7)

VOID Init_EBILED(CHAR cValue);
VOID Set_EBILED(CHAR cValue);

#endif
