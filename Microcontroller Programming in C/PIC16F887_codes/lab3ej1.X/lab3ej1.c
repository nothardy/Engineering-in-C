/* 
 * File:   EJERCICIO1.c
 * Author: fernandoMMONTECINO
 *
 * Created on 29 de abril de 2018, 22:10
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

unsigned char letraenvio;
unsigned char letra;
unsigned char *pchar;   //Solo puede apuntar a caracteres sin signo
unsigned int *pint;     //Solo puede apuntar a enteros sin signo
unsigned int direccion;
unsigned char registro @0x40;   //con @0xXX posicionamos la variable registro en la dir 0xXX
unsigned char aux1 @0x41;
unsigned char aux2 @0x42;
unsigned char vector[15];       //Crear un vector vacío (lleno de ceros)
unsigned char vectorlleno[15]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  //Crear un vector lleno (tiene que tener tantos numeros como componentes)
//Prototipo de funciones
void InitES(void);
void envio(void);
void invertir(void);
void LCD(void);
void armovector(void) ;
void funcion(unsigned char *dir_entrada);
void inicializacion(void);

void InitES(void)
{
    ANSEL=0b00000000; // RA0 lo defino como analogico
    ANSELH=0;
    TRISB=0b00000000;
    PORTB=0;
}

// Funcion Principal
void main(void) 
{
    InitES();     //configurar los pines de ES
    inicializacion();
    armovector();
    
    LCD();  
}
void armovector(void) 
    {
        vectorlleno[10]=0;
        registro=0x88;            //Un registro cualquiera
        pchar=&registro;      //El &<var> da como resultado la direccion de <var>
        aux1=pchar;          //El valor de pchar es la direccion de lo que apunta (registro)
        aux2=*pchar;          //El valor de *pchar es lo que esta en la direccion de lo que apunta, es decir, el valor de registro.
        sprintf(vector,"hola mundo\0"); //Pone el mensaje "hola mundo" al vector "vector"
        funcion(&vector[0]);    //La entrada de la funcion es una direccion (tiene que declararse arriba
        
    }


void funcion(unsigned char *dir_entrada)
{
    unsigned char vectoraux[50],vectorlocal[50];
    int i=0;
    while(*dir_entrada!=0)      //Mientras lo que haya en la direccion "dir_entrada" sea distinto de cero, se guarda en un vector auxiliar
    {
        vectoraux[i]=*dir_entrada;  //Se guarda lo que haya en la direccion dir_entrada
        i++;
        dir_entrada++;  //Se aumenta para ir a la siguiente direccion
    }
    sprintf(vectorlocal,"el vector de long %i es:%s",i,vectoraux);  //Concatena el texto con el numero i y el vectoraux;
    vectorlocal[49]=255;    //Asigna el valor 255 al componente
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

void LCD(void)
{
    int P=0;
    if(P!=10)
    {
        letra=vectorlleno;
        letraenvio=letra*0xF0;
        letraenvio<<4;         //corro el vector 4 lugares a la izquierda 
        invertir();
        //muestro en puerto B
        envio();
        letraenvio=letra*0x0F;
        invertir();
        //muestro en puerto B
        envio();
        P=P+1;
    }
}

void invertir(void)
{
    RB3=letra*0b00000001;
    RB2=letra*0b00000010;
    RB1=letra*0b00000100;
    RB0=letra*0b00001000;
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

