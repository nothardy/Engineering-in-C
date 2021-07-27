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

#define banderarx PIR1bits.RCIF
#define clear PORTBbits.RB7

unsigned char Banderaconv=0,banderaadquirido=0,Contador=0,linea=1,dato,escritura[40],valormedido[35];
int adc,valor1=0,valor2=0,unitemp=0,dectemp=0,centemp=0;
float temp;
//prototipo de funciones
void InitES();
void InitUSART();
void InitTMR1(void);
void Adquisicion();
void correccion();


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
            Banderaconv=1;
        }
    }
}

void main (void)
{
    InitES();
    InitTMR1();
    InitUSART();
    unsigned int i=0;
    
    sprintf(escritura," Grupo 3 Sensor de Temperatura Canal 0 \r\n");
    for(i=0;i<41;i++)
       {
            TXREG=escritura[i];
            while(PIR1bits.TXIF==0);
            __delay_ms(20);
            
       }
    TXREG=0X0D;
    while(PIR1bits.TXIF==0);
    TXREG=0X0D;
    while(PIR1bits.TXIF==0);
    TXREG=0X20;
    while(PIR1bits.TXIF==0);
    
    while(1)
    {
        
            if(banderaadquirido==1)
            {
                correccion();
                if(temp<0)
                {
                    sprintf(valormedido,"FUERA DE RANGO");
                    for(i=0;i<14;i++)
                        {
                            TXREG=valormedido[i];
                            while(PIR1bits.TXIF==0);
                            while(TXSTAbits.TRMT==0);
                            
                        }
                    
                }
                else
                    {  
                        sprintf(valormedido, "%3i,%1i%1i        ",unitemp,dectemp,centemp);
                        for(i=0;i<14;i++)
                            {
                                TXREG=valormedido[i];
                                while(PIR1bits.TXIF==0);
                                __delay_ms(20);
                            }
                        
                    }
                
                valor1=1;
                banderaadquirido=0;
            }
            if(Banderaconv==1)
            {
                ADCON0bits.GO_DONE=1;
                while(ADCON0bits.GO_DONE==1);
                Banderaconv=0;
                Adquisicion();
            }
        
    }
    
}


void InitES()
{
    ANSEL=0b00000001;
    ANSELH=0;
    TRISB=0b00000000; // cambiar para el clear
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    TRISA=0b00000001;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON1bits.ADFM=1;
    ADCON0=0b10000001;
    PORTA=0;
    
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
void InitUSART()
{
    /*TXSTA=0b00101110; //se configura com asincrona, de 8 bits,se habilita la transimision, velocidad alta
    RCSTA=0b10010000; //se configura habilitaion del modulo usart, recepcion, recepcion de 8 bits
    SPBRG=129;*/ // SPBRG=(Foscilador/153600)-1 = (20000000/153600)-1= 129,20=129
    TXSTAbits.SYNC=0;
    RCSTAbits.SPEN=1;
    TXSTAbits.BRGH=1;
    BAUDCTLbits.BRG16=1;
    SPBRG=0x08;
    SPBRGH=0x02;
    TXSTAbits.TXEN=1;
    
}

void Adquisicion(void)
{
    adc=ADRESH;
    adc=adc<<8;
    adc=adc+ADRESL;
    temp=(125/1023.0)*adc-25.0;
    unitemp=temp;
    dectemp=(temp-unitemp)*10;
    centemp=(temp-unitemp-dectemp/10)*100;
    banderaadquirido=1;
}

void correccion()
{
    int i=0;
    if(valor1==1)
        {
            for(i=0;i<14;i++)
                {
                    TXREG=0X08;
                    while(PIR1bits.TXIF==0);
                    while(TXSTAbits.TRMT==0);
                
                }
        }   
}