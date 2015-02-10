/* main.h */

#ifndef __MAIN_H__
#define __MAIN_H__

#define ID_STATUS00			0x0000
#define ID_STATUS01			0x0001
#define ID_STATUS02			0x0002
#define ID_STATUS03			0x0004
#define ID_STATUS04			0x0008
#define ID_STATUS05			0x0010
#define ID_STATUS06			0x0020
#define ID_STATUS07			0x0040
#define ID_STATUS08			0x0080
#define ID_STATUS09			0x0100
#define ID_STATUS10			0x0200
#define ID_STATUS11			0x0400
#define ID_STATUS12			0x0800
#define ID_STATUS13			0x1000
#define ID_STATUS14			0x2000
#define ID_STATUS15			0x4000
#define ID_STAT_RES			0x8000

#define CAN_ID_ATATUS_MAX	16
#define CAN_ID_USE_UNIT		3	// Use 3 Radar

#define CAN_DetTime			12
#define CAN_DetSTATUS		((CAN_DetTime*2)+1)

void can_init(void);
void io_init(void);
void var_init(void);
extern void display(void);
extern void can_fct_it_txok (void);
extern void can_fct_it_rxok (void);
void can_it_routine(void);
extern void can_detect(void);


#endif

