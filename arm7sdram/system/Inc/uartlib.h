/****************************************************************************
 * 
 * Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved. 
 *
 ****************************************************************************/
 
/****************************************************************************
 * 
 * FILENAME
 *     uartlib.h
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *	Winbond W90P710 UART Driver header
 *
 * DATA STRUCTURES
 *		None
 *
 * FUNCTIONS
 *		None
 *
 * HISTORY
 *	2006/03/09		Ver 1.0 Created by NS22 HHWu
 *
 * REMARK
 *     None
 *************************************************************************/
#ifndef _UARTLIB_H
#define _UARTLIB_H


#include "wblib.h"

/*  */
#define UARTOFFSET    0x100

/*  */
#define UARTWRITESIZE    100

/*  */
#define UARTINTMODE     1
#define UARTPOLLMODE    0

/* IrDA */
#define ENABLEIrDA	  1
#define DISABLEIrDA   0
#define IrDA_TX		  0
#define IrDA_RX		  1	

#define IRCR_TXPOWERSAVING    (1<<7)  // new, Tx power saving (1.6us, 115200bps)
#define IRCR_INVRX            (1<<6)
#define IRCR_INVTX            (1<<5)
#define IRCR_RXISDEN          (1<<3)  // new, Rx input signal de-bounce (1.0us)
#define IRCR_LB               (1<<2)
#define IRCR_TXSELECT         (1<<1)
#define IRCR_IrDAEN           (1<<0)

/*  */
#define UART0	0
#define UART1	1
#define UART2	2
#define UART3	3

#define ALLCHANNEL  4  

#define UART_NUM    4

/* define IOCTL command of UART operation mode, interrupt or pooling mode */
#define UART_IOC_SETTXMODE    	     	 1
#define UART_IOC_SETRXMODE    	     	 2
#define UART_IOC_GETRECCHARINFO      	 3
#define UART_IOC_SETUARTPARAMETER    	 4
#define UART_IOC_PERFORMBLUETOOTH	 	 5
#define UART_IOC_PERFORMIrDA         	 6
#define UART_IOC_GETUARTREGISTERVALUE    7
#define UART_IOC_GETERRNO                8

#define UART_IOC_SETMODEMLOOPBACK		 9
#define UART_IOC_GETDSRSTATE			 10  // DSR
#define UART_IOC_SETDTRSIGNAL			 11  // DTR
#define UART_IOC_SETINTERRUPT			 12
#define UART_IOC_SETBREAKCONTROL		 13
#define UART_IOC_GETBIISTATE			 14

/*  */
#define UART_BII	1  // break interrupt 
#define UART_FEI	2  // framing error 
#define UART_PEI    3  // parity error 
#define UART_OEI	4  // overrun error 

/* define UARTx interrupt enable register value */
#define DISABLEALLIER    0
#define IER_MOS         (1<<3)
#define IER_RLS         (1<<2)
#define IER_THRE        (1<<1)
#define IER_RDA         (1<<0)

/* define UARTx interrupt identification register value */
#define IIR_RLS    0x06
#define IIR_RDA    0x04
#define IIR_TOUT   0x0C
#define IIR_THRE   0x02
#define IIR_MOS    0x00	  

/* define UARTx line status control register value */
#define LSR_THRE    0x20
#define LSR_RFDR    0x01

#define LSR_BII     0x10
#define LSR_FEI     0x08
#define LSR_PEI     0x04
#define LSR_OEI     0x02

/* Define constants for use UART in service parameters. */
#define DATA_BITS_5    		0x00
#define DATA_BITS_6    		0x01
#define DATA_BITS_7    		0x02
#define DATA_BITS_8    		0x03

#define STOP_BITS_1    		0x00
#define STOP_BITS_1_Half    0x04  // 1.5 STOP bits generated when 5-bit word length is selected.
#define STOP_BITS_2    		0x04  // 2 STOP bits generated when 6, 7, 8-bit word length is selected.

#define PARITY_NONE         0x00
#define PARITY_ODD     	    0x08  // 01.24 modify
#define PARITY_EVEN         0x18  // 01.24 modify
#define PARITY_STICK        0x20

#define LEVEL_1_BYTES       0x01
#define LEVEL_4_BYTES       0x41
#define LEVEL_8_BYTES       0x81
#define LEVEL_14_BYTES      0xC1

/* UBCR */
#define UBCR_15MHz    15000000	
#define UBCR_30MHz    30000000	
#define UBCR_43MHz    43600000
#define UBCR_48MHz    48000000	
#define UBCR_60MHz    60000000	

/* These error code can get from UART_IOC_GETERRNO */  
#define UART_ERR_PARITY_INVALID          -1
#define UART_ERR_DATA_BITS_INVALID       -2
#define UART_ERR_STOP_BITS_INVALID       -3
#define UART_ERR_TRIGGERLEVEL_INVALID    -4
#define UART_ERR_CHANNEL_INVALID         -5
#define UART_ERR_ALLOC_MEMORY_FAIL       -6
#define UART_ERR_CLOCK_SOURCE_INVALID    -7
#define UART_ERR_BAUDRATE_INVALID        -8
#define UART_ERR_CONFIGURE_BT_FAIL       -9  // BT, bluetooth
#define UART_ERR_IrDA_COMMAND_INVALID    -10
#define UART_ERR_TX_BUF_NOT_ENOUGH       -11
#define UART_ERR_OPERATE_MODE_INVALID    -12

/* These are the error code actually returns to user application */
#define UART_ENOTTY	   (1 | UART_ERR_ID)    // Command not support
#define UART_ENODEV    (2 | UART_ERR_ID)    // Interface number out of range 
#define UART_EIO       (3 | UART_ERR_ID)    // Read/Write error     


/* Define UART register structure */
typedef struct UART_REGISTER_STRUCT
{
	UINT32 uUartReg[8][2];
} UART_REGISTER_T;	

/* Define UART Tx, Rx FIFO structure */
typedef struct UART_BUFFER_STRUCT
{
	UINT32 volatile  uUartTxHead, uUartTxTail; 
	UINT32 volatile  uUartRxHead, uUartRxTail;  
	
	PUINT8    pucUartTxBuf;
	PUINT8    pucUartRxBuf;
	PVOID     pvUartVector;
	BOOL      bIsUseUARTTxInt;
	BOOL      bIsUseUARTRxInt;
    BOOL      bIsUARTInitial;
    
    PINT      pucUARTFlag;  
    UINT32 volatile uRecCnt;
    INT32 volatile nErrno;  // 03.09 add, Michael
    
} UART_BUFFER_T;	

/* Define UART initialization data structure */
typedef struct UART_STRUCT
{
    UINT32		uFreq;
    UINT32		uBaudRate;
    UINT8		ucUartNo;
    UINT8		ucDataBits;
    UINT8		ucStopBits;
    UINT8		ucParity;
    UINT8		ucRxTriggerLevel;
} UART_T;

/* Define UART functions */
INT uartOpen(PVOID param);
INT uartInit(VOID);
INT uartIoctl(INT nNum, UINT32 uCom, UINT32 uArg0, UINT32 uArg1);
INT32 uartClose(INT nNum);
INT32 uartWrite(INT nNum, PUINT8 pucBuf, UINT32 uLen);
INT32 uartRead(INT nNum, PUINT8 pucBuf, UINT32 uLen); 



#endif  /* _UARTLIB_H */

