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
#include <xc.h>
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



void InitES(void);
void envio(unsigned char);
void bajar (void);
void subir(void);

void limpiarLCD(void);
void Comando(char valor);
void INICLcd(void);
void conversion(void);


int temp, contador;
int tempfinal;
int valorbits=0;
unsigned char recibir=0,linea1[16]=0,linea2[16]=0,i=0,escritura1[40]=0,escritura2[40]=0; // ERROR 1 nose que pasa aca

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
int main(void)
{
    PORTE=0;
    PORTD=0;
    PORTB=0;
    InitES();
    INICLcd();
    __delay_ms(20);
    limpiarLCD();
    sprintf(linea1,"Bienvenido a");
    sprintf(linea2,"TP4EJ1 - USART");
    LCD(&linea1);
    LCD2(&linea2);
    while(1)
    {
        conversion();
        
        sprintf(escritura1,"TEMP: %2i",tempfinal);
        sprintf(escritura2,"POTE:%i ",valorbits); //como obtengo el valor de bits
        for(i=0;i<41;i++)
       {
            U2TXREG=escritura1[i]; //registro de pic24
            while(U2STAbits.UTXISEL1!=1 && U2STAbits.UTXISEL0!=0); // UTXISEL<1:0> = 10, the UxTXIF is set when the character is transferred to the Transmit
                //Shift register (UxTSR) and the transmit buffer is empty.
            __delay_ms(20);
            
       }
        U2TXREG=0X20; //envio un enter
        for(i=0;i<41;i++)
       {
            U2TXREG=escritura2[i]; //registro de pic24
            while(U2STAbits.UTXISEL1!=1 && U2STAbits.UTXISEL0!=0); // bandera de pic24
            __delay_ms(20);
            
       }
        //borro las lineas con comandos para escribirlas nuevamente
    };
    
    
}

void InitES (void)
{
    
    //inicializo UART
    U1BRG=270; //Set Baudrate
IPC3bits.U1TXIP2 = 1; //Set Uart TX Interrupt Priority
IPC3bits.U1TXIP1 = 0;
IPC3bits.U1TXIP0 = 0;
IPC2bits.U1RXIP2 = 1; //Set Uart RX Interrupt Priority
IPC2bits.U1RXIP1 = 0;
IPC2bits.U1RXIP0 = 0;
U1STA = 0;
U1MODE = 0x8000; //Enable Uart for 8-bit data
//no parity, 1 STOP bit
U1STAbits.UTXEN = 1; //Enable Transmit
IEC0bits.U1TXIE = 1; //Enable Transmit Interrupt
IEC0bits.U1RXIE = 1; //Enable Receive Interrupt
}


//------------------------------------------------------------------------------



void initADC(void){
    AD1PCFG = 0; // Configure A/D port
                // all input pins are analog
    AD1CON1 = 0x2208; // Configure sample clock source
                // and conversion trigger mode.
                // Unsigned Fraction format (FORM<1:0>=10),
                // Manual conversion trigger (SSRC<3:0>=000),
                // Manual start of sampling (ASAM=0),
                // No operation in Idle mode (ADSIDL=1).
    AD1CON2 = 0; // Configure A/D voltage reference
                // and buffer fill modes.
                // Vr+ and Vr- from AVdd and AVss (VCFG<2:0>=000),
                // Inputs are not scanned,
                // Interrupt after every sample
    AD1CON3 = 0; // Configure A/D conversion clock as Tcy/2
    AD1CHS = 0; // Configure input channels,
                // CH0+ input is AN0,
                // CH0- input is Vr- (AVss).
    AD1CSSL = 0; // No inputs are scanned.
    IFS0bits.AD1IF = 0; // Clear A/D conversion interrupt.
                        // Configure A/D interrupt priority bits (AD1IP<2:0>) here, if
                        // required. Default priority level is 4.
    IEC0bits.AD1IE = 1; // Enable A/D conversion interrupt
    AD1CON1bits.ADON = 1; // Turn on A/D
    AD1CON1bits.SAMP = 1; // Start sampling the input
    __delay_us(1); // Ensure the correct sampling time has elapsed
            // before starting conversion.
    AD1CON1bits.SAMP = 0; // End A/D sampling and start conversion
                          // Example code for A/D ISR:
//void __attribute__ ((__interrupt__)) _ADC1Interrupt(void)
//{
//IFS0bits.AD1IF = 0;
//}
}

void conversion(void){
    




tempfinal = 0; // clear value
temp = &ADC1BUF0; // initialize ADC1BUF pointer
IFS0bits.AD1IF = 0; // clear ADC interrupt flag
AD1CON1bits.ASAM = 1; // auto start sampling for 31Tad
// then go to conversion
while (AD1CON1bits.DONE=0); // conversion done?
AD1CON1bits.ASAM = 0; // yes then stop sample/convert
tempfinal = temp >> 6; 
//valorbits= ;

// revisar si esta justificado a la izq o derecha, verificar PARA despues desplazar la temp.

  
}
