/* 
 * File:   lab3ej1.c
 * Author: julian
 *
 * Created on 15 de mayo de 2018, 10:31
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000 // Indicamos a que frecuencia de reloj esta funcionando el micro
#include <xc.h> // Librería XC8
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

//Asigno las salidas del pic a las entradas del LCD

#define chipenable PORTCbits.RC0
unsigned char linea1[16],linea2[16],bufer[16],BanderaAdquisicion=0, Contador;


// Funcion de interrupciones
void interrupt rutinainterrupciones()
{
    if(PIR1bits.TMR1IF==1)
    {
        PIR1bits.TMR1IF=0;
        Contador++;
        TMR1=3036;
        if(Contador==10)
        {
            Contador=0;
            BanderaAdquisicion=1;
        }
    }
}

//Prototipo de funciones
void InitES(void);
void InitTMR1(void);
void InitSPI(void);
void Adquisicion(void);

void main(void) 
{
    InitES();
    inicializacion();
    InitSPI();
    InitTMR1();
    while(1)
    {
        if(BanderaAdquisicion==1)
        {   
            BanderaAdquisicion=0;
            Adquisicion();
            int j=0;
                for(j=0;j<7;j++)
                {
                    bufer[j]=((bufer[j] & 0xF0)>>4) *10 + (bufer[j] & 0x0F);
                }
                sprintf(linea1,"FECHA %02u/%02u/%02u",bufer[4],bufer[5],bufer[6]);
                sprintf(linea2,"HORA %02u:%02u:%02u",bufer[2],bufer[1],bufer[0]);
        }
        LCD(&linea1);
        LCD2(&linea2);
    } 
}

void InitES(void)
{
    ANSEL=0;
    ANSELH=0;
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC3=0;
    TRISCbits.TRISC4=1;
    TRISCbits.TRISC5=0;
    TRISB=0;
    PORTB=0;
    PORTC=0;
}

void InitTMR1(void)
{
    T1CON=T1CON | 0x30;    //Pre escalador en 8
    T1CONbits.TMR1CS = 0;    //Se utiliza FCY para temporizaciÓn
    T1CONbits.TMR1GE = 0;    //No se usa gate
    TMR1H = 0x0B;            //Se configura valor inicial
    TMR1L = 0xDC;            //en 3036. Cuenta hasta 65535
    PIR1bits.TMR1IF = 0;     //Se baja bandera de interrupción por las dudas
    INTCONbits.GIE = 1;      //Se activan interrupciones globales
    INTCONbits.PEIE = 1;     //Se activan interrupciones de perifEricos
    PIE1bits.TMR1IE = 1;     //Se activa interrupción por desborde de timer 1
    T1CONbits.TMR1ON = 1;    //Se enciende timer 1
}
void InitSPI(void)
{
    SSPSTAT=0b00000000;
    SSPCON=0b11100000;
    //comienza config inicial
    chipenable=1;
    SSPBUF=0x8f;
    while(SSPSTATbits.BF==0);
    SSPBUF=0;
    while(SSPSTATbits.BF==0);
    chipenable=0;
    /*chipenable=1; 
    SSPBUF=0x10;
    while(SSPSTATbits.BF==0);
    SSPBUF=0;
    while(SSPSTATbits.BF==0);
    chipenable=0;
    */__delay_ms(1);
    chipenable=1;
    SSPBUF=0x80;
    while(SSPSTATbits.BF==0);
    SSPBUF=0x20;//seg iniciales
    while(SSPSTATbits.BF==0);
    SSPBUF=0x20;//min iniciales
    while(SSPSTATbits.BF==0);
    SSPBUF=0x20;//hr iniciales
    while(SSPSTATbits.BF==0);
    SSPBUF=0x04;//dia en nombre iniciales
    while(SSPSTATbits.BF==0);
    SSPBUF=0x24;//dia iniciales
    while(SSPSTATbits.BF==0);
    SSPBUF=0x05;//mes iniciales
    while(SSPSTATbits.BF==0);
    SSPBUF=0x18;//año iniciales
    while(SSPSTATbits.BF==0);
    chipenable=0;
}

void Adquisicion(void)
{
    int i=0;
            chipenable=1;
            SSPBUF=0; //buscar en placA
            while(SSPSTATbits.BF==0);
            SSPBUF=0b11111111;
            while(SSPSTATbits.BF==0);
            for (i=0;i<7;i++)
            {
                bufer[i]=SSPBUF;
                SSPBUF=0xf2;
                while(SSPSTATbits.BF==0);
            }
            chipenable=0;
}