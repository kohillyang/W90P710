
#include <GUI.h>
#include <LISTVIEW.h>
#include <FRAMEWIN.h>
#include <WM.h>
#include <stddef.h>
#include <stdint.h>
#include <PROGBAR.h>
#include <stdbool.h>
#include <stdio.h>
#include <HEADER.h>
#include <TEXT.h>
#include <SLIDER.h>
#include <string.h>
static unsigned char saveDtmp[16];
void EEPROMRead(void *p,unsigned int addr,unsigned int sizeB);
void EEPROMProgram(void *p,unsigned int addr,unsigned int sizeB);
void EEPROMRead(void *p,unsigned int addr,unsigned int sizeB){
	memcpy(p,(unsigned char *)saveDtmp+addr,sizeB);
}
void EEPROMProgram(void *p,unsigned int addr,unsigned int sizeB){
	memcpy((unsigned char *)saveDtmp+addr,p,sizeB);
}
//FRAMEWIN_Handle frameHandle;
LISTVIEW_Handle listviewHandle;
PROGBAR_Handle progressHandle;
HEADER_Handle headerHandle;
TEXT_Handle hText;
SLIDER_Handle hSlider;
WM_HWIN hWin;
WM_HWIN hWinLmh6401;

extern GUI_CONST_STORAGE GUI_FONT GUI_FontLight16;

const char* ppText[][3]=
{
	{"-20dB","0.10","0.00V"},
	{"-19dB","0.11","0.12V"},
	{"-18dB","0.13","0.25V"},
	{"-17dB","0.14","0.38V"},
	{"-16dB","0.16","0.50V"},
	{"-15dB","0.18","0.62V"},
	{"-14dB","0.20","0.75V"},
	{"-13dB","0.22","0.88V"},
	{"-12dB","0.25","1.00V"},
	{"-11dB","0.28","1.12V"},
	{"-10dB","0.32","1.25V"},
	{" -9dB","0.35","1.38V"},
	{" -8dB","0.40","1.50V"},
	{" -7dB","0.45","1.62V"},
	{" -6dB","0.50","1.75V"},
	{" -5dB","0.56","1.88V"},
	{" -4dB","0.63","2.00V"},
	{" -3dB","0.71","2.12V"},
	{" -2dB","0.79","2.25V"},
	{" -1dB","0.89","2.38V"},
	{"  0dB","1.00","2.50V"},
	{"  1dB","1.12","2.62V"},
	{"  2dB","1.26","2.75V"},
	{"  3dB","1.41","2.88V"},
	{"  4dB","1.58","3.00V"},
	{"  5dB","1.78","3.12V"},
	{"  6dB","2.00","3.25V"},
	{"  7dB","2.24","3.38V"},
	{"  8dB","2.51","3.50V"},
	{"  9dB","2.82","3.62V"},
	{" 10dB","3.16","3.75V"},
	{" 11dB","3.55","3.88V"},
	{" 12dB","3.98","4.00V"},
	{" 13dB","4.47","4.12V"},
	{" 14dB","5.01","4.25V"},
	{" 15dB","5.62","4.38V"},
	{" 16dB","6.31","4.50V"},
	{" 17dB","7.08","4.62V"},
	{" 18dB","7.94","4.75V"},
	{" 19dB","8.91","4.88V"},
	{" 20dB","10.00","5.00V"},

};
typedef struct{
	uint32_t index;
	uint32_t voltage;
}WM_USER_STRUCT;

void mainWindowCB(WM_MESSAGE *pMsg){
	WM_USER_STRUCT st;
	switch (pMsg->MsgId) {
	case WM_PAINT:
		GUI_Clear();
		GUI_SetFont(&GUI_FontLight16);
		GUI_DispStringHCenterAt("可变增益宽带放大器", GUI_GetScreenSizeX() / 2, 0);
		GUI_DispStringHCenterAt(GUI_GetVersionString(), GUI_GetScreenSizeX() / 2, 0);
		break;
	case WM_KEY:
		WM_GetUserData(hWin,&st,sizeof(WM_USER_STRUCT));

		switch (((WM_KEY_INFO*) (pMsg->Data.p))->Key) {
		case GUI_KEY_DOWN:
			if(st.index==0){
				break;
			}
			st.index--;
			break;
		case GUI_KEY_UP:
			if(st.index==(GUI_COUNTOF(ppText)-1)){
				break;
			}
			st.index++;
			break;
		case GUI_KEY_TAB:
			WM_HideWindow(pMsg->hWin);
			WM_ShowWindow(hWinLmh6401);
			WM_SetFocus(hWinLmh6401);

			break;

		}
		LISTVIEW_DeleteAllRows(listviewHandle);
		LISTVIEW_AddRow(listviewHandle,ppText[st.index]);
		SLIDER_SetValue(hSlider,st.index);
		//tlc5615setVoltage(1024*st.index/GUI_COUNTOF(ppText));
		EEPROMProgram((uint32_t*)&st,0,sizeof(WM_USER_STRUCT));
		WM_SetUserData(hWin,&st,sizeof(WM_USER_STRUCT));
	}
}
void lmh6401CB(WM_MESSAGE *pMsg){
	int db;
	EEPROMRead((uint32_t *)&db,8,sizeof(int));

	switch (pMsg->MsgId) {
	case WM_PAINT:
		GUI_Clear();
		GUI_DispStringHCenterAt("Lmh6401 Control Panel", 128 / 2, 0);
		GUI_SetFont(GUI_FONT_4X6);
		GUI_DispStringHCenterAt("CS--PF1 SDO--PF3 CLK--PE3", 128 / 2, 8);
		char buf[32];
		sprintf(buf,"%2ddB",(int)db);
		GUI_DispStringHCenterAt(buf, 128 / 2, 16);
		break;
	case WM_KEY:

		switch (((WM_KEY_INFO*) (pMsg->Data.p))->Key) {
		case GUI_KEY_DOWN:
			if(db<=-6){
				break;
			}
			db--;
			break;
		case GUI_KEY_UP:
			if(db>=26){
				break;
			}
			db++;
			break;
		case GUI_KEY_TAB:
			WM_HideWindow(pMsg->hWin);
			WM_ShowWindow(hWin);
			WM_SetFocus(hWin);
			break;
		}
//		lm6401setGain(db);
		EEPROMProgram((uint32_t*)&db,8,sizeof(WM_USER_STRUCT));
		WM_Paint(pMsg->hWin);
	}

}

void gui_init(){
	__asm("cpsid i");
	GUI_UC_SetEncodeUTF8();
	GUI_AA_SetFactor(1);
	hWin= WM_CreateWindow(0,0,320,200,WM_CF_SHOW,mainWindowCB,8);
	listviewHandle = LISTVIEW_CreateEx(0,16,0,0,hWin,WM_CF_SHOW,0,GUI_ID_LISTVIEW0);
	LISTVIEW_SetFont(listviewHandle,GUI_FONT_8X13_ASCII);
	LISTVIEW_SetDefaultFont(GUI_FONT_8X16_1);
	LISTVIEW_SetFixed(listviewHandle,3);
	LISTVIEW_AddColumn(listviewHandle, 42, "(DB)",GUI_TA_CENTER);
	LISTVIEW_AddColumn(listviewHandle, 40, "(V/V)",GUI_TA_CENTER);
	LISTVIEW_AddColumn(listviewHandle, 40, "V",GUI_TA_CENTER);
	LISTVIEW_SetGridVis(listviewHandle,true);
	LISTVIEW_SetDefaultBkColor(LISTVIEW_CI_SEL,0);
	LISTVIEW_SetDefaultTextColor(1,0);
	LISTVIEW_SetTextColor(listviewHandle,LISTVIEW_CI_SEL,0);
	LISTVIEW_SetFont(listviewHandle,GUI_FONT_6X9);
	LISTVIEW_AddRow(listviewHandle,ppText[0]);
	LISTVIEW_SetSel(listviewHandle,0);
	hSlider = SLIDER_Create(0,48,0,0,hWin,GUI_ID_SLIDER0,WM_CF_SHOW,0);
	SLIDER_SetRange(hSlider,0,40);
	SLIDER_SetNumTicks(hSlider,GUI_COUNTOF(ppText));
	WM_USER_STRUCT st;
	EEPROMRead((uint32_t *)&st,0,sizeof(WM_USER_STRUCT));
	LISTVIEW_DeleteAllRows(listviewHandle);
	LISTVIEW_AddRow(listviewHandle,ppText[st.index]);
	SLIDER_SetValue(hSlider,st.index);
	EEPROMProgram((uint32_t*)&st,0,sizeof(WM_USER_STRUCT));
	WM_SetUserData(hWin,&st,sizeof(WM_USER_STRUCT));
	hWinLmh6401 = WM_CreateWindow(0,0,128,64,WM_CF_HIDE,lmh6401CB,8);
	EEPROMRead((uint32_t *)&st,8,sizeof(WM_USER_STRUCT));
	WM_SetUserData(hWinLmh6401,&st,sizeof(WM_USER_STRUCT));
	__asm("cpsie i");
	WM_SetFocus(hWin);

}

