/****************************************************************************
*                                                                           *
* Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
*                                                                           *
*****************************************************************************/

/****************************************************************************
* FILENAME
*   gpio.h
*
* VERSION
*   1.0
*
* DESCRIPTION
*   The header file of Winbond ARM7 MCU GPIO device library
*
* HISTORY
*   12/19/05    Ver 1.0 Created by WTLiu
*
* REMARK
*   None
****************************************************************************/
#ifndef _GPIO_H_
#define _GPIO_H_

//Pin Assignment

//PORT0
#define P0C0_AC97REST    0x1
#define P0C1_AC97DATAI   0x1
#define P0C2_AC97DATAO   0x1
#define P0C3_AC97SYNC    0x1
#define P0C4_AC97BITCLK  0x1

#define P0C0_I2SMCLK     0x1
#define P0C1_I2SDATAI    0x1
#define P0C2_I2SDATAO    0x1
#define P0C3_I2SLRCLK    0x1
#define P0C4_I2SBITCLK   0x1

#define P0C0_nIRQ4       0x2
#define P0C1_PWM0        0x2
#define P0C2_PWM1        0x2
#define P0C3_PWM2        0x2
#define P0C4_PWM3        0x2

#define P0C0_USB_PWREN   0x3
#define P0C1_DTR3        0x3
#define P0C2_DSR3        0x3
#define P0C3_TXD3        0x3
#define P0C4_RXD3        0x3

//PORT1
#define P1C0_nXDACK      0x1
#define P1C1_nXDREQ      0x1
#define P1C2_SD_CD       0x1
#define P1C4_SD_DAT3     0x1
#define P1C5_SD_DAT2     0x1
#define P1C6_SD_DAT1     0x1
#define P1C7_SD_DAT0     0x1
#define P1C8_SD_CLK      0x1
#define P1C9_SD_CMD      0x1

#define P1C0_SC1_PWR     0x2
#define P1C1_SC1_PRES    0x2
#define P1C2_SC1_RST     0x2
#define P1C3_SC1_CLK     0x2
#define P1C4_SC1_DAT     0x2
#define P1C5_SC0_PWR     0x2
#define P1C6_SC0_PRES    0x2
#define P1C7_SC0_RST     0x2
#define P1C8_SC0_CLK     0x2
#define P1C9_SC0_DAT     0x2

#define P1C0_VD8         0x3
#define P1C1_VD9         0x3
#define P1C2_VD10        0x3
#define P1C3_VD11        0x3
#define P1C4_VD12        0x3
#define P1C5_VD13        0x3
#define P1C6_VD14        0x3
#define P1C7_VD15        0x3
#define P1C8_VD16        0x3
#define P1C9_VD17        0x3

//PORT2
#define P2C0_PHY_RXERR   0x1
#define P2C1_PHY_CRSDV   0x1
#define P2C2_PHY_RXD0    0x1
#define P2C3_PHY_RXD1    0x1
#define P2C4_PHY_REFCLK  0x1
#define P2C5_PHY_TXEN    0x1
#define P2C6_PHY_TXD0    0x1
#define P2C7_PHY_TXD1    0x1
#define P2C8_PHY_MDIO    0x1
#define P2C9_PHY_MDC     0x1

#define P2C0_KPCOL0      0x2
#define P2C1_KPCOL1      0x2
#define P2C2_KPCOL2      0x2
#define P2C3_KPCOL3      0x2
#define P2C4_KPCOL4      0x2
#define P2C5_KPCOL5      0x2
#define P2C6_KPCOL6      0x2
#define P2C7_KPCOL7      0x2
#define P2C8_KPROW0      0x2
#define P2C9_KPROW1      0x2

#define P2C0_VD8         0x3
#define P2C1_VD9         0x3
#define P2C2_VD10        0x3
#define P2C3_VD11        0x3
#define P2C4_VD12        0x3
#define P2C5_VD13        0x3
#define P2C6_VD14        0x3
#define P2C7_VD15        0x3
#define P2C8_VD16        0x3
#define P2C9_VD17        0x3

//PORT3
#define P3C0_D24         0x1
#define P3C1_D25         0x1
#define P3C2_D26         0x1
#define P3C3_D27         0x1
#define P3C4_D28         0x1
#define P3C5_D29         0x1
#define P3C6_D30         0x1
#define P3C7_D31         0x1

#define P3C0_VD16        0x2
#define P3C1_VD17        0x2
#define P3C2_VD18        0x2
#define P3C3_VD19        0x2
#define P3C4_VD20        0x2
#define P3C5_VD21        0x2
#define P3C6_VD22        0x2
#define P3C7_VD23        0x2

//PORT4
#define P4C0_D16         0x1
#define P4C1_D17         0x1
#define P4C2_D18         0x1
#define P4C3_D19         0x1
#define P4C4_D20         0x1
#define P4C5_D21         0x1
#define P4C6_D22         0x1
#define P4C7_D23         0x1
#define P4C8_nWBE2       0x1
#define P4C9_nWBE3       0x1
#define P4C10_nWAIT      0x1

#define P4C8_SDQM2       0x1
#define P4C9_SDQM3       0x1

#define P4C0_VD8         0x2
#define P4C1_VD9         0x2
#define P4C2_VD10        0x2
#define P4C3_VD11        0x2
#define P4C4_VD12        0x2
#define P4C5_VD13        0x2
#define P4C6_VD14        0x2
#define P4C7_VD15        0x2
#define P4C10_nIRQ5      0x2

//PORT5
#define P5C0_TXD0        0x1
#define P5C1_RXD0        0x1
#define P5C2_TXD1        0x1
#define P5C3_RXD1        0x1
#define P5C4_TXD2        0x1
#define P5C5_RXD2        0x1
#define P5C6_SCL0        0x1
#define P5C7_SDA0        0x1
#define P5C8_SCL1        0x1
#define P5C9_SDA1        0x1
#define P5C10_nWDOG      0x1
#define P5C11_nIRQ0      0x1
#define P5C12_nIRQ1      0x1
#define P5C13_nIRQ2      0x1
#define P5C14_nIRQ3      0x1

#define P5C4_CTS1        0x2
#define P5C5_RTS1        0x2
#define P5C6_SFRM        0x2
#define P5C7_SSPTXD      0x2
#define P5C8_SSPSCLK     0x2
#define P5C9_SSPRXD      0x2
#define P5C10_USBPWREN   0x2
#define P5C12_USBOVCUR   0x2

#define P5C0_FA20XL      0x3
#define P5C1_IRQ1X       0x3
#define P5C2_IRQ12X      0x3
#define P5C3_T00X        0x3
#define P5C4_PS2CLK      0x3
#define P5C5_PS2DATA     0x3
#define P5C6_TIMER0      0x3
#define P5C7_TIMER1      0x3
#define P5C8_KPROW3      0x3
#define P5C9_KPROW2      0x3

//PORT6
#define P6C0_VCLK        0x1
#define P6C1_VDEN        0x1
#define P6C2_VSYNC       0x1
#define P6C3_HSYNC       0x1
#define P6C4_VD0         0x1
#define P6C5_VD1         0x1
#define P6C6_VD2         0x1
#define P6C7_VD3         0x1
#define P6C8_VD4         0x1
#define P6C9_VD5         0x1
#define P6C10_VD6        0x1
#define P6C11_VD7        0x1

#define P6C0_KPROW0      0x2
#define P6C1_KPROW1      0x2
#define P6C2_KPROW2      0x2
#define P6C3_KPROW3      0x2
#define P6C4_KPCOL0      0x2
#define P6C5_KPCOL1      0x2
#define P6C6_KPCOL2      0x2
#define P6C7_KPCOL3      0x2
#define P6C8_KPCOL4      0x2
#define P6C9_KPCOL5      0x2
#define P6C10_KPCOL6     0x2
#define P6C11_KPCOL7     0x2

#define GPIO_00     ((GPIO_PORT0<<4)|GPIO_CFG0)
#define GPIO_01     ((GPIO_PORT0<<4)|GPIO_CFG1)
#define GPIO_02     ((GPIO_PORT0<<4)|GPIO_CFG2)
#define GPIO_03     ((GPIO_PORT0<<4)|GPIO_CFG3)
#define GPIO_04     ((GPIO_PORT0<<4)|GPIO_CFG4)
#define GPIO_05     ((GPIO_PORT5<<4)|GPIO_CFG0)
#define GPIO_06     ((GPIO_PORT5<<4)|GPIO_CFG1)
#define GPIO_07     ((GPIO_PORT5<<4)|GPIO_CFG2)
#define GPIO_08     ((GPIO_PORT5<<4)|GPIO_CFG3)
#define GPIO_09     ((GPIO_PORT5<<4)|GPIO_CFG4)
#define GPIO_10     ((GPIO_PORT5<<4)|GPIO_CFG5)
#define GPIO_11     ((GPIO_PORT5<<4)|GPIO_CFG6)
#define GPIO_12     ((GPIO_PORT5<<4)|GPIO_CFG7)
#define GPIO_13     ((GPIO_PORT5<<4)|GPIO_CFG8)
#define GPIO_14     ((GPIO_PORT5<<4)|GPIO_CFG9)
#define GPIO_15     ((GPIO_PORT5<<4)|GPIO_CFG10)
#define GPIO_16     ((GPIO_PORT5<<4)|GPIO_CFG11)
#define GPIO_17     ((GPIO_PORT5<<4)|GPIO_CFG12)
#define GPIO_18     ((GPIO_PORT5<<4)|GPIO_CFG13)
#define GPIO_19     ((GPIO_PORT5<<4)|GPIO_CFG14)
#define GPIO_20     ((GPIO_PORT1<<4)|GPIO_CFG0)
#define GPIO_21     ((GPIO_PORT1<<4)|GPIO_CFG1)
#define GPIO_22     ((GPIO_PORT1<<4)|GPIO_CFG2)
#define GPIO_23     ((GPIO_PORT1<<4)|GPIO_CFG3)
#define GPIO_24     ((GPIO_PORT1<<4)|GPIO_CFG4)
#define GPIO_25     ((GPIO_PORT1<<4)|GPIO_CFG5)
#define GPIO_26     ((GPIO_PORT1<<4)|GPIO_CFG6)
#define GPIO_27     ((GPIO_PORT1<<4)|GPIO_CFG7)
#define GPIO_28     ((GPIO_PORT1<<4)|GPIO_CFG8)
#define GPIO_29     ((GPIO_PORT1<<4)|GPIO_CFG9)
#define GPIO_30     ((GPIO_PORT6<<4)|GPIO_CFG0)
#define GPIO_31     ((GPIO_PORT6<<4)|GPIO_CFG1)
#define GPIO_32     ((GPIO_PORT6<<4)|GPIO_CFG2)
#define GPIO_33     ((GPIO_PORT6<<4)|GPIO_CFG3)
#define GPIO_34     ((GPIO_PORT6<<4)|GPIO_CFG4)
#define GPIO_35     ((GPIO_PORT6<<4)|GPIO_CFG5)
#define GPIO_36     ((GPIO_PORT6<<4)|GPIO_CFG6)
#define GPIO_37     ((GPIO_PORT6<<4)|GPIO_CFG7)
#define GPIO_38     ((GPIO_PORT6<<4)|GPIO_CFG8)
#define GPIO_39     ((GPIO_PORT6<<4)|GPIO_CFG9)
#define GPIO_40     ((GPIO_PORT6<<4)|GPIO_CFG10)
#define GPIO_41     ((GPIO_PORT6<<4)|GPIO_CFG11)
#define GPIO_42     ((GPIO_PORT2<<4)|GPIO_CFG0)
#define GPIO_43     ((GPIO_PORT2<<4)|GPIO_CFG1)
#define GPIO_44     ((GPIO_PORT2<<4)|GPIO_CFG2)
#define GPIO_45     ((GPIO_PORT2<<4)|GPIO_CFG3)
#define GPIO_46     ((GPIO_PORT2<<4)|GPIO_CFG4)
#define GPIO_47     ((GPIO_PORT2<<4)|GPIO_CFG5)
#define GPIO_48     ((GPIO_PORT2<<4)|GPIO_CFG6)
#define GPIO_49     ((GPIO_PORT2<<4)|GPIO_CFG7)
#define GPIO_50     ((GPIO_PORT2<<4)|GPIO_CFG8)
#define GPIO_51     ((GPIO_PORT2<<4)|GPIO_CFG9)
#define GPIO_52     ((GPIO_PORT4<<4)|GPIO_CFG0)
#define GPIO_53     ((GPIO_PORT4<<4)|GPIO_CFG1)
#define GPIO_54     ((GPIO_PORT4<<4)|GPIO_CFG2)
#define GPIO_55     ((GPIO_PORT4<<4)|GPIO_CFG3)
#define GPIO_56     ((GPIO_PORT4<<4)|GPIO_CFG4)
#define GPIO_57     ((GPIO_PORT4<<4)|GPIO_CFG5)
#define GPIO_58     ((GPIO_PORT4<<4)|GPIO_CFG6)
#define GPIO_59     ((GPIO_PORT4<<4)|GPIO_CFG7)
#define GPIO_60     ((GPIO_PORT3<<4)|GPIO_CFG0)
#define GPIO_61     ((GPIO_PORT3<<4)|GPIO_CFG1)
#define GPIO_62     ((GPIO_PORT3<<4)|GPIO_CFG2)
#define GPIO_63     ((GPIO_PORT3<<4)|GPIO_CFG3)
#define GPIO_64     ((GPIO_PORT3<<4)|GPIO_CFG4)
#define GPIO_65     ((GPIO_PORT3<<4)|GPIO_CFG5)
#define GPIO_66     ((GPIO_PORT3<<4)|GPIO_CFG6)
#define GPIO_67     ((GPIO_PORT3<<4)|GPIO_CFG7)
#define GPIO_68     ((GPIO_PORT4<<4)|GPIO_CFG8)
#define GPIO_69     ((GPIO_PORT4<<4)|GPIO_CFG9)
#define GPIO_70     ((GPIO_PORT4<<4)|GPIO_CFG10)

#define GPIO_PORT0	    0
#define GPIO_PORT1	    1
#define GPIO_PORT2	    2
#define GPIO_PORT3	    3
#define GPIO_PORT4	    4
#define GPIO_PORT5	    5
#define GPIO_PORT6	    6

#define GPIO_CFG0		0
#define GPIO_CFG1		1
#define GPIO_CFG2		2
#define GPIO_CFG3		3
#define GPIO_CFG4		4
#define GPIO_CFG5		5
#define GPIO_CFG6		6
#define GPIO_CFG7		7
#define GPIO_CFG8		8
#define GPIO_CFG9		9
#define GPIO_CFG10		10
#define GPIO_CFG11		11
#define GPIO_CFG12		12
#define GPIO_CFG13		13
#define GPIO_CFG14		14
#define GPIO_CFG15		15

//for GPIO CFG
#define GPIO_IO     0x00

//for GPIO_DIR
#define PUPEN_ENABLE    1
#define PUPEN_DISABLE   0
#define GPIO_OUTPUT     1
#define GPIO_INPUT      0

//for GPIO_DATAOUT/GPIO_DATAIN
#define GPIO_HI     1
#define GPIO_LO     0

//for GPIO_DBNCECON and XICFG
#define DBEN_ENABLE     1
#define DBEN_DISABLE    0

#define DBEN0       0
#define DBEN1       1
#define DBEN2       2
#define DBEN3       3
#define DBCLKSEL    4

#define DBEN_VALUE(n, v)    (v<<n)
#define DBEN0_MASK       0x1
#define DBEN1_MASK       0x2
#define DBEN2_MASK       0x4
#define DBEN3_MASK       0x8
#define DBCLKSEL_MASK    0x30

#define XICFG_INT5       4
#define XICFG_INT4       0

#define XICFG_MASK(n)       (0xF<<n)
#define XICFG_VALUE(n, v)   (v<<n)

#define XICFG_LOW_LEVEL_SENSITIVE    0x0
#define XICFG_HIGH_LEVEL_SENSITIVE   0x1
#define XICFG_NEGATIVE_EDGE_TRIGGER  0x2
#define XICFG_POSITIVE_EDGE_TRIGGER  0x3

#define DBE_ENABLE      0x4
#define DBE_DISABLE     0
#define ENINT_ENABLE    0x8
#define ENINT_DISABLE   0

#define XISTATUS_INT4   0x1
#define XISTATUS_INT5   0x2

//GPIO Error code
#define gpioInvalidPort  	    (GPIO_ERR_ID|0x1)
#define gpioInvalidIntNum 	    (GPIO_ERR_ID|0x2)
#define gpioInvalidIoctlCommand (GPIO_ERR_ID|0x3)
#define gpioInvalidCfg          (GPIO_ERR_ID|0x4)
#define gpioInvalidPUPEN        (GPIO_ERR_ID|0x5)
#define gpioInvalidIO           (GPIO_ERR_ID|0x6)

#define CFG_VALUE(n,v)		        ( (v) << ((n&0x0F)*2 ) )
#define CFG_MASK(n)	                ( 0x3 << ((n&0x0F)*2 ) )
#define DIR_VALUE(n,omden,pupen)    ( (omden<<(n&0x0F)) | (pupen<<((n&0x0F)+16)) )
#define DIR_MASK(n)	                ( (0x1  <<(n&0x0F)) | (0x1  <<((n&0x0F)+16)) )
#define DATAOUT_VALUE(n,v)	        ( v << (n&0x0F) )
#define DATAIN_VALUE(n,v)		    ((v&(0x1<<(n&0x0F)))>>(n&0x0F))
#define DATA_MASK(n)	            (0x1 << (n&0x0F) )

//ioctl command table
#define SET_CFG         0
#define SET_DIR         1
#define SET_DATAOUT     2
#define GET_DATAIN      3
#define SET_DBNCECON    4
#define SET_XICFG       5
#define GET_XISTATUS    6
#define SET_IO          7
#define SET_OUTPUT      8
#define GET_INPUT       9

extern INT gpioIoctl(CONST INT nPort, CONST UINT uCommand, CONST UINT uIndication, CONST UINT uValue);

#endif
