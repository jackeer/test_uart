#define __TP6822UART__
//#include "W77E516.h"
#include "def.h"
#include "mpu.h"
#undef __TP6822UART__



//===================================================================
//	F: putchar()
//	Put One Character to UART
//
//	IN: OneChar = a character
//===================================================================
void putchar(BYTE OneChar)
{
	EA = 0; // disable all interrupt
#if 1
	SBUF = OneChar; // transfer UART

	while(1) // wait completing
		{
		if (TI)
			break;
		}
	  
	TI = 0; // clear TI
#else
	SBUF1 = OneChar; // transfer UART

	while(1) // wait completing
		{
		if (TI_1)
			break;
		}
	  
	TI_1 = 0; // clear TI
#endif
	EA = 1; // release EA bit
}


//===================================================================
//	TP6761 check ok
//	F: InitUART()
//===================================================================

void InitUART(void)
{
	IE = 0xD1;                   //   IE: enable UART interrupt
	SCON0 = 0x50;                 // SCON: mode 1, 8-bit UART, enable rcvr
	SCON1 = 0x50;
	TMOD = 0x20;
	TH1 = 0xFD;         // TH1: 9600 (10416.6) bit/sec , 20MHz
//	TL1 = 0xFD;
	//PCON = PCON | 0x80;
//	WDCON = WDCON | 0x80;
	TCON = 5;
	
	TR1 = 1;            // TR1: timer 1 run
	ET0 = 0;
}

///////////////////////////////////////
//  put string to UART
//
//   IN: pString = string address
///////////////////////////////////////
void printf(BYTE code *pString)
{
 
 BYTE CharBff; // character buffer
 
 while(1) // while for put character
 {
  CharBff = *pString; // get character

  if (CharBff == EOS) // end of string
   break;

  putchar(CharBff); // put character
  pString++; // next
 } // while
}
//================================= @4.UART Common Subroutines =================================
//////////////////////////////////////////////////////////////
//  Convert HEX value TO ASCII
//    IN : one byte
//    OUT: two bytes (low ASCII code, high ASCII code)
//////////////////////////////////////////////////////////////
UINT HEX2ASCII(BYTE OneByte)
{
 BYTE OutByte1, OutByte2; // Output byte buffers

 // low 4 bits
 OutByte1 = OneByte & 0x0F;
 if (OutByte1 < 10) // 0-9
  OutByte1 += '0';
 else // A-F
  OutByte1 = OutByte1 - 10 + 'A';

 // high 4 bits
 OutByte2 = OneByte / 0x10;
 if (OutByte2 < 10) // 0-9
  OutByte2 += '0';
 else // A-F
  OutByte2 = OutByte2 - 10 + 'A';

 return (MAKEUINT(OutByte2, OutByte1)); // 2 ASCII Unit
}
///////////////////////////////////////
//  Send One HEX to UART
//   IN: OneHEX = one byte
///////////////////////////////////////
void putHEX(BYTE OneHEX)
{
 UINT ASCBff; // ASCII Buffer

 ASCBff = HEX2ASCII(OneHEX);
 putchar((BYTE)(ASCBff / 0x100)); // High Byte
 putchar((BYTE)ASCBff); // Low Byte
}
//===================================================================
//	F: UART_WriteData()
//===================================================================
void UART_WriteDataToSerial1(BYTE Data)
{
	//EA = 0; // disable all interrupt
	SBUF1 = Data;
	
	while (TI_1 == 0);
	TI_1 = 0;
	//EA = 1; // release EA bit
}
//===================================================================
//	F: UART_WriteData()
//===================================================================
void UART_WriteDataToSerial0(BYTE Data)
{
//	EA = 0; // disable all interrupt
	SBUF = Data;
	
	while (TI == 0);
	TI = 0;
//	EA = 1; // release EA bit
}