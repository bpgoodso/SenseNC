#include <MKL25Z4.h>
#include <stdint.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern char g_RPMString[6];

uint16_t ExtractRPM(COMMAND_BUFFER* cb, uint8_t placecount)
{
	uint8_t i;
	uint16_t rpmValue;
	
	rpmValue = 0;
	
	for(i = 2; placecount != 0; placecount--, i++)
	{
		switch(placecount)
		{
			case 5:
			{
				rpmValue += ((cb->buffer[i] = 0x30) * 10000);
				
				break;
			}
			
			case 4:
			{
				rpmValue += ((cb->buffer[i] - 0x30) * 1000);
				
				break;
			}
			
			case 3:
			{
				rpmValue += ((cb->buffer[i] - 0x30) * 100);
				
				break;
			}
			
			case 2:
			{
				rpmValue += ((cb->buffer[i] - 0x30) * 10);
				
				break;
			}
			
			case 1:
			{
				rpmValue += (cb->buffer[i] - 0x30);
				
				break;
			}
			
			default:
			{
				break;
			}
		}
		
		g_RPMString[i-2] = cb->buffer[i];
		
	}
	
	// Clear trailing digits from previous inputs
	i-= 2;
	
	while(i < 6)
	{
		g_RPMString[i++] = '\0';
	}
	
	return rpmValue;	
}
