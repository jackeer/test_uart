#include "Main.h"

void Init_UART()
{
	SCON0=0x50;	//設定UART工作在MODE1 REN=1
	TMOD=0x20;	//設定TIMER1在MODE2 
	TH1=0xFD;	//設鮑率為9600, OSC=11.0592MHz
	TR1=1;		//啟動TIMER1
}

static char READ(void)	//*READ 為靜態字元函數
{
	while(RI!=0)	//偵測RI=1否
	RI=0;			//是則表是SBUF接收完成
	return(SBUF);	//返回主程式並將SBUF的內容送回
}																			 