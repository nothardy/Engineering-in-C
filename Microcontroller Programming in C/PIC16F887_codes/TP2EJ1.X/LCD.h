/*
** LCD.h
**
*/
#include <xc.h>
#include <libpic30.h>       // se necesita para "__delay_ms()"

/*#define LCDDATA 1
#define LCDCMD  0
#define PMDATA  PMDIN1

void InitLCD( void);
char ReadLCD( int addr);

#define BusyLCD() ReadLCD( LCDCMD) & 0x80
#define AddrLCD() ReadLCD( LCDCMD) & 0x7F
#define getLCD()  ReadLCD( LCDDATA)


void WriteLCD( int addr, char c);

#define putLCD( d)  WriteLCD( LCDDATA, (d))
#define CmdLCD( c)  WriteLCD( LCDCMD, (c))

#define HomeLCD()   WriteLCD( LCDCMD, 2)
#define ClrLCD()    WriteLCD( LCDCMD, 1)
#define SetLCDG( a) WriteLCD( LCDCMD, (a & 0x3F) | 0x80)//Fila 1
#define SetLCDC( a) WriteLCD( LCDCMD, (a & 0x3F) | 0xC0)//Fila 2

void putsLCD( char *s);
 * */

//----------------------------------------------------------------

#define RS PORTBbits.RB15
#define RW PORTDbits.RD5
#define E PORTDbits.RD4
#define DB0 PORTEbits.RE0
#define DB1 PORTEbits.RE1
#define DB2 PORTEbits.RE2
#define DB3 PORTEbits.RE3
#define DB4 PORTEbits.RE4
#define DB5 PORTEbits.RE5
#define DB6 PORTEbits.RE6
#define DB7 PORTEbits.RE7



void envio(unsigned char entrada)
{
    RS=1;
    RW=0;
    PORTE= entrada & 0x00FF;
    __delay_ms(1);
    E=1;
    __delay_us(2);
    E=0;
}

void inicializacion(void) //modificar para que sea con 8 bits
{    __delay_ms(30);
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=1;
    DB4=1;
    DB3=1;
    DB2=0;
    DB1=0;
    DB0=0;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
    __delay_us(48);
    //------------------------// 100us o más
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    DB3=1;
    DB2=1;
    DB1=0;
    DB0=0;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
    __delay_us(48);
    //-------------
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    DB3=0;
    DB2=0;
    DB1=0;
    DB0=1;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
    __delay_ms(1.6);
    //---------------
    RS=0;
    RW=0;
    DB7=0;
    DB6=0;
    DB5=0;
    DB4=0;
    DB3=0;
    DB2=1;
    DB1=1;
    DB0=0;
    E=1;
    __delay_ms(5);
    E=0;
    __delay_ms(5);
    __delay_ms(1.6);
}


void bajar(void)
{
    RW=0;
    RS=0;
    DB7=1;
    DB6=1;
    DB5=0;
    DB4=0;
    DB3=0;
    DB2=0;
    DB1=0;
    DB0=0;
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
    DB3=0;
    DB2=0;
    DB1=0;
    DB0=0;
    E=1;
    __delay_ms(5);
    E=0;
}

void LCD(unsigned char *p1)
{
    unsigned char letraenvio=0;
    while(*p1!=0)
    {
        letraenvio = *p1;
        envio(letraenvio);
        p1++;
    }
}

void LCD2(unsigned char *p2)
{
    unsigned char letraenvio=0;
    bajar();
    while(*p2!=0)
    {
        letraenvio = *p2;
        envio(letraenvio);
        p2++;
    }
    subir();
}
