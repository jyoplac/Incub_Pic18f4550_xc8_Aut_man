
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "adc.h"
#include "config.h"
#include "lcd.h"
#include "teclado.h"

void main(void) {
    
    char Temperatura[10];
    float celsius;
    OSCCON = 0x72;
    LCD_Init();
    ADC_Init();
    
    while (1){
        LCD_String_xy(1,0,"TEMPERATURA");
        celsius = (ADC_Read(1)*4.88);
        celsius =(celsius/10.00);
        sprintf(Temperatura,"%d C ",(int)celsius);
        LCD_String_xy(2,0,Temperatura);           
        MSdelay(10);
        memset(Temperatura,0,10);
    }
    
}
