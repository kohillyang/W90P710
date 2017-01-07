/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   kpi.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of Winbond ARM7 MCU KPI device library
*
* HISTORY
*   12/22/05    Ver 1.0 Created by WTLiu
*
* REMARK
*
****************************************************************************/
#ifndef _KPI_H_
#define _KPI_H_

//Constants
#define KPI                     0
#define NONBLOCK_MODE           0
#define BLOCK_MODE              1


//ioctl command table
#define SET_KPICONF         0
#define SET_KPI3KCONF       1
#define SET_KPILPCONF       2
#define CLEAN_KPI_BUFFER    3

//KPICONF
typedef union
{
    UINT value;
    struct
    {
        UINT prescale:8,
            dbtc:8,
            ksize:2,enkp:1,kpsel:1,oden:1,encode:1,
            _reserved22_31:10;
    }KPICONF_field;
}KPICONF_union;
#define PRESCALE   (kpiconf.KPICONF_field.prescale)
#define DBTC       (kpiconf.KPICONF_field.dbtc)
#define KSIZE      (kpiconf.KPICONF_field.ksize)
#define ENKP       (kpiconf.KPICONF_field.enkp)
#define KPSEL      (kpiconf.KPICONF_field.kpsel)
#define ODEN       (kpiconf.KPICONF_field.oden)
#define ENCODE     (kpiconf.KPICONF_field.encode)

#define KSIZE_00            0x0
#define KSIZE_01            0x1
#define KSIZE_1X            0x3
#define ENKP_ENABLE         0x1
#define ENKP_DISABLE        0x0
#define KPSEL_PORT6         0x1
#define KPSEL_PORT25        0x0
#define ODEN_ENABLE         0x1
#define ODEN_DISABLE        0x0
#define ENCODE_ENABLE       0x1
#define ENCODE_DISABLE      0x0

//KPI3KCONF
typedef union
{
    UINT value;
    struct
    {
        UINT k30c:3,k30r:4,_reserved7:1,
            k31c:3,k31r:4,_reserved15:1,
            k32c:3,k32r:4,_reserved23:1,
            enrst:1,en3ky:1,
            _reserved26_31:6;
    }KPI3KCONF_field;
} KPI3KCONF_union;
#define K30C       (kpi3kconf.KPI3KCONF_field.k30c)
#define K30R       (kpi3kconf.KPI3KCONF_field.k30r)
#define K31C       (kpi3kconf.KPI3KCONF_field.k31c)
#define K31R       (kpi3kconf.KPI3KCONF_field.k31r)
#define K32C       (kpi3kconf.KPI3KCONF_field.k32c)
#define K32R       (kpi3kconf.KPI3KCONF_field.k32r)
#define ENRST      (kpi3kconf.KPI3KCONF_field.enrst)
#define EN3KY      (kpi3kconf.KPI3KCONF_field.en3ky)

#define ENRST_ENABLE    0x1
#define ENRST_DISABLE   0x0
#define EN3KY_ENABLE    0x1
#define EN3KY_DISABLE   0x0

//KPILPCONF
typedef union
{
    UINT value;
    struct
    {
        UINT lpwr:4,_reserved4_7:4,
            lpwcen:8,
            wake:1,
            _reserved17_31:15;
    }KPILPCONF_field;
} KPILPCONF_union;
#define LPWR    (kpilpconf.KPILPCONF_field.lpwr)
#define LPWCEN  (kpilpconf.KPILPCONF_field.lpwcen)
#define LPWAKE  (kpilpconf.KPILPCONF_field.wake)

#define WAKE_ENABLE     0x1
#define LPWCEN_COL0     1<<0
#define LPWCEN_COL1     1<<1
#define LPWCEN_COL2     1<<2
#define LPWCEN_COL3     1<<3
#define LPWCEN_COL4     1<<4
#define LPWCEN_COL5     1<<5
#define LPWCEN_COL6     1<<6
#define LPWCEN_COL7     1<<7

#define LPWR_4ROW0      0x1
#define LPWR_4ROW1      0x2
#define LPWR_4ROW2      0x4
#define LPWR_4ROW3      0x8

#define LPWR_ROW0       0x0
#define LPWR_ROW1       0x1
#define LPWR_ROW2       0x2
#define LPWR_ROW3       0x3
#define LPWR_ROW4       0x4
#define LPWR_ROW5       0x5
#define LPWR_ROW6       0x6
#define LPWR_ROW7       0x7
#define LPWR_ROW8       0x8
#define LPWR_ROW9       0x9
#define LPWR_ROW10      0xA
#define LPWR_ROW11      0xB
#define LPWR_ROW12      0xC
#define LPWR_ROW13      0xD
#define LPWR_ROW14      0xE
#define LPWR_ROW15      0xF

//KPISTATUS
typedef union
{
    UINT value;
    struct
    {
        UINT key0c:3,key0r:4,_reserved7:1,
            key1c:3,key1r:4,_reserved15:1,
            _1key:1,_2key:1,_3key:1,pdwake:1,_3krst:1,_int:1,
            _reserved22_31:10;
    }KPISTATUS_field;
}KPISTATUS_union;
#define KEY0C       (kpikey.KPISTATUS_field.key0c)
#define KEY0R       (kpikey.KPISTATUS_field.key0r)
#define KEY1C       (kpikey.KPISTATUS_field.key1c)
#define KEY1R       (kpikey.KPISTATUS_field.key1r)
#define _1KEY       (kpikey.KPISTATUS_field._1key)
#define _2KEY       (kpikey.KPISTATUS_field._2key)
#define _3KEY       (kpikey.KPISTATUS_field._3key)
#define PDWAKE      (kpikey.KPISTATUS_field.pdwake)
#define _3KRST      (kpikey.KPISTATUS_field._3krst)
#define _INT        (kpikey.KPISTATUS_field._int)

//KPI Error code
#define kpiReadModeError        (KEYPAD_ERR_ID|0x1)
#define kpiInvalidIoctlCommand  (KEYPAD_ERR_ID|0x2)
#define kpiNotOpen              (KEYPAD_ERR_ID|0x3)
#define kpiBusy                 (KEYPAD_ERR_ID|0x4)
#define kpiNoKey                (KEYPAD_ERR_ID|0x5)

// Function definition
extern INT kpiInit(VOID);
extern INT kpiExit(VOID);
extern INT kpiOpen(CONST INT nDevIdentity);
extern INT kpiClose(CONST INT nDevIdentity);
extern INT kpiRead(CONST INT nDevIdentity, PUCHAR key, CONST UINT uReadMode);
extern INT kpiIoctl(CONST INT nDevIdentity,CONST UINT uCommand, CONST UINT uIndication, UINT uValue);

#endif
