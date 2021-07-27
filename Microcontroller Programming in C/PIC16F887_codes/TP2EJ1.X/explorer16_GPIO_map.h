// Placa experimental Explorer 16
// Definición de Pulsadores y LEDs:

//MICRO = PIC24FJ128GA010
#define S4 PORTDbits.RD13       // Explorer 16 pulsador s4 (pulsador ubicado a la derecha)
#define S5 PORTAbits.RA7        // Explorer 16 pulsador s5
#define S6 PORTDbits.RD7        // Explorer 16 pulsador s6
#define S3 PORTDbits.RD6        // Explorer 16 pulsador s3 (pulsador ubicado a la izquierda)
#define LED_D3 LATAbits.LATA0   // Explorer 16 LED D3 (Led ubicado a la derecha)
#define LED_D4 LATAbits.LATA1   // Explorer 16 LED D4
#define LED_D5 LATAbits.LATA2   // Explorer 16 LED D5
#define LED_D6 LATAbits.LATA3   // Explorer 16 LED D6
#define LED_D7 LATAbits.LATA4   // Explorer 16 LED D7
#define LED_D8 LATAbits.LATA5   // Explorer 16 LED D8
#define LED_D9 LATAbits.LATA6  // Explorer 16 LED D9
#define LED_D10 LATAbits.LATA7  // Explorer 16 LED D10 (Led ubicado a la izquierda)
