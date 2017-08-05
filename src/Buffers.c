#include <MKL25Z4.h>
#include <stdint.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern uint16_t g_RPMValue;
extern uint8_t  g_SystemControlReg;

extern char     g_RPMString[6];

void LoadBuffer(COMMAND_BUFFER* cb, char input)
{	
	switch(cb->state)
	{
		case WAITING:
		{
			cb->state = FILLING;
		
			StoreInBuffer(cb, input);
			
			break;
		}//============================
		
		case FILLING:
		{
			if(input == 0x0D) // Carriage Return to end terminal command
			{
				cb->state = READY;
			}
			else
			{
				StoreInBuffer(cb, input);
			}
			
			break;
		}//=============================

		default:
		{
			break;
		}
	}
	
	return;
}

void StoreInBuffer(COMMAND_BUFFER* cb, char input)
{
	if((input == 0x7F) || (input == 0x08)) // Backspace clears last input
	{
		if(cb->head > 0)
		{
			cb->buffer[--cb->head] = 0x00;
		}
	}
	
	else
	{
		cb->buffer[cb->head] = input;
	
		if(++cb->head >= BUFFER_SIZE) // Overflow protection
		{
			ClearBuffer(cb);
			cb->head = RESET;
		}
	}
	
	return;
}


void ProcessCommand(COMMAND_BUFFER* cb)
{
	uint8_t i;
	uint8_t rpmPlaceCount;
	
	rpmPlaceCount = RESET;
	
	//============================================
	// Set Motor Speed Command
	//============================================
	if(IS_S(cb->buffer[0]) && IS_S(cb->buffer[1]))
	{
		for(i = 2; (i < BUFFER_SIZE); i++)
		{
			if(cb->buffer[i] == 0x00)
			{ 
				if(rpmPlaceCount == 0)
				{
					// No rpm value provided
					SendString("\n\rERROR: NO RPM VALUE PROVIDED\n\r");
					break;
				}
				else
				{
					// Valid Input
					
					// Pull Speed Value
					g_RPMValue = ExtractRPM(cb, rpmPlaceCount);
					
					// Set Analog Out for motor control
					SetDAC(VSetCalc(g_RPMValue));
					
					// Reset process
					break;
				}
			}
			
			else if(!ISNUMERIC(cb->buffer[i]))
			{
				// Error: Non integer rpm input
				SendString("\n\rERROR: NON INTEGER RPM VALUE PROVIDED\n\r");				
				break;
			}
				
			else
			{				
				rpmPlaceCount++;
			}
		}
			
		ClearBuffer(cb);
		
		SendString("\n\n\r> ");
	}
	
	//=================================================
	// Toggle Laser Output Command
	//=================================================
	else if(IS_S(cb->buffer[0]) && IS_L(cb->buffer[1]))
	{
		if(cb->buffer[2] == '0')
		{
			// Turn Laser Diode Pin Off
			PTE->PCOR = MASK(L1);
			
			g_SystemControlReg &= ~LASER1_STATUS;  // Set status bit 0
			
			ClearBuffer(cb);
		
			SendString("\n\n\r> ");
		}
		else if(cb->buffer[2] == '1')
		{
			// Turn Laser Diode Pin On
			PTE->PSOR = MASK(L1);
			
			g_SystemControlReg |= LASER1_STATUS;  // Set status bit 1
			
			ClearBuffer(cb);
		
			SendString("\n\n\r> ");
		}
		else
		{
			ClearBuffer(cb);
			
			SendString("\n\rERROR: INVALID COMMAND\n\n\r> ");
		}
	}
	
	//==============
	// System Status
	//==============
	else if(IS_S(cb->buffer[0]) && IS_T(cb->buffer[1]) && IS_A(cb->buffer[2]))
	{
		SystemStatus();
		
		ClearBuffer(cb);
		
		SendString("\n\n\r> ");
	}
	
	else
	{
		// Error: Invalid Command
		ClearBuffer(cb);
		
		SendString("\n\rERROR: INVALID COMMAND\n\n\r> ");
	}
		
	return;
}


void ClearBuffer(COMMAND_BUFFER* cb)
{
	uint8_t i;
	
	for(i = RESET; i < BUFFER_SIZE; i++)
	{
		cb->buffer[i] = RESET;
	}
	
	cb->head  = RESET;
	cb->state = WAITING;
	
	return;
}


void BufferCopy(char* src, char* dest)
{
	uint8_t i;
	
	i = RESET;
	
	while((src[i] != '\0') && (i < BUFFER_SIZE))
	{
		dest[i] = src[i];
	}
	
	return;
}
