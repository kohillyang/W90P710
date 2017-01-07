/*
 * W90P710.h
 *
 *  Created on: 2016Äê10ÔÂ23ÈÕ
 *      Author: kohill
 */

#ifndef W90P710_H_
#define W90P710_H_

#include "710defs.h"

/* Register access definitions                                                */
#define Reg8(adr)  (*((volatile unsigned char  *) (adr)))
#define Reg16(adr) (*((volatile unsigned short *) (adr)))
#define Reg32(adr) (*((volatile unsigned long  *) (adr)))

#endif /* W90P710_H_ */
