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

#define	F_CPU	8000000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#include "hc05.h"
/*Includes hc05.h header file which defines different functions for HC-05 Bluetooth Module. HC-05 header file version is 1.1*/


int main(void)
{
	DDRB=0x0f;
	/*PB0,PB1,PB2 and PB3 pins of PortB are declared output ( i/p1,i/p2,i/p3,i/p4 pins of DC Motor Driver are connected )*/
	
	char received_data,password_entered[5],password_set[5]="1234";
	unsigned char count=0,status=0;
	/*Variable declaration */
	
	usart_init();
	/*USART initialization*/
	
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
	
	/*Password status loop(Entered password is right or wrong)*/
	while(status==0)
	{
		/*Password entry loop*/
		while(count<4)
		{
			received_data=hc_05_bluetooth_receive_byte();
			/*Microcontroller receives data from Bluetooth Module */

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
		
		/*Checking the pressed key value to move the robot in different direction*/
		if(received_data == 'F' || received_data == 'f')
		{
			PORTB=0x0A;
			/*Robot will move forward direction*/

			hc_05_bluetooth_transmit_string("Moving Forward");
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'B' || received_data == 'b')
		{
			PORTB=0x05;
			/*Robot will move backward direction*/

			hc_05_bluetooth_transmit_string("Moving Backward");
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'L' || received_data == 'l')
		{
			PORTB=0x02;
			/*Robot will move towards left direction*/

			hc_05_bluetooth_transmit_string("Moving Left");
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'R' || received_data == 'r')
		{
			PORTB=0x08;
			/*Robot will move towards right direction*/

			hc_05_bluetooth_transmit_string("Moving Right");
			/*Transmits a string to Bluetooth of Module*/
		}
		else if(received_data == 'S' || received_data == 's')
		{
			PORTB=0x0f;
			/*Robot will stop*/

			hc_05_bluetooth_transmit_string("Stopped");
			/*Transmits a string to Bluetooth of Module*/
		}
		else
		{
			hc_05_bluetooth_transmit_string("Invalid Key");
			/*Transmits a string to Bluetooth of Module*/
		}

		hc_05_bluetooth_transmit_byte(0x0d);
		/*Transmits Carriage return to Bluetooth Module*/
		
		hc_05_bluetooth_transmit_byte(0x0a);
		/*Transmits New Line to Bluetooth Module for new line*/
	}
}
/*End of program*/


