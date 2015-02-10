/*H**************************************************************************
* NAME:         compiler.h
*----------------------------------------------------------------------------
* Copyright (c) 2003 Atmel.
*----------------------------------------------------------------------------
* RELEASE:      cc03-canmon-0_0_1      
* FILE_REV:     1.17     
*----------------------------------------------------------------------------
* PURPOSE:
* This file redefines dedicated KEIL, RAISONANCE and TASKINKG C51/C251
* keywords in order to ensure that any source file can be processed by
* these compilers.
*****************************************************************************/

#ifndef _COMPILER_H_
#define _COMPILER_H_

/*_____ I N C L U D E S ____________________________________________________*/


/*_____ D E C L A R A T I O N S ____________________________________________*/
#ifndef ASM_INCLUDE // define ASM_INCLUDE in your a51 source code before include of .h file
typedef unsigned char       Uchar;
typedef float               Float16;

typedef unsigned char       Uint8;   // Obsolete. Please use U8
typedef unsigned int        Uint16;  // Obsolete. Please use U16
typedef unsigned long int   Uint32;  // Obsolete. Please use U32

typedef char                Int8;    // Obsolete. Please use S8
typedef int                 Int16;   // Obsolete. Please use S16
typedef long int            Int32;   // Obsolete. Please use S32

typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned long int   U32;

typedef char                S8;
typedef short               S16;
typedef long int            S32;

typedef unsigned char       Bool;
typedef unsigned char       Byte;
typedef unsigned int        Word;
typedef unsigned long int   DWord;

typedef	unsigned char		BYTE;
typedef	unsigned int		WORD;
typedef	unsigned long		DWORD;

typedef union 
{
  Uint32 dw; // l changed in dw (double word) because l is used for signed long...
  Uint16 w[2];
  Uint8  b[4];
} Union32;

typedef union 
{
  Uint16 w;
  Uint8  b[2];
} Union16;
#endif


#define DATA		data
#define PDATA		pdata
#define XDATA		xdata
#define IDATA		data
#define CODE		code
#define CODE_P
#define PDATA_P
#define IDATA_P
#define DATA_P


/*_____ M A C R O S ________________________________________________________*/
/* little-big endian management */
#define INTEL_ALIGNMENT     LITTLE_ENDIAN
#define MOTOROLA_ALIGNMENT  BIG_ENDIAN

// Union16/32 endian handlers
#ifdef LITTLE_ENDIAN     // => 16bit: (LSB,MSB), 32bit: (LSW,MSW) or (LSB0,LSB1,LSB2,LSB3) or (MSB3,MSB2,MSB1,MSB0)
#define MSB(union16)        ((union16).b[1])
#define LSB(union16)        (*(union16).b)
#define MSW(union32)        ((union32).w[1])
#define LSW(union32)        (*(union32).w)
#define MSB0(union32)       ((union32).b[3])
#define MSB1(union32)       ((union32).b[2])
#define MSB2(union32)       ((union32).b[1])
#define MSB3(union32)       (*(union32).b)
#define LSB0(union32)       (*(union32).b)
#define LSB1(union32)       ((union32).b[1])
#define LSB2(union32)       ((union32).b[2])
#define LSB3(union32)       ((union32).b[3])
#else // BIG_ENDIAN         => 16bit: (MSB,LSB), 32bit: (MSW,LSW) or (LSB3,LSB2,LSB1,LSB0) or (MSB0,MSB1,MSB2,MSB3)
#define MSB(union16)        (*((Union16*)&union16)->b)
#define LSB(union16)        (((Union16*)&union16)->b[1])
#define MSW(union32)        (*((Union32*)&union32)->w)
#define LSW(union32)        (((Union32*)&union32)->w[1])
#define MSB0(union32)       (*((Union32*)&union32)->b)
#define MSB1(union32)       (((Union32*)&union32)->b[1])
#define MSB2(union32)       (((Union32*)&union32)->b[2])
#define MSB3(union32)       (((Union32*)&union32)->b[3])
#define LSB0(union32)       (((Union32*)&union32)->b[3])
#define LSB1(union32)       (((Union32*)&union32)->b[2])
#define LSB2(union32)       (((Union32*)&union32)->b[1])
#define LSB3(union32)       (*((Union32*)&union32)->b)
#endif

// Endian converters
#define LE16(b) (((Uint16)((b) & 0xFF) << 8) | (((Uint16)(b) & 0xFF00) >> 8))
#define LE32(b) (((Uint32)((b) & 0xFF) << 24) | ((Uint32)((Uint16)(b) & 0xFF00) << 8) | \
                   (((Uint32)(b) & 0xFF0000) >> 8) | (((Uint32)(b) & 0xFF000000) >> 24))

// host to network conversion: used for Intel HEX format, TCP/IP, ...
// Convert a 16-bit value from host-byte order to network-byte order
// Standard Unix, POSIX 1003.1g (draft)
#ifdef LITTLE_ENDIAN
#define htons(a)    LE16(a)
#define ntohs(a)    htons(a)
#define htonl(a)    LE32(a)
#define ntohl(a)    htonl(a)
#else
#define htons(a)    (a)
#define ntohs(a)    (a)
#define htonl(a)    (a)
#define ntohl(a)    (a)
#endif

/* Memory Type Location */
#ifndef _ConstType_
#define _ConstType_ code
#endif

#ifndef _MemType_
#define _MemType_
#endif

#ifndef _GenericType_
#define _GenericType_
#endif

/* Constants */
#define FALSE   0
#define TRUE    1
#define KO      0
#define OK      1
#define OFF     0
#define ON      1
#ifndef ASM_INCLUDE // define ASM_INCLUDE in your a51 source code before include of .h file
#define CLR     0
#define SET     1
#endif

/* Bit and bytes manipulations */
#define LOW(U16)                ((Uchar)U16)
#define HIGH(U16)               ((Uchar)(U16>>8))
#define TST_BIT_X(addrx,mask)   (*addrx & mask)
#define SET_BIT_X(addrx,mask)   (*addrx = (*addrx | mask))
#define CLR_BIT_X(addrx,mask)   (*addrx = (*addrx & ~mask))
#define OUT_X(addrx,value)      (*addrx = value)
#define IN_X(addrx)             (*addrx)

/*M**************************************************************************
* NAME: Long_call
*----------------------------------------------------------------------------
* PARAMS:
* addr: address of the routine to call
*----------------------------------------------------------------------------
* PURPOSE: 
* Call the routine at address addr: generate an Assembly LCALL addr opcode.
*----------------------------------------------------------------------------
* EXAMPLE:
* Long_call(0); // Software reset (if no IT used before)
*----------------------------------------------------------------------------
* NOTE: 
* May be used as a long jump opcode in some special cases
*****************************************************************************/
#define Long_call(addr)         ((*(void (_ConstType_*)(void))(addr))())

/* {For Langdoc} */

/***********************************************************
 SET_SFR_BIT macro 
  parameters 
    sfr_reg : defined value in include file for sfr register 
    bit_pos : defined value B_XX in include file for particular
              bit of sfr register 
    bit_val : CLR / SET 
************************************************************/
#define SET_SFR_BIT(sfr_reg, bit_pos, bit_val) { sfr_reg &= ~(1<<(bit_pos)); sfr_reg |= ((bit_val)<<(bit_pos));}

/***********************************************************
 TST_SFR_BIT macro 
  parameters 
    sfr_reg : defined value in include file for sfr register 
    bit_pos : defined value B_XX in include file for particular
              bit of sfr register 
************************************************************/
#define TST_SFR_BIT(sfr_reg, bit_pos) ((sfr_reg & (1<<(bit_pos)))>>(bit_pos))

#ifdef KEIL             /* KEIL compiler */

#define Reentrant(x)    x reentrant
#define Sfr(x,y)        sfr x = y
#define Sfr16(x,y)      sfr16 x = y
#define Sbit(x,y,z)     sbit x = y ^ z
#define Interrupt(x,y)  x interrupt y
#define At(x)           _at_ x

#ifdef __C51__          /* C51 Compiler */
#define far  xdata      /* far is for C251 only */  
#endif

#endif                  /* End of KEIL */


#ifdef RAISONANCE       /* RAISONANCE compiler */

#define Reentrant(x)    x reentrant
#define Sfr(x,y)        sfr x = y
#define Sbit(x,y,z)     sbit x = y ^ z
#define Interrupt(x,y)  x interrupt y
#define At(x)           _at_ x

#ifdef __C51__          /* C51 Compiler */
#define far  xdata      /* far is for 251 only */
#endif

#endif                  /* End of RAISONANCE */


#ifdef TASKING          /* TASKING compiler */

#include <keil.h>       /* Include Tasking / Keil compatibility header file */ 

#define far             _far
#define Reentrant(x)    _reentrant x
#define Sfr(x,y)        _sfrbyte x _at(y)
#define Sbit(x,y,z)     _sfrbit x _atbit(y,z)
#define Interrupt(x,y)  _interrupt(y) x

#endif                  /* End of TASKING */
#ifdef _IAR_AVR_  
        
#define __IOMACRO_H

#define TID_GUARD(proc) ((__TID__ & 0x7FF0) != ((90 << 8) | ((proc) << 4)))

#if !(__IAR_SYSTEMS_ICC__ > 2) && !defined(__IAR_SYSTEMS_ASM__)
#error This file should only be compiled with iccavr or aavr.
#endif /* !(__IAR_SYSTEMS_ICC__ > 2) && !defined __IAR_SYSTEMS_ASM__ */

/* The assembler uses a special set of macros... */
#ifdef __IAR_SYSTEMS_ASM__

/* Byte sized SFRs */
#define SFR_B_BITS(_NAME,_ADDR,_A,_B,_C,_D,_E,_F,_G,_H)\
	sfrb	_NAME = _ADDR
#define SFR_B_BITS_EXT(_NAME,_ADDR,_A,_B,_C,_D,_E,_F,_G,_H)\
	sfrb	_NAME = _ADDR
#define SFR_B2_BITS(_NAME1,_NAME2,_ADDR,_A,_B,_C,_D,_E,_F,_G,_H)\
	ASMSFRB2 _NAME1, _NAME2, _ADDR

ASMSFRB2 MACRO
	sfrb	\1 = \3
	sfrb	\2 = \3
	ENDM


/* Word sized SFRs, needs to be expanded into an assembler macro first. */
#define SFR_W_BITS(_NAME, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H, _I,_J,_K,_L,_M,_N,_O,_P)\
	ASMSFRW	_NAME, _ADDR

#define SFR_W_BITS_EXT(_NAME, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H, _I,_J,_K,_L,_M,_N,_O,_P)\
	ASMSFRW	_NAME, _ADDR

ASMSFRW	MACRO
	sfrw	\1  = \2
	sfrb	\1L = (\2+0)
	sfrb	\1H = (\2+1)
	ENDM

#endif /* __IAR_SYSTEMS_ASM__ */

#ifdef __ICCAVR__

#define __BYTEBITS(_NAME,_A,_B,_C,_D,_E,_F,_G,_H) \
unsigned char _NAME ## _ ## _A:1, \
              _NAME ## _ ## _B:1, \
              _NAME ## _ ## _C:1, \
              _NAME ## _ ## _D:1, \
              _NAME ## _ ## _E:1, \
              _NAME ## _ ## _F:1, \
              _NAME ## _ ## _G:1, \
              _NAME ## _ ## _H:1;

#define SFR_B_BITS(_NAME, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H) \
    __io union { \
      unsigned char   _NAME;           /* The sfrb as 1 byte */ \
      struct {                        /* The sfrb as 8 bits */ \
        __BYTEBITS(_NAME, _A,_B,_C,_D,_E,_F,_G,_H) \
      };  \
    } @ _ADDR;
#define SFR_B2_BITS(_NAME1, _NAME2, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H) \
    __io union { \
      unsigned char   _NAME1;           /* The sfrb as 1 byte */ \
      unsigned char   _NAME2;           /* The sfrb as 1 byte */ \
      struct {                        /* The sfrb as 8 bits */ \
        __BYTEBITS(_NAME1, _A,_B,_C,_D,_E,_F,_G,_H) \
      };  \
      struct {                        /* The sfrb as 8 bits */ \
        __BYTEBITS(_NAME2, _A,_B,_C,_D,_E,_F,_G,_H) \
      };  \
    } @ _ADDR;
#define SFR_B_BITS_EXT(_NAME, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H) \
    __tiny __no_init volatile union { \
      unsigned char   _NAME;           /* The sfrb as 1 byte */ \
      struct {                        /* The sfrb as 8 bits */ \
        __BYTEBITS(_NAME, _A,_B,_C,_D,_E,_F,_G,_H) \
      };  \
    } @ _ADDR;
  
#define SFR_W_BITS(_NAME, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H, _I,_J,_K,_L,_M,_N,_O,_P) \
    __io union { \
      unsigned short  _NAME;  /* The sfrw as 1 short */ \
      struct {                /* The sfrw as 16 bits */ \
        __BYTEBITS(_NAME, _A,_B,_C,_D,_E,_F,_G,_H)   /* Bit names defined by user */  \
        __BYTEBITS(_NAME, _I,_J,_K,_L,_M,_N,_O,_P)   /* Bit names defined by user */  \
      };  \
      struct { /* The sfrw as 2 bytes */ \
        unsigned char _NAME ## L; \
        unsigned char _NAME ## H; \
      };  \
      struct {                          /* The sfrw as 2 x 8 bits */ \
        __BYTEBITS(_NAME ## L, Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)  /* Bit names hard coded to 0-7 */ \
        __BYTEBITS(_NAME ## H, Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)  /* Bit names hard coded to 0-7 */ \
      };  \
    } @ _ADDR;

#define SFR_W_BITS_EXT(_NAME, _ADDR, _A,_B,_C,_D,_E,_F,_G,_H, _I,_J,_K,_L,_M,_N,_O,_P) \
   __tiny __no_init volatile union { \
    unsigned short  _NAME;   \
     struct {                /* The sfrw_ext as 16 bits */ \
        __BYTEBITS(_NAME, _A,_B,_C,_D,_E,_F,_G,_H)   /* Bit names defined by user */  \
        __BYTEBITS(_NAME, _I,_J,_K,_L,_M,_N,_O,_P)   /* Bit names defined by user */  \
      };  \
      struct { /* The sfrw _ext as 2 bytes */ \
        unsigned char _NAME ## L; \
        unsigned char _NAME ## H; \
      };  \
      struct {                          /* The sfrw_ext as 2 x 8 bits */ \
        __BYTEBITS(_NAME ## L, Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)  /* Bit names hard coded to 0-7 */ \
        __BYTEBITS(_NAME ## H, Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)  /* Bit names hard coded to 0-7 */ \
      };  \
    } @ _ADDR;

#endif /* __ICCAVR__ */

#define SFR_B(_NAME, _ADDR) SFR_B_BITS(_NAME, _ADDR, \
                                    Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)
#define SFR_B2(_NAME1, _NAME2, _ADDR) SFR_B2_BITS(_NAME1, _NAME2, _ADDR, \
                                    Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)
#define SFR_B_EXT(_NAME, _ADDR) SFR_B_BITS_EXT(_NAME, _ADDR, \
                                    Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7)

#define SFR_W(_NAME, _ADDR)  SFR_W_BITS(_NAME, _ADDR, \
                                    Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7, \
                                    Bit8,Bit9,Bit10,Bit11,Bit12,Bit13,Bit14,Bit15)

#define SFR_W_EXT(_NAME, _ADDR)  SFR_W_BITS_EXT(_NAME, _ADDR, \
                                    Bit0,Bit1,Bit2,Bit3,Bit4,Bit5,Bit6,Bit7, \
                                    Bit8,Bit9,Bit10,Bit11,Bit12,Bit13,Bit14,Bit15)

#endif /* _IAR_AVR_ */





#endif /* _COMPILER_H_ */

