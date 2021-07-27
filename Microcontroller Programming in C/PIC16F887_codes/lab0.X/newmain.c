/* 
 * File:   newmain.c
 * Author: piniel
 *
 * Created on March 25, 2018, 6:00 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000
#include <xc.h>
#include <pic16f887.h>
#define FCY (_XTAL_FREQ/4)
#define LED PORTBbits.RB0
#define PULSADOR PORTBbits.RB1

void ConfigIni(void);
void Titilar(void);
void Alternador(void);


/* titila un led con pulsador
 * 
 */
int main(int argc, char** argv) 
{
    ConfigIni();
    
    while(1)
    {  
        Alternador();
            
        if(PULSADOR == 1)
        { Titilar();
        }
        
    }
    
    

    return (EXIT_SUCCESS);
}

void ConfigIni(void)
{   
    ANSELH = 0x00;
    ANSEL = 0x00;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 1;
}

void Titilar(void)
{
    LED = 1;
    __delay_ms(500);
    
    LED = 0;
    __delay_ms(500);
    
}

void Alternador(void)
{
    if(PULSADOR == 1)
    {
        PULSADOR = 0; }
        if(PULSADOR == 0)
        { PULSADOR = 1;
}
}

            
   


