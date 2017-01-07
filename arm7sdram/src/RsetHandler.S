/*
 * RsetHandler.S
 *
 *  Created on: 2016Äê10ÔÂ23ÈÕ
 *      Author: kohill
 */
.global ResetISR
.global ResetISR_C
.global IRQ_Handler
.global __rt_udiv10
#define Stack_Top (8*1024*1024 + 0x00)
#define Mode_USR 0x10
#define Mode_FIQ 0x11
#define Mode_IRQ 0x12
#define Mode_SVC 0x13
#define Mode_ABT 0x17
#define Mode_UND 0x1B
#define Mode_SYS 0x1F

#define I_Bit    0x80//            ; when I bit is set, IRQ is disabled
#define F_Bit    0x40//            ; when F bit is set, FIQ is disabled
#define UND_Stack_Size 0x00000000
#define SVC_Stack_Size 0x00000008
#define ABT_Stack_Size 0x00000000
#define FIQ_Stack_Size 0x00000000
#define IRQ_Stack_Size 0x00000080
#define USR_Stack_Size 0x00000400



.section .isr_vector
ResetISR:
	b init
	b .
	b .
	b .
	SUBS PC, R14, #8
	b .
	b IRQ_Handler
	b .

init:

	LDR     R0, =Stack_Top
// Enter Undefined Instruction Mode and set its Stack Pointer
	MSR     CPSR_c, #( Mode_UND |F_Bit|I_Bit)
    MOV     SP, R0
    SUB     R0, R0, #UND_Stack_Size

//;  Enter Abort Mode and set its Stack Pointer
    MSR     CPSR_c, #Mode_ABT|I_Bit|F_Bit
    MOV     SP, R0
    SUB     R0, R0, #ABT_Stack_Size

//;  Enter FIQ Mode and set its Stack Pointer
    MSR     CPSR_c, #Mode_FIQ|I_Bit|F_Bit
    MOV     SP, R0
    SUB     R0, R0, #FIQ_Stack_Size

//;  Enter IRQ Mode and set its Stack Pointer
    MSR     CPSR_c, #Mode_IRQ|I_Bit|F_Bit
    MOV     SP, R0
    SUB     R0, R0, #IRQ_Stack_Size

//;  Enter Supervisor Mode and set its Stack Pointer
	MSR     CPSR_c, #Mode_SVC|I_Bit|F_Bit
	MOV     SP, R0
	SUB     R0, R0, #SVC_Stack_Size

//	;  Enter User Mode and set its Stack Pointer
    MSR     CPSR_c, #Mode_USR
	MOV     SP, R0
	SUB     SL, SP, #USR_Stack_Size
	b ResetISR_C
__rt_udiv10:
    sub   r1,r0,#10            /* might be less than 10 but */
                               /* dont special case, constant exec time */
    sub   r0,r0,r0,lsr #2      /* (1-2^-2) [3/4] */
    add   r0,r0,r0,lsr #4      /* (1+2^-4)  */
    add   r0,r0,r0,lsr #8      /* (1+2^-8)  */
    add   r0,r0,r0,lsr #16     /* (1+2^-16) */
    mov   r0,r0,lsr #3         /* 2^-3 left to do */

    /* We are done but.. this could be off by 1 (truncation of rep(3))
     * Its cheap to multiply back by 10 and check it over.
     * Besides, dont we need the remainder anyways.
     */
#if defined(ADS)
    add   r3,r0,r0,lsl #2      /* times 5.. */
    subs  r1,r1,r3,lsl #1      /* ..times 2 is (Quotient*10)  */
                               /* Take it away from (Dividend-10) */
#else
    add   r3,r0,r0,asl #2      /* times 5.. */
    subs  r1,r1,r3,asl #1      /* ..times 2 is (Quotient*10)  */
                               /* Take it away from (Dividend-10) */
#endif
    addmi r1,r1,#10            /* too much ? add 10 back into remainder */
    addpl r0,r0,#1             /* otherwise adjust the result */

    /* Done
     */
    mov   pc,lr


