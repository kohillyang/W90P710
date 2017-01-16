/*
 * task.c
 *
 *  Created on: 2015Äê1ÔÂ14ÈÕ
 *      Author: kohill
 */

#include "task.h"
#include "public_header.h"
#include "led.h"
void delay() {
	int i = 0;
	for (i = 0; i < 0xfffff; i++)
		;
}
void Delay() {
	int i = 0;
	for (i = 0; i < 1; i++)
		;
}
void led1_task() {
	static bool _islight = true;
	while (1) {
		if(_islight){
			ledClose(red);
			_islight =!_islight;
			delay();
		}
		else{
			_islight =!_islight;
			ledOpen(red);
			delay();
		}
	};
}
void led2_task() {
	static bool _islight = true;
	while (1) {
		if(_islight){
			ledClose(green);
			_islight =!_islight;
			delay();
		}
		else{
			_islight =!_islight;
			ledOpen(green);
			delay();
		}
	};
}
void led3_task() {
	static bool _islight = true;
	while (1) {
		ledOpen(red);
	}
}
