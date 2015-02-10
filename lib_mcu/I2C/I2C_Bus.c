/*C*****************************************************************************
* FILE_NAME         : I2C_Bus.c                                             
*----------------------------------------------------------------------------
* FILE_CREATED_BY   : Peter chung
* FILE_CREATION_DATE: 07/02/2008                                             
*----------------------------------------------------------------------------
* FILE_PURPOSE: provide I2C interface controller   
*
******************************************************************************/

/*_____ I N C L U D E - F I L E S ____________________________________________*/


#include "config.h"
#include "I2C_Bus.h"
#include <intrins.h>



/*_____ G L O B A L S ________________________________________________________*/

/* variables used by I2C command */
typedef union
{				
	Uchar	valB[2];		//B[ ]={0xaa,0xbb}
	Uint16	valW;		//W=0xaabb
	
}W_TEMP;

W_TEMP I2C_Send_Address;



/*_____ P R I V A T E - F U N C T I O N S - D E C L A R A T I O N ____________*/


/*_____ L O C A L S __________________________________________________________*/


/*_____ P U B L I C - F U N C T I O N S ______________________________________*/


/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/

//--------------------------------------------------------
void Delay_i2c(void)
{
}
//--------------------------------------------------------
void Delay_Ms(Uint16 ms)
{
	Uint16 I;
	for (;ms > 0;ms--)
	{
		for (I=0; I < MS_DLY; I++)
		{
			_nop_();
			_nop_();
		}
	}

}
//--------------------------------------------------------
void Delay_Sec(Uchar sec)
{
	for (;sec > 0;sec--)
		Delay_Ms(2000);
	
}
//--------------------------------------------------------
void Delay_Us(Uint16 us)
{

	for (;us > 0;us--)
	{
		_nop_();
		_nop_();
	}    

}
//.........................................................................................................................................
void Initial_I2C(void)
{
	SDA=1;
	SDA=0;
	SCL=1;
	while(!SCL);
	
	SDA=1;
}
//.........................................................................................................................................
void START(void)
{
   SDA=1;
   SCL=1;   Delay_i2c();
   SDA=0;   Delay_i2c();
   SCL=0;   /*delay_i2c();*/
}
//.........................................................................................................................................
void STOP(void)
{
   SDA=0;
   SCL=1;   Delay_i2c();
   SDA=1;   /*Delay_i2c();*/
}
//.........................................................................................................................................
void Tran_data(Uchar sendData)
{
   char i;

   for (i=0;i<8;i++)
   {
      if ((sendData&0x80)==0)        
	  	SDA=0;
      else                       
	  	SDA=1;
      Delay_i2c();

      SCL=1; Delay_i2c();
      SCL=0; Delay_i2c();

      sendData=sendData<<1;
   }

   SDA=1;  Delay_i2c();
   SCL=1;  Delay_i2c();
   //   while (SDA==1) ;  
   SCL=0; Delay_i2c();
   SDA=0; Delay_i2c();
}
//.........................................................................................................................................
Uchar I2C_ReadOneByte(bit noack)
{
   unsigned get;
   char i;

   get=0;
   SDA=1;
   i=0;

   do
   {
      SCL=1; Delay_i2c();
      get=get<<1;
      if (SDA==1)  get=get|1;

      SCL=0; Delay_i2c();
      i++;
   } while(i!=8);

   if(noack)	
   	SDA=1;
   else	
   	SDA=0;
   Delay_i2c();
   
   SCL=1; Delay_i2c();
   SCL=0;

   return(get);
}
//.........................................................................................................................................
void I2CByteWrite(Uchar id, Uchar addr, Uchar I2CData)
{
   START();
   Tran_data(id); 
   Tran_data(addr);
   Tran_data(I2CData);
   STOP();   
}
//.........................................................................................................................................
Uchar I2CByteRead(Uchar id, Uint16 addr)
{
  Uchar I2C_ReadData;
 
  START();

  Tran_data(id);
  Tran_data(addr);
  SDA=1;
  SCL=1;  Delay_i2c();

  START();
  
  Tran_data(id | 0x01); 
 
  I2C_ReadData = I2C_ReadOneByte(1);
  
  STOP();
  
  return(I2C_ReadData);
}
//.........................................................................................................................................
void I2CSeqRead(Uchar id,Uchar addr,Uchar *databuf,Uint16 number)
{
  Uchar BitLoop;
  START();

  Tran_data(id);
  Tran_data(addr);
  SDA=1;
  SCL=1;  Delay_i2c();

  START();
  Tran_data(id | 0x01);  /*Delay_i2c();*/
  
  for(BitLoop = 0; BitLoop < number-1; BitLoop++)
  { 
	databuf[BitLoop] = I2C_ReadOneByte(0);
  }
  databuf[BitLoop] = I2C_ReadOneByte(1);

  STOP();
}

/****************************************************************************
* Writes value to a Register
****************************************************************************/

void wrRegUART(Uchar reg, Uchar uc) 
{
	I2CByteWrite(I2C_SPI_UART_ADR_W,reg<<3,uc);
}

/****************************************************************************
* Reads contents of specified Register
****************************************************************************/
Uchar rdRegUART(Uchar reg)
{
  Uchar I2C_ReadData;
 
  START();

  Tran_data(I2C_SPI_UART_ADR_W);
  Tran_data(reg<<3);
  SDA=1;
  SCL=1;  Delay_i2c();

  START();
  
  Tran_data(I2C_SPI_UART_ADR_W|0x01); 
 
  I2C_ReadData = I2C_ReadOneByte(1);
  
  STOP();
  
  return(I2C_ReadData);
  
}

//****************************************************************************
// Initialization Functions at power up, Reset or program change      
//****************************************************************************

void i2c_uart_init(void) {
	wrRegUART(LCR, DLAB);			// 0x80 to access program baud rate
	//wrRegUART(DLL, LOW(UART_BAUD_RATE));	// program baud rate low byte
	//wrRegUART(DLM, HIGH(UART_BAUD_RATE));			// program baud rate high byte
	
	wrRegUART(DLL, 0x20);			// program baud rate low byte
	wrRegUART(DLM, 0x01);			// program baud rate high byte
	
	wrRegUART(LCR, 0X03); 			// access EFR
	wrRegUART(SPR, 0x55);  			// write 0x55 to scratch pad register
	wrRegUART(IER, 0x01);	 	  	// enable receive interrupt
	wrRegUART(FCR, 0x06); 		 	// reset TXFIFO, reset RXFIFO, non FIFO mode
	wrRegUART(FCR, 0x01); 			// enable FIFO mode
	
}

