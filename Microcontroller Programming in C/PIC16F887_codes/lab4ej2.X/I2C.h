#define slaveACK SSPCON2bits.ACKSTAT
#define ACK SSPCON2bits.ACKDT
#define banderassp PIR1bits.SSPIF
#define recepcion SSPCON2bits.RCEN
#define habilitadorACK SSPCON2bits.ACKEN
esperaI2C(void)
{
    while ( (SSPCON2 & 0b00011111) || (SSPSTAT & 0b00000100) ); /*Función de espera: mientras se esté iniciada una comunicación,
                                                                 esté habilitado una recepción, esté habilitado una parada
                                                                 esté habilitado un reinicio de la comunicación, esté iniciada
                                                                 una comunicación o se este transmitiendo, el PIC espera
                                                                 antes de realizar algúna instruccion*/
}
InitCOM(void)
{
    SSPCON2bits.SEN=1; // inicio comunicacion
}
StopCOM(void)
{
    esperaI2C();
    SSPCON2bits.PEN=1;// detengo la comunicacion
}
ResetCOM(void)
{
    esperaI2C();         
    SSPCON2bits.RSEN = 1; //reseteo la comunicación
}

void InitI2C(void)
{
    // CONFIGURACION SSPSTAT
    SSPSTATbits.SMP=1; //velocidad de transmision alta 0, normal 1
    SSPSTATbits.CKE=0; //bus i2c 0, bus smbus 1
    SSPSTATbits.D_A=0; // data-adress para el esclavo 0 direccion, 1 dato
    SSPSTATbits.P=0; // condicion de parada, 0 no, 1 si
    SSPSTATbits.S=0; // condicion de start, 1 se detecto condicion start, 0 no se detecto condicion
    SSPSTATbits.R_W=0; //en el esclavo se hara 1 lectura, 0 escritura
    SSPSTATbits.UA=0; // solo en caso de que la direccion del esclavo sea de 10 bits. en 0 no actualiza, en 1 actualiza
    SSPSTATbits.BF=0; // buferfull, 0 vacio, 1 lleno.
    //CONFIGURACION SSPCON
    SSPCONbits.WCOL=0; // para maestro, 1 se cargaron datos al sspbuf sin las condiciones de i2c; en 0 esta todo ok. Para esclavo, 1 se cargaron datos sin que se haya terminado de trasnsmitir el dato anterior, 0 todo ok.
    SSPCONbits.SSPOV=0; // sobreescrituras, 1 si, 0 no
    SSPCONbits.SSPEN=1; // habilitacion puerto asincrono. 1 habilita el i2c, 0 no habilita.
    SSPCONbits.CKP=0; // mientras esclavo cargue dato en el sspbuf este bit es 0. cuando el dato este para enviar , ckp es 1.
    SSPCONbits.SSPM3=1; // sspm3-sspm0 son 4 bits. indican que modo i2c se utiliza.
    SSPCONbits.SSPM2=0;
    SSPCONbits.SSPM1=0;
    SSPCONbits.SSPM0=0;// 1000 pic sera el maestro
    // CONFIGURACION SSPCON2
    SSPCON2bits.GCEN=0; // sirve cuando el pic es esclavo. 0 si no es esclavo
    SSPCON2bits.ACKSTAT=0; //0 si hay comunicacion y se ha recibido el ack, 1 si no hay comunicacion y  el maestro no ha recibido el ack
    SSPCON2bits.ACKDT=0; //ack del maestro al esclavo, 0 si quiere seguir recibiendo datos, 1 si no quiere recibir mas
    SSPCON2bits.ACKEN=0; // 1 para habilitar envio del bit ackdt, 0 para no enviarlo
    SSPCON2bits.RCEN=0;// 1 habilita la recepcion de datos por parte del micro, 0 no habilita recepcion
    SSPCON2bits.PEN=0; // 1 detiene la comunicacion, se hace 0 solo luego de detener la comunicacion. por defecto sera 0
    SSPCON2bits.RSEN=0; // 1 reinicia la comunicacion, se hace 0 solo luego de reiniciar la comunicacion. por defecto sera 0
    SSPCON2bits.SEN=0; // 1 inicia la comunicacion, luego se hace solo 0. para iniciar se pone en 1.
    //CONGIGURACION DE VELOCIDAD
    SSPADD=49; // SSPADD=(20000000/(4*100000))-1   velocidad de 100kbps
    //CONFIGURACION TERMOMETRO
    InitCOM();
    while(SSPCON2bits.SEN==1);
    SSPBUF= 0b10010000; // adress byte indicando que el termometro sera escrito.
    //while(SSPSTATbits.BF==1); //espero que se baje, cuando se baje, es que se termino de enviar el dato
    __delay_ms(1); // lo puse por un warning en proteus
    while(slaveACK==0);
    SSPBUF=0b00000001; // pointer seteado en configuration register
   //while(SSPSTATbits.BF==1); //espero que se baje, cuando se baje, es que se termino de enviar el dato
    __delay_ms(1); // lo puse por un warning en proteus
    while(slaveACK==0);
    SSPBUF=0;// configuration register del termo seteado.
    //while(SSPSTATbits.BF==1); //espero que se baje, cuando se baje, es que se termino de enviar el dato
    __delay_ms(1); // lo puse porque no estaba recibiendo el nACK
    while(slaveACK==0);
    ACK=1;
    StopCOM();
    __delay_ms(1); // lo puse porque en I2C Debugger del proteus no me aparecia la P al final de cada conversacion.
    //copy data desde sram hasta eeprom ¿es necesario?
    InitCOM();
    while(SSPCON2bits.SEN==1);
    SSPBUF= 10010000;
    __delay_ms(1);
    while(slaveACK==0);
    SSPBUF=0x48;
    StopCOM();
    __delay_ms(1);
    //indico que voy a leer temperatura luego
    InitCOM();
    while(SSPCON2bits.SEN==1);
    SSPBUF= 10010000; // indico que voy a realizar lecturas.
    __delay_ms(1);
    while(slaveACK==0);
    SSPBUF=0; //seteo el pointer a temperatura
    StopCOM();
    __delay_ms(1);
}

