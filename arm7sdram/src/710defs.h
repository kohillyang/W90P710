/**************************************************************************************************
 *
 * Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.
 *
 * FILENAME
 *     w90p710.h
 *
 * VERSION
 *     0.1
 *
 * DESCRIPTION
 *     This file contains the register map of W90P710 processor.
 *
 *     1. System Address Map
 *     2. System Manager Control Registers
 *     3. EBI
 *     4. SDRAM
 *     5. PCI
 *     6. MAC
 *     7. NATA
 *     8. GDMA
 *     9. USB Host Controller
 *    10. Network Security Engine
 *    11. UART
 *    12. Timer
 *    13. AIC
 *    14. GPIO
 *
 * HISTORY
 *     2004/11/04		 0.1 Draft version, Created by PC30 MNCheng
 *
 *
 * REMARK
 *     None
 *
 *************************************************************************************************/
#ifndef _W90P710_H
#define _W90P710_H

/****************************************************************************************************
 *
 * Data Types
 *
 ****************************************************************************************************/
#include <stdint.H>
typedef signed char  int8;
typedef unsigned char  uint8;
typedef int16_t          int16;
typedef uint16_t uint16;
typedef int32_t            int32;
typedef uint32_t   uint32;
typedef uint32_t   UINT;

#define S8    signed char
#define S16   signed short
#define S32   signed int
#define U8    unsigned char
#define U16   unsigned short

#define REG8  unsigned char volatile
#define REG16 unsigned short volatile
#define REG32 unsigned int volatile
#define BYTE  U8


/****************************************************************************************************
 *
 * I/O routines
 *
 ****************************************************************************************************/
#define VPint   			*(unsigned int volatile *)
#define VPshort 			*(unsigned short volatile *)
#define VPchar  			*(unsigned char volatile *)

#define outpw(port,value)	port=value
#define inpw(port)			port


/****************************************************************************************************
 *
 * 1. System Address Map
 *
 ****************************************************************************************************/
/* SDRAM Interface */
//#define DRAM_Base				0x00000000  /* ~ 0x1FFFFFFF, 512MB */

/* On-chip Modules */
#define AHB_IO_BASE				0xFFF00000
#define APB_IO_BASE				0xFFF80000

#if 0
/* External Bus Interface */
#define ExtIO_Mem_Base			0xC0000000  /* ~ 0xCFFFFFFF, 256MB */
#define PCI_IO_Base				0xD0000000  /* ~ 0xDFFFFFFF, 256MB for PCI I/O access */
#define PCI_Mem_Base			0xE0000000  /* ~ 0xEFFFFFFF, 256MB for PCI Memory access */
#define PCMCIA_CommMem_Base		0xF0000000  /* ~ 0xF3FFFFFF, 64MB for PCMCIA Common Memory access */
#define PCMCIA_AtribMem_Base	0xF4000000  /* ~ 0xF7FFFFFF, 64MB for PCMCIA Attribute Memory access */
#define PCMCIA_IO_Base			0xF8000000  /* ~ 0xFBFFFFFF, 64MB for PCMCIA I/O access */
#define bootROM_Base			0xFE000000  /* ~ 0xFFFFFFFF, 64MB for boot ROM */
#endif


/****************************************************************************************************
 *
 * 2. System Manager Control Registers
 *
 ****************************************************************************************************/
#define REG_PDID		(VPint(AHB_IO_BASE+0x0000))	/* Product Identifier Register  */
#define REG_ARBCON		(VPint(AHB_IO_BASE+0x0004))	/* Arbitration Control Register */
#define REG_PLLCON		(VPint(AHB_IO_BASE+0x0008))	/* PLL Control Register */
#define REG_CLKSEL		(VPint(AHB_IO_BASE+0x000C))	/* Clock Select Register */
#define REG_PMCON		(VPint(AHB_IO_BASE+0x0010))	/* Power Management Register */


/****************************************************************************************************
 *
 * 3. Memory Control Registers
 *
 ****************************************************************************************************/
#define REG_EBICON		(VPint(AHB_IO_BASE+0x1000))	/* EBI control register */
#define REG_ROMCON		(VPint(AHB_IO_BASE+0x1004))	/* ROM/FLASH control register */
#define REG_SDCONF0		(VPint(AHB_IO_BASE+0x1008))	/* SDRAM bank 0 configuration register */
#define REG_SDCONF1		(VPint(AHB_IO_BASE+0x100C))	/* SDRAM bank 1 configuration register */
#define REG_SDTIME0		(VPint(AHB_IO_BASE+0x1010))	/* SDRAM bank 0 timing control register */
#define REG_SDTIME1		(VPint(AHB_IO_BASE+0x1014))	/* SDRAM bank 1 timing control register */
#define REG_EXT0CON		(VPint(AHB_IO_BASE+0x1018))	/* External I/O 0 control register */
#define REG_EXT1CON		(VPint(AHB_IO_BASE+0x101C))	/* External I/O 1 control register */
#define REG_EXT2CON		(VPint(AHB_IO_BASE+0x1020))	/* External I/O 2 control register */
#define REG_EXT3CON		(VPint(AHB_IO_BASE+0x1024))	/* External I/O 3 control register */


/****************************************************************************************************
 *
 * 6. MAC Registers
 *
 ****************************************************************************************************/
	/* Control register */
#define REG_CAMCMR			(VPint(AHB_IO_BASE+0x3000))	/* CAM Command Register */
#define REG_CAMEN			(VPint(AHB_IO_BASE+0x3004))	/* CAM Enable Register */
#define REG_CAM0M_Base		(VPint(AHB_IO_BASE+0x3008))
#define REG_CAM0L_Base		(VPint(AHB_IO_BASE+0x300c))
#define REG_CAMxM_Reg(x)	(REG_CAM0M_Base+x*0x8)		/*  */
#define REG_CAMxL_Reg(x)	(REG_CAM0L_Base+x*0x8)		/*  */

#define REG_TXDLSA			(VPint(AHB_IO_BASE+0x3088))	/* Transmit Descriptor Link List Start Address Register */
#define REG_RXDLSA			(VPint(AHB_IO_BASE+0x308C))	/* Receive Descriptor Link List Start Address Register */
#define REG_MCMDR			(VPint(AHB_IO_BASE+0x3090))	/* MAC Command Register */
#define REG_MIID			(VPint(AHB_IO_BASE+0x3094))	/* MII Management Data Register */
#define REG_MIIDA			(VPint(AHB_IO_BASE+0x3098))	/* MII Management Control and Address Register */
#define REG_FFTCR			(VPint(AHB_IO_BASE+0x309C))	/* FIFO Threshold Control Register */
#define REG_TSDR			(VPint(AHB_IO_BASE+0x30a0))	/* Transmit Start Demand Register */
#define REG_RSDR			(VPint(AHB_IO_BASE+0x30a4))	/* Receive Start Demand Register */
#define REG_DMARFC			(VPint(AHB_IO_BASE+0x30a8))	/* Maximum Receive Frame Control Register */
#define REG_MIEN			(VPint(AHB_IO_BASE+0x30ac))	/* MAC Interrupt Enable Register */
	/* Status Registers */
#define REG_MISTA			(VPint(AHB_IO_BASE+0x30b0))	/* MAC Interrupt Status Register */
#define REG_MGSTA			(VPint(AHB_IO_BASE+0x30b4))	/* MAC General Status Register */
#define REG_MPCNT			(VPint(AHB_IO_BASE+0x30b8))	/* Missed Packet Count Register */
#define REG_MRPC			(VPint(AHB_IO_BASE+0x30bc))	/* MAC Receive Pause Count Register */
#define REG_MRPCC			(VPint(AHB_IO_BASE+0x30c0))	/* MAC Receive Pause Current Count Register */
#define REG_MREPC			(VPint(AHB_IO_BASE+0x30c4))	/* MAC Remote Pause Count Register */
#define REG_DMARFS			(VPint(AHB_IO_BASE+0x30c8))	/* DMA Receive Frame Status Register */
#define REG_CTXDSA			(VPint(AHB_IO_BASE+0x30cc))	/* Current Transmit Descriptor Start Address Register */
#define REG_CTXBSA			(VPint(AHB_IO_BASE+0x30d0))	/* Current Transmit Buffer Start Address Register */
#define REG_CRXDSA			(VPint(AHB_IO_BASE+0x30d4))	/* Current Receive Descriptor Start Address Register */
#define REG_CRXBSA			(VPint(AHB_IO_BASE+0x30d8))	/* Current Receive Buffer Start Address Register */
	/* Diagnostic Registers */
#define REG_RXFSM			(VPint(AHB_IO_BASE+0x3200))	/* Receive Finite State Machine Register */
#define REG_TXFSM			(VPint(AHB_IO_BASE+0x3204))	/* Transmit Finite State Machine Register */
#define REG_FSM0			(VPint(AHB_IO_BASE+0x3208))	/* Finite State Machine Register 0 */
#define REG_FSM1			(VPint(AHB_IO_BASE+0x320c))	/* Finite State Machine Register 1 */
#define REG_DCR				(VPint(AHB_IO_BASE+0x3210))	/* Debug Configuration Register */
#define REG_DMMIR			(VPint(AHB_IO_BASE+0x3214))	/* Debug Mode MAC Information Register */
#define REG_BISTR			(VPint(AHB_IO_BASE+0x3300))	/* BIST Mode Register */


/****************************************************************************************************
 *
 * 8. GDMA Registers
 *
 ****************************************************************************************************/
#define REG_GDMA_CTL0		(VPint(AHB_IO_BASE+0x4000))  /* Channel 0 Control Register */
#define REG_GDMA_SRCB0		(VPint(AHB_IO_BASE+0x4004))  /* Channel 0 Source Base Address Register */
#define REG_GDMA_DSTB0		(VPint(AHB_IO_BASE+0x4008))  /* Channel 0 Destination Base Address Register */
#define REG_GDMA_TCNT0		(VPint(AHB_IO_BASE+0x400C))  /* Channel 0 Transfer Count Register */
#define REG_GDMA_CSRC0		(VPint(AHB_IO_BASE+0x4010))  /* Channel 0 Current Source Address Register */
#define REG_GDMA_CDST0		(VPint(AHB_IO_BASE+0x4014))  /* Channel 0 Current Destination Address Register */
#define REG_GDMA_CTCNT0		(VPint(AHB_IO_BASE+0x4018))  /* Channel 0 Current Transfer Count Register */
#define REG_GDMA_CTL1		(VPint(AHB_IO_BASE+0x4020))  /* Channel 1 Control Register */
#define REG_GDMA_SRCB1		(VPint(AHB_IO_BASE+0x4024))  /* Channel 1 Source Base Address Register */
#define REG_GDMA_DSTB1		(VPint(AHB_IO_BASE+0x4028))  /* Channel 1 Destination Base Address Register */
#define REG_GDMA_TCNT1		(VPint(AHB_IO_BASE+0x402C))  /* Channel 1 Transfer Count Register */
#define REG_GDMA_CSRC1		(VPint(AHB_IO_BASE+0x4030))  /* Channel 1 Current Source Address Register */
#define REG_GDMA_CDST1		(VPint(AHB_IO_BASE+0x4034))  /* Channel 1 Current Destination Address Register */
#define REG_GDMA_CTCNT1		(VPint(AHB_IO_BASE+0x4038))  /* Channel 1 Current Transfer Count Register */


/****************************************************************************************************
 *
 * 9. USB Host Controller Registers
 *
 ****************************************************************************************************/
/* OpenHCI Registers */
#define REG_HcRevision			(VPint(AHB_IO_BASE+0x5000))	/*	Host Controller Revision Register */
#define REG_HcControl			(VPint(AHB_IO_BASE+0x5004))	/*	Host Controller Control Register */
#define REG_HcCommandStatus		(VPint(AHB_IO_BASE+0x5008))	/*	Host Controller Command Status Register */
#define REG_HcInterruptStatus 	(VPint(AHB_IO_BASE+0x500C))	/*	Host Controller Interrupt Status Register */
#define REG_HcInterruptEnable	(VPint(AHB_IO_BASE+0x5010))	/*	Host Controller Interrupt Enable Register */
#define REG_HcInterruptDisable	(VPint(AHB_IO_BASE+0x5014))	/*	Host Controller Interrupt Disable Register */
#define REG_HcHCCA				(VPint(AHB_IO_BASE+0x5018))	/*	Host Controller Communication Area Register */
#define REG_HcPeriodCurrentED	(VPint(AHB_IO_BASE+0x501C))	/*	Host Controller Period Current ED Register */
#define REG_HcControlHeadED		(VPint(AHB_IO_BASE+0x5020))	/*	Host Controller Control Head ED Register */
#define REG_HcControlCurrentED	(VPint(AHB_IO_BASE+0x5024))	/*	Host Controller Control Current ED Register */
#define REG_HcBulkHeadED		(VPint(AHB_IO_BASE+0x5028))	/*	Host Controller Bulk Head ED Register */
#define REG_HcBulkCurrentED		(VPint(AHB_IO_BASE+0x502C))	/*	Host Controller Bulk Current ED Register */
#define REG_HcDoneHead			(VPint(AHB_IO_BASE+0x5030))	/*	Host Controller Done Head Register */
#define REG_HcFmInterval		(VPint(AHB_IO_BASE+0x5034))	/*	Host Controller Frame Interval Register */
#define REG_HcFrameRemaining	(VPint(AHB_IO_BASE+0x5038))	/*	Host Controller Frame Remaining Register */
#define REG_HcFmNumber			(VPint(AHB_IO_BASE+0x503C))	/*	Host Controller Frame Number Register */
#define REG_HcPeriodicStart		(VPint(AHB_IO_BASE+0x5040))	/*	Host Controller Periodic Start Register */
#define REG_HcLSThreshold		(VPint(AHB_IO_BASE+0x5044))	/*	Host Controller Low Speed Threshold Register */
#define REG_HcRhDescriptorA		(VPint(AHB_IO_BASE+0x5048))	/*	Host Controller Root Hub Descriptor A Register */
#define REG_HcRhDescriptorB		(VPint(AHB_IO_BASE+0x504C))	/*	Host Controller Root Hub Descriptor B Register */
#define REG_HcRhStatus			(VPint(AHB_IO_BASE+0x5050))	/*	Host Controller Root Hub Status Register */
#define REG_HcRhPortStatus1		(VPint(AHB_IO_BASE+0x5054))	/*	Host Controller Root Hub Port Status [1] */
#define REG_HcRhPortStatus2		(VPint(AHB_IO_BASE+0x5058))	/*	Host Controller Root Hub Port Status [2] */

/* USB Configuration Registers */
#define TestModeEnable			(VPint(AHB_IO_BASE+0x5200))	/*	USB Test Mode Enable Register */
#define OperationalModeEnable	(VPint(AHB_IO_BASE+0x5204))	/*	USB Operational Mode Enable Register */


/**********************************************************************************************************
 *
 * 9. USB Device Control Registers
 *
 **********************************************************************************************************/
#define REG_USB_CTL	  		(VPint(AHB_IO_BASE+0x6000))    /* USB control register */
#define REG_USB_CVCMD		(VPint(AHB_IO_BASE+0x6004))    /* USB class or vendor command register */
#define REG_USB_IE	  		(VPint(AHB_IO_BASE+0x6008))    /* USB interrupt enable register */
#define REG_USB_IS	  		(VPint(AHB_IO_BASE+0x600c))    /* USB interrupt status register */
#define REG_USB_IC	  		(VPint(AHB_IO_BASE+0x6010))    /* USB interrupt status clear register */
#define REG_USB_IFSTR		(VPint(AHB_IO_BASE+0x6014))    /* USB interface and string register */
#define REG_USB_ODATA0		(VPint(AHB_IO_BASE+0x6018))    /* USB control transfer-out port 0 register */
#define REG_USB_ODATA1		(VPint(AHB_IO_BASE+0x601C))    /* USB control transfer-out port 1 register */
#define REG_USB_ODATA2		(VPint(AHB_IO_BASE+0x6020))    /* USB control transfer-out port 2 register */
#define REG_USB_ODATA3		(VPint(AHB_IO_BASE+0x6024))    /* USB control transfer-out port 3 register */
#define REG_USB_IDATA0		(VPint(AHB_IO_BASE+0x6028))    /* USB control transfer-in data port 0 register */
#define REG_USB_IDATA1		(VPint(AHB_IO_BASE+0x602C))    /* USB control transfer-in data port 1 register */
#define REG_USB_IDATA2		(VPint(AHB_IO_BASE+0x6030))    /* USB control transfer-in data port 2 register */
#define REG_USB_IDATA3		(VPint(AHB_IO_BASE+0x6034))    /* USB control transfer-in data port 2 register */
#define REG_USB_SIE			(VPint(AHB_IO_BASE+0x6038))    /* USB SIE status Register */
#define REG_USB_ENG			(VPint(AHB_IO_BASE+0x603c))    /* USB Engine Register */
#define REG_USB_CTLS		(VPint(AHB_IO_BASE+0x6040))    /* USB control transfer status register */
#define REG_USB_CONFD		(VPint(AHB_IO_BASE+0x6044))    /* USB Configured Value register */
#define REG_USB_EPA_INFO	(VPint(AHB_IO_BASE+0x6048))    /* USB endpoint A information register */
#define REG_USB_EPA_CTL		(VPint(AHB_IO_BASE+0x604c))    /* USB endpoint A control register */
#define REG_USB_EPA_IE		(VPint(AHB_IO_BASE+0x6050))    /* USB endpoint A Interrupt Enable register */
#define REG_USB_EPA_IC		(VPint(AHB_IO_BASE+0x6054))    /* USB endpoint A interrupt clear register */
#define REG_USB_EPA_IS		(VPint(AHB_IO_BASE+0x6058))    /* USB endpoint A interrupt status register */
#define REG_USB_EPA_ADDR	(VPint(AHB_IO_BASE+0x605c))    /* USB endpoint A address register */
#define REG_USB_EPA_LENTH	(VPint(AHB_IO_BASE+0x6060))    /* USB endpoint A transfer length register */
#define REG_USB_EPB_INFO	(VPint(AHB_IO_BASE+0x6064))    /* USB endpoint B information register */
#define REG_USB_EPB_CTL		(VPint(AHB_IO_BASE+0x6068))    /* USB endpoint B control register */
#define REG_USB_EPB_IE		(VPint(AHB_IO_BASE+0x606c))    /* USB endpoint B Interrupt Enable register */
#define REG_USB_EPB_IC		(VPint(AHB_IO_BASE+0x6070))    /* USB endpoint B interrupt clear register */
#define REG_USB_EPB_IS		(VPint(AHB_IO_BASE+0x6074))    /* USB endpoint B interrupt status register */
#define REG_USB_EPB_ADDR	(VPint(AHB_IO_BASE+0x6078))    /* USB endpoint B address register */
#define REG_USB_EPB_LENTH	(VPint(AHB_IO_BASE+0x607c))    /* USB endpoint B transfer length register */
#define REG_USB_EPC_INFO	(VPint(AHB_IO_BASE+0x6080))    /* USB endpoint C information register */
#define REG_USB_EPC_CTL		(VPint(AHB_IO_BASE+0x6084))    /* USB endpoint C control register */
#define REG_USB_EPC_IE		(VPint(AHB_IO_BASE+0x6088))    /* USB endpoint C Interrupt Enable register */
#define REG_USB_EPC_IC		(VPint(AHB_IO_BASE+0x608c))    /* USB endpoint C interrupt clear register */
#define REG_USB_EPC_IS		(VPint(AHB_IO_BASE+0x6090))    /* USB endpoint C interrupt status register */
#define REG_USB_EPC_ADDR	(VPint(AHB_IO_BASE+0x6094))    /* USB endpoint C address register */
#define REG_USB_EPC_LENTH	(VPint(AHB_IO_BASE+0x6098))    /* USB endpoint C transfer length register */
#define REG_USB_EPA_XFER	(VPint(AHB_IO_BASE+0x609c))    /* USB endpoint A remain transfer length register */
#define REG_USB_EPA_PKT		(VPint(AHB_IO_BASE+0x60a0))    /* USB endpoint A remain packet length register */
#define REG_USB_EPB_XFER	(VPint(AHB_IO_BASE+0x60a4))    /* USB endpoint B remain transfer length register */
#define REG_USB_EPB_PKT		(VPint(AHB_IO_BASE+0x60a8))    /* USB endpoint B remain packet length register */
#define REG_USB_EPC_XFER	(VPint(AHB_IO_BASE+0x60ac))    /* USB endpoint C remain transfer length register */
#define REG_USB_EPC_PKT		(VPint(AHB_IO_BASE+0x60b0))    /* USB endpoint C remain packet length register */


/****************************************************************************************************
 *
 * 11. UART Control Registers
 *
 ****************************************************************************************************/
/* UART 1 */
#define REG_UART_TX_0	(VPint(APB_IO_BASE+0x0000))		/* (W) TX buffer */
#define REG_UART_RX_0	(VPint(APB_IO_BASE+0x0000))		/* (R) RX buffer */
#define REG_UART_LSB_0	(VPint(APB_IO_BASE+0x0000))		/* Divisor latch LSB */
#define REG_UART_MSB_0	(VPint(APB_IO_BASE+0x0004))		/* Divisor latch MSB */
#define REG_UART_IER_0	(VPint(APB_IO_BASE+0x0004))		/* Interrupt enable register */
#define REG_UART_IIR_0	(VPint(APB_IO_BASE+0x0008))		/* (R) Interrupt ident. register */
#define REG_UART_FCR_0	(VPint(APB_IO_BASE+0x0008))		/* (W) FIFO control register */
#define REG_UART_LCR_0	(VPint(APB_IO_BASE+0x000C))		/* Line control register */
#define	REG_UART_LSR_0	(VPint(APB_IO_BASE+0x0014))		/* (R) Line status register */
#define	REG_UART_TOR_0	(VPint(APB_IO_BASE+0x001C))		/* (R) Time out register */
#define	REG_UART_IRCR_0	(VPint(APB_IO_BASE+0x0020))		/* IrDA */

/* UART 2 */
#define REG_UART_TX_1	(VPint(APB_IO_BASE+0x0100))		/* (W) TX buffer */
#define REG_UART_RX_1	(VPint(APB_IO_BASE+0x0100))		/* (R) RX buffer */
#define REG_UART_LSB_1	(VPint(APB_IO_BASE+0x0100))		/* Divisor latch LSB */
#define REG_UART_MSB_1	(VPint(APB_IO_BASE+0x0104))		/* Divisor latch MSB */
#define REG_UART_IER_1	(VPint(APB_IO_BASE+0x0104))		/* Interrupt enable register */
#define REG_UART_IIR_1	(VPint(APB_IO_BASE+0x0108))		/* (R) Interrupt ident. register */
#define REG_UART_FCR_1	(VPint(APB_IO_BASE+0x0108))		/* (W) FIFO control register */
#define REG_UART_LCR_1	(VPint(APB_IO_BASE+0x010C))		/* Line control register */
#define REG_UART_MCR_1	(VPint(APB_IO_BASE+0x0110))		/* Modem control register */
#define	REG_UART_LSR_1	(VPint(APB_IO_BASE+0x0114))		/* (R) Line status register */
#define REG_UART_MSR_1	(VPint(APB_IO_BASE+0x0118))		/* (R) Modem status register */
#define	REG_UART_TOR_1	(VPint(APB_IO_BASE+0x011C))		/* (R) Time out register */
#define	REG_UART_UBCR_1	(VPint(APB_IO_BASE+0x0120))		/* Bluetooth */

/* UART 3 */
#define REG_UART_TX_2	(VPint(APB_IO_BASE+0x0200))		/* (W) TX buffer */
#define REG_UART_RX_2	(VPint(APB_IO_BASE+0x0200))		/* (R) RX buffer */
#define REG_UART_LSB_2	(VPint(APB_IO_BASE+0x0200))		/* Divisor latch LSB */
#define REG_UART_MSB_2	(VPint(APB_IO_BASE+0x0204))		/* Divisor latch MSB */
#define REG_UART_IER_2	(VPint(APB_IO_BASE+0x0204))		/* Interrupt enable register */
#define REG_UART_IIR_2	(VPint(APB_IO_BASE+0x0208))		/* (R) Interrupt ident. register */
#define REG_UART_FCR_2	(VPint(APB_IO_BASE+0x0208))		/* (W) FIFO control register */
#define REG_UART_LCR_2	(VPint(APB_IO_BASE+0x020C))		/* Line control register */
#define	REG_UART_LSR_2	(VPint(APB_IO_BASE+0x0214))		/* (R) Line status register */
#define	REG_UART_TOR_2	(VPint(APB_IO_BASE+0x021C))		/* (R) Time out register */

/* UART 4 */
#define REG_UART_TX_3	(VPint(APB_IO_BASE+0x0300))		/* (W) TX buffer */
#define REG_UART_RX_3	(VPint(APB_IO_BASE+0x0300))		/* (R) RX buffer */
#define REG_UART_LSB_3	(VPint(APB_IO_BASE+0x0300))		/* Divisor latch LSB */
#define REG_UART_MSB_3	(VPint(APB_IO_BASE+0x0304))		/* Divisor latch MSB */
#define REG_UART_IER_3	(VPint(APB_IO_BASE+0x0304))		/* Interrupt enable register */
#define REG_UART_IIR_3	(VPint(APB_IO_BASE+0x0308))		/* (R) Interrupt ident. register */
#define REG_UART_FCR_3	(VPint(APB_IO_BASE+0x0308))		/* (W) FIFO control register */
#define REG_UART_LCR_3	(VPint(APB_IO_BASE+0x030C))		/* Line control register */
#define REG_UART_MCR_3	(VPint(APB_IO_BASE+0x0310))		/* Modem control register */
#define	REG_UART_LSR_3	(VPint(APB_IO_BASE+0x0314))		/* (R) Line status register */
#define REG_UART_MSR_3	(VPint(APB_IO_BASE+0x0318))		/* (R) Modem status register */
#define	REG_UART_TOR_3	(VPint(APB_IO_BASE+0x031C))		/* (R) Time out register */


/****************************************************************************************************
 *
 * 12. Timer Control Registers
 *
 ****************************************************************************************************/
#define REG_TCR0		(VPint(APB_IO_BASE+0x1000)) 	/* Timer Control Register 0 */
#define REG_TCR1		(VPint(APB_IO_BASE+0x1004)) 	/* Timer Control Register 1 */
#define REG_TICR0		(VPint(APB_IO_BASE+0x1008)) 	/* Timer Initial Control Register 0 */
#define REG_TICR1		(VPint(APB_IO_BASE+0x100C)) 	/* Timer Initial Control Register 1 */
#define REG_TDR0		(VPint(APB_IO_BASE+0x1010)) 	/* Timer Data Register 0 */
#define REG_TDR1		(VPint(APB_IO_BASE+0x1014)) 	/* Timer Data Register 1 */
#define REG_TISR		(VPint(APB_IO_BASE+0x1018)) 	/* Timer Interrupt Status Register */
#define REG_WTCR		(VPint(APB_IO_BASE+0x101C)) 	/* Watchdog Timer Control Register */


/****************************************************************************************************
 *
 * 13. Advanced Interrupt Controller Registers
 *
 ****************************************************************************************************/
#define REG_AIC_SCR1	(VPint(APB_IO_BASE+0x2004))		/* Source control register 1 */
#define REG_AIC_SCR2	(VPint(APB_IO_BASE+0x2008))		/* Source control register 2 */
#define REG_AIC_SCR3	(VPint(APB_IO_BASE+0x200C))		/* Source control register 3 */
#define REG_AIC_SCR4	(VPint(APB_IO_BASE+0x2010))		/* Source control register 4 */
#define REG_AIC_SCR5	(VPint(APB_IO_BASE+0x2014))		/* Source control register 5 */
#define REG_AIC_SCR6	(VPint(APB_IO_BASE+0x2018))		/* Source control register 6 */
#define REG_AIC_SCR7	(VPint(APB_IO_BASE+0x201C))		/* Source control register 7 (timer0) */
#define REG_AIC_SCR8	(VPint(APB_IO_BASE+0x2020))		/* Source control register 8 (timer1) */
#define REG_AIC_SCR9	(VPint(APB_IO_BASE+0x2024))		/* Source control register 9 */
#define REG_AIC_SCR10	(VPint(APB_IO_BASE+0x2028))		/* Source control register 10 */
#define REG_AIC_SCR11	(VPint(APB_IO_BASE+0x202C))		/* Source control register 11 */
#define REG_AIC_SCR12	(VPint(APB_IO_BASE+0x2030))		/* Source control register 12 */
#define REG_AIC_SCR13	(VPint(APB_IO_BASE+0x2034))		/* Source control register 13 */
#define REG_AIC_SCR14	(VPint(APB_IO_BASE+0x2038))		/* Source control register 14 */
#define REG_AIC_SCR15	(VPint(APB_IO_BASE+0x203C))		/* Source control register 15 */
#define REG_AIC_SCR16	(VPint(APB_IO_BASE+0x2040))		/* Source control register 16 */
#define REG_AIC_SCR17	(VPint(APB_IO_BASE+0x2044))		/* Source control register 17 */
#define REG_AIC_SCR18	(VPint(APB_IO_BASE+0x2048))		/* Source control register 18 */
#define REG_AIC_SCR19	(VPint(APB_IO_BASE+0x204C))		/* Source control register 18 */
#define REG_AIC_SCR20	(VPint(APB_IO_BASE+0x2050))		/* Source control register 18 */
#define REG_AIC_SCR21	(VPint(APB_IO_BASE+0x2054))		/* Source control register 18 */
#define REG_AIC_SCR22	(VPint(APB_IO_BASE+0x2058))		/* Source control register 18 */
#define REG_AIC_SCR23	(VPint(APB_IO_BASE+0x205C))		/* Source control register 18 */
#define REG_AIC_SCR24	(VPint(APB_IO_BASE+0x2060))		/* Source control register 18 */
#define REG_AIC_SCR25	(VPint(APB_IO_BASE+0x2064))		/* Source control register 18 */
#define REG_AIC_SCR26	(VPint(APB_IO_BASE+0x2068))		/* Source control register 18 */
#define REG_AIC_SCR27	(VPint(APB_IO_BASE+0x206C))		/* Source control register 18 */
#define REG_AIC_SCR28	(VPint(APB_IO_BASE+0x2070))		/* Source control register 18 */

#define REG_AIC_IRSR	(VPint(APB_IO_BASE+0x2100))		/* Interrupt raw status register */
#define REG_AIC_IASR	(VPint(APB_IO_BASE+0x2104))		/* Interrupt active status register */
#define REG_AIC_ISR		(VPint(APB_IO_BASE+0x2108))		/* Interrupt status register */
#define REG_AIC_IPER	(VPint(APB_IO_BASE+0x210C))		/* Interrupt priority encoding register */
#define REG_AIC_ISNR	(VPint(APB_IO_BASE+0x2110))		/* Interrupt source number register */
#define REG_AIC_IMR		(VPint(APB_IO_BASE+0x2114))		/* Interrupt mask register */
#define REG_AIC_OISR	(VPint(APB_IO_BASE+0x2118))		/* Output interrupt status register */

#define REG_AIC_MECR	(VPint(APB_IO_BASE+0x2120))		/* Mask enable command register */
#define REG_AIC_MDCR	(VPint(APB_IO_BASE+0x2124))		/* Mask disable command register */

#define REG_AIC_SSCR	(VPint(APB_IO_BASE+0x2128))		/* Source set command register */
#define REG_AIC_SCCR	(VPint(APB_IO_BASE+0x212C))		/* Source clear command register */
#define REG_AIC_EOSCR	(VPint(APB_IO_BASE+0x2130))		/* End of service command register */

#define REG_AIC_TEST    (VPint(APB_IO_BASE+0x2200))		/* ICE/Debug mode register */


/****************************************************************************************************
 *
 * 14. General-Purpose Input/Output Controller Registers
 *
 ****************************************************************************************************/
#define REG_GPIO_CFG		(VPint(APB_IO_BASE+0x3000)) /*	GPIO Configuration Register */
#define REG_GPIO_DIR		(VPint(APB_IO_BASE+0x3004)) /*	GPIO Direction Register */
#define REG_GPIO_OUT		(VPint(APB_IO_BASE+0x3008)) /*	GPIO Data Output Register */
#define REG_GPIO_IN			(VPint(APB_IO_BASE+0x300C)) /*	GPIO Data Input Register */
#define REG_GPIO_DEB		(VPint(APB_IO_BASE+0x3010)) /*	GPIO De-bounce Control Register */
#define REG_GPIO_INV		(VPint(APB_IO_BASE+0x3014)) /*	GPIO Data Input Inverse Register */


/****************************************************************************************************
 *
 * Usual constants
 *
 ****************************************************************************************************/
/* OSC freq. */
#define EXT_CLOCK_RATE	25000000L

/* Interrupt Source */
#define 	IRQ_WDT			1 	/* Watch Dog Timer Interrupt */
#define 	IRQ_nIRQ0		2 	/* External Interrupt 0 */
#define 	IRQ_nIRQ1		3 	/* External Interrupt 1 */
#define 	IRQ_nIRQ2		4 	/* External Interrupt 2 */
#define 	IRQ_nIRQ3		5 	/* External Interrupt 3 */
#define 	IRQ_AC97		6 	/* AC97 Interrupt */
#define 	IRQ_LCD			7 	/* LCD Controller Interrupt */
#define 	IRQ_RTC			8 	/* RTC Controller Interrupt */
#define 	IRQ_UART0		9 	/* UART 0 Interrupt */
#define 	IRQ_UART1		10 	/* UART 1 Interrupt */
#define 	IRQ_UART2		11	/* UART 2 Interrupt */
#define 	IRQ_UART3		12 	/* UART 3 Interrupt */
#define 	IRQ_TIMER0		13 	/* Timer Interrupt 0 */
#define 	IRQ_TIMER1		14	/* Timer Interrupt 1 */
#define 	IRQ_USBH0		15 	/* USB Host Interrupt 0 */
#define 	IRQ_USBH1		16 	/* USB Host Interrupt 1 */
#define 	IRQ_EMCTX		17	/* EMC TX Interrupt */
#define 	IRQ_EMCRX		18	/* EMC RX Interrupt */
#define 	IRQ_GDMA0		19	/* GDMA Channel Interrupt 0 */
#define 	IRQ_GDMA1		20	/* GDMA Channel Interrupt 1 */
#define 	IRQ_SDIO		21 	/* SDIO Interrupt */
#define 	IRQ_USBD		22 	/* USB Device Interrupt */
#define 	IRQ_SC0			23 	/* SmartCard Interrupt 0 */
#define 	IRQ_SC1			24 	/* SmartCard Interrupt 1 */
#define 	IRQ_I2C0		25 	/* I2C Interrupt 0 */
#define 	IRQ_I2C1		26 	/* I2C Interrupt 1 */
#define 	IRQ_SPI			27 	/* SPI Interrupt */
#define 	IRQ_SPP			28 	/* SPP Interrupt */

#endif /* _W90P710_H */
