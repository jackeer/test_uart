
#include "config.h"

#ifdef DBG_monitor

#include "STDIO.H"
#include "STRING.H"
#include "main.h"
#include "monitor.h"


bit f_access;
extern bit f_DBG_CYC;


//=============================================================================
//			clean screen
//=============================================================================
void clean_screen(void) large
{
	Printf("\r\n===============================================================");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
	Printf("\r\n");
}

//=============================================================================
//			Help Message
//=============================================================================
void MonHelp(void) large
{
	Printf("\r\n====================================================================");
	Printf("\r\n>>>              Welcome to Xmode Monitor  Rev 1.00              <<<");
	Printf("\r\n====================================================================");
	// Printf("\r\n   R ii             ; Read data");
	// Printf("\r\n   W ii dd          ; Write data");
	// Printf("\r\n   D [ii] [cc]      ; Dump");
	// Printf("\r\n   C aa             ; Change I2C address");
	// Printf("\r\n   M ?              ; Current Input");
	// Printf("\r\n   M dd             ; Change Input");

	Printf("\r\n   clean               ; clean Screan                       cls ");
	Printf("\r\n   access              ; Program Access OFF/ON              acc ");
	// Printf("\r\n   display             ; Display CAN ID & DATA              dis ");
	Printf("\r\n   help                ; Show HELP                          ? & h ");
	// Printf("\r\n   incpage             ; Inc CAN Channel                    ip ");
	// Printf("\r\n   findchannel         ; Show CAN CH. Info [0 - 15]         ff  ");
	// Printf("\r\n   asc2bin [00-ff]     ; Type asc2bin Then Type Num.        a2b ");
	// Printf("\r\n   reset               ; Software reset                     rst ");
	// Printf("\r\n   setchannel          ; Set Channel                        setch ");
	// Printf("\r\n   disnodet            ; Dis No Detect Show                 dndt ");

	// Printf("\r\n   canon               ; Enable CAN                         canon ");
	// Printf("\r\n   canoff              ; Disable CAN                        canof ");
	// Printf("\r\n   cantrigger          ; Show CAN Trigger Status            ctrg ");
	// Printf("\r\n   cycstatus           ; Show Cycle Status                  cycst ");

	// Printf("\r\n   AutoDetect [0,1] ; PC Automode OFF/ON");
	// Printf("\r\n   PCAuto		    ; RUN PC Auto Adjust");
	// Printf("\r\n   Debug [0..255]   ; Debuging display level");
	// Printf("\r\n   Echo On/Off      ; Terminal Echoing On/Off");
	// Printf("\r\n   Delta            ; Init DeltaRGB Panel");
	// Printf("\r\n   Delta w ii dh dl; SPI Write to DeltaRGB Panel");
	Printf("\r\n");
	Printf("\r\n====================================================================");
	Printf("\r\n");
}

#if 0
BYTE Asc1Bin(BYTE asc) large
{
	if(asc>='0' && asc <='9') return (asc - '0');
	if(asc>='a' && asc <='f') return (asc - 'a' + 0x0a);
	if(asc>='A' && asc <='F') return (asc - 'A' + 0x0a);

	return asc;
}

void Asc2Bin(BYTE *s, BYTE *bin) large
{
	BYTE *ptr_tmp;

	ptr_tmp = bin;
	while(*s != '\0' && *s !=' ' && *s !='\n') 
		{
		*bin = Asc1Bin(*s);
		printf("str... %s01\n", s);
		printf("bin... %x01\n", bin);
		s++;
		bin++;
		}

	// printf(" == %x == \n", ptr_tmp);
	*bin='\n';
}
#endif

//=============================================================================
//			For Get UART RX line String
//=============================================================================
int getline(char s[], int N) large
{
    int c, i;

    for (i=0; i<N-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

//=============================================================================
//		Serial RX Check 												   
//=============================================================================
BYTE RS_ready(void) large
{
	return RI;		// Set by hardware at the end of the 8th bit time in mode 0
}

void Monitor(void) large
{
    BYTE ch_buf[STR_MAX]=0, ch_data[STR_MAX]=0;
    int num;

    // while ((n = getline(ch_buf, 8)) > 0)
    printf("\rPrompt:>");
	num = getline(ch_buf, STR_MAX);
        printf("\r%d:%s\n", (WORD)num-1, ch_buf);

	// printf("strncmp( ch_buf, auto,4 )) = %d\n",(WORD)(strncmp( ch_buf, "auto",4 )));
	
	if( !strncmp( ch_buf, "clean",5) || !strncmp( ch_buf, "cls",3 ) ) 
		clean_screen();
	else if( !strncmp( ch_buf, "access",6) || !strncmp( ch_buf, "acc",3 ) ) 
		{
		if(f_access)
			{
			f_access=0;
			printf("\rAccess = Enable LOW \n");
			}
		else
			{
			f_access=1;
			printf("\rAccess = Disable HI \n");
			}
		}
	// else if( !strncmp( ch_buf, "display",7) || !strncmp( ch_buf, "dis",3 ) ) 
		// {
		// can_detect();
		// display();
		// }
	// else if( !strncmp( ch_buf, "asc2bin",7) || !strncmp( ch_buf, "a2b",3 ) ) 
		// {
		// printf("\rasc2bin Please Type Num.\n");
		// num = getline(ch_buf, STR_MAX);
		// Asc2Bin(ch_buf, ch_data);
		// printf("\rInput Char Num = %x\n", ch_data);
		// }
	// else if( !strncmp( ch_buf, "reset",5 ) || !strncmp( ch_buf, "rst",3 )) 
		// {
		// Long_call(0);
		// printf("\rReset... \n");
		// }
	// else if( !strncmp( ch_buf, "setchannel",10 ) || !strncmp( ch_buf, "setch",5 )) 
		// {
		// printf("\rasc2bin Please Type Num.\n");
		// num = getline(ch_buf, STR_MAX);
		// CAN_SET_CHANNEL(Asc2Bin(ch_buf));
		// printf("\rSet Channel = %02x\n",(WORD)(Asc2Bin(ch_buf)));
		// }
	//------------------------- Help -------------------------------
	else if( !strncmp( ch_buf, "help",4 ) || !strncmp( ch_buf, "?",1 ) || !strncmp( ch_buf, "h",1 )) 
		{
		MonHelp();
		}
	//---------------------- Test Function -------------------------
/*
	else if( !strncmp( ch_buf, "findchannel",11) || !strncmp( ch_buf, "ff",2 )) 
		{
		printf("\rPage = %2x\n",(WORD)(CAN_GET_CHANNEL & 0x03));
		printf("\rChannel = %2x\n",(WORD)(FindFirstChIt() & 0x0f));
		// printf("\rChannel = %2x\n",(WORD)(CANSIT2 & 0x0f));
		printf("\rCAN Enable = %02x\n",(WORD)(CANEN2 & 0x0f));
		}
	else if( !strncmp( ch_buf, "incpage",7 ) || !strncmp( ch_buf, "ip",2 )) 
		{
		num = (BYTE)((CAN_GET_CHANNEL & 0x03)+1);
		if (num > 3)
			num=0;
		CAN_SET_CHANNEL(num);
		CAN_CHANNEL_IT_ENABLE(num);
		can_detect();
		display();
		// printf("\rSet Channel = %02x\n",(WORD)(Asc2Bin(ch_buf)));
		}
	else if( !strncmp( ch_buf, "disnodet",8 ) || !strncmp( ch_buf, "dndt",4 )) 
		{
		DIS_NODET;
		dputs("\rCAN NO Detect... \n");
		}
	else if( !strncmp( ch_buf, "canon",5 ) || !strncmp( ch_buf, "canon",5 )) 
		{
		CAN_CONTROLLER_ENABLE;
		dputs("\rCAN_CONTROLLER_ENABLE \n");
		}
	else if( !strncmp( ch_buf, "canoff",6 ) || !strncmp( ch_buf, "canof",5 ))
		{
		CAN_CONTROLLER_DISABLE;
		dputs("\rCAN_CONTROLLER_DISABLE \n");
		}
	else if( !strncmp( ch_buf, "cantrigger",10 ) || !strncmp( ch_buf, "ctrg",4 )) 
		{
		dputs("\rSTD_System		0 \n");
		dputs("\rCAN_System		1 \n");
		printf("\rCANSTD_SW = %x \n",(WORD)CANSTD_SW);
		printf("\rRadar1_Type = %x \n",(WORD)Radar1_Type);
		printf("\rRadar2_Type = %x \n",(WORD)Radar2_Type);
		printf("\rRadarTrigger = %x \n",(WORD)RadarTrigger);
		}
	else if( !strncmp( ch_buf, "cycstatus",10 ) || !strncmp( ch_buf, "cycst",5 ))
		{
		printf("\rCySw2 = %x \n",(WORD)CySw2);
		printf("\rCySw3 = %x \n",(WORD)CySw3);
		if(f_DBG_CYC)
			{
			f_DBG_CYC=0;
			dputs("\rf_DBG_CYC = Low \n");
			}
		else
			{
			f_DBG_CYC=1;
			dputs("\rf_DBG_CYC = Hi \n");
			}
		}
*/
	

	//---------------------- End -----------------------------------
	else
		{
		printf("\rType null \n");
		}

}

#endif // end DBG_monitor


