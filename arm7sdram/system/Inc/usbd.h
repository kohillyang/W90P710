/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   usbd.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of USB Device
*
* HISTORY
*
* REMARK
*   None
****************************************************************************/
#ifndef _USBD_H_
#define _USBD_H_

//define by project
//#define RAMDISK
//#define F_SD
//#define F_CF
//#define F_SM
//#define NAND_FLASH
//#define Bulk_Set_Cmd

//#define USE_VBUS

#define SizePerSector 512

typedef struct Disk_Par_Inf{
    UINT32	partition_size,
        	data_location,
        	bpb_location,
                fat_location,
         	rootdir_location,
         	free_size;
    UINT16	rootdirentryno,
                totalcluster,
        	NumCyl;
    UINT8	NumHead,
         	NumSector,
    	        capacity,
    	        fatcopyno,
                fatsectorno,
                fat16flg;
    }Disk_Par_Info;
extern Disk_Par_Info DDB;

typedef struct {
    UINT8 EP_Num;
    UINT8 EP_Dir;
    UINT8 EP_Type;
} USB_EP_Inf_T;

/* Define Endpoint feature */
#define Ep_In        0x01
#define Ep_Out       0x00
#define Ep_Bulk      0x01
#define Ep_Int       0x02
#define Ep_Iso       0x03
#define EP_A         0x01
#define EP_B         0x02
#define EP_C         0x03

extern UINT8 volatile USB_Power_Flag; // 0: bus power de-attached; 1: attached
extern UINT8 volatile Bulk_First_Flag;
extern UINT8 volatile USBModeFlag;    //way
extern UINT8 volatile bulkonlycmd;
extern UINT32 volatile USB_MEM_START;

VOID USBD_Init(VOID);
VOID USBD_Exit(VOID);
VOID USBD_Int_Init(VOID);
VOID USB_All_Flag_Clear(VOID);
#ifdef USE_VBUS
UINT Get_USB_Power(VOID);
INT volatile GET_USB_Status(VOID);
#endif

VOID INIT_MASSMEM(VOID);

void SDRAM2USB_Bulk(UINT32 DRAM_Addr ,UINT32 Tran_Size);
void USB2SDRAM_Bulk(UINT32 DRAM_Addr ,UINT32 Tran_Size);
void SDRAM2USB_Int(UINT32 DRAM_Addr ,UINT32 Tran_Size);


void MassBulk(void);
UINT8 Flash_Init(void);
VOID MASS_InitBuffer(VOID);


#define USB_OFF         0
#define USB_POWERED     2
#define USB_SUSPENDED   3
#define USB_DEFAULT     4

#endif
