/*H***************************************************************************
* FILE_NAME:    can_lib.
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : J.S. BERTHY                                           
* FILE_CREATION_DATE: 28/09/99                                              
*----------------------------------------------------------------------------
* FILE_PURPOSE: This file contains all prototypes and macros exported.      
******************************************************************************/

#ifndef 	_I2C_Bus_H_
#define 	_I2C_Bus_H_

#define	MS_DLY		99


//=================================================================
/* baud		Value		(X1=1.8432Mhz)
 * 115200	0x01
 *  57600	0x02
 *  38400	0x03
 *  19200	0x06
 *   9600	0x0c
 *   4800	0x18
 *   2400	0x30
 *   1200	0x60
 *    600	0xc0
 Micro baud rate is set in UART.C */

//#define	UART_BAUD_RATE	0x0c	// 0xC0=600, 0x0C=9600, 0x01=115.2K with X1=1.8432Mhz
#define	UART_BAUD_RATE	288	//  0x60=9.6k, 0x30=19.2k,0x10=56k,0x08=115.2K with X1=14.456Mhz





/***********************************************************************/
#define THR		 	0x00		// transmit FIFO, write only
#define RHR			0x00		// receive FIFO, read oly
#define IER			0x01		// interrup enable reg., R/W
#define FCR			0x02		// FIFO control, write only
#define IIR			0x02		// interrupt status, read only
#define LCR			0x03		// line control, R/W
#define MCR			0x04		// modem control, R/W
#define LSR			0x05		// Line status, R/W
#define MSR			0x06		// Modem status, R/W
#define SPR			0x07		// scratch pad, R/W
#define TXFIFO		0x08		// TX FIFO, R
#define RXFIFO		0x09		// RX FIFO, R
#define DLAB			0x80		// Way to swap mem banks

#define IODIR		0x0A		// IO Direction Control R/W
#define IOSTATE		0x0B		// IO State R/W
#define IOINTMSK	0x0C		// IO Interrupt Mask R/W
//#define Reserved	0x0D	// Reserved
#define IOCTRL		0x0E		// IO Control R/W
#define EFCR			0x0F		//  Enhancede Function Reg R/W

/* special registers, LCR.7 must be set to 1 to R/W to these registers */
#define DLL			0x00		// baud rate divisor, LSB, R/W
#define DLM			0x01		// baud rate divisor, MSR, R/W
#define EFR			0x02		// enhanced register, R/W
#define XON1			0x04		// flow control
#define XON2			0x05		// flow control
#define XOFF1		0x06		// flow control
#define XOFF2		0x07		// flow control
/***********************************************************************/


void Delay_i2c(void);
void Delay_Ms(Uint16 ms);
void Delay_Us(Uint16 us);
void Delay_Sec(Uchar sec);
void Initial_I2C();
void START(void);
void STOP(void);
void Tran_data(Uchar sendData);
Uchar I2C_ReadOneByte(bit noack);
void I2CByteWrite(Uchar id, Uchar addr, Uchar I2CData);
Uchar I2CByteRead(Uchar id, Uint16 addr);
void I2CSeqRead(Uchar id,Uchar addr,Uchar *databuf,Uint16 number);


void wrRegUART(Uchar reg, Uchar uc);
Uchar rdRegUART(Uchar reg);
void i2c_uart_init(void);


#endif /* _I2C_Bus_H_ */

