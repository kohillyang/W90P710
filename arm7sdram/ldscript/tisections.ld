/******************************************************************************
 *
 * interrupts.ld - Linker configuration file for interrupts.
 *
 * Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
 * Software License Agreement
 * 
 * Texas Instruments (TI) is supplying this software for use solely and
 * exclusively on TI's microcontroller products. The software is owned by
 * TI and/or its suppliers, and is protected under applicable copyright
 * laws. You may not combine this software with "viral" open-source
 * software in order to form a larger program.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 * NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
 * NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
 * CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 * 
 * This is part of revision 2.1.0.12573 of the DK-TM4C123G Firmware Package.
 *
 *****************************************************************************/
GROUP(
	libc.a
	libm.a
	libgcc.a
	librdimon.a
	Audio.a
	GPIO.a
	i2clib.a
	KPI_EVB.a
	LCDC.a
	MAC.a
	MassStroage_SingleTask.a
	ps2lib.a
	PWM.a
	rtclib.a
	sdiolib.a
	smartcardlib.a
	SYSLIB.a
	UART.a
	USB_Core_SingleTask.a
	USB_DEVICE_SD.a
	usilib.a
	WBFAT_SingleTask.a	
)
MEMORY
{
    FLASH (rwx) : ORIGIN = 0x00000000, LENGTH = 0x00000000
    SRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 4096k
}
PROVIDE ( _Heap_Begin = _end_noinit ) ;
PROVIDE ( _Heap_Limit = __stack - __Main_Stack_Size ) ;

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > SRAM

    .data : AT(ADDR(.text) + SIZEOF(.text))
    {
        _data = .;
        *(vtable)
        *(.data*)
        *(section i.*)
        _edata = .;
        end = .; /*Note : _sbrk need this*/
    } > SRAM
	.ARM.exidx : {
	    __exidx_start = .;
	    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
	    __exidx_end = .;
	} >SRAM
    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
        _end_noinit = .;   
    } > SRAM
}
