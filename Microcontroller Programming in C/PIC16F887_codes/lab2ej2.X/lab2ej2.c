/* 
 * File:   lab2ej2.c
 * Author: Xavier
 *
 * Created on April 17, 2018, 5:36 PM
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
unsigned char Contador=0,BanderaConversion=0;
int adc;
float volt;

//Prototipo de funciones
void InitES(void);
void InitTMR1(void);
void InitADC(void);
void Adquisicion(void); // adquiero valores de conversion mediante esta funcion, fuera de la interrupcion
//void MostrarPeso(unsigned char Uni,unsigned char Dec,unsigned char Cen);

// Funcion de interrupciones
void interrupt rutinainterrupciones()
{
    if(PIR1bits.TMR1IF == 1)
    {
        PIR1bits.TMR1IF=0;
        TMR1=3036;
        ADCON0bits.GO_DONE=1;
    }  
    while(ADCON0bits.GO_DONE==1); //espero que la conversion termine, no tarda tanto.
    BanderaConversion=1; // una vez que sale del while, termino la conversion, levanto esta bandera para adquirir valor fuera de la interrupcion.
}
// Funcion Principal
void main(void) 
{
    InitES();     //configurar los pines de ES
    InitTMR1();    //configurar timer 1
    InitADC();     //configurar ADC

    while(1)
    {
        if(BanderaConversion==1)
        {
            BanderaConversion=0;
            Adquisicion();
        }
        if (volt>=0.555)
        {
            PORTB=0b00000001;
            
            if (volt>=1.11)
            {
                PORTB=0b00000011;
                if (volt>=1.665)
                {
                    PORTB=0b00000111;
                    if (volt>=2.22)
                    {
                        PORTB=0b00001111;
                        if (volt>=2.775)
                        {
                            PORTB=0b00011111;
                            if (volt>=3.33)
                            {
                                PORTB=0b00111111;
                                if (volt>=3.885)
                                {
                                    PORTB=0b01111111;
                                    if (volt>=4.44)
                                    {
                                        PORTB=0b11111111;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            PORTB=0;
        }
    }
}

void InitES(void)
{
    ANSEL=0b00000001; // RA0 lo defino como analógico
    ANSELH=0;
    TRISA=0b00000001;// RA0 como entrada
    TRISB=0b00000000;
    PORTB=0;
    PORTA=0;
   
}
void InitTMR1(void)
{
    T1CON = T1CON | 0x30;    //Pre escalador en 8
    T1CONbits.TMR1CS = 0;    //Se utiliza FCY para temporizaci?n
    T1CONbits.TMR1GE = 0;    //No se usa gate
    TMR1=3036;            //en 3036. Cuenta hasta 65535
    PIR1bits.TMR1IF = 0;     //Se baja bandera de interrupci?n por las dudas
    INTCONbits.GIE = 1;      //Se activan interrupciones globales
    INTCONbits.PEIE = 1;     //Se activan interrupciones de perif?ricos
    PIE1bits.TMR1IE = 1;     //Se activa interrupci?n por desborde de timer 1
    T1CONbits.TMR1ON = 1;    //Se enciende timer 1  
    
}
void InitADC(void)
{
    ADCON0bits.CHS0=0; //CANAL 0
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS2=0;
    ADCON0bits.CHS3=0;
    ADCON1bits.VCFG0=0; // REFERENCIA NEGATIVA VSS
    ADCON1bits.VCFG1=0;// referencia positiva vdd
    ADCON0bits.ADCS1=1; // señal de reloj interno (la del micro)
    ADCON0bits.ADCS0=0;
    ADCON1bits.ADFM=1;// JUSTIFICANDO A LA DERECHA
    ADCON0bits.ADON=1;// ADC ENCENDIDO
    PIE1bits.ADIE=0; //INHABILITO INTERRUPCIONES POR CONVERSOR, NO ME INTERESAN.
    ADCON0bits.GO_DONE=0;
}

void Adquisicion(void)
{
        adc = ADRESH;
        adc=adc<<8;
        adc=adc+ADRESL;
        volt=adc*(5.0/1023.0);
}