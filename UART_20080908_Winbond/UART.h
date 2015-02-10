#ifndef _TP6822UART_H
#define _TP6822UART_H

#ifdef __TP6822UART__
#define	AUTOEXT
#else
#define	AUTOEXT extern
#endif

AUTOEXT void putchar(BYTE OneChar) ;

//===================================================================
//	TP6761 check ok
//	F: InitUART()
//===================================================================
AUTOEXT void InitUART(void)	;


///////////////////////////////////////
//  put string to UART
//
//   IN: pString = string address
///////////////////////////////////////
AUTOEXT void printf(BYTE code *pString);

//================================= @4.UART Common Subroutines =================================
//////////////////////////////////////////////////////////////
//  Convert HEX value TO ASCII
//    IN : one byte
//    OUT: two bytes (low ASCII code, high ASCII code)
//////////////////////////////////////////////////////////////
AUTOEXT UINT HEX2ASCII(BYTE OneByte);

///////////////////////////////////////
//  Send One HEX to UART
//   IN: OneHEX = one byte
///////////////////////////////////////
AUTOEXT void putHEX(BYTE OneHEX) ;

#endif