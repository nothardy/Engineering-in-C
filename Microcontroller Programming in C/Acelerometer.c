/* 
 * File:   Acelerometro.c
 * Author: xavi
 *
 * Created on 4 de diciembre de 2018, 15:51
 */

#include <p33FJ128GP202.h>
//#include <p33FJ16GP304.h>
#define FCY 40000000UL//
#define BAUDRATE 19200
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>

#define bandera IFS1bits.MI2C1IF
//#define banderassp I2C1STATbits.RBF
#define slaveACK I2C1STATbits.ACKSTAT
#define ACK I2C1CONbits.ACKDT
#define recepcion I2C1CONbits.RCEN
#define habilitadorACK I2CCONbits.ACKEN


_FICD(ICS_PGD1 & JTAGEN_OFF); // Para hacer debuging por el puerto 2
_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);
#pragma config ALTI2C=ON // uso los pines alternativos de i2c



unsigned char Estado=0, whoami=0;


//prototipo de funciones

void configI2C(void);
void configES(void);
void configUART(void);
void I2C(void);
void envioUART(void);

void main() 
{
    configES();
    configI2C();
    configUART();
    envioUART();
    I2C();
    while(1)
    {
        
        
        //I2C();
//        switch (Estado)
//        {
//            case ;
//        }
    }
}

void configI2C(void)
{
    //configuro I2C1CON
    I2C1CONbits.I2CEN=1; // prendo i2c y uso sda y scl
    I2C1CONbits.I2CSIDL=0; // sigue funcionando en espera
    //I2C1CONbits.SCLREL=1; se usa en caso de ser esclavo
    I2C1CONbits.IPMIEN=0; // no uso el IMPI
    //I2C1CONbits.A10M=1; SE USA EN CASO DE ESCLAVO
    I2C1CONbits.DISSLW=1; // DESABILITO EL SLEW RATE CONTROL
    I2C1CONbits.SMEN=0; // DESABILITO LOS UMBRALES DE LOS PINES I/O
    //I2C1CONbits.GCEN=1; se usa si sos esclavo
    //I2C1CONbits.STREN=1; se usa si sos esclavo
    
    //I2C1CONbits.ACKDT=1; se usa en la comunicacion
    //I2C1CONbits.ACKEN=1;se usa en la comunicacion
    //I2C1CONbits.RCEN=0;se usa en la comunicacion
    //I2C1CONbits.PEN=1; se usa en la comunicaicon
    //I2C1CONbits.RSEN=1; se usa en la comunicacion
    //I2C1CONbits.SEN=1; se usa en la comunicacion
    I2C1BRG=0x5d;
}

void configUART(void)
{
    OSCCON = 0x46;			// Command Sequence- Registro de control del oscilador
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 0;		// Peripherial pin select is not locked
    //remapeo de pines
    
   //RECEPTOR
    RPINR18bits.U1RXR4=0; //remapea a rp8
    RPINR18bits.U1RXR3=1;
    RPINR18bits.U1RXR2=0;
    RPINR18bits.U1RXR1=0;
    RPINR18bits.U1RXR0=0;
    
    //TRANSMISOR
    RPOR3bits.RP7R4=0;
    RPOR3bits.RP7R3=0;
    RPOR3bits.RP7R2=0;
    RPOR3bits.RP7R1=1;
    RPOR3bits.RP7R0=1;
    
    OSCCON = 0x46;			// Command Sequence- Registro de control del oscilador
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 1;		// Peripherial pin select is not locked
    //configuro el registro U1MODE
    U1MODEbits.UARTEN=1; // prendo el modulo
    U1MODEbits.USIDL=0; // continua funcionando en modo espera
    U1MODEbits.IREN=0; // IrDA desactivado
    //U1MODEbits.RTSMD=0; lo dejo en default por ahora
    U1MODEbits.UEN1=0;
    U1MODEbits.UEN0=0; // solo uso tx y rx
    //U1MODEbits.WAKE=0; no lo uso por ahora
    //U1MODEbits.LPBACK=0; por ahora no uso el loopback
    U1MODEbits.ABAUD=0; //lo dejo por defecto
    U1MODEbits.URXINV=1; //idle state es 0
    U1MODEbits.BRGH=0; //MODO STANDARD DE VELOCIDAD
    U1MODEbits.PDSEL1=0;
    U1MODEbits.PDSEL0=0; // byte de datos de 8 bits, sin paridad
    U1MODEbits.STSEL=0; // un bit de stop
    
    //CONFIGURO EL REGISTRO U1STA
    U1STAbits.UTXISEL1=0;
    U1STAbits.UTXISEL0=0; //son de interrupciones, no lo uso
    U1STAbits.UTXINV=1; // espera del tx es cero
    U1STAbits.UTXBRK=0; // deshabilito  el sync break
    U1STAbits.UTXEN=1; //habilito el tx
//    U1STAbits.URXISEL1=1; no lo uso porque es para interrupcion
//    U1STAbits.URXISEL0=0;
    U1STAbits.ADDEN=0; //modo deteccion de direccion desacctivado
    //U1BRG=(((FCY/BAUDRATE)/16)-1); //129,20
    U1BRG=129;
    __delay_ms(60);
    IFS0bits.U1TXIF=0;
    
}

void configES(void)
{
    // Configure Oscillator to operate the device at 40 MHz
    // Fosc = Fin * M/(N1 * N2), Fcy = Fosc/2
    // Fosc = 8M * 40/(2 * 2) = 80 MHz for 8M input clock

    PLLFBD = 40; 			    // M = 40
    CLKDIVbits.PLLPOST = 0;		// N2 = 2
    CLKDIVbits.PLLPRE = 0; 		// N1 = 2
    __builtin_write_OSCCONH(0x03);	// Initiate Clock Switch to Primary Oscillator with PLL (NOSC = 0b011)
    __builtin_write_OSCCONL(0x01);
    while(OSCCONbits.COSC != 0b011);// Wait for Clock switch to occur
    while(OSCCONbits.LOCK != 1){};	// Wait for PLL to lock
    

    
//    _RB5=1; //pin sda alternativo
//    _RB6=1; // pin scl alternativo
//    _RB7=1;
//    _RB8=0;
    AD1PCFGL=0xFFFF;
    TRISBbits.TRISB5=1;
    TRISBbits.TRISB6=1;
    TRISBbits.TRISB7=0;
    TRISBbits.TRISB8=1;
     
}

void I2C(void)
{
    //comienza protocolo I2C para adquirir temperatura
            I2C1CONbits.SEN=1; // comienzo la comunicacion
            while(I2C1CONbits.SEN==1);
            bandera=0;
            slaveACK=1;
            I2C1TRN=0x0D; // direccion DEL WHO AM I
            while(bandera==0); //espero que se levante, cuando se levanta, es que se termino de enviar el dato
            bandera=0;
            while(slaveACK==1); // verifico que el nACK sea 1
            recepcion=1;
            while(bandera==0); // se pone a cero automaticamente cuando termina de recibir todo el dato el bufer
            bandera=0;
            whoami=I2C1RCV;
            habilitadorACK=1;
            ACK=1;
            while(habilitadorACK==1);
            I2C1CONbits.PEN=1;
            while(I2C1CONbits.PEN==1);
}

void envioUART(void)
{
    U1TXREG=0x22;
    while (U1STAbits.UTXBF==1);
    U1TXREG=0x19;
    while(U1STAbits.UTXBF==1);
}