/* 
 * File:   lab3ej1mio.c
 * Author: piniel
 *
 * Created on May 2, 2018, 10:54 AM
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 20000000 // Indicamos a que frecuencia de reloj esta funcionando el micro
#include <xc.h> // Librería XC8

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

#define RS PORTBbits.RB6
#define RW PORTBbits.RB5
#define E PORTBbits.RB4
#define DB4 PORTBbits.RB3
#define DB5 PORTBbits.RB2
#define DB6 PORTBbits.RB1
#define DB7 PORTBbits.RB0

// Declaracion de variables globales
unsigned char vector[15];
unsigned char *p;
unsigned char letra,letraenvio;
//unsigned char registro @0x40;
//Prototipo de funciones
void InitES(void);
void envio(void);
void invertir(void);
void LCD(void);
void armovector(void) ;
void inicializacion(void);


void main(void) 
{
    inicializacion();
    InitES();
    armovector();
    LCD();  
}
void InitES(void)
{
    ANSEL=0b00000000; // RA0 lo defino como analogico
    ANSELH=0;
    TRISB=0b00000000;
    PORTB=0;
}
void inicializacion(void)
{
    __delay_ms(30);
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=1;
    DB4=1;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=1;
    DB4=1;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
    if (BF==0)
    {
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=1;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    }
    if (BF==0)
    {
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=1;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    RS=0;
    RW=0;
    DB7=0;      //fijar numero de lineas usamos una linea
    DB6=1;       //fijar numero de Caracteres usamos tamaño 5X10 puntos
    E=1;
    __delay_ms(5);
    E=0;
    }
    if (BF==0)
    {
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    RS=0;
    RW=0;
    DB7=1;      
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    }
    if (BF==0)
    {
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    RS=0;
    RW=0;
    DB7=0;      
    DB6=0;
    DB5=0;
    DB4=1;
    E=1;
    __delay_ms(5);
    E=0;
    }
    if (BF==0)
    {
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    RS=0;
    RW=0;
    DB7=1;      
    DB6=1;
    DB5=1;          //incremento luego de escritura
    DB4=0;          //corre cursor luego del ingreso de datos
    E=1;
    __delay_ms(5);
    E=0;
    }
}

void armovector(void)
 {
   unsigned char vector[20]={"HOLA MUNDO! k"};
    p=&vector;
   
    
   
}
void LCD(void)
{
    unsigned char k= 0b01101011;
    while(*p!=k)
    {
        letra = *p;
        letraenvio = letra;
        letraenvio= letraenvio>>4;         //corro el vector 4 lugares a la izquierda 
        invertir();
        //muestro en puerto B
        envio();
        letraenvio=letra & 0x0F;
        invertir();
        //muestro en puerto B
        envio();
        p=p+1;
    }
    
       if(*p==k)
       {
          __delay_ms(3600); //para que no se refresque tan rapido. ¿se puede refrescar a una frecuencia tal que el ojo no lo note?
      
       }
      
}
void invertir(void)
{
    PORTBbits.RB3= letraenvio & 0b00000001;
    PORTBbits.RB2= (letraenvio & 0b00000010)>>1;
    PORTBbits.RB1= (letraenvio & 0b00000100)>>2;
    PORTBbits.RB0= (letraenvio & 0b00001000)>>3;   
}
void envio(void)
{
    RS=1;
    RW=0;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(20);
}


