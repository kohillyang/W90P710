/*
 * led.c
 *
 *  Created on: 2014Äê11ÔÂ1ÈÕ
 *      Author: kohill
 */

#ifndef SRC_LED_C_
#define SRC_LED_C_
#include  "led.h"
#include "inc/tm4c123gh6pm.h"
void led_init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
	GPIO_PORTF_DIR_R |= (LED1_BIT)|(LED2_BIT)|(LED3_BIT);
	GPIO_PORTF_DEN_R |= (LED1_BIT)|(LED2_BIT)|(LED3_BIT);
}

bool ledIsOn(LED led) {
	return GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1)&led;
}

void ledOpen(uint32_t led) {
	GPIO_PORTF_DATA_R |= led;
}

void ledClose(uint32_t led) {
	GPIO_PORTF_DATA_R &= ~led;
}

#endif /* SRC_LED_C_ */
