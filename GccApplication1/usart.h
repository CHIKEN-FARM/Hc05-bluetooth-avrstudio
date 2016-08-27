//Micricontroller		:All 8-bit AVR Micricontrollers with Similar Register Configuration with ATmega16
//System Clock			:8 MHz
//Header File Version 		:1.1
//Author			:Arun Kumar Garg 
//				:ABLab Solutions
//				:www.ablab.in
//				:arun@ablab.in
//Date				:1st August 2011

/*Copyright (c) 2011 ABLab Solutions All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 	following disclaimer in the documentation 
     and/or other materials provided with the distribution.
   * Neither the name of the copyright holders nor the names of contributors may be used to endorse or promote products derived from this software without 
     specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */


/*The functions and macros defined in this header file are for USART of all 8-bit AVR Micricontrollers with Similar Register Configuration 
with ATmega 16*/

#ifndef	_USART_H_
#define	_USART_H_ 	1



#include<avr/io.h>
#include<util/delay.h>



/*The function is declared to initialize the USART with following cinfiguration:-
USART mode - Asynchronous
Baud rate - 9600
Data bits - 8
Stop bit - 1
Parity - No parity.*/

//#define BAUD 921600
#define BAUD 9600
//#define MYUBRR F_CPU/16/BAUD-1
#define MYUBRR ((F_CPU)/(BAUD*16UL)-1)    // set baudrate value for UBRR

void usart_init(uint16_t ubrr);




/*The function is declared to transmit data.*/

void usart_data_transmit(unsigned char data );




/*The function is declared to receive data.*/

unsigned char usart_data_receive( void );




/*The function is declared to transmit string.*/

void usart_string_transmit(char *string);




/*The function is declared to receive string.*/

char *usart_string_receive(char *receive_string,unsigned char terminating_character);



/*Function defination*/
/*
void usart_init()
{
UBRRH = 0;
UBRRL =51;
UCSRB|= (1<<RXEN)|(1<<TXEN);
UCSRC |= (1 << URSEL)|(3<<UCSZ0);
}

*/

void usart_init( uint16_t ubrr) {
    // Set baud rate
    UBRRH = (uint8_t)(ubrr>>8);
    UBRRL = (uint8_t)ubrr;
    // Enable receiver and transmitter
    UCSRB = (1<<RXEN)|(1<<TXEN);
    // Set frame format: 0stop bit, 8data
    //UCSRC = (1<<URSEL)|(3<<UCSZ0);//|(0<<USBS);
	//UCSRC &= ~(1 << USBS); //clears the USBS for 1 stop bit, only needed if the bit was already set 
	 UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);// 8bit data format
	 //sei();
}
/*
volatile char REC;
ISR(USART_RXC_vect){
REC = UDR;
}
*/
void usart_data_transmit(unsigned char data )
{
while ( !( UCSRA & (1<<UDRE)) )
;
UDR = data;
_delay_ms(1);
}

unsigned char usart_data_receive( void )
{
while ( !(UCSRA & (1<<RXC)) )
;
return UDR;
}

void usart_string_transmit(char *string)
{
while(*string)
{
usart_data_transmit(*string++);
}
}

char *usart_string_receive(char *receive_string,unsigned char terminating_character)
{
	unsigned char temp=0x00;
	for(unsigned char i=0;;i++)
	{
		*(receive_string+i)=usart_data_receive();
		if(*(receive_string+i)==terminating_character)
			break;
		else
		temp++;
	}
	*(receive_string+temp)='\0';
	return receive_string;
}
#endif
