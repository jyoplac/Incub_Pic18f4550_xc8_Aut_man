
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adc.h"
#include "config.h"
#include "lcd.h"
#include "teclado.h"

void dimmer(int brillo); 
unsigned char seg = 0;

int main() {
    
    char tecla;
    int modo; //modo=1 automatico ; modo =2 manual
    char sp[2];
    unsigned int insp=0;
    unsigned long SetPoint;
    unsigned int error=0;
    unsigned int Tem_Act=0;
    int tiempo=0;
    char Temperatura[10];
    char Potencio[10];
    float potenciometro;
    float celsius;
    float pot;
    
    TRISC1 = 1;//ZEROS 
    TRISC0 = 0;//TRIGGER
    LATC0 = 0;
    
    OSCCON = 0x72;
    RBPU = 0;
    LCD_Init();
    ADC_Init();
    
    
    LCD_String_xy(1,0,"A=Automatico");
    LCD_String_xy(2,0,"B=Manual");
    MSdelay(1000);
    
    LCD_Clear();
    LCD_Command(0x80);
    
    while(1){
        tecla = keyfind();
        MSdelay(20);
        if(tecla!=' '){
            if (tecla == 'A'){
                LCD_String_xy(1,0,"A=Automatico");
                modo = 1;
                MSdelay(1000);
                break;
            }
            else if(tecla == 'B'){
                LCD_String_xy(1,0,"B=Manual");
                modo = 2;
                MSdelay(1000);
                break;
            }            
        }
        
    }
    tecla = ' ';
    LCD_Clear();
    LCD_Command(0x80);
    
    while (1){
              
        if(modo == 1){ // automatico
            LCD_String_xy(1,0,"SETPOINT ");
            while(1){
                tecla = keyfind();
                
                
                if(tecla!=' '){
                    if(tecla!='A' && tecla!='B' && tecla!='C' && tecla!='D' && tecla!='E'){
                        sp[insp]=tecla;
                        insp++;
                    }
                    if(tecla=='E'){
                        SetPoint = atol(sp);
                        while(1){
                            
                            LCD_String_xy(2,0,"TEMPERATURA");
                            celsius = (ADC_Read(0)*4.887);
                            celsius =(celsius/10.00);
                            Tem_Act = (int)celsius;
                            sprintf(Temperatura,"%d C ",(int)celsius);
                            LCD_String_xy(2,12,Temperatura);           
                            
                            error = (SetPoint - Tem_Act) * 1;
                            
                            dimmer(8-error);
                            
                            memset(Temperatura,0,10);
                            
                        }
                    }
                }   
            }  
        }
        
        
        
        
        else if(modo == 2){ //manual
            while(1){
                LCD_String_xy(1,0,"TEMPERATURA");
                celsius = (ADC_Read(0)*4.887);
                celsius =(celsius/10.00);
                Tem_Act = (int)celsius;
                sprintf(Temperatura,"%d C ",(int)celsius);
                LCD_String_xy(1,12,Temperatura);
                MSdelay(1);
                pot = (ADC_Read(1)/124);
                pot = (int)pot;
                potenciometro = pot * 100 / 8;
                LCD_String_xy(2,0,"POT. DIMMER");
                sprintf(Potencio,"%d ",(int)potenciometro);
                LCD_String_xy(2,13,Potencio);
                
                dimmer(pot);
                            
                memset(Temperatura,0,10);
            }
        }
        
    }
    
}

void dimmer(int brillo){//7min max 1    8 cero
    if (brillo >=8) brillo=8;
    if (brillo <=0) brillo=0;
    
    switch(brillo){
        case 0 :
            MSdelay(0);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 1 :
            MSdelay(1);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 2 :
            MSdelay(2);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 3 :
            MSdelay(3);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 4 :
            MSdelay(4);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 5 :
            MSdelay(5);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 6 :
            MSdelay(6);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 7 :
            MSdelay(7);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;
        case 8 :
            MSdelay(8);
            LATC0 = 1;
            while(RC1 == 0);
            LATC0 = 0;
            break;                    
    }  
    
} 
