
#include "teclado.h"

unsigned char keyfind(){
    
    Direction_Port = 0xf0;  /*PORTD.0-PORTD.3 as a Output Port and PORTD.4-PORTD.7 as a Input Port*/
    write_port = 0xf0;      /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
    
    do{
          
        do{
            col_loc = read_port & 0xf0; /*mask port with f0 and copy it to col_loc variable*/   
        }while(col_loc!=0xf0);          /*Check initially at the start there is any key pressed*/ 
            
        col_loc = read_port & 0xf0;    /*mask port with f0 and copy it to col_loc variable*/  
            
    }while(col_loc!=0xf0);
      
    write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
    
    do{ 
        do{   
            col_loc = read_port & 0xf0;
        }while(col_loc==0xf0);      /*Wait for key press*/
        col_loc = read_port & 0xf0;
        
    }while(col_loc==0xf0);          /*Wait for key press*/
               
    MSdelay(20);
         
        col_loc = read_port & 0xf0;
              
    while(1){
        write_port  = 0xfe;                 /*make Row0(D0) Gnd and keep other row(D1-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=0;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Monitor the status of Port and Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/    
            }
            break;
        }
        
        write_port = 0xfd;                  /*make Row1(D1) Gnd and keep other row(D0-D2-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=1;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Monitor the status of Port and Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
        write_port = 0xfb;                  /*make Row0(D2) Gnd and keep other row(D0-D1-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=2;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
        write_port = 0xf7;                  /*make Row0(D3) Gnd and keep other row(D0-D2) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=3;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
    }

    
    
    while(1){
        
        if(col_loc==0xe0)
        {  
            //3 0 on/c
                        
            if(lim==0)LCD_Char(keypad[rowloc][0]);   /*Display Keypad location on LCD*/
            
            if(rowloc==3) lim=0;
            
             return keypad[rowloc][0];      /*Return key pressed value to calling function*/            
        }
        else 
            if(col_loc==0xd0)
        {
            if(lim==0)LCD_Char(keypad[rowloc][1]);   /*Display Keypad location on LCD*/
            return keypad[rowloc][1];       /*Return key pressed value to calling function*/   
        }
        else
            if(col_loc==0xb0)
        {
            //3 2 =
            if(rowloc==3) lim=1;
            
            if(lim==0)LCD_Char(keypad[rowloc][2]);   /*Display Keypad location on LCD*/
            return keypad[rowloc][2];       /*Return key pressed value to calling function*/
        }
        else
            
        {
            if(lim==0)LCD_Char(keypad[rowloc][3]);   /*Display Keypad location on LCD*/
            return keypad[rowloc][3];       /*Return key pressed value to calling function*/           
        }    
    }
    
   MSdelay(200);     
   return 0;
}

