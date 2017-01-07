/**************************************************************************************************
 *                                                                          
 * Copyright (c) 2004 - 2007 Winbond Electronics Corp. All rights reserved.      
 *                                                                         
 * FILENAME
 *     AC97.h
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *     This file contains the register map of AC97 audio codec
 *
 * HISTORY
 *     02/09/2004		 Ver 1.0 Created by PC30 YCHuang
 *	   04/01/2006		 Modify for W90P710 audio controller	
 *
 * REMARK
 *     None
 *     
 *************************************************************************************************/

#ifndef _W90P710_AUDIO_H_
#define _W90P710_AUDIO_H_

#include "wberrcode.h"		/* error code difinition */

typedef INT (AU_CB_FUNC_T)(UINT32, UINT32);

typedef struct audio_t
{
	AU_CB_FUNC_T 	*fnPlayCallBack;
	AU_CB_FUNC_T 	*fnRecCallBack;
	INT				nPlaySamplingRate;
	INT				nRecSamplingRate;
	BOOL			bPlayLastBlock;
	UINT16			sPlayVolume;
	UINT16			sRecVolume;
}	AUDIO_T;

typedef struct wb_audio_volume_t{
	char right;
	char left;
}AU_VOLUME_T;

typedef enum au_dev_e
{
	AU_DEV_AC97,
	AU_DEV_IIS,
	AU_DEV_ADC,
	AU_DEV_DAC,
	AU_DEV_MA3,
	AU_DEV_MA5,
	AU_DEV_W5691,
	AU_DEV_WM8753,
	AU_DEV_WM8978,
	AU_DEV_MA5I
} AU_DEV_E;

#define AU_SAMPLE_RATE_48000	48000
#define AU_SAMPLE_RATE_44100	44100
#define AU_SAMPLE_RATE_32000	32000
#define AU_SAMPLE_RATE_24000	24000
#define AU_SAMPLE_RATE_22050	22050
#define AU_SAMPLE_RATE_16000	16000
#define AU_SAMPLE_RATE_12000	12000
#define AU_SAMPLE_RATE_11025	11025
#define AU_SAMPLE_RATE_8000		8000

#define AU_CH_MONO		1
#define AU_CH_STEREO	2

#define AUDIO_SET_SAMPLINGRATE 			1
#define AUDIO_SET_CHANNELS				2
#define AUDIO_SET_PLAYVOLUME			3
#define AUDIO_SET_PLAYBUFFERADDRESS 	4
#define AUDIO_SET_RECORDBUFFERADDRESS	5
#define AUDIO_GET_BLOCKSIZE				6
#define AUDIO_STOP_PLAY 				7
#define AUDIO_STOP_RECORD				8
#define AUDIO_START_PLAY				9

/* Error Code */
#define ERR_AU_GENERAL_ERROR	( ADO_ERR_ID | 1 )
#define ERR_AU_NO_MEMORY		( ADO_ERR_ID | 5 )	/* memory allocate failure */
#define ERR_AU_ILL_BUFF_SIZE	( ADO_ERR_ID | 10 )		/* illegal callback buffer size */
#define ERR_AC97_CODEC_RESET	( ADO_ERR_ID | 20 )		/* AC97 codec reset failed */
#define ERR_AC97_PLAY_ACTIVE	( ADO_ERR_ID | 22 )		/* AC97 playback has been activated */
#define ERR_AC97_REC_ACTIVE		( ADO_ERR_ID | 23 )		/* AC97 record has been activated */
#define ERR_AC97_NO_DEVICE		( ADO_ERR_ID | 24 )		/* have no AC97 codec on board */
#define ERR_MA3_PLAY_ACTIVE		( ADO_ERR_ID | 50 )		/* MA3 playback has been activated */
#define ERR_MA3_NO_DEVICE		( ADO_ERR_ID | 51 )		/* have no MA3 chip on board */
#define ERR_MA5_PLAY_ACTIVE		( ADO_ERR_ID | 80 )		/* MA5 playback has been activated */
#define ERR_MA5_NO_DEVICE		( ADO_ERR_ID | 81 )		/* have no MA5 chip on board */
#define ERR_MA5I_NO_DEVICE		( ADO_ERR_ID | 90 )		/* have no MA5i chip on board */
#define ERR_DAC_PLAY_ACTIVE		( ADO_ERR_ID | 110 )	/* DAC playback has been activated */
#define ERR_DAC_NO_DEVICE		( ADO_ERR_ID | 111 )	/* DAC is not available */
#define ERR_ADC_REC_ACTIVE		( ADO_ERR_ID | 120 )	/* ADC record has been activated */
#define ERR_ADC_NO_DEVICE		( ADO_ERR_ID | 121 )	/* ADC is not available */
#define ERR_IIS_PLAY_ACTIVE		( ADO_ERR_ID | 140 )	/* IIS playback has been activated */
#define ERR_IIS_REC_ACTIVE		( ADO_ERR_ID | 141 )	/* IIS record has been activated */
#define ERR_IIS_NO_DEVICE		( ADO_ERR_ID | 142 )	/* has no IIS codec on board */
#define ERR_WM8753_NO_DEVICE	( ADO_ERR_ID | 150 )	/* has no wm8753 codec on board */
#define ERR_W5691_PLAY_ACTIVE	( ADO_ERR_ID | 160 )	/* W5691 playback has been activated */
#define ERR_W5691_NO_DEVICE		( ADO_ERR_ID | 161 )	/* Have no W5691 chip on board */
#define ERR_NO_DEVICE			( ADO_ERR_ID | 201 )	/* audio device not available */
#define ERR_BUFFER_FULL			( ADO_ERR_ID | 210 )	/* audio buffer is full */
#define ERR_BUFFER_EMPTY		( ADO_ERR_ID | 211 )	/* audio buffer is empty */

/* Device Selection */
#define AC97_DEVICE 0
#define IIS_DEVICE 	1

INT32 audioWrite(INT32 fd, PUINT8 buffer, UINT32 len);
INT32 audioRead(INT32 fd, PUINT8 buffer, UINT32 len);
INT32 audioOpen(INT32 fd);
INT32 audioIoctl(INT32 fd, UINT32 cmd, UINT32 arg);
VOID audioClose(VOID);
VOID audioExit(VOID);
INT32 audioInit(VOID);

#endif	/* _W90P710_AUDIO_H_ */
