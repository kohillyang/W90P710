/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   ps2.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of  PS/2 device library
*
* HISTORY
*   12/22/05    Ver 1.0 Created by YCChang
*
* REMARK
*
****************************************************************************/
#ifndef _PS2_H
#define _PS2_H
#include "wblib.h"

INT ScanCodeTest(VOID);


/*----- Keyboard Command -----*/
#define KBCMD_SETLED        0xED
#define KBCMD_ECHO          0xEE
#define KBCMD_ENABLE        0xF4
#define KBCMD_DISABLE       0xF5
#define KBCMD_RESEND        0xFE
#define KBCMD_RESET         0xFF
#define KBSTS_ACK			0xFA
#define KBSTS_ERR_COMD		0xFE
#define KBSTS_RD_ID			0xF2

#define BLOCK				1
#define NON_BLOCK			0


/* ==========================PS2 scancode register========================== */
typedef union 
{
    UINT value;
    struct{
        	INT scancode:8,RX_extend:1,RX_release:1,RX_shift_key:1,un:21;
          }SCANCODE_field;
} PS2_SCANCODE_union;
#define PS2_SCANCODE      	(PS2_SCANCODE_REG.SCANCODE_field.scancode)
#define RX_SHIFT_KEY        (PS2_SCANCODE_REG.SCANCODE_field.RX_shift_key)
#define RX_RELEASE_KEY      (PS2_SCANCODE_REG.SCANCODE_field.RX_release)
#define RX_EXTEND_KEY       (PS2_SCANCODE_REG.SCANCODE_field.RX_extend)


/* ==========================PS2 STS register========================== */
typedef union 
{
    UINT value;
    struct{
        	INT RX_IRQ:1,un:3,TX_IRQ:1,TX_err:1,un2:26;
          }STS_field;
} PS2_STS_union;
#define RX_IRQ      		(PS2_STS_REG.STS_field.RX_IRQ)
#define TX_IRQ        		(PS2_STS_REG.STS_field.TX_IRQ)
#define TX_ERR      		(PS2_STS_REG.STS_field.TX_err)


/* ==========================PS2 CMD register========================== */
typedef union 
{
    UINT value;
    struct{
        	INT PS2CMD:8,EnCMD:1,TRAP_SHIFT:1,un:22;
          }CMD_field;
} PS2_CMD_union;
#define PS2_CMD      		(PS2_CMD_REG.CMD_field.PS2CMD)
#define PS2_EnCMD       	(PS2_CMD_REG.CMD_field.EnCMD)
#define PS2_TRAP_SHIFT  	(PS2_CMD_REG.CMD_field.TRAP_SHIFT)

/* ==========================PS2 ASCII register========================== */
typedef union 
{
    UINT value;
    struct{
        	INT PS2ASCII:8,un:24;
          }ASCII_field;
} PS2_ASCII_union;
#define PS2_ASCII      		(PS2_ASCII_REG.ASCII_field.PS2ASCII)

#define RETURN_KEY_STATUS	0x03
#define RX_FIFO_DATA_READY	0x1
#define EnCMD				0x100
#define CLEAR_RX			0x01	

#define MAX_PS2_BUFFER_SIZE 50
#define PS2_QUE_SIZE        (MAX_PS2_BUFFER_SIZE+1)
#define BEMPTY 				-1
#define COMMAND_NOT_FOUND 	-2
#define COM_ACK_LEN_ERR		-3	


//Error code 
#define PS2_OPEN_ERR  	(1|PS2_ERR_ID)
#define PS2_NOPEN	  	(2|PS2_ERR_ID)	
#define PS2_COMMAND_ERR	(3|PS2_ERR_ID)
#define PS2_NOKEY		(4|PS2_ERR_ID)
#define PS2_TIME_OUT	(5|PS2_ERR_ID)
//#define PS2_COM_LEN_ERR (6|PS2_ERR_ID)
//#define PS2_COMMAND_NOT_FOUND (7|PS2_ERR_ID)
//#define PS2_ACK_LEN_ERR (8|PS2_ERR_ID)
#define PS2_ACK_BUFLEN_ERR (9|PS2_ERR_ID)

					
#define COMMANDCOUNT 		17
#define DEVICE_ID_LENGTH	2
//Ioctl command
#define FLUSH_QUEUE		1

//functions define

extern INT ps2Init(void);
extern INT ps2Open(void);
extern INT ps2Read(INT rarg,UINT buf,INT mode);
extern INT ps2Write(INT rarg,UCHAR *cmd,UCHAR cmd_len,UCHAR *resbuf,UCHAR *resbuf_len);
extern INT ps2Close(INT arg );
extern INT ps2Ioctl(INT32 res_arg,INT cmd,UINT32 arg,INT32 arg1);



struct  ps2_data{
	INT scode;
	INT acode;
	INT ShiftKeyByte;
	INT ReleaseKeyByte;
	INT ExtendKeyByte;
	INT CAP_LED;
	INT SCROLL_LED;
	INT NUM_LOCK_LED;
};  


struct ps2cmdTable 
{
	UCHAR ps2cmd;
	UCHAR ps2arglength;
	UCHAR ps2acklength;
};



#endif
