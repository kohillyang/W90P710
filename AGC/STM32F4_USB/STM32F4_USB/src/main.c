/*
 * main.c
 *
 *  Created on: 2016��1��7��
 *      Author: kohill
 */
#include <stm32f4xx.h>
#include <GUI.h>
#include <stdio.h>
#include "kohill/fastconfig.h"
#include "board/board.h"
#include "gui/kgui.h"
#include "touch.h"
#include "kohill/fastconfig.h"
#include "jianboqi.h"
int main(void);

int main(){

  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);
	Touch_Init();
	k_DAC_Fast_Config();
	GUI_Init();
	GUI_UC_SetEncodeUTF8();
	CreateAGC_Panel();
	jianboqi_init();
	DAC_SetChannel1Data(DAC_Align_12b_R,0);
	while(1){
		GUI_Exec();
		WM_Exec();
		GUI_TOUCH_Exec();
	}

};
