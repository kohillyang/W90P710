/*
 * usb_capi.h
 *
 *  Created on: 2015Äê12ÔÂ5ÈÕ
 *      Author: kohill
 */

#ifdef __cplusplus
extern "C"
#endif
#include <stm32f4xx.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "usb_core.h"
#define D_COUNT 	printf(__FUNCTION__);\
					static int i = 0;i++;\
					printf(" %d \r\n",i);
extern USB_OTG_CORE_HANDLE USB_OTG_dev;
void usb_init(void);
#ifdef __cplusplus
}
#endif
