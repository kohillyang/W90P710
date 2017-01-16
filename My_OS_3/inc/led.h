/*
 * led.h
 *
 *  Created on: 2014Äê11ÔÂ1ÈÕ
 *      Author: kohill
 */

#ifndef SRC_LED_H_

#include "inc/hw_memmap.h"
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define LED1_BIT 0x08
#define LED2_BIT 0x10
#define LED3_BIT 0x12
//led1 red
//led2 blue
//led3 green
typedef enum {
	green = 0x08, blue = 0x10, red = 0x12
} LED;
void led_init(void);
bool ledIsOn(LED led);
void ledOpen(uint32_t led);
void ledClose(uint32_t led);
#endif /* SRC_LED_H_ */
