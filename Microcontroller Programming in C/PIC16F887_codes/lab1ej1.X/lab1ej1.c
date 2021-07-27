/* 
 * File:   Ejercicio1.c
 * Author: Xavier
 *
 * Created on 26 de marzo de 2018, 09:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#define _XTAL_FREQ 20000000
#define FCY (_XTAL_FREQ/4)
// PIC16F887 Configuration Bit Settings
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define pulsador PORTBbits.RB7
unsigned char mate = 0; // arranca de 0 a 255 porque char es de 8 bits
/*
 * 
 */
void main() 
{
    ANSEL=0;
    ANSELH=0;
    TRISB=0b10000000;
    PORTB=0; //clear
    
    while(1) 
    {
        if (pulsador==1)
        {
           __delay_ms(20);
           if (pulsador==1)
           {                
                while (pulsador==0); // pongo ; y no llaves porque no hay nada adentro
                __delay_ms(20);
                if (pulsador==0)
                {
                mate = mate++;                        
                }
            }
        }
        if (mate==128)
        {
            mate=0;
        }
        PORTB = mate;
    }
}

