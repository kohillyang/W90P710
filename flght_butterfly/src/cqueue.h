/*
 * cqueue.h
 *
 *  Created on: 2017Äê1ÔÂ25ÈÕ
 *      Author: kohill
 */

#ifndef CQUEUE_H_
#define CQUEUE_H_
#ifdef __cplusplus
extern "C"{
#endif
#include <stddef.h>
#include <stdint.h>

void nrf_send_buf_enque(const unsigned char *p,size_t len);
void nrf_send_buf_deque32(unsigned char *p);
size_t nrf_send_buf_getlen();

#ifdef __cplusplus
}
#endif
#endif /* CQUEUE_H_ */
