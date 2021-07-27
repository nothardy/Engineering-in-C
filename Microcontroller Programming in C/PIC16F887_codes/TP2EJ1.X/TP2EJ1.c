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
#include "explorer16_GPIO_map.h"  // Archico Headrer para definir LEDs y pulsadores
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
        

const unsigned char miString[] = "Hola Mundo";
const unsigned char miArray[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

unsigned char data,linea1[16];         // variable en memoria de datos



//------------------------------------------------------------------------------
//  Prototipos de funciones
//------------------------------------------------------------------------------


//==============================================================================
//  FUNCCION:     main()
//  DESCRIPCION:
//  PARAMETROS:
//  RETORNA:        nada
//  REQUERIMIENTOS: nada
//==============================================================================
void main(void)
{
    
    PORTB=0;
    PORTE=0;
    PORTD=0;
    TRISB=0;
    TRISE=0;
    TRISD=0;
    inicializacion();
    sprintf(linea1,"HOLA");
    LCD(&linea1);

    while(1)
    {
    
    }
}


