/* 
 * File:   Acelerometro2.c
 * Author: xavi
 *
 * Created on 14 de diciembre de 2018, 09:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <P33FJ128MC202.h>
//#include <p33FJ16GP304.h>
#define FCY 40000000UL//
#include <libpic30.h>

_FICD(ICS_PGD2 & JTAGEN_OFF); // Para hacer debuging por el puerto 2
_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_XT);
_FWDT(FWDTEN_OFF);
#pragma config ALTI2C=ON // uso los pines alternativos de i2c

//Prototipo de funciones
void ConfigIni(void);
void ConfigES (void);
void ConfigUART(void);
void ConfigI2C(void);
void sendUART(unsigned char enviodato);
unsigned char readUART(void);
void initI2C(void);
void stopI2C(void);
void sendI2C(unsigned char enviodato);
unsigned char readI2C(void);
void restartI2C(void);
void I2C(unsigned char datoenviado);
void multipleI2C(unsigned char datoenviado,unsigned char k);
unsigned char multiplereadI2C(void);




//Variables
unsigned char datoentrada=0;
unsigned char ferr=0,oerr=0;
unsigned char orden=0;
unsigned char datorecibido=0;
unsigned char contador=1;
unsigned char maxX=0,minX=0,maxY=0,minY=0,maxZ=0,minZ=0;
unsigned char vector[100]={'\0'};
unsigned char registro[49]={'\0'};
unsigned char dato=0;
unsigned char bandera=0;
unsigned char datomultiple[20]={'\0'};


void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt()
{ 
    dato=U1RXREG; 
    IFS0bits.U1RXIF = 0;
   
    if (dato==0xFD)
    {
        contador++;
    }
    else if (contador==2)
    {
        vector[0]=dato;
        contador++;
    }
    else if (contador==3)
    {
        vector[1]=dato;
        
        contador++;
        if(vector[0]==0x03)
        {
            bandera=1;
        }
    }
    else if (contador<=(vector[0]-1))
    {
        vector[contador-2]=dato;
        contador++;
        
    }
    else if (contador==vector[0])
    {
        vector[contador-2]=dato;
        bandera=1;
        
    }
}

void main(void) {
    ConfigIni();
    ConfigES();
    ConfigUART();
    ConfigI2C();
    initI2C();
    sendI2C(0x38); // confguro el mma para poder leerlo ma tarde
    sendI2C(0x2A);
    sendI2C(0x01);
    stopI2C();
    
    while(1)
    {
        unsigned char i=0;
        if(bandera==1)
        {
            orden=vector[1];
            switch (orden)
            {
                case 0x41:
                    
                
//                    while(i<=49)
//                    {
//                        I2C(i);
//                        registro[i]=datorecibido;
//                        i++;
//                    }
//                    sendUART(0xFE);
//                    
//                    sendUART(0x34);//cant bytes
//                   
//                    sendUART(0x42);//orden
//                    i=0;
//                    //envio adicionales
//                    while (i<=49)
//                    {
//                        sendUART(registro[i]);
//                        i++;
//                    }
                    // problema: algun problema en recibir alguno de los registros, el codigo no llega al envio final
                    I2C(0x00);
                    registro[0]=datorecibido;
                    __delay_us(40);//
                    I2C(0x01);
                    registro[1]=datorecibido;
                    __delay_us(40);//
                    I2C(0x02);
                    registro[1]=datorecibido;
                    __delay_us(40);//
                    I2C(0x03);
                    registro[3]=datorecibido;
                    __delay_us(40);//
                    I2C(0x04);
                    registro[4]=datorecibido;
                    __delay_us(40);//
                    I2C(0x05);
                    registro[5]=datorecibido;
                    __delay_us(40);//
                    I2C(0x06);
                    registro[6]=datorecibido;
                    __delay_us(40);//
                    I2C(0x07);
                    registro[7]=datorecibido;
                    __delay_us(40);//
                    I2C(0x08);
                    registro[8]=datorecibido;
                    __delay_us(40);//
                    I2C(0x09);
                    registro[9]=datorecibido;
                    __delay_us(40);//
                    I2C(0x0A);
                    registro[10]=datorecibido;
                    __delay_us(40);//
                    I2C(0x0B);
                    registro[11]=datorecibido;
                    __delay_us(40);//
                    I2C(0x0C);
                    registro[12]=datorecibido;
                    __delay_us(40);//
                    I2C(0x0D);
                    registro[13]=datorecibido;
                    __delay_us(40);//
                    I2C(0x0E);
                    registro[14]=datorecibido;
                    __delay_us(40);//
                    I2C(0x0F);
                    registro[15]=datorecibido;
                    __delay_us(40);//
                    I2C(0x10);
                    registro[16]=datorecibido;
                    __delay_us(40);//
                    I2C(0x11);
                    registro[17]=datorecibido;
                    __delay_us(40);//
                    I2C(0x12);
                    registro[18]=datorecibido;
                    __delay_us(40);//
                    I2C(0x13);
                    registro[19]=datorecibido;
                    __delay_us(40);//
                    I2C(0x14);
                    registro[20]=datorecibido;
                    __delay_us(40);//
                    I2C(0x15);
                    registro[21]=datorecibido;
                    __delay_us(40);//
                    I2C(0x16);
                    registro[22]=datorecibido;
                    __delay_us(40);//
                    I2C(0x17);
                    registro[23]=datorecibido;
                    __delay_us(40);//
                    I2C(0x18);
                    registro[24]=datorecibido;
                    __delay_us(40);//
                    I2C(0x019);
                    registro[25]=datorecibido;
                    __delay_us(40);//
                    I2C(0x1A);
                    registro[26]=datorecibido;
                    __delay_us(40);//
                    I2C(0x1B);
                    registro[27]=datorecibido;
                    __delay_us(40);//
                    I2C(0x1C);
                    registro[28]=datorecibido;
                    __delay_us(40);//
                    I2C(0x1D);
                    registro[29]=datorecibido;
                    __delay_us(40);//
                    I2C(0x1E);
                    registro[30]=datorecibido;
                    __delay_us(40);//
                    I2C(0x1F);
                    registro[31]=datorecibido;
                    __delay_us(40);//
                    I2C(0x20);
                    registro[32]=datorecibido;
                    __delay_us(40);//
                    I2C(0x21);
                    registro[33]=datorecibido;
                    __delay_us(40);//
                    I2C(0x22);
                    registro[34]=datorecibido;
                    __delay_us(40);//
                    I2C(0x23);
                    registro[35]=datorecibido;
                    __delay_us(40);//
                    I2C(0x24);
                    registro[36]=datorecibido;
                    __delay_us(40);//
                    I2C(0x25);
                    registro[37]=datorecibido;
                    __delay_us(40);//
                    I2C(0x26);
                    registro[38]=datorecibido;
                    __delay_us(40);//
                    I2C(0x27);
                    registro[39]=datorecibido;
                    __delay_us(40);//
                    I2C(0x28);
                    registro[40]=datorecibido;
                    __delay_us(40);//
                    I2C(0x29);
                    registro[41]=datorecibido;
                    __delay_us(40);//
                    I2C(0x2A);
                    registro[42]=datorecibido;
                    __delay_us(40);//
                    I2C(0x2B);
                    registro[43]=datorecibido;
                    __delay_us(40);//
                    I2C(0x2C);
                    registro[44]=datorecibido;
                    __delay_us(40);//
                    I2C(0x2D);
                    registro[45]=datorecibido;
                    __delay_us(40);//
                    I2C(0x2E);
                    registro[46]=datorecibido;
                    __delay_us(40);//
                    I2C(0x2F);
                    registro[47]=datorecibido;
                    __delay_us(40);//
                    I2C(0x30);
                    registro[48]=datorecibido;
                    __delay_us(40);//
                    I2C(0x31);
                    registro[49]=datorecibido;
                    __delay_us(40);//
                    sendUART(0xFE);
                    
                    sendUART(0x35);//cant bytes 5
                   
                    sendUART(0x41);//orden
                    i=0;
                    while(i<=49)
                    {
                    sendUART(registro[i+1]);
                    i++;
                    }
                    
                    
                    orden=0;
                    bandera=0;
                    contador=1;
                    sprintf(registro, '\0');
                    break;
                case 0x42://recibo aceleraciones
                    
//                    multipleI2C(0x00,6);
//                    sendUART(0xFE);
//                    sendUART(0x09);
//                    sendUART(0x42);
//                    sendUART(datomultiple[2]);
//                    sendUART(datomultiple[3]);//adicionales
//                    sendUART(datomultiple[4]);
//                    sendUART(datomultiple[5]);
//                    sendUART(datomultiple[6]);
//                    sendUART(datomultiple[0]);
                    
                    I2C(0x00);
                    minZ=datorecibido;
                    __delay_us(40);
                    I2C(0x01);
                    __delay_us(40);
                    I2C(0x02);
                    maxX=datorecibido;
                   __delay_us(40); //
                    I2C(0x03);
                    minX=datorecibido;
                    __delay_us(40);//
                    I2C(0x04);
                    maxY=datorecibido;
                    __delay_us(40);//
                    I2C(0x05);
                    minY=datorecibido;
                    __delay_us(40);//
                    I2C(0x06);
                    maxZ=datorecibido;
                    __delay_us(40);
//                    I2C(0x00);
//                    minZ=datorecibido;
                    
                    //envio datos al programa
                    sendUART(0xFE);
                    
                    sendUART(0x09);//cant bytes
                   
                    sendUART(0x42);//orden
                    sendUART(maxX);//adicionales
                    sendUART(minX);
                    sendUART(maxY);
                    sendUART(minY);
                    sendUART(maxZ);
                    sendUART(minZ);
                    orden=0;
                    bandera=0;
                    contador=1;
                    break;
                case 0x47: //prendo led
                    PORTBbits.RB0=1;
                    orden=0;
                    bandera=0;
                    contador=1;
                    break;
                case 0x48://apago led
                    PORTBbits.RB0=0;
                    orden=0;
                    bandera=0;
                    contador=1;
                    break;
                default:
                    orden=0;
                    bandera=0;
                    contador=1;
                    break;
            }
        }    
    }
}

void ConfigIni (void) 
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
    

    OSCCON = 0x46;			// Command Sequence- Registro de control del oscilador
    OSCCON = 0x57;
    OSCCONbits.IOLOCK = 0;		// Peripherial pin select is not locked

}

void ConfigES(void)
{
    ADPCFG = 0xFFFF;
    //AD1PCFGL=0xFFFF;
    //TRISBbits.TRISB5=1; //I2C
    //TRISBbits.TRISB6=1; //I2C
    //TRISBbits.TRISB7=0; //UART
    //TRISBbits.TRISB8=1; //UART
    TRISBbits.TRISB0=0; // LED
}
    
void ConfigUART(void)
{
    //REMAPEO DE PINES
    
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
    
    //Configuración UART
    
    U1BRG=129;
    
    U1MODEbits.PDSEL0 = 0;
    U1MODEbits.PDSEL1 = 0;
    
    U1MODEbits.STSEL = 0;
    U1MODEbits.ABAUD = 0;
    U1MODEbits.BRGH = 0;
    IEC0bits.U1TXIE = 0;
    
    U1STAbits.UTXISEL1 = 1;
    U1STAbits.UTXISEL0 = 0; // LA BANDERA SE LEVANTA CUANDO EL ULTIMO CARACTER SALE DEL TSR
    U1STAbits.URXISEL=0;
    IFS0bits.U1RXIF=0;
    U1MODEbits.UEN=0b00;
    U1MODEbits.UARTEN = 1; // ENABLE
    IEC0bits.U1RXIE=1; //interrupcion por recepcion
    U1STAbits.UTXEN = 1;  // HABILITA TRANSMISION
    __delay_us(60); 
    IFS0bits.U1TXIF = 0;
    IFS0bits.U1RXIF = 0;
}    

void sendUART(unsigned char enviodato)
{
    while(U1STAbits.UTXBF == 1);
    //while(U1STAbits.TRMT == 0);
    U1TXREG = enviodato;
    __delay_ms(1);
    ferr=U1STAbits.FERR;
    oerr=U1STAbits.OERR;
}

unsigned char readUART(void)
{
    unsigned char datorecibido=0;
    while(U1STAbits.URXDA == 0);
    datorecibido=U1RXREG;
    __delay_ms(5);
    return datorecibido;
}

void ConfigI2C(void)
{
    I2C1BRG = 0x5D; // 0x5D
    
    I2C1CONbits.I2CEN = 1;
    
    IFS1bits.SI2C1IF = 0;
    
    //Acelerometro SA0 = 0 entonces codigo de familia = 0x1C
    //I2CADD = 0x1C;
    I2C1CONbits.DISSLW = 1;
    
    I2C1CONbits.IPMIEN = 0;
    
    __delay_ms(10);
    //WAKE UP ACELEROMETRO
    initI2C();
    sendI2C(0x38);
    sendI2C(0x2A);
    sendI2C(0x09);
    stopI2C();
    
}

void initI2C(void)
{
    I2C1CONbits.SEN = 1;    
    while(I2C1CONbits.SEN == 1);
}

void stopI2C(void)
{
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN == 1);
}

void sendI2C(unsigned char enviodato)
{
    IFS1bits.MI2C1IF = 0; //bajo bandera
    I2C1TRN = enviodato; //cargo el bufer con el dato a mandar
    while(I2C1STATbits.ACKSTAT == 1); //espero que baje el ackstat
    while(IFS1bits.MI2C1IF == 1); //
    IFS1bits.MI2C1IF = 0;

    while(I2C1STATbits.TRSTAT == 1); //espero al tr
}

unsigned char readI2C(void)
{
    unsigned char datorecibid;
    
    IFS1bits.MI2C1IF = 0; //bajo bandera
    I2C1CONbits.RCEN = 1; //habilito recepcion
//    while(I2C1CONbits.RCEN = 1);
    while(IFS1bits.MI2C1IF == 1); //espero bandera
    IFS1bits.MI2C1IF = 0; //bajo bandera
    //while (I2C1STATbits.RBF==1); //espero que se vacie
    datorecibid = I2C1RCV; //leo el dato
    
    I2C1CONbits.ACKDT=1; // ACK
    I2CCONbits.ACKEN=1; // habilitador ACK
    while(I2CCONbits.ACKEN == 1);
    
    
    return datorecibid;
}

void restartI2C(void)
{
    I2C1CONbits.RSEN=1;
    while(I2C1CONbits.RSEN==1);
}

void I2C(unsigned char datoenviado)
{
    initI2C();
    sendI2C(0x38); // codigo de familia para decir que envio algo
    sendI2C(datoenviado);
    restartI2C();
    sendI2C(0x39); // codigo de familia para decir que leo
    datorecibido=readI2C();
    stopI2C();
}

void multipleI2C(unsigned char datoenviado, unsigned char k)
{
    unsigned char i=0;
    initI2C();
    sendI2C(0x38); // codigo de familia para decir que envio algo
    sendI2C(datoenviado);
    restartI2C();
    sendI2C(0x39); // codigo de familia para decir que leo
    for(i=0;i<k; i++)
    {
        datomultiple[i]=multiplereadI2C();
        __delay_us(40);
        
    }
    datomultiple[k]=readI2C();
    __delay_us(40);
    stopI2C();
}

unsigned char multiplereadI2C(void)
{
    unsigned char datorecibid;
    
    IFS1bits.MI2C1IF = 0; //bajo bandera
    I2C1CONbits.RCEN = 1; //habilito recepcion
    while(IFS1bits.MI2C1IF == 1); //espero bandera
    IFS1bits.MI2C1IF = 0; //bajo bandera
    //while (I2C1STATbits.RBF==1); //espero que se vacie
    datorecibid = I2C1RCV; //leo el dato
    
    I2C1CONbits.ACKDT=0; // ACK
    I2CCONbits.ACKEN=1; // habilitador ACK
    while(I2CCONbits.ACKEN == 1);
    
    return datorecibid;
}

