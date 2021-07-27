/* 
 * File:   lab3ej2.c
 * Author: Xavier
 *
 * Created on 3 de mayo de 2018, 01:10
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

#define pulsador PORTBbits.RB7
#define RS PORTBbits.RB6
#define RW PORTBbits.RB5
#define E PORTBbits.RB4
#define DB4 PORTBbits.RB3
#define DB5 PORTBbits.RB2
#define DB6 PORTBbits.RB1
#define DB7 PORTBbits.RB0

// Declaracion de variables globales
unsigned char *p1;
unsigned char *p2;
unsigned char u=0;
unsigned char letraenvio=0, Contador=0;
float volt=0;
unsigned int adc=0;
unsigned char linea1[16];
unsigned char linea2[16];


//Prototipo de funciones
void InitES(void);
void envio(void);
void invertir(void);
void LCD(void);
void LCD2(void);
void armovector(void) ;
void inicializacion(void);
void InitTMR1(void);
void bajar(void);
void subir(void);

//rutina interrupciones
void interrupt rutinainterrupciones(void)
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
        }
    }
    if (PIR1bits.ADIF==1)
    {
        PIR1bits.ADIF=0;
        adc=ADRESH;
        adc=adc<<8;
        adc=adc+ADRESL;
        volt=adc*(5.0/1023.0);
    }
}

void main(void) 
{
    InitES();      
    InitTMR1();
    inicializacion();
    while(1)
    {
        armovector();
        LCD();
        LCD2();        
    }
}

void InitES(void)
{
    ANSEL=0b00000011;
    ANSELH=0;
    TRISA=0b00000011;
    TRISB=0b10000000;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON1bits.ADFM=1;
    ADCON0=0b10000101;
    PORTA=0;
    PORTB=0;
}

void armovector(void)
{
    if (pulsador==1)
    {
        ADCON0=0b10000001;
        u=0;
        sprintf(linea1,"voltimetro AN%u\0",u);
        p1=&linea1;
        sprintf(linea2,"%1.3fV // %4i\0",volt,adc);
        p2=&linea2;
    }
    else
    {
        ADCON0=0b10000101;
        u=1;
        sprintf(linea1,"voltimetro AN%u\0",u);
        p1=&linea1;
        sprintf(linea2,"%1.3fV // %4i\0",volt,adc);
        p2=&linea2;
    }
}

void LCD(void)
{
    //subir();
    while(*p1!=0)
    {
        letraenvio = *p1;
        letraenvio= letraenvio>>4;  //corro el vector 4 lugares a la izquierda 
        invertir(); //muestro en puerto B
        envio();
        letraenvio= *p1 & 0x0F;
        invertir(); //muestro en puerto B
        envio();
        p1++;
    }
}

void LCD2(void)
{
    bajar();
    while(*p2!=0)
    {
        letraenvio = *p2;
        letraenvio= letraenvio>>4;  //corro el vector 4 lugares a la izquierda 
        invertir(); //muestro en puerto B
        envio();
        letraenvio= *p2 & 0x0F;
        invertir(); //muestro en puerto B
        envio();
        p2++;
    }
    subir();
}

void invertir(void)
{
    DB4= letraenvio & 0b00000001;
    DB5= (letraenvio & 0b00000010)>>1;
    DB6= (letraenvio & 0b00000100)>>2;
    DB7= (letraenvio & 0b00001000)>>3;   
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
    PIE1bits.ADIE=1;
}

void bajar(void)
{
    RW=0;
    RS=0;
    DB7=1;
    DB6=1;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    RW=0;
    RS=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
}
void subir(void)
{
    RW=0;
    RS=0;
    DB7=1;
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    RW=0;
    RS=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
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
    __delay_ms(10); // 5ms + BF
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=1;
    DB4=0;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5); //BF
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
    DB7=1;      //fijar numero de lineas usamos una linea
    DB6=1;       //fijar numero de Caracteres usamos tamaño 5X10 puntos
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
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
    __delay_ms(5); //BF
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
    __delay_ms(5); //BF
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