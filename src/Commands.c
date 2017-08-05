#include <MKL25Z4.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern char g_RPMString[6];
extern uint8_t g_SystemControlReg;

void SystemStatus(void)
{
	SendString("\n\n\r===================");
	SendString("\n\r   SYSTEM STATUS\n\r");
	SendString("===================\n\r");
	
	//============================
	// Motor Status
	//============================
	SendString("\n\r");
	SendString("   MOTOR RPM..");
	
	if(g_SystemControlReg & MOTOR_STATUS)
	{	
		SendString(&g_RPMString[0]);
		SendString("\n\n\r");
	}
	else
	{
		SendString("OFF\n\n\r");
	}
	
	//============================
	// Laser 1 Status
	//============================
	SendString("   DIODE 1....");
	
	if(g_SystemControlReg & LASER1_STATUS)
	{
		SendString("ON\n\r");
	}
	else
	{
		SendString("OFF\n\r");
	}
	
	//============================
	// Laser 2 Status
	//============================
	SendString("   DIODE 2....");
	
	if(g_SystemControlReg & LASER2_STATUS)
	{
		SendString("ON\n\r");
	}
	else
	{
		SendString("OFF\n\r");
	}
	
	SendString("\n\r===================");
	
	return;
}
