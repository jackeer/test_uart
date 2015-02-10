/******************************************************************************
 Copyright (c) 2007 Topro Technology Inc.
 All rights reserved.

 Module Name: TP6822DEF.H

 Abstract:
   C languge MACRO definition

 Author:         10-Oct-2007

 Reversion History:

*******************************************************************************/
#ifndef _TP6822DEF_H
#define _TP6822DEF_H
//#include "mpu.h" 

//--------------------------- Definition ---------------------------
typedef bit               BIT;
typedef bit               BOOL;
typedef unsigned char     UCHAR;
typedef unsigned char     BYTE;
typedef unsigned int      UINT;
typedef unsigned int      WORD;
typedef unsigned long     ULONG;
typedef unsigned long     DWORD;
typedef unsigned short	USHORT;

typedef unsigned char     *PUCHAR;
typedef BYTE              *PBYTE;
typedef UINT              *PUINT;
typedef WORD              *PWORD;
typedef ULONG             *PULONG;
typedef DWORD             *PDWORD;
typedef void              *PVOID;
#define EOS 			'\0'
#define FALSE             (BOOL)0
#define TRUE              (BOOL)!FALSE

#ifndef NULL
#define NULL              0
#endif

//--------------------------- KEIL C ---------------------------
#define DATA              data
#define BDATA             bdata
#define IDATA             idata
#define PDATA             pdata
#define XDATA             xdata
#define RDATA             code

#define CBYTE             ((unsigned char volatile code  *) 0)
#define DBYTE             ((unsigned char volatile data  *) 0)
#define PBYTE             ((unsigned char volatile pdata *) 0)
#define XBYTE             ((unsigned char volatile xdata *) 0)

//--------------------------- MACRO ---------------------------
#define HIBYTE_REF(addr)          (*((BYTE *) & addr))
#define LOBYTE_REF(addr)          (*((BYTE *) & addr + 1))
#define MAKEWORD(value1, value2)  (((WORD)value1) * 0x100) + value2
#define MAKEUINT(value1, value2)  (((WORD)value1) * 0x100) + value2
#define HIBYTE(value)             ((BYTE)(value / 0x100))
#define LOBYTE(value)             ((BYTE)value)

#define MAX(a, b)         (((a) > (b)) ? (a) : (b))
#define MIN(a ,b)         (((a) < (b)) ? (a) : (b))

//--------------------------- Common ----------------------------
// The following registers are TP67XX system registers. They are located on a data area of MPU
// through memory mapping and can be accessed by address writes.
#define TP_SREG           ((unsigned char volatile pdata *) 0) // TP67XX Registers

#define Disp1Ch	1
#define Disp2Ch 2

#define HIGH 1
#define LOW  0

#define END_OF_TABLE 0xffff
//---------------------------------------------------------------
//            For External Flash  & SRam
//
#define	FlashAddr	0x0000FD00
#define	NumData	    0x000002FF
#define	SRamAddr	0x0000FD00
//#define DemoKit	



#endif
