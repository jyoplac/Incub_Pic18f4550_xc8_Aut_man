
// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i2c_lcd.h"
#include "teclado.h"
#define _XTAL_FREQ 20000000

#define zeros PORTBbits.RB2
#define trigger LATBbits.LATB3
#define trigger_tris TRISBbits.RB3

int i;
int v=2130;//min brillo 2160
char x = 0, text[4];

//bienven contra
void bienv_cont (void);
unsigned char contra = ' ';
char contras[4];
long contrasena;
int incon = 0;
int acceso = 2;
////////////////


//modo
void modo (void);
unsigned char tecla;
int modo2 = 0;
////////////////

//automatico
void automatic (void);
char sp[2];
unsigned int insp=0;
unsigned long SetPoint;
int Tem_Act = 0;
//float lecturas[10];
//int lec=0;
/////////////////////


////////pid
int pid(int setpoint,float tem_act);
int kp=2;
int ki=0;
int kd=0;
float P=0;
float I=0;
float D=0;
int error_past=0;
int error=0;
int error_total=0;
/////////


///lm35
float celsius;
char Temperatura[10];
/////

// manual
void manual (void);
char Potencio[10];
float potenciometro;    
float pot;
//////////////////


void main(void) {
    /////////////////////////////////////////////////////
    //////configuracion dimmer
    trigger_tris = 0 ;
    trigger = 0;
    
    INTEDG2 = 1;
    INT2IP = 1;
    INT2IE = 0;
    IPEN = 0;
    GIE = 1;
    
    ////////////////////////////////////////////////////////////
    /////configracion adc
    TRISA = 0x03;
    ADCON1 = 0x0D;
    ADCON2 = 0x9D;
    //int valor=0;
    
    
    ///////////////////////////////////////////////////////
    ////configuracion lcd i2c
    
    I2C_Init(100000);   // initialize I2C bus with clock frequency of 100kHz
    LCD_Begin(0x4E);    // Initialize LCD module with I2C address = 0x4E
 
    bienv_cont();
    modo();
    
    
    
    while(1);
       
    return;
}

void __interrupt (high_priority) INT2ISR (void) {
           
    for(i=0;i<v;i++){
        __delay_us(8);
    }
    trigger = 1;
    __delay_us(200);
    trigger = 0;
    INT2IF = 0;
    
}

void bienv_cont(void){
    LCD_Goto(1,1);
    LCD_Print("Bienvenido");  
    __delay_ms(2000);
    LCD_Cmd(LCD_CLEAR);
    
    while(1){
        LCD_Goto(1,1);
        LCD_Print("Ingrese Contra.");
        LCD_Cmd(LCD_SECOND_ROW);
		
		
		//primera cifra
        contra = keyfind();
        __delay_ms(20);
        
        if (contra != ' '){
            if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){
             
   
                if (contra == '5'){
                    incon++;
                    LCD_Goto(incon,2);
                    LCD_Print("*");
                    LCD_Goto(1,2);
                    LCD_Print("*");
                    
                    ///segunda cifra
                    while(1){
                        contra = keyfind();
                        __delay_ms(20);

                        if (contra != ' '){
                            if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){
                                
                                
                                
                                if (contra == '5'){
                                    incon++;
                                    LCD_Goto(incon,2);
                                    LCD_Print("*");
                                    LCD_Goto(1,2);
                                    LCD_Print("*");
                                    
                                    /////tercera cifra
									
									
									while(1){
										contra = keyfind();
										__delay_ms(20);

										if (contra != ' '){
											if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){

												if (contra == '5'){
													incon++;
													LCD_Goto(incon,2);
													LCD_Print("*");
													LCD_Goto(2,2);
													LCD_Print("*");
                                    
													/////cuarta cifra
													
													while(1){
														contra = keyfind();
														__delay_ms(20);

														if (contra != ' '){
															if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){
																if (contra == '5'){
																	incon++;
																	LCD_Goto(incon,2);
																	LCD_Print("*");
																	LCD_Goto(3,2);
																	LCD_Print("*");
																	acceso = 1;
																	goto acces;
																}
                                
																else{
																	goto cuarta_mal;
                                    
																}
                                
															}
														}
													}

													/////////

												}
												else{
													goto tercer_mal;
                                    
												}
                                
                                
                                
											}
										}
									}

									//////////fin tercera cifra
                                } 
                                else{
									goto segunda_mal;    
                                }    
                            }
                        }
                    }
					///////////////////////////fin segunda cifra
                    
                }
               
			   
                else{
                    incon++;
                    LCD_Goto(incon,2);
                    LCD_Print("*");
                    LCD_Goto(1,2);
                    LCD_Print("*");
                    
					
					///segunda cifra
					while(1){
						contra = keyfind();
						__delay_ms(20);
						if (contra != ' '){
							if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){
								segunda_mal:;
                                incon++;
                                LCD_Goto(incon,2);
								LCD_Print("*");
								LCD_Goto(1,2);
								LCD_Print("*");
															
								///tercera cifra
								while(1){
									contra = keyfind();
									__delay_ms(20);
									if (contra != ' '){
										if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){
											tercer_mal:;
                                            incon++;
                                            LCD_Goto(incon,2);
											LCD_Print("*");
											LCD_Goto(2,2);
											LCD_Print("*");
																					
											//cuarta cifra
											
											while(1){
												contra = keyfind();
												__delay_ms(20);
												if (contra != ' '){
													if (contra!='A' && contra!='B' && contra!='C' && contra!='D' && contra!='E'){
														cuarta_mal:;
                                                        incon++;
                                                        LCD_Goto(incon,2);
														LCD_Print("*");
														LCD_Goto(3,2);
														LCD_Print("*");
														acceso = 0;
														goto acces;
                                                    }
                                                }
                                            }
	
										}
									}
								}
								
							}
						}
					}
				}
			}
        }
        /////////////////////////////fin primera cifra 
        
        acces:;
        
        if(acceso == 1){
            LCD_Cmd(LCD_CLEAR);
            LCD_Goto(1,1);
            LCD_Print("ACCESO");
            LCD_Goto(1,2);
            LCD_Print("CONCEDIDO");
            __delay_ms(1000);
            break;
        }
        else if(acceso == 0){
            LCD_Cmd(LCD_CLEAR);
            LCD_Goto(1,1);
            LCD_Print("ACCESO");
            LCD_Goto(1,2);
            LCD_Print("DENEGADO");
            __delay_ms(1000);
            LCD_Cmd(LCD_CLEAR);
            memset(contras,0,4);
            incon = 0;
        }
        
       
    }
    LCD_Cmd(LCD_CLEAR);
    __delay_ms(2);
    
}

void modo (void){
    LCD_Goto(1,1);
    LCD_Print("A=AUTOMATICO");
    LCD_Goto(1,2);
    LCD_Print("B=MANUAL");
    __delay_ms(50);
    
    while(1){
        tecla = keyfind();
        __delay_ms(30);
        if(tecla!=' '){
            if (tecla == 'A'){
                LCD_Cmd(LCD_CLEAR);
                LCD_Goto(1,1);
                LCD_Print("A=Automatico");
                modo2 = 1;
                __delay_ms(1000);
                break;
            }
            else if(tecla == 'B'){
                LCD_Cmd(LCD_CLEAR);
                LCD_Goto(1,1);
                LCD_Print("B=Manual");
                modo2 = 2;
                __delay_ms(1000);
                break;
            }            
        }  
    }
    
    tecla=' ';
    LCD_Cmd(LCD_CLEAR);
    
    while(1){
        if (modo2 == 1){
           automatic();
        }
        else if (modo2 == 2){
           manual();
        }
    }
    
}

void automatic (void){
    LCD_Goto(1,1);
    LCD_Print("SETPOINT");
    LCD_Goto(10,1);
    while(1){
        tecla = keyfind();
        __delay_ms(30);
        if(tecla!=' '){
            if(tecla!='A' && tecla!='B' && tecla!='C' && tecla!='D' && tecla!='E'){
                sp[insp]=tecla;
                insp++;
            }
            if(tecla=='E'){
                SetPoint = atol(sp);
                LCD_Goto(1,2);
                LCD_Print("TEMP.");
                INT2IE = 1;
                while(1){
                    
                    
                    ///1
                    ADCON0 = 0x04;
                    ADCON0bits.ADON = 1;
                    __delay_us(20);
                    ADCON0bits.GO = 1;
                    while(ADCON0bits.GO);
                    celsius = ADRES;
                    celsius = (celsius*500);
                    celsius = celsius/1024;
                    ADCON0bits.ADON = 0;
                    
                    ADCON0 = 0x04;
                    ADCON0bits.ADON = 1;
                    __delay_us(20);
                    ADCON0bits.GO = 1;
                    while(ADCON0bits.GO);
                    celsius = ADRES;
                    celsius = (celsius*500);
                    celsius = celsius/1024;
                    sprintf(Temperatura,"%d C",(int)celsius);
                    LCD_Goto (7,2);
                    LCD_Print(Temperatura);
                    ADCON0bits.ADON = 0;
                    
                    Tem_Act = (int)celsius;
                    
                    
                    error = (SetPoint-Tem_Act);
                    error = (error*1023);
                    error = (2130 - error);
                    
                    if(error > 2130){
                        error = 2130;
                    }
                    else if (error < 0){
                        error = 0;
                    }
                    
                    
                    v = error;
                    //v = pid(SetPoint,celsius);
                    //error;//2120 max
                    __delay_us(100);
                    memset (Temperatura,0,10);
                    
                }
            }
        }
    }
    
}

void manual (void){
    INT2IE = 1;
    LCD_Goto(1,1);
    LCD_Print ("TEMP.");
    LCD_Goto(1,2);
    LCD_Print ("POT.DIMMER");
    while(1){
        /////lm35 //1
        ADCON0 = 0x04;
        ADCON0bits.ADON = 1;
        __delay_us(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        celsius = ADRES;
        celsius = (celsius*500);
        celsius = celsius/1024;
        sprintf(Temperatura,"%d C",(int)celsius);
        LCD_Goto (7,1);
        LCD_Print(Temperatura);
        ADCON0bits.ADON = 0;
        __delay_us(20);
        
        /////lm35 //2
        ADCON0 = 0x04;
        ADCON0bits.ADON = 1;
        __delay_us(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        celsius = ADRES;
        celsius = (celsius*500);
        celsius = celsius/1024;
        sprintf(Temperatura,"%d C",(int)celsius);
        LCD_Goto (7,1);
        LCD_Print(Temperatura);
        ADCON0bits.ADON = 0;
        __delay_us(20);
        
        
        
        ///////////pot 1
        ADCON0 = 0x00;
        ADCON0bits.ADON = 1;
        __delay_us(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        pot = ADRES;
        v = ADRES;
        potenciometro = pot*100/1023;
        sprintf(Potencio,"%d ",(int)((70-(int)potenciometro))*100/70);
        LCD_Goto(13,2);
        LCD_Print(Potencio);
        ADCON0bits.ADON = 0;
        __delay_us(20);
        
        ///////pot 2
        ADCON0 = 0x00;
        ADCON0bits.ADON = 1;
        __delay_us(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        pot = ADRES;
        v = ADRES;
        potenciometro = pot*100/1023;
        sprintf(Potencio,"%d ",(int)((70-(int)potenciometro))*100/70);
        LCD_Goto(13,2);
        LCD_Print(Potencio);
        ADCON0bits.ADON = 0;
        __delay_us(20);
        
        
    }
}


int pid(int setpoint,float tem_act){
    error = setpoint-tem_act;
    
    P = error * kp;
    I = (I+error)*ki;
    D = (error-error_past)*kd;
    error = error_past;
    error_total = (P+I+D);
    if (error_total>100){
        error_total = 100;
    }
    if (error_total < 0){
        error_total = 0;
    }
    
    error_total = 2130*(1-(error_total/100));
    
    return error_total;
}
