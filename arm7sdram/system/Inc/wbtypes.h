/****************************************************************************
*                                                                          *
* Copyright (c) 2000 - 2002 Winbond Electronics Corp. All rights reserved. *
*                                                                          *
***************************************************************************/

/****************************************************************************
*
* FILENAME
*     wbtypes.h
*
* VERSION
*     1.0
*
* DESCRIPTION
*     This PreDefined data types for Winbond ARM7 MCU
*
* DATA STRUCTURES
*     None
*
* FUNCTIONS
*     None
*
* HISTORY
*     03/11/02       Ver 1.0 Created by PC30 YCHuang
*
* REMARK
*     None
**************************************************************************/
#ifndef _WBTYPES_H_
#define _WBTYPES_H_

/* wbtypes.h Release 1.0 */

#define CONST             const

#define FALSE             0
#define TRUE              1

#undef VOID
typedef void              VOID;
typedef void *            PVOID;

typedef char              BOOL;
typedef char *            PBOOL;

typedef char              INT8;
typedef char              CHAR;
typedef char *            PINT8;
typedef char *            PCHAR;
typedef unsigned char     UINT8;
typedef unsigned char     UCHAR;
typedef unsigned char *   PUINT8;
typedef unsigned char *   PUCHAR;
typedef char *            PSTR;
typedef const char *      PCSTR;

typedef short             SHORT;
typedef short *           PSHORT;
typedef unsigned short    USHORT;
typedef unsigned short *  PUSHORT;

typedef short             INT16;
typedef short *           PINT16;
typedef unsigned short    UINT16;
typedef unsigned short *  PUINT16;

typedef int               INT;
typedef int *             PINT;
typedef unsigned int      UINT;
typedef unsigned int *    PUINT;

typedef signed long       INT32;
typedef int *             PINT32;
typedef unsigned long     UINT32;
typedef unsigned int *    PUINT32;

//typedef int64_t           INT64;
//typedef unsigned __int64  UINT64;

typedef float             FLOAT;
typedef float *           PFLOAT;

typedef double            DOUBLE;
typedef double *          PDOUBLE;

typedef int               SIZE_T;

typedef unsigned char     REG8;
typedef unsigned short    REG16;
typedef unsigned int      REG32;

#endif /* _WBTYPES_H */
