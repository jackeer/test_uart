#include <intrins.h>
#include "def.h"
#include "mpu.h"
//#include	"W77E516.h"
extern void printf(BYTE code *pString);
extern void putHEX(BYTE OneHEX);
BYTE READ(void);  		//PC 	   ==>W77E516
void SEND(BYTE c);		 //W77E516 ==>TP2852
BYTE data _data0;
BYTE data _data1;
bdata bit ReceiveFlag0;
bdata bit ReceiveFlag1;
//===================================================================
//	F: UART_WriteData()
//===================================================================
extern void UART_WriteDataToSerial1(BYTE Data);
extern void UART_WriteDataToSerial0(BYTE Data);
extern void InitUART(void);
extern void DelayX1ms(unsigned int count);
extern void DelayX10ms(unsigned int count);
//==============================
//	
//	ISP_Trigger()
//==============================
void ISP_Trigger()
{
	T_P2_6 = 0;
	T_P2_7 = 0;
	DelayX10ms(6);
	Reset = 1;
	DelayX10ms(16);
	Reset = 0;
	T_P2_6 = 0;
	T_P2_7 = 0;
	DelayX10ms(16);
	T_P2_6 = 1;
	T_P2_7 = 1;	

}      

void InitVar()
{
	Reset = 0;
   	ReceiveFlag0 = FALSE;
	ReceiveFlag1 = FALSE;
}
void main(void)
{
	 InitVar();
	InitUART();
	//printf("\r\n<<InitUart>>");
	ISP_Trigger();
	//_data0 = 0xFF;
//	P1= 0xFF;
	while(1)
	{
#if 0 
	 	if(ReceiveFlag1)
	  {

	  	 	UART_WriteDataToSerial0(_data1);
			//SBUF = _data1;
			ReceiveFlag1 = FALSE;
	  }
	  if(ReceiveFlag0)
	  {
	
	  		UART_WriteDataToSerial1(_data0);
			//SBUF1 = _data0;
			ReceiveFlag0 = FALSE;
	  }
#endif
			//P1= ~ P1;
	//	P1=~READ();
	//	SEND(P1);
	}
}
#if	1
//////////////////////////////////////
// UART Interrupt
///////////////////////////////////////
//===================================================================
//	F: UART_S()
//===================================================================  
void UART_S0(void) interrupt 4
{
//	BYTE temp; // loop index


	EA = 0; // disable all interrupt
    //P1 = 0x00;
	
	if (_testbit_(TI) == 0) // check if translate command
		{
			_data0 = SBUF; // recieve UAR
			RI = 0; // clear UART recieve interrupt
			
			UART_WriteDataToSerial1(_data0);
		
		} // if TI
		
	EA = 1; // release EA bit
}
//////////////////////////////////////
// UART Interrupt
///////////////////////////////////////
//===================================================================
//	F: UART_S()
//===================================================================  
void UART_S1(void) interrupt 7
{
//	BYTE temp; // loop index


	EA = 0; // disable all interrupt
    //P1 = 0x00;
	
	if (_testbit_(TI_1) == 0) // check if translate command
		{
			_data1 = SBUF1; // recieve UAR
			RI_1 = 0; // clear UART recieve interrupt
		
		   UART_WriteDataToSerial0(_data1);
		  
		
		} // if TI
	  
	EA = 1; // release EA bit
}
#endif
