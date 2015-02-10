/*H**************************************************************************
* NAME:         config.h         
*****************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/*------ Include of file register */
#include "lib_mcu/compiler.h"
#include "AT89X51.H"
// #include "REG51.H"

/*------ FOSC declaration in kHz */
#define FOSC 12000


/*------- jackeer define --------*/

#define debug
#ifdef debug
#define DBG_monitor			// for mon command UART & PC  ctrl

#endif




#ifdef debug
#define dprintf printf
#define dputs puts

// #define dputchar putchar
#else
#define dprintf(a,b)
#define dputs(a)

// #define dputchar(a)
#endif

#endif /* _CONFIG_H_ */
