
#include "uart_driver.h"
#include "avr/delay.h"
#include "MOTOR.h"

void appCallBack(uint8_t u8DataReceived);

int main(void)
{
Disable_Interrupts();
// not to interrupt initialization
UART_Init(9600,appCallBack);
// send baud rate and call back fn
Enable_Interrupts();
// enable interrupts again after initialization
UART_Write_String("AT+RST\r\n");
// A command to reset WIFI module
_delay_ms(1000);
UART_Write_String("AT+CWMODE_DEF=2\r\n");
// A command to set MODE of WIFI module as an access point (AP)
_delay_ms(1000);
UART_Write_String("AT+CWSAP_DEF=\"Yaakoub_WIFI\",\"12345678\",5,3\r\n");
// A command to  set SSID(LAN Name) , Password, channel and security
_delay_ms(1000);
UART_Write_String("AT+CIBMUX=1\r\n");
// A command to allow a multiple connections to AP
_delay_ms(1000);
UART_Write_String("AT+CIPSERVER=1,1234\r\n");
// A command to set port number
_delay_ms(1000);


while (1)
{

}


}

/*
 * function name :
 *
 *
 *
 *
 * */

void appCallBack(uint8_t u8DataReceived)   // call back fn
{


	if(u8DataReceived=='f'||u8DataReceived=='F') // car move forward
	{
		motor_On(RIGHT_MOTOR,FORWARD);
		motor_On(LEFT_MOTOR,FORWARD);

	}
	else if(u8DataReceived=='B'||u8DataReceived=='b') //car move backward
	{
		motor_On(RIGHT_MOTOR,BACKWARD);
		motor_On(LEFT_MOTOR,BACKWARD);
	}
	else if(u8DataReceived=='r'||u8DataReceived=='R')// car move right
	{
		motor_On(LEFT_MOTOR,FORWARD);
		motor_Off(RIGHT_MOTOR);
	}
	else if(u8DataReceived=='L'||u8DataReceived=='l') // car move left
	{
		motor_Off(LEFT_MOTOR);
		motor_On(RIGHT_MOTOR,FORWARD);
	}
	else if (u8DataReceived=='s'||u8DataReceived=='S') // car stop
	{
		motor_Off(RIGHT_MOTOR);
		motor_Off(LEFT_MOTOR);
	}
}
