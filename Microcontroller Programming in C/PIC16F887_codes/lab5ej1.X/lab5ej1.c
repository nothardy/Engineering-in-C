/* 
 * File:   lab3ej1.c
 * Author: julian
 *
 * Created on 15 de mayo de 2018, 10:31
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000 // Indicamos a que frecuencia de reloj esta funcionando el micro
#include <xc.h>
#include <pic16f887.h> // Librería XC8
#include "LCD.h"


#define FCY (_XTAL_FREQ/4)      //Frecuencia de trabajo
// PIC16F887 Configuration Bit Settings
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define banderarx PIR1bits.RCIF
#define clear PORTDbits.RD7

unsigned char BanderaINT=0,linea=1,dato,escritura[10];
//prototipo de funciones
void InitES();
void InitUSART();
void InitINTERRUPT();


void interrupt rutinainterrupciones()
{
    if(banderarx==1)
    {
        banderarx=0;
        BanderaINT=1;
        dato=RCREG; // lo leo aca, sino nunca sale de la interrupcion
    }
}

void main (void)
{
    InitES();
    InitINTERRUPT();
    inicializacion();
    InitUSART();
    while(1)
    {
        if (clear==1)
        {
           __delay_ms(20);
           if (clear==1)
           {                
                while (clear==0); // pongo ; y no llaves porque no hay nada adentro
                __delay_ms(20);
                if (clear==0)
                {
                Limpiardisplay();                        
                }
            }
        }
        if (BanderaINT==1)
        {
            BanderaINT=0;
            switch(dato)
            {
                case 0x08:
                    dato=0;
                    backspace();
                    break;
                case 0x0D:
                    if(linea==1)
                    {
                        bajar();
                        dato=0; 
                        linea=2;
                    }
                    else
                    {
                        subir();
                        dato=0;
                        linea=1;
                    }
                    break;
                default:
                    sprintf(escritura,"%c",dato);
                    dato=0;
                    if(linea==1)
                    {
                        LCD(&escritura);
                    
                    }
                    else
                    {
                        LCD(&escritura);
                    }
                    break;
            }
                    
                    
                    
                
        }
            /*if(dato==0xB6)
            {
                dato=0;
                backspace();
            }
            if(dato==0x0D) //0D representa el enter
            {
                if(linea==1)
                {
                    bajar();
                    dato=0; 
                    linea=2;
                }
                else
                {
                    subir();
                    dato=0;
                    linea=1;
                }
                
            }
            else
            {
                sprintf(escritura,"%c",dato);
                dato=0;
                if(linea==1)
                {
                    LCD(&escritura);
                    
                }
                else
                {
                    LCD(&escritura);
                }
            }*/
    }
}

void InitES()
{
    ANSEL=0;
    ANSELH=0;
    TRISB=0b00000000; // cambiar para el clear
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    PORTC=0;
    TRISD=0b10000000;
    PORTD=0;
    
}

void InitINTERRUPT()
{
    INTCONbits.GIE = 1;      //Se activan interrupciones globales
    INTCONbits.PEIE = 1;       //se activan interrupciones perifericas
    PIE1bits.RCIE=1; // HABILITO INTERRUPCIONES POR RECEPTOR
}

void InitUSART()
{
    TXSTA=0b00101110; //se configura com asincrona, de 8 bits,se habilita la transimision, velocidad alta
    RCSTA=0b10010000; //se configura habilitaion del modulo usart, recepcion, recepcion de 8 bits
    SPBRG=129; // SPBRG=(Foscilador/153600)-1 = (20000000/153600)-1= 129,20=129
}

