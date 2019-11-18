
#ifndef TECLADO_H
#define	TECLADO_H

#include <xc.h> 
#include "lcd.h"


#define write_port LATB             /* latch register to write data on port */
#define read_port PORTB             /* PORT register to read data of port */
#define Direction_Port TRISB
unsigned char col_loc,rowloc,temp_col,lim;

unsigned char keypad[4][4]= {'1','2','3','+',
                             '4','5','6','-',
                             '7','8','9','*',
                             ' ','0','=','/'};
unsigned char keyfind();            /* function to find pressed key*/

#endif	

