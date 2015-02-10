//#include "MAIN.h"


/*****************************/
void DelayX1ms(unsigned int count)	//crystal=12Mhz
{
    unsigned int i,j;			//variable:declare Word 
     
    for(i=0; i<count; i++)
       for(j=0; j<120; j++)
          ;
}

void DelayX1ms1(unsigned int count)
{
    unsigned int j;
     
    while (count-- != 0)
       for(j=0; j<72; j++)
          ;
}

void DelayX1ms2(unsigned char count)
{
    unsigned char i,j,k;			//declare Byte,assembly different
     
    for(i=0; i<count; i++)
       for(j=0; j<40; j++)
           for(k=0; k<120; k++)
              ;
}


void DelayX10ms(unsigned int count)
{
    unsigned int j,k;  
     
    while (count-- != 0)
       for(j=0; j<10; j++)
          for(k=0; k<72; k++)
             ;
}

