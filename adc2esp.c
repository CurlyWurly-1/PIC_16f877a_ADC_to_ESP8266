/****************************************************************************************
* Analogue to Digital
****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

const unsigned char TABLE[] = {0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f};
#define AN0 CHS0=CHS1=CHS2=0;

void adc_on();
void adc_off();
void DELAY();                                   //delay
void DELAY1();
void init();                                    //
void seven_seg_display(int x);                  //
void adc_init();                                //adc
char UART_TX_Empty();
char UART_Data_Ready();
char UART_Read();
void UART_init();
void UART_connect();
void UART_Write_Hex(char data);   // You would think these
void UART_Write_Char(int data);   // are the wrong way round!!
void UART_Write_Text(char *text);
void UART_Display(int x);

unsigned int ad_0();                            //adc

 #ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
 #define _XTAL_FREQ 4000000
 #endif


/****************************************************************************
* main
****************************************************************************/
void main()
{
        UART_init();
        UART_connect();
        int result  = 0x00;          		//
        int resulta  = 0x00;          		//
        int resultb  = 0x00;          		//
        int result1 = 0x00;          		//
        int result2 = 0x00;          		//
        int result3 = 0x00;          		//
        int result4 = 0x00;          		//
        int cnt;
        int i;
        init();  				//
	adc_init();
	while (1)                  		//
	{
            for (cnt =600;cnt--;)               //
            {                                   //
                result1 = 0x00;              	//
                result1 = ad_0();

                result2 = 0x00;              	//
                result2 = ad_0();

                result3 = 0x00;              	//
                result3 = ad_0();

                result4 = 0x00;              	//
                result4 = ad_0();

                resulta =  ( result1 + result2 + result3 + result4) / 4;
                result1 = 0x00;              	//
                result1 = ad_0();

                result2 = 0x00;              	//
                result2 = ad_0();

                result3 = 0x00;              	//
                result3 = ad_0();

                result4 = 0x00;              	//
                result4 = ad_0();

                resultb =  ( result1 + result2 + result3 + result4) / 4;
                result  =  ( resulta + resultb ) / 2;
                seven_seg_display(result);      // Send t0 Display
            }
            UART_Display(result);        	// Send out via UART
        }
}

/***************************************************************************
* UART_init()
****************************************************************************/
void UART_init()
{
    TRISC=0xff;
    TXSTA=0x24;
    RCSTA=0x90;
    SPBRG=25;
    GIE=1;
    PEIE=1;
    RCIE=1;
}


/***************************************************************************
* UART_connect()
****************************************************************************/
void UART_connect()
{
    UART_Write_Text("AT\r\n");

    __delay_ms(1000);
    UART_Write_Text("AT+CWMODE=1\r\n");

    __delay_ms(1000);
    UART_Write_Text("AT+CWJAP=\"PUT_YOUR_WIFI_SSID_HERE\",\"PUT_YOUR WIFI_PASSWORD_HERE\"\r\n");
    __delay_ms(7000);
}

/***************************************************************************
* UART_Write_Hex()
****************************************************************************/
void UART_Write_Hex(char data)
{
    while(!TRMT);
    TXREG = data;
}

/***************************************************************************
* UART_Write_Char()
****************************************************************************/
void UART_Write_Char(int data)
{
    while(!TRMT);
    TXREG = data;
}

/***************************************************************************
* UART_Write_text()
****************************************************************************/
void UART_Write_Text(char *text)
{
    int i;
    for(i=0;text[i]!='\0';i++)
        UART_Write_Char(text[i]);
}


/****************************************************************************
* UART_Display
****************************************************************************/
void UART_Display(int x)
{

        int bai, shi, ge, qian, temp;           //
	temp = x;                               //
	qian= temp/1000            + 0x30;
	bai = (temp %1000)  /100   + 0x30;      //
	shi = (temp % 0x64) / 0xa  + 0x30;      //
	ge  = (temp % 0x64) % 0xa  + 0x30;      //

//        UART_Write_Hex(0x0c);   // Clear  Line Feed
//        UART_Write_Hex(0x0e);   // Clear  Line Feed
        UART_Write_Text("AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n");
        __delay_ms(1000);
        UART_Write_Text("AT+CIPSEND=47\r\n");
        __delay_ms(1000);
        UART_Write_Text("GET /update?key=PUT_YOUR API_KEY_HERE&field1=");

        if(qian>0x30)
            UART_Write_Char(qian);
	else
            UART_Write_Char(' ');

	if(bai>0x30)
          UART_Write_Char(bai);
        else
            if(qian>0x30)
                UART_Write_Char(bai);
            else
                UART_Write_Char(' ');

        UART_Write_Char(shi);                   //
        UART_Write_Char('.');                   //
        UART_Write_Char(ge);
        UART_Write_Text("\r\n");
        __delay_ms(1000);

}

/****************************************************************************
* init
****************************************************************************/
void init()
{
	TRISA  = 0X00;                          //
	TRISE  = 0X02;                          //
	TRISD  = 0X00;                          //
	ADCON1 = 0XB0;                          //
	ADCON0 = 0X71;                          //
	DELAY();                                //
	PORTA  = 0x00;                          //
	PORTD  = 0x00;
}

/****************************************************************************
* adc_init
****************************************************************************/
void adc_init()
{
	ADCON1=0X80;                            //
	ADCS1 = 1;                              //FOSC/32
	ADCS0 = 0;
	ADON=1;
	DELAY();                                //
}

/****************************************************************************
* display
****************************************************************************/
void seven_seg_display(int x)
{
	int bai, shi, ge,qian, temp;            //
	temp = x;                               //
	qian= temp/1000;
	bai = (temp %1000)/100;                 //
	shi = (temp % 0x64) / 0xa;              //
	ge = (temp % 0x64) % 0xa;               //

        if(qian>1)
		PORTD = ~0x71;                  //
	else
		PORTD = ~TABLE[qian];           //
	PORTA = ~0x20;                          //
	DELAY1();                               //
        PORTD = ~TABLE[bai];                    //
	PORTA = ~0x10;                          //
	DELAY1();                               //
	PORTD = ~TABLE[shi];                    //
	PORTA = ~0x8;                           //
	DELAY1();                               //
	PORTD = ~TABLE[ge];                     //
	PORTA = ~0x04;                          //
	DELAY1();                               //
        PORTA = 0xff;                           // Switch off
}

/****************************************************************************
* ad_0()
****************************************************************************/
unsigned int ad_0()
{
	unsigned int res;
	adc_on();
	CHS0=0;CHS1=1;CHS2=1;
	DELAY1();                               //
	GO = 1;                                 //
    while (GO);                                 //
	res=ADRESH&0x03;
	res=res<<8|ADRESL;
	adc_off();
	return res ;                            //
}

/****************************************************************************
* DELAY()
****************************************************************************/
void DELAY()                                    //
{
	int i;                                  //
	for (i =10000;i--;);                    //
}

/****************************************************************************
* adc_off()
****************************************************************************/
void adc_off()
{
	ADCON1 = 0X86;                          //1000_0110
	ADON=0;
}

/****************************************************************************
* adc_on()
****************************************************************************/
void adc_on()
{
	ADCON1 = 0X80;                          //1000_0000
	ADON=1;
}

/****************************************************************************
* DELAY1()
****************************************************************************/
void DELAY1()                                   //
{
	int i;                                  //
	for (i =100;i--;);                      //
}


/***************************************************************************
* UART_TX_Empty()
****************************************************************************/
char UART_TX_Empty()
{
    return TRMT;
}

/***************************************************************************
* UART_Data_Ready()
****************************************************************************/
char UART_Data_Ready()
{
   return RCIF;
}

/***************************************************************************
* UART_Read()
****************************************************************************/
char UART_Read()
{
    while(!RCIF);
    return RCREG;
}

/***************************************************************************
* com()
****************************************************************************/
void interrupt com()
{

    unsigned char uart_rd;

    if (UART_Data_Ready()) {     // If data is received,
        uart_rd = UART_Read();     // read the received data,
//      UART_Write(uart_rd);        // and send data via UART
//  	TXREG=RCREG;
 //       UART_Write_Text(ztext_string2);
    }

    if(RCIE&&RCIF)
    {
  	TXREG=RCREG;
        while(!TRMT);
    }

}
