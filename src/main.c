#include <MKL25Z4.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

#define DEATH_LASER_ACTIVE (0) // WARNING: DO NOT ENABLE

COMMAND_BUFFER g_CmdBuffer;

uint16_t g_RPMValue;
char     g_RPMString[6];

uint8_t  g_TxRxFlag;
uint8_t  g_SystemControlReg;

void main(void)
{	
	ClearBuffer(&g_CmdBuffer);
	
	g_TxRxFlag        = 0x00;
	g_SystemControlReg = 0x00;
	
	g_RPMString[0] = '0';
	g_RPMString[5] = '\0';
	
	__disable_irq();
	
	Init_UART0(SYS_BAUDRATE);
	Init_PIT(PIT_PERIOD);
	Init_DAC();
	Init_GPIO();
	
	__enable_irq();
	
	SendString("SENSUS CONTROL v0.1a\n\n\r> ");
	
	while(1)
	{
		if(g_CmdBuffer.state == READY)
		{
			ProcessCommand(&g_CmdBuffer);
		}
	}
}
