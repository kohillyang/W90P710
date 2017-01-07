/****************************************************************************
 *                                                                           *
 * Copyright (c) 2004 - 2006 Winbond Electronics Corp. All rights reserved.  *
 *                                                                           *
 *****************************************************************************/

/****************************************************************************
 * FILENAME
 *   audio_test.c
 *
 * VERSION
 *   1.0
 *
 * DESCRIPTION
 *   The AC97 test program
 *
 * DATA STRUCTURES
 *   None
 *
 * FUNCTIONS
 *   Audio_AdjustVolume      Audio volume adjust
 *   Audio_Item              Show audio test menu
 *   Audio_MediaPlayTest     Play audio form USB Disk or SD Card
 *   Audio_PlayMenu          Show audio play menu
 *   Audio_PlayTest          Play audio form build in pattern
 *   Audio_RecordTest        Audio record test
 *   Audio_Test              Audio test main function
 *   Clean_TimerLED          Reset playing time and timer LED
 *   GetChannel              Get channel from user input
 *   GetSamplerate           Get sample rate from user input
 *   GetVolume               Get volume from user input
 *   Init_TimerLED           Initiate playing time and timer LED
 *   Set_TimerLED            Set playing time and timer LED
 *
 * HISTORY
 *   2006-02-08  Ver 1.0 Modified from Audio library test program by NS21 WTLiu
 *
 * REMARK
 *   None
 ****************************************************************************/
#define sysPrintf(...)
#include <stdlib.h>
#include <string.h>
#include <math.h>

//defin by project
//#define SD_PATTERN

//System Library
#include "wblib.h"

//NON OS Library
#include "w90p710_Audio.h"
#include "gpio.h"
#ifdef SD_PATTERN
#include "wbfmi.h"
#endif

//Application layer head file
#include "ebi_led.h"
#include "wbfat_test.h"
#include "audio_pattern.h"

#define WAVE_HEADER_SIZE 44
typedef struct waveformat_tag {
	UCHAR ucRIFF[4];
	UINT uFileSize;
	UCHAR ucWAVEFMT[8];
	UINT uBlackSize;
	UINT16 uTag;
	UINT16 uChannel;
	UINT uSamplesPerSec;
	UINT uAvgBytesPerSec;
	UINT _reserved[4];
} WAVEFORMAT;

UCHAR ucRIFF[4] = { 'R', 'I', 'F', 'F' };
UCHAR ucWAVEFMT[8] = { 'W', 'A', 'V', 'E', 'f', 'm', 't', 0x20 };

#define DEFAULT_VOLUME      27
#define DEFAULT_MIN_VOLUME  22
#define DEFAULT_MAX_VOLUME  30
#define MAX_VOLUME_LENGTH   2
#define RX_FIFO_DATA_READY  0x1
#define CONTINUE_PLAY       0
#define STOP_PLAY           1
#define NEXT_ONE            2
#define PREVIOUS_ONE        3

#ifdef DEBUG_TEST_MODE
#define DEMO_PCM_LEN        184320
#else
#define DEMO_PCM_LEN        328600
#endif

#define DEMO_SAMPLINGRATE   AU_SAMPLE_RATE_16000
#define DEMO_CHANNEL        1

//Global variable
// for LED control
static CONST CHAR cVolumeLED[9] = { 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F,
		0x7F, 0xFF };
static INT volatile nTimerLED = 0;
static INT volatile nTimerCount = 0;
static UINT uTimeEventNum;
// for volume adjust
static INT nVolumeSetting = DEFAULT_VOLUME;

//Function Definition
#ifdef SD_PATTERN
extern VOID SD_Init(VOID);
#endif
extern VOID Hub_CheckIrqEvent(VOID);

static INT Audio_AdjustVolume(INT nDevice);
static VOID Audio_Item(VOID);
static VOID Audio_MediaPlayTest(INT nDevice, UINT32 uDiskType);
static VOID Audio_PlayMenu(VOID);
VOID Audio_PlayTest(INT nDevice);
static VOID Audio_RecordTest(INT nDevice);

static VOID Clean_TimerLED(VOID);
static INT GetChannel(VOID);
static INT GetSamplerate(VOID);
static INT GetVolume(VOID);
static VOID Init_TimerLED(VOID);
static VOID Set_TimerLED(VOID);

/****************************************************************************
 * FUNCTION
 *   Audio_AdjustVolume
 *
 * DESCRIPTION
 *   The volume adjust function for audio play test. This function detect the
 *   user Key press in console, and then increase or reduce volume according
 *   to the global variable, nVolumeSetting. This function allowed volume form
 *   22 to 30 since this volume is suitable in evaluation board. The volume value
 *   should be indicated by EDI LED.
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   nDevice
 *
 * OUTPUTS
 *   CONTINUE_PLAY/STOP_PLAY
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static INT Audio_AdjustVolume(INT nDevice) {
	CHAR cKeyPress;
	AU_VOLUME_T volume;
	if ( inpb(REG_UART0_LSR) & 0x01) {
		cKeyPress = sysGetChar();
		switch (cKeyPress) {
		case 'r':
		case 'R': {
			return PREVIOUS_ONE;
			break;
		}
		case 'n':
		case 'N': {
			return NEXT_ONE;
			break;
		}
		case 27: // ESC exit
		{
			return STOP_PLAY;
			break;
		}
		case 45: // press - Reduce volume
		{
			if ((nVolumeSetting - 1) < DEFAULT_MIN_VOLUME) {
				break;
			}
			nVolumeSetting--;
			volume.right = (CHAR) nVolumeSetting;
			volume.left = (CHAR) nVolumeSetting;
			audioIoctl(nDevice, AUDIO_SET_PLAYVOLUME, (UINT32) &volume);
			Set_EBILED(cVolumeLED[nVolumeSetting - DEFAULT_MIN_VOLUME]);
			break;
		}
		case 43: //press + Increase volume
		case 61: {
			if ((nVolumeSetting + 1) > DEFAULT_MAX_VOLUME) {
				break;
			}
			nVolumeSetting++;
			volume.right = (CHAR) nVolumeSetting;
			volume.left = (CHAR) nVolumeSetting;
			audioIoctl(nDevice, AUDIO_SET_PLAYVOLUME, (UINT32) &volume);
			Set_EBILED(cVolumeLED[nVolumeSetting - DEFAULT_MIN_VOLUME]);
			break;
		}
		}
	}
	return CONTINUE_PLAY;
}

/****************************************************************************
 * FUNCTION
 *   Audio_Item
 *
 * DESCRIPTION
 *   The test menu of AC97 test program
 *
 * CALLED BY
 *   Audio_Test
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static VOID Audio_Item(VOID) {
	sysPrintf("\n\n\n");sysPrintf("+------------------------------------------------------+\n");sysPrintf("| Winbond AC97 Diagnostic Code                         |\n");sysPrintf("+------------------------------------------------------+\n");sysPrintf("| Audio play test(Build in pattern)              - [1] |\n");sysPrintf("| Audio play test(file in USB disk)              - [2] |\n");
#ifdef SD_PATTERN
	sysPrintf("| Audio play test(file in SD card)               - [3] |\n");
	sysPrintf("| Audio record test(Loop back)                   - [4] |\n");
#else
	sysPrintf("| Audio record test(Loop back)                   - [3] |\n");
#endif
	sysPrintf("| Quit                                         - [ESC] |\n");sysPrintf("+------------------------------------------------------+\n");sysPrintf("Please Select : \r\n");
}

/****************************************************************************
 * FUNCTION
 *   Audio_MediaPlayTest
 *
 * DESCRIPTION
 *   This function play audio form SD card or USB Disk according to the
 *   parameter, uDiskType.
 *
 * CALLED BY
 *   Audio_Test
 *
 * INPUTS
 *   nDevice
 *   uDiskType   USB_DISK/SD_DISK
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/

/****************************************************************************
 * FUNCTION
 *   Audio_PlayMenu
 *
 * DESCRIPTION
 *   The audio play menu of audio paly test. This function also call
 *   Init_TimerLED and Set_EBILED function which use for timer, LED
 *   and EBI LED control, respectively.
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static VOID Audio_PlayMenu(VOID) {
	sysPrintf("\n\n\n\n");sysPrintf("======================================\n");sysPrintf("=            Audio Playing           =\n");sysPrintf("======================================\n");sysPrintf("= Increase volume                [+] =\n");sysPrintf("= Reduce volume                  [-] =\n");sysPrintf("= Quit                         [Esc] =\n");sysPrintf("======================================\n");sysPrintf("00:00:00");
	Init_TimerLED();
	Set_EBILED(cVolumeLED[DEFAULT_VOLUME - DEFAULT_MIN_VOLUME]);
}

/****************************************************************************
 * FUNCTION
 *   Audio_PlayTest
 *
 * DESCRIPTION
 *   This function paly a build in audio pattern which audio time is around nine
 *   second.(16kHz, 1 Channel)
 *
 * CALLED BY
 *   Audio_Test
 *
 * INPUTS
 *   nDevice
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
VOID Audio_PlayTest(INT nDevice) {
	INT nLoop2 = 0;
	UINT uBlockSize = 0;

	INT nBlockCount = 0;
	INT nLastBlock = 0;
	INT nLastStart = 0;
	INT nLastSilent = 0;

	PUINT8 puBuffer;
	AU_VOLUME_T volume;

	audioOpen(nDevice);
//	while (1) {
	//get the buffer size
	audioIoctl(nDevice, AUDIO_GET_BLOCKSIZE, (UINT32) &uBlockSize);
	puBuffer = (PUINT8) malloc(uBlockSize);

	// set audio codec parameters
	nVolumeSetting = DEFAULT_VOLUME;
	volume.right = (CHAR) nVolumeSetting;
	volume.left = (CHAR) nVolumeSetting;
	audioIoctl(nDevice, AUDIO_SET_PLAYVOLUME, (UINT32) &volume);

	audioIoctl(nDevice, AUDIO_SET_SAMPLINGRATE, (UINT32) DEMO_SAMPLINGRATE);
	audioIoctl(nDevice, AUDIO_SET_CHANNELS, (UINT32) DEMO_CHANNEL);

	// show menu to user
	//Audio_PlayMenu();

	// start play
	nBlockCount = (DEMO_PCM_LEN / uBlockSize);
	nLastStart = nBlockCount * uBlockSize;
	nLastBlock = DEMO_PCM_LEN - nLastStart;
	nLastSilent = uBlockSize - nLastBlock;
#ifdef DEBUG_TEST_MODE
	sysPrintf("nBlockCount:%d\n", nBlockCount);
	sysPrintf("nLastStart:%d\n", nLastStart);
	sysPrintf("nLastBlock:%d\n", nLastBlock);
	sysPrintf("nLastSilent:%d\n", nLastSilent);
#endif
	for (nLoop2 = 0; nLoop2 < nBlockCount; nLoop2++) {
		// detect user key input
		//if(Audio_AdjustVolume(AUDIODEVICE) == STOP_PLAY)
		//{
		//    break;
		//}
		memcpy(puBuffer, pcm + (nLoop2 * uBlockSize), uBlockSize);
		if (audioWrite(nDevice, (PUINT8) puBuffer, uBlockSize) < 0)	//buffer full error
				{
			while (audioWrite(nDevice, (PUINT8) puBuffer, uBlockSize))
				;
		}
	}
	if (nLastBlock) {
		memcpy(puBuffer, pcm + nLastStart, nLastBlock);
		memset(puBuffer + nLastBlock, 0, nLastSilent);
		if (audioWrite(nDevice, (PUINT8) puBuffer, uBlockSize) < 0)	//buffer full error
				{
			while (audioWrite(nDevice, (PUINT8) puBuffer, uBlockSize))
				;
		}
	}
	audioClose();
	free(puBuffer);
//	}
	Clean_TimerLED();
	sysPrintf("\n\nAC97 play test finish!\n");
}

/****************************************************************************
 * FUNCTION
 *   Audio_RecordTest
 *
 * DESCRIPTION
 *   The audio recode test function of AC97 test program
 *
 * CALLED BY
 *   Audio_Test
 *
 * INPUTS
 *   nDevice
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static VOID Audio_RecordTest(INT nDevice) {
	INT nChannel, nSamplingRate, nVolume;
	UINT uBlockSize = 0;
	PUINT8 puTmpBuffer;
	PUINT8 puRecBuffer;
	UINT uBufferSize;
	INT nLoop, nLoop2;
	AU_VOLUME_T volume;

	audioOpen(nDevice);
	//get the buffer size
	audioIoctl(nDevice, AUDIO_GET_BLOCKSIZE, (UINT32) &uBlockSize);

	// set audio codec parameters

	nVolume = GetVolume();
	volume.right = (CHAR) nVolume;
	volume.left = (CHAR) nVolume;
	audioIoctl(nDevice, AUDIO_SET_PLAYVOLUME, (UINT32) &volume);

	nSamplingRate = GetSamplerate();
	audioIoctl(nDevice, AUDIO_SET_SAMPLINGRATE, (UINT32) nSamplingRate);

	nChannel = GetChannel();
	audioIoctl(nDevice, AUDIO_SET_CHANNELS, (UINT32) nChannel);

	// setting buffer
	//uBufferSize = (UINT)(uBlockSize * ceil((double)((nSamplingRate*nChannel)/1500)));// around 5s
	uBufferSize = (UINT) (uBlockSize
			* ceil((double) ((nSamplingRate * nChannel) / 7500)));  // around 5s
	if ((puTmpBuffer = (PUINT8) malloc(uBlockSize)) == NULL) {
		sysPrintf("puTmpBuffer malloc error!!!");
		return;
	}
	memset(puTmpBuffer, 0, uBlockSize);
	if ((puRecBuffer = (PUINT8) malloc(uBufferSize)) == NULL) {
		sysPrintf("puRecBuffer malloc error!!!");
		return;
	}
	memset(puRecBuffer, 0, uBufferSize);

	sysPrintf("\nPress any key to start record....");
	sysGetChar();
	sysPrintf("\nRecording....\n00:00:00");
	Init_TimerLED();

	// start to record
	for (nLoop2 = 0; nLoop2 < (uBufferSize / uBlockSize); nLoop2++) {
		while (audioRead(nDevice, puRecBuffer + (nLoop2 * uBlockSize),
				uBlockSize) != 0)
			;
	}

	Clean_TimerLED();
	audioIoctl(nDevice, AUDIO_STOP_RECORD, 0);
	for (nLoop = 0; nLoop < 1000; nLoop++)
		;

	sysPrintf("\nPress any key to start play....");
	sysGetChar();
	sysPrintf("\nPlaying....\n00:00:00");
	Init_TimerLED();

	// start to play
	for (nLoop2 = 0; nLoop2 < (uBufferSize / uBlockSize); nLoop2++) {
		memcpy(puTmpBuffer, puRecBuffer + (nLoop2 * uBlockSize), uBlockSize);

		if (audioWrite(nDevice, puTmpBuffer, uBlockSize) < 0) {
			for (nLoop = 0; nLoop < 10; nLoop++)
				;
			while (audioWrite(nDevice, puTmpBuffer, uBlockSize) != 0)
				;
		}
	}
	//for(nLoop = 0; nLoop < 1000; nLoop++);
	sysDelay(100);
	audioClose();
	Clean_TimerLED();
	free(puRecBuffer);
	free(puTmpBuffer);

	sysPrintf("\n\nAC97 record test finish!\n");
}

/****************************************************************************
 * FUNCTION
 *   Audio_Test
 *
 * DESCRIPTION
 *   The main function of AC97 test program
 *
 * CALLED BY
 *   main
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
VOID Audio_Test(VOID) {
	CHAR cUserSelect;

	// init audio
	audioInit();
	while (1) {
		Audio_PlayTest(AC97_DEVICE);
	}
	audioExit();

//    do
//    {
//        Audio_Item();// Show menu
//        cUserSelect = '1';//();// Get user select
//
//        switch(cUserSelect)
//        {
//            case '1':
//            {
//
//                break;
//            }
//            case '2':
//            {
//
//	            sysPrintf("Press any key to continue....");
//	            sysGetChar();
//                break;
//            }
//            #ifdef SD_PATTERN
//            case '3':
//            {
//                Audio_MediaPlayTest(AC97_DEVICE, SD_DISK);
//	            sysPrintf("Press any key to continue....");
//	            sysGetChar();
//                break;
//            }
//            case '4':
//            {
//                Audio_RecordTest(AC97_DEVICE);
//	            sysPrintf("Press any key to continue....");
//	            sysGetChar();
//                break;
//            }
//            #else
//            case '3':
//            {
//                Audio_RecordTest(AC97_DEVICE);
//	            sysPrintf("Press any key to continue....");
//	            sysGetChar();
//                break;
//            }
//            #endif
//            default:    break;
//        }
//    }while (cUserSelect != 27);// Do until user press ESC
	Set_EBILED(0x00);
}

/****************************************************************************
 * FUNCTION
 *   Clean_TimerLED
 *
 * DESCRIPTION
 *   This function clear LED(GPIO11) as LOW and clear timer event which
 *   use to show the audio play time.
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static VOID Clean_TimerLED(VOID) {
	UINT uMask, uValue;

	// Clear timer status
	sysClearTimerEvent(TIMER1, uTimeEventNum);
	sysStopTimer(TIMER1);

	// Set LED OFF
	uMask = DATA_MASK(GPIO_CFG6);
	uValue = DATAOUT_VALUE(GPIO_CFG6, GPIO_LO);
	gpioIoctl(GPIO_PORT5, SET_DATAOUT, uMask, uValue);
}

/****************************************************************************
 * FUNCTION
 *   GetChannel
 *
 * DESCRIPTION
 *   This function get user's input for channel setting
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   1/2
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static INT GetChannel(VOID) {
	CHAR cInput = 0;
	while (1) {
		sysPrintf("\nSelect number of channel:\n");sysPrintf("1.Mono\n");sysPrintf("2.Stereo\n");
		cInput = sysGetChar();
		switch (cInput) {
		case '1':
			return 1;
			break;
		case '2':
			return 2;
			break;
		default:
			break;
		}
	}
}

/****************************************************************************
 * FUNCTION
 *   GetSamplerate
 *
 * DESCRIPTION
 *   This function get user's input for sample rate setting
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   AU_SAMPLE_RATE_8000
 *   AU_SAMPLE_RATE_11025
 *   AU_SAMPLE_RATE_12000
 *   AU_SAMPLE_RATE_16000
 *   AU_SAMPLE_RATE_22050
 *   AU_SAMPLE_RATE_24000
 *   AU_SAMPLE_RATE_32000
 *   AU_SAMPLE_RATE_44100
 *   AU_SAMPLE_RATE_48000
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static INT GetSamplerate(VOID) {
	CHAR cInput = 0;
	while (1) {
		sysPrintf("\nSelect sampling rate:\n");sysPrintf("1.8k\n");sysPrintf("2.11.025k\n");sysPrintf("3.12k\n");sysPrintf("4.16k\n");sysPrintf("5.22.05k\n");sysPrintf("6.24k\n");sysPrintf("7.32k\n");sysPrintf("8.44.1k\n");sysPrintf("9.48k\n");

		cInput = sysGetChar();
		switch (cInput) {
		case '1':
			return AU_SAMPLE_RATE_8000;
			break;
		case '2':
			return AU_SAMPLE_RATE_11025;
			break;
		case '3':
			return AU_SAMPLE_RATE_12000;
			break;
		case '4':
			return AU_SAMPLE_RATE_16000;
			break;
		case '5':
			return AU_SAMPLE_RATE_22050;
			break;
		case '6':
			return AU_SAMPLE_RATE_24000;
			break;
		case '7':
			return AU_SAMPLE_RATE_32000;
			break;
		case '8':
			return AU_SAMPLE_RATE_44100;
			break;
		case '9':
			return AU_SAMPLE_RATE_48000;
			break;
		default:
			break;
		}
	}
	return 0;

}

/****************************************************************************
 * FUNCTION
 *   GetVolume
 *
 * DESCRIPTION
 *   This function get user's input for volume setting
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   1~30
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static INT GetVolume(VOID) {
	INT nVolume = 0;
	INT nLoop = 0;
	CHAR cInputVolume[MAX_VOLUME_LENGTH + 1] = { 0 };
	while (1) {
		sysPrintf("\nInput the volume(1-30):\n");
		while ((cInputVolume[nLoop] = sysGetChar()) != 0x0d) {
			if (cInputVolume[nLoop] == 8) {
				if (nLoop != 0) {
					cInputVolume[nLoop] = 0;
					cInputVolume[nLoop - 1] = 0;
					sysPrintf("\r                                   ");sysPrintf("\r%s", cInputVolume);
					nLoop--;
				}
			} else if (cInputVolume[nLoop] >= '0'
					&& cInputVolume[nLoop] <= '9') {
				sysPrintf("%c", cInputVolume[nLoop]);
				nLoop++;
				if (nLoop == MAX_VOLUME_LENGTH + 1) {
					nLoop = 0;
					memset(cInputVolume, 0, MAX_VOLUME_LENGTH);
					sysPrintf("\r                                   \r");
				}
			}
		}
		nVolume = atoi(cInputVolume);
		if (nVolume <= 30 && nVolume > 0) {
			break;
		} else {
			nLoop = 0;
			memset(cInputVolume, 0, MAX_VOLUME_LENGTH);
		}
	}
	return nVolume;
}

/****************************************************************************
 * FUNCTION
 *   Init_TimerLED
 *
 * DESCRIPTION
 *   The timer LED initiation function.
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static VOID Init_TimerLED(VOID) {
	UINT uMask, uValue;

	// Set GPIO pin 11 and 12 as GPIO output mode(internal pull-up enable)
	uMask = CFG_MASK(GPIO_CFG6);
	uValue = CFG_VALUE(GPIO_CFG6, GPIO_IO);
	gpioIoctl(GPIO_PORT5, SET_CFG, uMask, uValue);

	uMask = DIR_MASK(GPIO_CFG6);
	uValue = DIR_VALUE(GPIO_CFG6, GPIO_OUTPUT, PUPEN_ENABLE);
	gpioIoctl(GPIO_PORT5, SET_DIR, uMask, uValue);

	// reset flag and counter
	nTimerLED = 0;
	nTimerCount = 0;

	// start time1 to flash LED and show audio play time
	sysSetTimerReferenceClock(TIMER1, 15000000);
	sysStartTimer(TIMER1, 1, PERIODIC_MODE);
	uTimeEventNum = (UINT) sysSetTimerEvent(TIMER1, 1, (PVOID) Set_TimerLED);
}

/****************************************************************************
 * FUNCTION
 *   Set_TimerLED
 *
 * DESCRIPTION
 *   This function set LED(GPIO11) HIGH or LOW according to the global
 *   variable, nTimerLED. The audio play timer also print to screen in
 *   this function.
 *
 * CALLED BY
 *   various components
 *
 * INPUTS
 *   None
 *
 * OUTPUTS
 *   None
 *
 * HISTORY
 *   NAME        DATE        REMARKS
 *   NS21 WTLiu	2006-02-08	Created initial version
 *
 * REMARK
 *     None
 ****************************************************************************/
static VOID Set_TimerLED(VOID) {
	UINT uMask, uValue;
	INT nHour = 0, nMinute = 0, nSecond = 0;

	//time counter increase
	nTimerCount++;

	// convert to time format hh:mm:ss
	nSecond = nTimerCount % 60;
	nMinute = ((nTimerCount - nSecond) / 60) % 60;
	nHour = ((nTimerCount - (nMinute * 60) - nSecond) / (60 * 60) % 60);

	//show audio play time
	sysPrintf("\r                    ");sysPrintf("\r%02d:%02d:%02d", nHour, nMinute, nSecond);

	// set LED
	if (nTimerLED == GPIO_HI) {
		nTimerLED = GPIO_LO; // LED OFF
	} else {
		nTimerLED = GPIO_HI; // LED ON
	}
	uMask = DATA_MASK(GPIO_CFG6);
	uValue = DATAOUT_VALUE(GPIO_CFG6, nTimerLED);
	gpioIoctl(GPIO_PORT5, SET_DATAOUT, uMask, uValue);
}
