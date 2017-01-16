/*
 * callbcak.h
 *
 *  Created on: 2016Äê6ÔÂ3ÈÕ
 *      Author: yks
 */

#ifndef GUI_CALLBCAK_H_
#define GUI_CALLBCAK_H_
#include <stdio.h>
#define ID_FRAMEWIN_AGC_PANEL (GUI_ID_USER + 0x08)
//#define ID_BUTTON_0 (GUI_ID_USER + 0x0A)

//#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)
#define ID_BUTTON_UP     (GUI_ID_USER + 0x01)
#define ID_BUTTON_DOWN     (GUI_ID_USER + 0x02)
#define ID_BUTTON_SW     (GUI_ID_USER + 0x03)
#define ID_SLIDER_0     (GUI_ID_USER + 0x04)

#define ID_TEXT_TITLE     (GUI_ID_USER + 0x05)
#define ID_TEXT_1     (GUI_ID_USER + 0x06)
#define ID_TEXT_2     (GUI_ID_USER + 0x07)
#define ID_TEXT_GAIN     (GUI_ID_USER + 0x07)
#define DAC_CH_AGC DAC_Channel_2
#define DAC_AGC_SET(x) DAC_SetChannel2Data(DAC_Align_12b_R,x)
#endif /* GUI_CALLBCAK_H_ */
