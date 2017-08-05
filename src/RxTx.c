#include <MKL25Z4.h>
#include <stdint.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern uint8_t g_TxRxFlag;

void SendChar(char input)
{
	if(!(UART0->C2 & UART_C2_TIE_MASK))
	{
		UART0->C2 |= UART_C2_TIE_MASK;
		UART0->D   = input;
	}
	
	return;
}

void SendString(char* string)
{
	uint16_t i = 0x0000;
	
	Start_PIT(); // Add to eliminate stomping message strings
	
	while((string[i] != 0x00) && (i < BUFFER_SIZE))
	{
		if(g_TxRxFlag & TRANSMIT_FLAG)
		{
			SendChar(string[i++]);
			
			g_TxRxFlag &= ~TRANSMIT_FLAG;
		}
	}
	
	Stop_PIT();
	
	return;
}
