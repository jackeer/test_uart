

#include "config.h"

#include "stdio.h"
#include "main.h"
#include "Monitor.h"

	/*
	#define	BUF_MAX 	20
	static	DATA BYTE	RS_buf[BUF_MAX];
	static	DATA BYTE   RS_in, RS_out;
	bit		RS_Xbusy=0;			// bit RS_Xbusy=0;
	*/

	/*
	* @brief This function initialize UART @4800 baud for 12MHz XTAL.
	*
	*
	* @warning 12MHz XTAL required
	*
	* @param void
	*
	* @return void
	*
	*/
void io_init(void)
{
	SCON = 0x50;				// Set to enable serial reception. 8-bit UART Variable
	TMOD = TMOD | 0x20;			// Timer 1 Mode 2: 8-bit auto-reload Timer/Counter (TL1).(1)Reloaded from TH1 at overflow.
	TH1 = 0xFA;					// 9600 bauds at 11.0592 MHz
	TL1 = TH1; 
	PCON = PCON | 0X80;			// SMOD0 Set to select double baud rate in mode 1, 2 or 3.
	TCON |= 0x40;				// Set to turn on Timer/Counter 1.   
	TI=1;						// Set by hardware at the end of the 8th bit time in mode 0 or at the beginning of the 
								// stop bit in the other modes.
}

void main (void) large
{
	io_init();				// Initialize UART

	printf("\n ATMEL AT89S51 ");			// Welcome message 
	printf("\n   Monitor \n\n");

	ES=1;			// Enable interrupts

	while (1)
		{
		/*
		if(RS_buf[1])
			{
			printf("\n RS_buf = ",RS_buf);
			RS_buf[1] = 0;
			}
		*/
		#ifdef DBG_monitor
		while( RS_ready() )
			{
			Monitor();				// for new monitor functions?		
			}
		#endif	// end DBG_monitor
		}
}


