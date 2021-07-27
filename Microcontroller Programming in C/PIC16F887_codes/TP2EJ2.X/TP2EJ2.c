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



int renglon=1,A=0,B=0,C=0,D=0,D1=0,D2=0,D3=0,D4=0;   
unsigned char titulo1[16]="INT. CLAVE ", titulo2[16]="CAMBIAR CLAVE", titulo3[16]="INT. CLAVE <",titulo4[16]="CAMBIAR CLAVE";

unsigned char clave[16], clavelista=0, salir1=0,salir2=0,salir3=0,salir4=0,salir5=0;
void CambiarClave(void);
void IntroClave(void);
void ClaveCheck(void);
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
    TRISDbits.TRISD7=1;
    TRISDbits.TRISD6=1;
    TRISDbits.TRISD13=1;
    TRISAbits.TRISA7=1;
    TRISAbits.TRISA0=0;
    TRISAbits.TRISA1=0;
    TRISAbits.TRISA2=0;
    TRISAbits.TRISA3=0;
    TRISAbits.TRISA4=0;
    TRISAbits.TRISA5=0;
    TRISAbits.TRISA6=0;
    inicializacion();
    LCD(&titulo3);
    LCD2(&titulo4);
    while(1)
    {
        if (p2==0)
        {
           __delay_ms(20);
           if (p2==0)
           {                
                while (p2==0); // pongo ; y no llaves porque no hay nada adentro
                __delay_ms(20);
                if (p2==1)
                {
                if(renglon==2)
                {
                renglon=1;
                sprintf(titulo4,"CAMBIAR CLAVE");
                sprintf(titulo3,"INT. CLAVE <");
                Limpiardisplay();
                LCD(&titulo3);
                LCD2(&titulo4);
                }
                else
                {
                renglon=2;
                sprintf(titulo3,"INT. CLAVE  ");
                sprintf(titulo4,"CAMBIAR CLAVE <");
                Limpiardisplay();
                LCD(&titulo3);
                LCD2(&titulo4);
                }                       
                }
           }
        }
        if (p1==0)
        {
           __delay_ms(20);
           if (p1==0)
           {                
                while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                __delay_ms(20);
                if (p1==1)
                {
                    if(renglon==2)
                    {
                        CambiarClave();
                        Limpiardisplay();
                        LCD(&titulo3);
                        LCD2(&titulo4);
                    }
                    else
                {
                    IntroClave();
                    LCD(&titulo3);
                    LCD2(&titulo4);
                } 
                }
                                       
            }
        }
    }
}

void CambiarClave(void)
{
    ClaveCheck();
    Limpiardisplay();
    sprintf(clave,"0 < 0  0  0");
    LCD(&clave);
    sprintf(titulo1,"INT. NUEVA CLAVE");
    LCD2(&titulo1);
    A=0;
        B=0;
        C=0;
        D=0;
        while(salir1==0)
        {
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        A=A+1;
                        if(A>9)
                    {
                        A=0;
                    }
                        sprintf(clave,"%u < %u  %u  %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    A=A-1;
                    if(A<0)
                    {
                        A=9;
                    }
                    sprintf(clave,"%u < %u  %u  %u",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir1=1;
                        Limpiardisplay();
                        sprintf(clave,"%u  %u < %u  %u",A,B,C,D);
                        
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
        }
        while(salir2==0)
        {
            salir1=0;
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        B=B+1;
                        if(B>9)
                    {
                        B=0;
                    }
                        sprintf(clave,"%u  %u < %u  %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    B=B-1;
                    if(B<0)
                    {
                        B=9;
                    }
                    sprintf(clave,"%u  %u < %u  %u",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir2=1;
                        sprintf(clave,"%u  %u  %u < %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
        }
        while(salir3==0)
        {
            salir2=0;
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        C++;
                        if(C>9)
                    {
                        C=0;
                    }
                        sprintf(clave,"%u  %u  %u < %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    C--;
                    if(C<0)
                    {
                        C=9;
                    }
                    sprintf(clave,"%u  %u  %u < %u",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir3=1;
                        sprintf(clave,"%u  %u  %u  %u <",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
        }
        while(salir4==0)
        {
            salir3=0;
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        D++;
                        if(D>9)
                    {
                        D=0;
                    }
                        sprintf(clave,"%u  %u  %u  %u <",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    D--;
                    if(D<0)
                    {
                        D=9;
                    }
                    sprintf(clave,"%u  %u  %u  %u <",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir4=1;
                    }
                }
            }
           clavelista=1; 
        }
        salir4=0;
    if(clavelista==1)
    {
        clavelista=0;
        D1=A;
        D2=B;
        D3=C;
        D4=D;
        unsigned char msjexito[16]="CLAVE GUARDADA";
        sprintf(clave,"%u %u %u %u",D1,D2,D3,D4);
        Limpiardisplay();
        LCD(&msjexito);
        LCD2(&clave);
        __delay_ms(2000);
        Limpiardisplay();
    }
}
    
    


void IntroClave(void)
{
    ClaveCheck();
    Limpiardisplay();
    unsigned char msjexito1[16]="CERRADURA";
    unsigned char msjexito2[16]="ABIERTA";
    LCD(&msjexito1);
    LCD2(&msjexito2);
    led0=1;
    led1=1;
    led2=1;
    led3=1;
    led4=1;
    led5=1;
    led6=1;
    salir5=0;
    while(salir5==0)
    {
        if (p2==0)
            {
                __delay_ms(20);
                if (p2==0)
                {                
                    while (p2==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p2==1)
                    {
                        salir5=1;
                        led0=0;
                        led1=0;
                        led2=0;
                        led3=0;
                        led4=0;
                        led5=0;
                        led6=0;
                        Limpiardisplay();
                    }
                }
            }
    }

    
}

void ClaveCheck(void)
{
    unsigned char claveok=0;
    Limpiardisplay();
    sprintf(clave,"0 < 0  0  0");
    LCD(&clave);
    sprintf(titulo1,"INT. CLAVE");
    LCD2(&titulo1);
    while(claveok==0)
    {
        
        A=0;
        B=0;
        C=0;
        D=0;
        while(salir1==0)
        {
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        A=A+1;
                        if(A>9)
                    {
                        A=0;
                    }
                        sprintf(clave,"%u < %u  %u  %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    A=A-1;
                    if(A<0)
                    {
                        A=9;
                    }
                    sprintf(clave,"%u < %u  %u  %u",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir1=1;
                        sprintf(clave,"%u  %u < %u  %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
        }
        while(salir2==0)
        {
            salir1=0;
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        B=B+1;
                        if(B>9)
                    {
                        B=0;
                    }
                        sprintf(clave,"%u  %u < %u  %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    B=B-1;
                    if(B<0)
                    {
                        B=9;
                    }
                    sprintf(clave,"%u  %u < %u  %u",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir2=1;
                        sprintf(clave,"%u  %u  %u < %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
        }
        while(salir3==0)
        {
            salir2=0;
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        C++;
                        if(C>9)
                    {
                        C=0;
                    }
                        sprintf(clave,"%u  %u  %u < %u",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    C--;
                    if(C<0)
                    {
                        C=9;
                    }
                    sprintf(clave,"%u  %u  %u < %u",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir3=1;
                        sprintf(clave,"%u  %u  %u  %u <",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
        }
        while(salir4==0)
        {
            salir3=0;
            if (p3==0)
            {
                __delay_ms(20);
                if (p3==0)
                {                
                    while (p3==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p3==1)
                    {
                        D++;
                        if(D>9)
                    {
                        D=0;
                    }
                        sprintf(clave,"%u  %u  %u  %u <",A,B,C,D);
                        Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p4==0)
            {
                __delay_ms(20);
                if (p4==0)
                {                
                    while (p4==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p4==1)
                    {
                    D--;
                    if(D<0)
                    {
                        D=9;
                    }
                    sprintf(clave,"%u  %u  %u  %u <",A,B,C,D);
                    Limpiardisplay();
                        LCD(&clave);
                        LCD2(&titulo1);
                    }
                }
            }
            if (p1==0)
            {
                __delay_ms(20);
                if (p1==0)
                {                
                    while (p1==0); // pongo ; y no llaves porque no hay nada adentro
                    __delay_ms(20);
                    if (p1==1)
                    {
                        salir4=1;
                    }
                }
            }
        }
        salir4=0;
        if(A==D1 && B==D2 && C==D3 && D==D4)
        {
            claveok=1;
            Limpiardisplay();
            unsigned char msjexito[16]="CLAVE CORRECTA";
            LCD(&msjexito);
            __delay_ms(1000);
            Limpiardisplay();
            sprintf(clave,"0 < 0  0  0");
            LCD(&clave);
            LCD2(&titulo1);
        }
        if(claveok==0)
        {
            unsigned char msjerror[16]="CLAVE INCORRECTA";
            Limpiardisplay();
            LCD(&msjerror);
            unsigned char msjerror2[16]="INTENTE DE NUEVO";
            LCD2(&msjerror2);
            __delay_ms(1000);
            Limpiardisplay();
            sprintf(clave,"0 < 0  0  0");
            LCD(&clave);
            LCD2(&titulo1);
        }
    }
}


