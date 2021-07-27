/*
 * File:   mainLab2.c
 * Author: Tecnicas Digitales II
 *
 * Created on 30 de Marzo de 2016, 10:00
 *  Microcontrolador: PIC16F887  Compilador XC8
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000 // Indicamos a que frecuencia de reloj esta funcionando el micro
#include <xc.h> // Librer?a XC8


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

// Declaracion de variables globales
int uni=0,dec=0,cen=0,Contador=0,banderaconversion=0;
float volt=0,p=0;
unsigned int adc=0;

// Funcion de interrupciones
void interrupt rutinainterrupciones()
{
    if(PIR1bits.TMR1IF==1)
    {
        PIR1bits.TMR1IF=0;
        Contador++;
        TMR1=3036;
        if(Contador==5)
        {
            Contador=0;
            ADCON0bits.GO_DONE=1;
            while(ADCON0bits.GO_DONE==1);
            banderaconversion=1;
        }
    }
}

//Prototipo de funciones
void InitES(void);
void InitTMR1(void);
void MostrarPeso(void);


// Funcion Principal
void main() 
{
    InitES();     //configurar los pines de ES
    InitTMR1();    //configurar timer 1
    while(1)
    {
        if( banderaconversion==1)
        {
            banderaconversion=0;
            adc=ADRESH;
            adc=adc<<8;
            adc=adc+ADRESL;
            volt=adc*(5.0/1023.0);
            uni=volt;
            dec=(volt-uni)*10;
            cen=(volt-uni-dec/10.0)*100;
        }
        MostrarPeso();  //Muestro los valores del peso en los displays
    }
}

void InitES(void)
{
    ANSEL=0b00000010;
    ANSELH=0;
    TRISA=0b00000010;
    TRISC=0b00000000;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON1bits.ADFM=1;
    ADCON0=0b10000001;
    PORTA=0;
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
    T1CONbits.TMR1ON = 1; 
}


void MostrarPeso(void)
{
    PORTC=cen | 0b01000000;
    __delay_ms(2);
    PORTC=dec | 0b00100000;
    __delay_ms(2);
    PORTC=uni | 0b00010000;
    __delay_ms(2);
}
