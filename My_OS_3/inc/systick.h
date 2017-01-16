/*
 * systick.h
 *
 *  Created on: 2015Äê1ÔÂ16ÈÕ
 *      Author: kohill
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <stdbool.h>
#include <stdint.h>
void SystickInit(uint32_t count,bool openInterrupt,bool openSystemInterrupt);
#endif /* SYSTICK_H_ */
