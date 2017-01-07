/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   rtc_test.c
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The RTC test program
*
* DATA STRUCTURES
*   None
*
* FUNCTIONS
*   Display_RTC_Time
*   Display_week
*   rtc_irq
*   rtc_Item
*   RTC_Test
*
* HISTORY
*   2005-12-20    Ver 1.0 Created by NM51 YCChang
*
* REMARK
*   None
****************************************************************************/
#include <stdio.h>
//System Library
#include "wblib.h"

//NON OS Library
#include "rtc.h"
#define sysPrintf(...)
//Global variable
BOOL bRTCIRQFlag = 0;
PINT pnTickInterrupt;

//Function Definition
static VOID Display_RTC_Time(struct rtc_time rtc_value);
static VOID Display_week(UINT uWeek);
VOID rtc_irq(VOID);
static VOID rtc_Item(VOID);
INT RTC_Test(INT rtctest);

/****************************************************************************
* FUNCTION
*  rtc_irq
*
* DESCRIPTION
*   The ISR of RTC test program
*
* CALLED BY
*   various components
*
* INPUTS
*   None
*
* OUTPUTS
*   None
*
* HISTORY
*   NAME            DATE        REMARKS
*   NM51 YCChang    2005-12-20	Created initial version
*
* REMARK
*     None
****************************************************************************/
VOID rtc_irq(VOID)
{
    rtcIoctl(0, (INT)RTC_RD_TICK_INTERRUPT_REG, (UINT32)pnTickInterrupt, 0);
    if(*pnTickInterrupt == 1) /* tick */
    {

        bRTCIRQFlag = 1;
        *pnTickInterrupt = 0;
        //clear Interrupt flag
        rtcIoctl(0, (INT)RTC_CLEAR_TICK_INTERRUPT_REG, 0, 0);
    }
}

/****************************************************************************
* FUNCTION
*  RTC_Test
*
* DESCRIPTION
*   The main function of RTC test program
*
* CALLED BY
*   main
*
* INPUTS
*   None
*
* OUTPUTS
*   None
*
* HISTORY
*   NAME            DATE        REMARKS
*   NM51 YCChang    2005-12-20	Created initial version
*
* REMARK
*     None
****************************************************************************/
//VOID RTC_Test(VOID)
INT RTC_Test(INT rtctest)
{
#define	DEBUG_TEST_MODE
    INT nItem, nRIER = 1;
    struct rtc_time rtc_data, rtc_data2;

	rtc_data.tm_year = 2008;
	rtc_data.tm_mon = 2;
	rtc_data.tm_mday = 28;
	rtc_data.tm_hour = 23;
	rtc_data.tm_min = 59;
	rtc_data.tm_sec = 00;
	rtc_data.tm_week = THURSDAY;

    if( rtcInit() ==  RTC_INIT_ERR)
    {
        sysPrintf("RTC init fail!\n");
        return;
    }

    rtcOpen();

    #ifdef DEBUG_TEST_MODE
    sysPrintf("\nStart RTC test:\n");
    rtcWrite((INT)RTC_TICK, (UINT32)&rtc_data, 0);

    sysPrintf("Set RTC as 2008/02/28 23:59:00 Thursday\n");
    rtcRead((INT)RTC_TICK, (UINT32)&rtc_data2, 0);

    sysPrintf("Get RTC time:");
    Display_RTC_Time(rtc_data2);
    sysPrintf("\n");

    nItem = Successful;

    if(rtc_data2.tm_year != rtc_data.tm_year)
    {
        nItem = Fail;
    }
    else if(rtc_data2.tm_mon != rtc_data.tm_mon)
    {
        nItem = Fail;
    }
    else if(rtc_data2.tm_mday != rtc_data.tm_mday)
    {
        nItem = Fail;
    }
    else if(rtc_data2.tm_hour != rtc_data.tm_hour)
    {
        nItem = Fail;
    }
    else if(rtc_data2.tm_min != rtc_data.tm_min)
    {
        nItem = Fail;
    }
    else if(rtc_data2.tm_week != rtc_data.tm_week)
    {
        nItem = Fail;
    }
    if(nItem == Fail)
    {
//        sysGetChar();
    }
    return;

    #endif
     rtcRead((INT)RTC_TICK, (UINT32)&rtc_data2, 0);
                Display_RTC_Time(rtc_data2);

  /*  do
    {
        rtc_Item();// Show menu
        nItem = sysGetChar();// Get user key
        switch(nItem)
        {
            case '1':
            {
                sysPrintf("Set RTC as 2008/02/28 23:59:00 Thursday\n");
                rtcWrite((INT)RTC_TICK, (UINT32)&rtc_data, 0);
                sysPrintf("Press any key to continue....");
                sysGetChar();
                break;
            }
            case '2':
            {
                rtcRead((INT)RTC_TICK, (UINT32)&rtc_data2, 0);
                Display_RTC_Time(rtc_data2);
                sysPrintf("\nPress any key to continue....");
                sysGetChar();
                break;
            }
            case '3':
            {
                sysSetInterruptType(IRQ_RTC, HIGH_LEVEL_SENSITIVE);
                sysInstallISR(IRQ_LEVEL_1, IRQ_RTC, (PVOID)rtc_irq, 0);
                sysSetLocalInterrupt(ENABLE_IRQ);
                sysEnableInterrupt(IRQ_RTC);
                sysPrintf("Press any key to quit....\n");
                //enable RIER
                rtcIoctl(0, (INT)SET_RTC_TIE, (UINT32)&nRIER, 0);
                while(1)
                {
                    if(bRTCIRQFlag == 1)
                    {
                        rtcRead((INT)RTC_TICK, (UINT32)&rtc_data2, 0);
                        Display_RTC_Time(rtc_data2);
                        bRTCIRQFlag = 0;
                    }
                    if(inpb(REG_UART0_LSR) & 0x01)
                    {
                        sysGetChar();
                        break;
                    }
                }
                break;

            }
            default:    break;
        }
    }while(nItem != 27);*/  //do until user press ESC
}

/****************************************************************************
* FUNCTION
*  rtc_Item
*
* DESCRIPTION
*   This function shows the RTC test item
*
* CALLED BY
*   RTC_Test
*
* INPUTS
*   None
*
* OUTPUTS
*   None
*
* HISTORY
*   NAME            DATE        REMARKS
*   NM51 YCChang    2005-12-20	Created initial version
*
* REMARK
*     None
****************************************************************************/
static VOID rtc_Item(VOID)
{
    sysPrintf("\n\n\n");
    sysPrintf("+------------------------------------------------------+\n");
    sysPrintf("| Winbond RTC Diagonistic code                         |\n");
    sysPrintf("+------------------------------------------------------+\n");
    sysPrintf("| Set RTC Tick time                                [1] |\n");
    sysPrintf("| Get RTC Tick time                                [2] |\n");
    sysPrintf("| Display RTC ALL Value                            [3] |\n");
    sysPrintf("| Quit                                           [ESC] |\n");
    sysPrintf("+------------------------------------------------------+\n");
    sysPrintf("Please Select : \r\n");
}

/****************************************************************************
* FUNCTION
*  Display_RTC_Time
*
* DESCRIPTION
*   This function shows the RTC time
*
* CALLED BY
*   RTC_Test
*
* INPUTS
*   None
*
* OUTPUTS
*   None
*
* HISTORY
*   NAME            DATE        REMARKS
*   NM51 YCChang    2005-12-20	Created initial version
*
* REMARK
*     None
****************************************************************************/
static VOID Display_RTC_Time(struct rtc_time rtc_value)
{
    CHAR cYear[5] = {0};
    sprintf(cYear, "%d", rtc_value.tm_year);
    sysPrintf("\r                                          ");
    sysPrintf("\r");
    sysPrintf("%s", cYear);
    sysPrintf("/%02d", rtc_value.tm_mon);
    sysPrintf("/%02d", rtc_value.tm_mday);
    sysPrintf(" %02d", rtc_value.tm_hour);
    sysPrintf(":%02d", rtc_value.tm_min);
    sysPrintf(":%02d", rtc_value.tm_sec);
    sysPrintf(" ");
    Display_week(rtc_value.tm_week);
}

/****************************************************************************
* FUNCTION
*  Display_week
*
* DESCRIPTION
*   This function shows the RTC week information
*
* CALLED BY
*   Display_RTC_Time
*
* INPUTS
*   None
*
* OUTPUTS
*   None
*
* HISTORY
*   NAME            DATE        REMARKS
*   NM51 YCChang    2005-12-20	Created initial version
*
* REMARK
*     None
****************************************************************************/
static VOID Display_week(UINT uWeek)
{
    switch(uWeek)
    {
        case 0:     sysPrintf("Sunday");        break;
        case 1:     sysPrintf("Monday");        break;
        case 2:     sysPrintf("Tuseday");       break;
        case 3:     sysPrintf("Wednesday");     break;
        case 4:     sysPrintf("Thursday");      break;
        case 5:     sysPrintf("Friday");        break;
        case 6:     sysPrintf("Saturday");      break;
        default:    break;
    }
}
