/****************************************************************************
 *                                                                                    
 * Copyright (c) 2004 - 2004 Winbond Electronics Corp. All rights reserved.           
 *                                                                                    
 ***************************************************************************/
 
/****************************************************************************
 * 
 * FILENAME
 *     w90p710_lcd.h
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *     The header file for LCD Controller.
 *
 * DATA STRUCTURES
 *     None
 *
 * FUNCTIONS
 *     None
 *
 * HISTORY
 *     12/20/04		 Ver 1.0 Created 
 *
 * REMARK
 *     None
 *
 **************************************************************************/
#include "wblib.h"

/*************************************
* LCD_IMAGE_T 
* Structure for image width and height 
*************************************/
typedef struct 
{
	unsigned int width;
	unsigned int height;
} LCD_IMAGE_T;

/************************************* 
* LCD_LOCATION_T
* Structure for location of image at panel 
*************************************/
typedef struct 
{
	unsigned int x;
	unsigned int y;
} LCD_LOCATION_T;

/**************************************
* LCD_DOWNSCALING_T
* Sturcture for image down-scaling function
*   hor_n : Horizontal n value
*   hor_m : Horizontal m value
*   ver_n : Vertical n value
*   ver_m : Vertical m value
*   
* Horizontal down-scaling ratio : n/m
* Vertical down-scaling ratio : n/m
*************************************/   
typedef struct 
{
	unsigned int hor_n;
	unsigned int hor_m;
	unsigned int ver_n;
	unsigned int ver_m;
} LCD_DOWNSCALING_T;

/**************************************
* LCD_CROPPINGWINDOW_T
* Sturcture for image cropping window function
*	window_x : cropping window x position
*	window_y : cropping window y position
*	winodw_width : cropping window width
*	window_height : cropping window height
*************************************/ 
typedef struct 
{
	unsigned int window_x;
	unsigned int window_y;
	unsigned int window_width;
	unsigned int window_height;
} LCD_CROPPINGWINDOW_T;


/***********************************
* Structure for Look-up Table
* copy from microwindows /include/inc/linux/fb.h */
typedef struct 
{
	int start;				/* First entry	*/
	int len;				/* Number of entries */
	unsigned short *red;				/* Red values	*/
	unsigned short *green;
	unsigned short *blue;
	short *transp;			/* transparency, can be NULL */
}LCD_PALETTE_T;
/******************************/

/* overlay display layer selection */
#define OVERLAY_DISPLAY_VIDEO		0
#define OVERLAY_DISPLAY_OSD			1
#define OVERLAY_DISPLAY_SYNTHESIZED	2

/* pixel sequence selection */
#define PIXELSEQ_R1G1B2R2G3B3	0
#define PIXELSEQ_R1G2B3R4G5B6	1
#define PIXELSEQ_R1G1B1R2G2B2	2

/* video systhesis level selection */
#define VIDEOSYSTHESISLEVEL0	0
#define VIDEOSYSTHESISLEVEL1	1
#define VIDEOSYSTHESISLEVEL2	2
#define VIDEOSYSTHESISLEVEL3	3
#define VIDEOSYSTHESISLEVEL4	4
#define VIDEOSYSTHESISLEVEL5	5
#define VIDEOSYSTHESISLEVEL6	6
#define VIDEOSYSTHESISLEVEL7	7
#define VIDEOSYSTHESISLEVEL8	8

/* IO control commands */
#define LCD_IOC_DISPLAY_ON				1
#define LCD_IOC_DISPLAY_OFF				2
#define LCD_IOC_SET_IMAGE_SIZE			3
#define LCD_IOC_SET_WINDOW				4
#define LCD_IOC_UPSCALING				5
#define LCD_IOC_DOWNSCALING				6
#define LCD_IOC_CROPPINGWINDOW			7
#define LCD_IOC_FILLWITHLOOKUPTABLE		8
#define LCD_IOC_LOOKUPTABLE_ON			9
#define LCD_IOC_LOOKUPTABLE_OFF			10
#define LCD_IOC_SET_BLINKING			11
#define LCD_IOC_SET_TRANSPARENT_BACKGROUND	12
#define LCD_IOC_SET_TRANSPARENT_IMAGE	13
#define LCD_IOC_SET_KEY_PATTERN			14
#define LCD_IOC_SET_KEY_MASK			15
#define LCD_IOC_BLINKING_ON				16
#define LCD_IOC_BLINKING_OFF			17
#define LCD_IOC_LCD_DISABLE				18
#define LCD_IOC_LCD_ENABLE				19
#define LCD_IOC_YUVFORMAT				20
#define LCD_IOC_RGBFORMAT				21
#define LCD_IOC_PIXELSEQ				22
#define LCD_IOC_SET_VIDEO_SYNTHESIS		23
#define LCD_IOC_SET_OVERLAY				24

/* LCD interface selection */
#define VIDEO_DEVICE 	1
#define OSD_DEVICE 		2

/* lcd control */
INT32 lcdOpen(INT32 fd); 	/* Open LCD device */
VOID lcdClose(VOID);		/* Close LCD device */
VOID lcdIoctl(INT32 fd, UINT32 cmd, UINT32 arg);	/* LCD IO control */
PUINT8 lcdMmap(INT32 fd, UINT32 buffer_size);		/* Map display buffer to user */
VOID lcdInit(INT fd);	/* Init LCD device */
