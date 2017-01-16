/*
 * resetHandler.S
 *
 *  Created on: 2015Äê1ÔÂ19ÈÕ
 *      Author: kohill
 */
.type resetHandler function
.type getPspTop function
.type main function
.global resetHandler
resetHandler:
	push {r0,lr}
	bl ResetISR
	bl getPspTop
	msr psp,r0
	mov r0,#0x03
	msr control,r0
	bl main
	pop {r0,pc}



