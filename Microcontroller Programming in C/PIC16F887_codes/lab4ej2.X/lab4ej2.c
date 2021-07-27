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
#include "I2C.h"

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

unsigned char  linea1[16],linea2[16],bufer[16],BanderaSprintf, Contador;
unsigned char temperatura=0,tempfinal=0,BanderaDeAdquisicion=0;


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
            BanderaDeAdquisicion=1;
        }
    }
   
}

//Prototipo de funciones
void InitES(void);
void InitTMR1(void);
void Adquisicion(void);

void main(void) 
{
    InitES(); //ENTRADAS SALIDAS
    inicializacion(); //LCD
    InitI2C(); //CONFIGURACION I2C + TERMOMETRO
    InitTMR1(); // TMR1 E INTERRUPCIONES
    while(1)
    {
        sprintf(linea1,"TEMPERATURA");
        if(BanderaDeAdquisicion==1)
        {
            Adquisicion();
        }
        if(BanderaSprintf==1)
            {
                BanderaSprintf=0;
                //tempfinal=((tempfinal & 0xF0)>>4) *10 + (tempfinal & 0x0F); //bcd a ascii
                sprintf(linea2," %3u 'C",tempfinal);
            }
        LCD(&linea1); // ESCRIBE LINEA SUPERIOR LCD
        LCD2(&linea2); // ESCRIBE LINEA INFERIOR LCD
    } 
}

void InitES(void)
{
    ANSEL=0;
    ANSELH=0;
    TRISCbits.TRISC4=1; // sda entrada
    TRISCbits.TRISC3=1; // scl entrada
    TRISB=0;
    PORTB=0;
    PORTC=0;
}

void InitTMR1(void)
{
    T1CON=T1CON | 0x30;    //Pre escalador en 8
    T1CONbits.TMR1CS = 0;    //Se utiliza FCY para temporizaciÓn
    T1CONbits.TMR1GE = 0;    //No se usa gate
    TMR1= 3036;            //Se configura valor inicial en 3036. Cuenta hasta 65535
    PIR1bits.TMR1IF = 0;     //Se baja bandera de interrupción por las dudas
    INTCONbits.GIE = 1;      //Se activan interrupciones globales
    INTCONbits.PEIE = 1;     //Se activan interrupciones de perifEricos
    PIE1bits.TMR1IE = 1;     //Se activa interrupción por desborde de timer 1
    T1CONbits.TMR1ON = 1;    //Se enciende timer 1
}
void Adquisicion(void)
{
             BanderaDeAdquisicion=0;
            //comienza protocolo I2C para adquirir temperatura
            InitCOM();
            while(SSPCON2bits.SEN==1);
            SSPBUF=0b10010001; // direccion 0x91 se va a leer un dato del termo
            banderassp=0;
            while(banderassp==0); //espero que se levante, cuando se levanta, es que se termino de enviar el dato
            while(slaveACK==0); // verifico que el nACK sea 1
            recepcion=1;
            while(recepcion==1); // se pone a cero automaticamente cuando termina de recibir todo el dato el bufer
            temperatura =SSPBUF; // adquiero el valor de temperatura
            tempfinal=temperatura; //temp final tendra el valor de los 9 bits de informacion sumados
            //ya adquiri el byte mas importante, necesito el ultimo bit LSB
            banderassp=0; // la bajo porque se va a levantar cuando termine el ACKEN
            habilitadorACK=1; // bit ACKEN que habilita mandar el ACKDT
            ACK=0; //indico al esclavo que recibi el dato y quiero seguir recibiendo
            recepcion=1; // habilito recepciones
            banderassp=0; // se levanto a 1 cuando termino el ACKEN
            while(banderassp==0); //espero que se levante, cuando se levanta, es que se termino de enviar el dato
            temperatura=SSPBUF;
            tempfinal=tempfinal + (temperatura>>7);
            ACK=1;
            StopCOM();
            BanderaSprintf=1;
}