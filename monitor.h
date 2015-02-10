/* monitor.h */

#ifndef __MONITOR_H__
#define __MONITOR_H__

#define Printf printf
#define stricmp strcmp

#define STR_MAX		22

extern void clean_screen(void) large;
extern void MonHelp(void) large;
extern BYTE Asc1Bin(BYTE asc) large;
extern void Asc2Bin(BYTE *s, BYTE *bin) large;
extern int getline(char* , int ) large;
extern BYTE RS_ready(void) large;
extern void Monitor(void) large;

extern bit f_access;

#endif

