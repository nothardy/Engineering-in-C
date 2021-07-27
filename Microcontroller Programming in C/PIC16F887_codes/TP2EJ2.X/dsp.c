//******************************************************************************
//
//  PROGRAMA:       PIC24Plantilla.c
//  AUTHOR:        SASE2014
//  DATE:          1/8/2014
//  DESCRIPCION:   Este proyecto tiene como finalidad la ser una plantilla tipo
//                 para realizar futoros laboratorios.
//                 Se utiliza el micro PIC25FJ128GA010 y una placa experimental
//                 Explorer16.
//                 
//
//  REQUIRIMIENTOS:
//                 Hardware: PIC24FJ64GA010 PIM sobre Explorer 16
//                 MPLAB X IDE v1.0 o mejor
//                 MPLAB XC16 Compiler for PIC24 v1.21 (libre)
//  NOTAS:
//
//  Revisión Histórica:
//  8/2014  SASE2014
//          Describir futuros agregados al proyecto o modificaciones.
//******************************************************************************
#define FOSC 32000000        // Frecuencia del clock del micro
#define FCY FOSC/2          // Frecuencia de instrucciones usada por  "__delay_ms()"
//------------------------------------------------------------------------------
//  ARCHIVOS HEADER
//------------------------------------------------------------------------------
#include <p24FJ128GA010.h>   // Header específico de un micro
                            //
                            // 
  // Archico Headrer para definir LEDs y pulsadores
                                  //para la placa Explorer16
#include <libpic30.h>       // se necesita para "__delay_ms()"
#include "LCD.h"

//------------------------------------------------------------------------------
//   CONFIGURACION DE BITS
//------------------------------------------------------------------------------

_CONFIG1( JTAGEN_OFF        // deshabilito interface JTAG
        & GCP_OFF           // deshabilito proteción de código general
        & GWRP_OFF          // deshabilito protección escritura flash
        & ICS_PGx2         // ICSP interface (2=default)
        & FWDTEN_OFF)       // deshabilito watchdog timer
_CONFIG2( IESO_OFF          // deshabilito 2 velocidades de start up
        & FCKSM_CSDCMD      // deshabilito clock-swithcing/monitor
        & FNOSC_PRIPLL      // primary oscillator: habilito PLL
        & POSCMOD_XT)       // primary oscillator: modo XT

//------------------------------------------------------------------------------
//  Constantes de Programa
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  Definición de Tipos de variable
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  Declaración de variables Globales
//------------------------------------------------------------------------------

// 
#define p1  PORTDbits.RD6 
#define p2  PORTDbits.RD7
#define p3  PORTAbits.RA7
#define p4  PORTDbits.RD13
#define led0  PORTAbits.RA0
#define led1  PORTAbits.RA1
#define led2  PORTAbits.RA2
#define led3  PORTAbits.RA3
#define led4  PORTAbits.RA4
#define led5  PORTAbits.RA5
#define led6  PORTAbits.RA6
        i=1;
        void filtrochorus(void);
        void main (void)
{
    while(1)
    {
        
    }
}
        
        void filtrochorus(void)
        {
            delay1=30;// tiempo en milisegundos despues de la señal original donde va ser sumada una nueva señal
rango1=50;
fbarrido1=2;
delay2=15; // tiempo en milisegundos despues de la señal original donde va ser sumada una nueva señal
rango2=14; //amplitud de la señal sumada
fbarrido2=0.3125;
//filtro flanger por medio de ecuacion en diferencias, esta ecuacion tiene
// 3 componentes con los que se modula el efecto de phaser/flanger/chorus
for (i=1;i>(length(x)-rango2-delay1);i++)
{
    y(i)=x(i) + x(i + delay1 + rango1*sin(2*pi*i*(fbarrido1/f)))+ x(i + delay2 + rango2*sin(2*pi*i*(fbarrido2/f)));
        }