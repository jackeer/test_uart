/******************************************************************************
 Copyright (c) 2007 Topro Technology Inc.
 All rights reserved.

 Module Name: 766MPU.H

 Abstract:
   MPU register definition.

 Author:         26-Oct-2007 THHSU

 Reversion History:

*******************************************************************************/
#ifndef _TP6822MPU_H
#define _TP6822MPU_H

#include	"W77E516.h"                // for the intended 8052 derivative

//======================== MPU Pin Define ========================



sbit R_LED    = P1 ^ 0;
sbit G_LED    = P1 ^ 7;
sbit T_P2_6 = P3 ^ 3;
sbit T_P2_7 = P3 ^ 4;
sbit Reset = P3 ^ 5;



/////////////////////////////////////////////////////////////////////
// PORT 4
// Another bit-addressable port P4 is also and only 4 bits(P4[3:0])
// can be used. This port address is located at D8 with the same
// function as that of port P1.
/////////////////////////////////////////////////////////////////////
sfr P4 = 0xD8;

sbit EE_Bank1 = P4 ^ 1;
sbit P4_0 = P4 ^ 0;
sbit P4_1 = P4 ^ 1;
sbit P4_2 = P4 ^ 2;
sbit P4_3 = P4 ^ 3;
#if 0
//========================== MPU Ports Pin Definition ============================
    
  sfr  SPIPort  = 0x93 ;
  sfr  SPIDOUT  = 0x94 ;
  //
  sbit	HOLD = P0 ^ 0;//P0_0 Hold
  sbit	C 	 = P0 ^ 1;//P0_1 C Serial Clock
  sbit	D 	 = P0 ^ 2;//P0_2 D Serial Data input
  sbit	S 	 = P0 ^ 7;//P0_3 S Chip Select
  sbit	Q 	 = P0 ^ 4;//P0_4 Q Serial Data output
  sbit	W 	 = P0 ^ 5;//P0_5 W Write Protect
  //  
 #endif
  sfr WESRAM = 0x8f;//Writer External SRam
 
 

//======================== Winbond W78E516/W78E62 ========================
// AUX-RAM 00-FF is addressed indirectly as the same way to access external
// data with thw MOVX instruction. Address pointer are R0 and R1 of the
// selected register bank and DPTR register. An access to external data
// memory locations higher than FF will be performed with the with the
// MOVX instruction in the same way as in the 8051. The AUX-RAM is disable
// after a reset. Setting the bit 4 in CHPCON register will enable the access
// to AUX-RAM. When AUX-RAM is enabled the instruction of "MOX @Ri" will always
// access to in-chip AUX-RAM. Wen executing from internal program memory, an
// access to AUX-RAM will not affect the Ports P0, P2, WR, RD/

////////////////////////////////
// #W78E516/62/65 MPU register
//
// Special Function Registers
////////////////////////////////
sfr CHPCON =  0xBF;     // In-System Programming Control Register
                        //   b7: Software reset
                        //   b6: Reserved
                        //   b5: Reserved
                        //   b4: Enable on-chip AUX-RAM
                        //   b3: must set to  0
                        //   b2: must set to  0
                        //   b1: The Program Location Select(0:64K, 1:4K)
                        //   b0: FLASH EPROM Programming Enable
sfr CHPENR =  0xF6;     // #W78E516 MPU register
sfr SFRAL  =  0xC4;     // The objective address of on-chip FLASH EPROM in the in-system programming(low)
sfr SFRAH  =  0xC5;     // The objective address of on-chip FLASH EPROM in the in-system programming(high)
sfr SFRFD  =  0xC6;     // The programming data for on-chip FLASH EPROM in programming mode
sfr SFRCN  =  0xC7;     // The control byte of on-chip FLASH EPROM programming mode
                        //   b7: Reserved
                        //   b6: On-chip FLASH EPROM bank select for in-system programming(0: 64K, 1: 4K)
                        //   b5: FLASH EPROM output enable
                        //   b4: FLASH EPROM chip enable
                        //   b3-0: The flash control signals


///////////////////////////////////////////
// SyncMOS SM2965 MPU Registers
//
// Special Function Registers
///////////////////////////////////////////
sfr WDTC  = 0x9f;       // Watch Dog Timer Register.
sfr SCONF = 0xbf;       // System Control Register.
                        //   b7: Watch dog timer reset. When system reset by watch dog timer overflow(=1).
                        //   b6-4: Reserved
                        //   b3: 64K Data Flash enable bit.(SM59264)
                        //   b2: ISP function enable bit.
                        //   b1: 768 byte on-chip RAM enable bit.(MOVX @DPTR)
                        //   b0: ALE output inhibit bit, to reduce EMI.
sfr SFAH  = 0xf4;       // Flash Address-High Register.
sfr SFAL  = 0xf5;       // Flash Address-Low Register.
sfr SFDAT = 0xf6;       // Flash Data Register.
sfr SFCR  = 0xf7;       // Flash Control Register.
                        //   b7: ISP function start bit
                        //   b6: Reserved
                        //   b5: 64K program Flash or 64K Data Flash select bit(SM59264)
                        //   b4-2: Reserved
                        //   b1-0: ISP function
sfr SFN   = 0xfa;       // ISP N Control Register.

sfr IMPSR = 0x85;       // Internal Memory Page Select Register.(MOVX @Ri: i=1,2)(SM2965)

sfr SRCON = 0x85;       // Second Data Pointer Register.(MOVX @Ri: i=1,2)(SM59264)
sfr DBANK = 0x86;       // Data Bank Control Register.(b3-0: 3fh)(MOV $040H-$07FH)(SM59264)

///////////////////////////////////////////
// Topro TP2804 MPU Registers
//
// Special Function Registers
/////////////////////////////////////////////#v1.1@8.10.2004
//sfr TPCHPCON = 0xbf;    // System Control Register.
                        //   b7: Software reset.
                        //   b6-5: Reserved
                        //   b4: Enable/Disable the on-chip AUX-RAM.
                        //   b3: Oscillator
                        //   b2: Fixed set to 0.
                        //   b1: Fixed set to 0.
                        //   b0: FLASH EPROM programming enable.
//sfr TPFCR    = 0xe8;    // Flash Control Register.
                        //   b7: ISP enable
                        //   b6-5: Reserved
                        //   b4: Fixed set to 0
                        //   b3: Fixed set to 1
                        //   b2: ISP Erase(512 bytes)
                        //   b1: ISP program(write 256 byte from AUX-RAM)
                        //   b1: ISP read(read 256 byte to AUX-RAM)
//sfr TPFRAH   = 0xe9;    // Flash Address-High Register.

//sfr TPFRAQ   = 0xc0;    // Flash Address-High Register.
sfr	ISP_Ctrl	=	0xE8;
sfr	ISP_Addr	=	0xE9;
sfr LOCKCON = 0xBE;    // System Control Register.
#endif
