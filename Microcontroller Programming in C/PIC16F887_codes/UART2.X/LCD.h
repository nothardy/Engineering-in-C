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

void Comando(char valor)
{
PORTE=valor;   
RS=0;
RW=0;
E=1;
__delay_us(1);
E=0;
__delay_ms(10);
}
void envio(unsigned char entrada)
{
    RS=1;
    RW=0;
    PORTE=entrada;
    __delay_ms(1);
    E=1;
    __delay_ms(2);
    E=0;
}

void bajar(void)
{
    __delay_ms(2);
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
    __delay_ms(2);
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
    //subir();
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
    //bajar();
    Comando(0xC0);
    Comando(0xC0);
    __delay_ms(2);
    while(*p2!=0)
    {
        letraenvio = *p2;
        envio(letraenvio);
        p2++;
    }
    //subir();
    Comando(0x80);
    Comando(0x80);
    
}

void limpiarLCD (void){
    __delay_ms(2);
    RS=0;
    RW=0;
    PORTE=0x0001;
    __delay_ms(1);
    E=1;
    __delay_us(2);
    E=0;
}

void INICLcd(void)
{
 unsigned int i;
// TRISBbits.TRISB15=0;
// TRISDbits.TRISD4=0;
// TRISDbits.TRISD5=0;
// TRISE=0;
 for(i=0; i<3;i++)
 {
     PORTE=0x30;
     RS=0;
     RW=0;
     E=1;
    __delay_us(1);
    E=0;
    __delay_ms(500);
 }
//Comando(0x38);
//Comando(0x0c);
//Comando(0x06);
//Comando(0x80);
 
 Comando(0x3C);
 Comando(0x0C);
 Comando(0x01);
 Comando(0x06);
}

