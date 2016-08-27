//**************************************************************//
//Microcontroller			:ATmega16
//System Clock				:8MHz
//Project					:Password Protected HC-05 Bluetooth based Android Mobile Controlled Wireless Robot with ATmega16
//Software					:ATmel Studio 6
//USART Baud Rate			:9600
//USART Data Bits			:8
//USART Stop Bits			:1
//USART Mode				:Asynchronous Mode
//USART Parity				:No Parity
//Author					:Arun Kumar Garg
//							:ABLab Solutions
//							:www.ablab.in
//							:info@ablab.in
//Date						:1st June 2015
//**************************************************************//

#include<avr/io.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/
/*
#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
*/

#ifndef F_CPU
//#define F_CPU 8000000   // 8 MHz clock speed
#define F_CPU 11059200UL // 8 MHz clock speed
//#define F_CPU 16000000UL // 16 MHz clock speed
#endif

/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#include "hc05.h"
/*Includes hc05.h header file which defines different functions for HC-05 Bluetooth Module. HC-05 header file version is 1.1*/

//----------------------------------------------------------------
/*
#define D4 eS_PORTC4
#define D5 eS_PORTC5
#define D6 eS_PORTC6
#define D7 eS_PORTC7
#define RS eS_PORTC2
#define EN eS_PORTC3

#define D4 eS_PORTC2
#define D5 eS_PORTC3
#define D6 eS_PORTC4
#define D7 eS_PORTC5
#define RS eS_PORTC0
#define EN eS_PORTC1
*/
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTB0
#define EN eS_PORTB2

#include "lcd.h" //Can be download from the bottom of this article
void usart_pstr (char *s);
void usart_putchar( char data );
/*
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include <util/delay.h>

void uart_init(uint32_t baudrate, uint8_t double_speed) {
    uint16_t ubrr = 0;
    if (double_speed) {
        UCSR0A = _BV(U2X0);  //Enable 2x speed
        ubrr = (F_CPU / (8UL * baudrate)) - 1;
    } else {
        ubrr = (F_CPU / (16UL * baudrate)) - 1;
    }
    UBRR0H = ubrr >> 8;
    UBRR0L = ubrr;

    UCSR0C &= ~(_BV(UMSEL01) | _BV(UMSEL00)); // enable asynchronous USART
    UCSR0C &= ~(_BV(UPM01) | _BV(UPM00)); // disable parity mode
    UCSR0C &= ~_BV(USBS0); // set 1-bit stop
    UCSR0C &= ~_BV(UCSZ02); 
    UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00); // set 8-bit data

    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // Enable RX and TX 
}


uint8_t uart_getchar() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void uart_read_line(uint8_t *value, uint8_t size) {
    for (uint8_t i = 0; i < size; i++) {
        value[i] = uart_getchar();
        if (value[i] == '\r') {
            value[i] = '\0';
            break;
        }
    }
}

void uart_putchar(const uint8_t data) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}


void uart_print(const char *value) {
    while (*value != '\0') {
        uart_putchar(*value++);
    }
}
*/
char 														Ctemp[10];
//char *receive_string2;
void usart_pstr(char *s) {
    // loop through entire string
    while (*s) {
    usart_putchar(*s);
    s++;
    }
}
void usart_putchar(char data) {
    // Wait for empty transmit buffer
    while ( !(UCSRA & (_BV(UDRE))) );
    // Start transmission
    UDR = data;
}

int main(void)
{
	//DDRB=0x0f;
	DDRB=0xff;
	DDRC = 0xFF;
	/*PB0,PB1,PB2 and PB3 pins of PortB are declared output ( i/p1,i/p2,i/p3,i/p4 pins of DC Motor Driver are connected )*/
	
	 char password_entered[5],password_set[5]="1234";
	unsigned char received_data;
	unsigned char count=0,status=0;
	unsigned char receive_string2,receive_string3;
	char buffer[6];
	char txt[10];
	int i;
	Lcd4_Init();
	Lcd4_Set_Cursor(1,1);
	//while(0==0)
	//{
	Lcd4_Write_String("LCD_Initial") ;
	//}	
	/*Variable declaration */
	delay_ms(500);
    //delay_ms(500);
	
	
	//uart_init(38400, 1);
    //sei();

    //uart_print("AT+NAME=BLUES\r\n");
    //_delay_ms(1000);

    //uart_print("AT+PSWD=7515\r\n");
    //_delay_ms(1000);

    //uart_print("AT+UART=38400,1,0\r\n");
    //_delay_ms(1000);

	//usart_init();
	usart_init(MYUBRR);
	//usart_pstr("Ready to rock and roll!\n\r");
	/*
	while(1)
	
	{
		Lcd4_Init();
		usart_string_receive(receive_string3,"\n");
		i = atoi(receive_string3);
		Lcd4_Set_Cursor(2,1);
		Lcd4_Write_String(i) ;
	}	
	
	
	while(1)
	
	{	
		//usart_pstr("Hi");
		//*(receive_string2)=usart_data_receive();
		receive_string2=usart_data_receive();
		 //if(!(strcmp(receive_string2,"")))
			//{
				//usart_string_transmit("ff");
				//*(receive_string2)=usart_data_receive();
				usart_string_transmit(receive_string2);
				sprintf(Ctemp,":%c",receive_string2);
				itoa(receive_string2,buffer,10);                  // convert numerals into string
				//_delay_ms(100);
				Lcd4_Clear();
				Lcd4_Set_Cursor(1,1);
				Lcd4_Write_String("Usart:") ;
				Lcd4_Set_Cursor(2,1);
				Lcd4_Write_String(Ctemp) ;
				Lcd4_Set_Cursor(2,6);
				Lcd4_Write_String(buffer) ;
				
				Lcd4_Set_Cursor(2,10);
				Lcd4_Write_String(receive_string2) ;
				
				//sprintf(txt,"code:%s",buffer);
				i = atoi(buffer);
				sprintf(txt,"code:%d",i);
				Lcd4_Set_Cursor(1,8);
				Lcd4_Write_String(i) ;
				//_delay_ms(100);
			//}				
	}	
	*/
	//usart_string_transmit("AT+UART=9600,1,0");
	/*USART initialization*/
	//while(0==0)
	//{
	hc_05_bluetooth_transmit_string("ABLab Solutions");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("www.ablab.in");
	/*Transmits a string to Bluetooth Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/
	
	hc_05_bluetooth_transmit_string("Enter Password:");
	/*Transmits a string to Bluetooth Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/
	//}	
	status=1;
	/*Password status loop(Entered password is right or wrong)*/
	while(status==0)
	{
		/*Password entry loop*/
		while(count<4)
		{
			received_data=hc_05_bluetooth_receive_byte();
			/*Microcontroller receives data from Bluetooth Module */
			Lcd4_Clear();
			Lcd4_Set_Cursor(1,1);
			//while(0==0)
			//{
			itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);
			Lcd4_Write_String(i) ;
			delay_ms(100);
			
			Lcd4_Set_Cursor(2,1);
		    sprintf(Ctemp,":%s",received_data);
		    Lcd4_Write_String(Ctemp) ;
			//Lcd4_Write_String(received_data) ;

			password_entered[count]=received_data;
			/*Inserting the usart(Bluetooth) received data into the password_entered array*/

			count++;
			/*Incrementing the counter variable*/
		}

		count=0;
		/*Counter variable is reset to zero*/
		
		hc_05_bluetooth_transmit_byte(0x0d);
		/*Transmits Carriage return to Bluetooth Module*/
		
		hc_05_bluetooth_transmit_byte(0x0a);
		/*Transmits New Line to Bluetooth Module for new line*/

		password_entered[4]='\0';
		/*Adding null character at the end of the password_entered array*/

		/*Comparing entered password with set password*/
		if(!(strcmp(password_entered,password_set)))
		{
			status=1;
			/*Entered password is right*/

			hc_05_bluetooth_transmit_string("Correct Password");
			/*Transmits a string to Bluetooth Module*/

			hc_05_bluetooth_transmit_byte(0x0d);
			/*Transmits Carriage return to Bluetooth Module*/
			
			hc_05_bluetooth_transmit_byte(0x0a);
			/*Transmits New Line to Bluetooth Module for new line*/
		}
		else
		{
			hc_05_bluetooth_transmit_string("Wrong Password");
			/*Transmits a string to Bluetooth Module*/

			status=0;
			/*Entered password is wrong*/

			hc_05_bluetooth_transmit_byte(0x0d);
			/*Transmits Carriage return to Bluetooth Module*/
			
			hc_05_bluetooth_transmit_byte(0x0a);
			/*Transmits New Line to Bluetooth Module for new line*/

			hc_05_bluetooth_transmit_string("Re-enter Password:");
			/*Transmits a string to Bluetooth Module*/
		}
	}
	
	hc_05_bluetooth_transmit_string("Control Keys for Robot:");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/
	
	hc_05_bluetooth_transmit_string("F or f=Forward");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("B or b=Backward");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("L or l f= Left");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("R or r=Right");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/

	hc_05_bluetooth_transmit_string("S or s=Stop");
	/*Transmits a string to Bluetooth of Module*/

	hc_05_bluetooth_transmit_byte(0x0d);
	/*Transmits Carriage return to Bluetooth Module*/
	
	hc_05_bluetooth_transmit_byte(0x0a);
	/*Transmits New Line to Bluetooth Module for new line*/
	
	/*Start of infinite loop*/
	while(1)
	{
		received_data=hc_05_bluetooth_receive_byte();
		/*Microcontroller will receive a character from Bluetooth Module*/
		Lcd4_Clear();
		
		Lcd4_Set_Cursor(1,1);
		itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);			
			Lcd4_Write_String(i) ;
			delay_ms(100);

		Lcd4_Set_Cursor(2,1);
		sprintf(Ctemp,"is:%s",received_data);
		Lcd4_Write_String("Rec:") ;
		Lcd4_Set_Cursor(2,5);
		Lcd4_Write_String(received_data) ;
		
		
		//while(0==0)
		//{
			
		/*Checking the pressed key value to move the robot in different direction*/
		if(received_data == 'F' || received_data == 'f')
		{
			PORTB=0x0A;
			/*Robot will move forward direction*/

			hc_05_bluetooth_transmit_string("Moving Forward");
			Lcd4_Clear();
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String("Moving Forward") ;
		    
			
			Lcd4_Set_Cursor(2,1);
			sprintf(Ctemp,"is:%c",received_data);
			Lcd4_Write_String("Rec:") ;
			Lcd4_Set_Cursor(2,5);
			Lcd4_Write_Char(Ctemp) ;
			
			Lcd4_Set_Cursor(2,7);
			Lcd4_Write_String(Ctemp) ;
			
			
			Lcd4_Set_Cursor(2,10);
			itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);			
			Lcd4_Write_String(i) ;
			//delay_ms(100);
		
			
			
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'B' || received_data == 'b')
		{
			PORTB=0x05;
			/*Robot will move backward direction*/

			hc_05_bluetooth_transmit_string("Moving Backward");
			Lcd4_Clear();
		    Lcd4_Set_Cursor(1,1);
			
			itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);			
			Lcd4_Write_String(received_data) ;
			
			Lcd4_Set_Cursor(1,10);
			Lcd4_Write_Char(received_data) ;
			delay_ms(100);
			
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("Moving Backward") ;
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'L' || received_data == 'l')
		{
			PORTB=0x02;
			/*Robot will move towards left direction*/

			hc_05_bluetooth_transmit_string("Moving Left");
			Lcd4_Init();
		    Lcd4_Set_Cursor(2,1);
			sprintf(Ctemp,"is:%c",received_data);
			Lcd4_Write_String("Rec:") ;
			Lcd4_Set_Cursor(2,5);
			Lcd4_Write_Char(Ctemp) ;
			
			Lcd4_Set_Cursor(2,7);
			Lcd4_Write_String(Ctemp) ;
			
			Lcd4_Set_Cursor(1,1);
			Lcd4_Write_String("Moving Left") ;
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'R' || received_data == 'r')
		{
			PORTB=0x08;
			/*Robot will move towards right direction*/

			hc_05_bluetooth_transmit_string("Moving Right");
			Lcd4_Init();
		    Lcd4_Set_Cursor(1,1);
			
			itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);			
			Lcd4_Write_String(i) ;
			delay_ms(100);
			
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("Moving Right") ;
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'S' || received_data == 's')
		{
			PORTB=0x0f;
			/*Robot will stop*/

			hc_05_bluetooth_transmit_string("Stopped");
			Lcd4_Init();
		    Lcd4_Set_Cursor(1,1);
			
			itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);			
			Lcd4_Write_String(i) ;
			delay_ms(100);
			
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("Stopped") ;
			/*Transmits a string to Bluetooth of Module*/
		}
		else
		{
			hc_05_bluetooth_transmit_string("Invalid Key");
			Lcd4_Init();
		    Lcd4_Set_Cursor(1,1);
			
			itoa(received_data,buffer,10);                  // convert numerals into string
			i = atoi(buffer);			
			Lcd4_Write_String(i) ;
			delay_ms(100);
			
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String("Invalid Key") ;
			/*Transmits a string to Bluetooth of Module*/
		}

		hc_05_bluetooth_transmit_byte(0x0d);
		/*Transmits Carriage return to Bluetooth Module*/
		
		hc_05_bluetooth_transmit_byte(0x0a);
		/*Transmits New Line to Bluetooth Module for new line*/
	}
}
/*End of program*/


