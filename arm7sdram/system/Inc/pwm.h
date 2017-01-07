/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   pwm.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of Winbond ARM7 MCU PWM device library
*
* HISTORY
*   12/23/05    Ver 1.0 Created by WTLiu
*
* REMARK
*   None
****************************************************************************/
#ifndef _PWM_H_
#define _PWM_H_

// Timer channel identity information
#define PWM_TIMER_NUM   4
#define PWM_TIMER_MIN   0
#define PWM_TIMER_MAX   3
#define PWM_TIMER0      0
#define PWM_TIMER1      1
#define PWM_TIMER2      2
#define PWM_TIMER3      3

//ioctl command
#define START_PWMTIMER          0
#define STOP_PWMTIMER           1
#define SET_CSR                 2
#define SET_CP                  3
#define SET_DZI                 4
#define SET_INVERTER            5
#define SET_MODE                6
#define ENABLE_DZ_GENERATOR     7
#define DISABLE_DZ_GENERATOR    8
#define ENABLE_PWMGPIOOUTPUT    9

#define PWM_STOP_METHOD1    1
#define PWM_STOP_METHOD2    2
//#define PWM_STOP_METHOD3  3 not recommended

//Timer default value
#define DEFAULT_CSR     CSRD16
#define DEFAULT_CP      255
#define DEFAULT_DZI     50
#define DEFAULT_CNR     19531
#define DEFAULT_CMR     (19531/4)
#define DEFAULT_MODE    PWM_TOGGLE

// for PWM_PPR
#define DZI_MIN     0
#define DZI_MAX     255
#define CP_MIN      0
#define CP_MAX      255

typedef union
{
    UINT value;
    struct
    {
        UINT cp0:8,cp1:8,dzi0:8,dzi1:8;
    }field;
}typePPR;

// for PWM_CSR
#define CSR_MIN     0
#define CSR_MAX     4
#define CSRD2       0x0
#define CSRD4       0x1
#define CSRD8       0x2
#define CSRD16      0x3
#define CSRD1       0x4

typedef union
{
    UINT value;
    struct
    {
        UINT   csr0:3, _reserved3:1,
               csr1:3, _reserved7:1,
               csr2:3, _reserved11:1,
               csr3:3, _reserved15:1,
               _reserved16_31:16;
    }field;
}typeCSR;

// for PWM_PCR
#define PWMDZG_ENABLE   1
#define PWMDZG_DISABLE  0
#define PWM_ENABLE      1
#define PWM_DISABLE     0
#define PWM_TOGGLE      1
#define PWM_ONESHOT     0
#define PWM_INVON       1
#define PWM_INVOFF      0

typedef union
{
    UINT value;
    struct
    {
        UINT   ch0_en:1,_reserved1:1,ch0_inverter:1,ch0_mode:1,
               grpup0_dzen:1,grpup1_dzen:1,
               _reserved6_7:2,
               ch1_en:1,_reserved9:1, ch1_inverter:1,ch1_mode:1,
               ch2_en:1,_reserved13:1,ch2_inverter:1,ch2_mode:1,
               ch3_en:1,_reserved17:1,ch3_inverter:1,ch3_mode:1,
               _reserved20_31:12;
    }field;
}typePCR;



// for PWM_CNR
#define CNR_MIN     0
#define CNR_MAX     65535

typedef union
{
    UINT value;
    struct
    {
        UINT cnr:16,_reserved16_31:16;
    }field;
}typeCNR;

// for PWM_CMR
#define CMR_MIN     0
#define CMR_MAX     65535

typedef union
{
    UINT value;
    struct
    {
        UINT cmr:16,_reserved16_31:16;
    }field;
}typeCMR;

// for write operation
typedef union
{
    UINT value;
    struct
    {
        UINT cnr:16,cmr:16;
    }field;
}typeTIMERVALUE;

// for read operation
typedef struct
{
    UINT volatile PDR;
    BOOL volatile InterruptFlag;
    BOOL _reversed0;
    BOOL _reversed1;
    BOOL _reversed2;
}typePWMSTATUS;

//PWM Error code
#define pwmInvalidTimerChannel  (PWM_ERR_ID|1)
#define pwmInvalidStructLength  (PWM_ERR_ID|2)
#define pwmInvalidIoctlCommand  (PWM_ERR_ID|3)
#define pwmInvalidStopMethod    (PWM_ERR_ID|4)
#define pwmInvalidCPValue       (PWM_ERR_ID|5)
#define pwmInvalidDZIValue      (PWM_ERR_ID|6)
#define pwmInvalidCSRValue      (PWM_ERR_ID|7)
#define pwmInvalidDZGStatus     (PWM_ERR_ID|8)
#define pwmInvalidTimerStatus   (PWM_ERR_ID|9)
#define pwmInvalidInverterValue (PWM_ERR_ID|10)
#define pwmInvalidModeStatus    (PWM_ERR_ID|11)
#define pwmInvalidCNRValue      (PWM_ERR_ID|12)
#define pwmInvalidCMRValue      (PWM_ERR_ID|13)
#define pwmTimerNotOpen         (PWM_ERR_ID|14)
#define pwmTimerBusy            (PWM_ERR_ID|15)

// function definition
extern INT pwmInit(VOID);
extern INT pwmExit(VOID);
extern INT pwmOpen(CONST INT nTimerIdentity);
extern INT pwmClose(CONST INT nTimerIdentity);
extern INT pwmRead(CONST INT nTimerIdentity, PUCHAR pucStatusValue, CONST UINT uLength);
extern INT pwmWrite(CONST INT nTimerIdentity, PUCHAR pucCNRCMRValue, CONST UINT uLength);
extern INT pwmIoctl(CONST INT nTimerIdentity, CONST UINT uCommand, CONST UINT uIndication, UINT uValue);

#endif
