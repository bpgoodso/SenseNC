#include <MKL25Z4.h>
#include <stdint.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern uint8_t g_SystemControlReg;

void Init_DAC(void)
{
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	
	DAC0_C0 |= DAC_C0_DACEN_MASK;     // Enable DAC
	
	DAC0_C0 &= ~DAC_C0_DACRFS_MASK;   // Reference to VREFH
	
	DAC0_C0 |= DAC_C0_DACTRGSEL_MASK; // Software Trigger
	DAC0_C0 &= ~DAC_C0_LPEN_MASK;     // High Power Mode
	DAC0_C0 &= ~DAC_C0_DACBTIEN_MASK; // Buffer Reader Pointer Top Flag Interrupt Disabled
	DAC0_C0 &= ~DAC_C0_DACBBIEN_MASK; // Buffer Reader Pointer Bottom Flag Interrupt Disabled
	
	DAC0_C1 &= ~DAC_C1_DMAEN_MASK;    // DMA Disabled
	DAC0_C1 &= ~DAC_C1_DACBFMD_MASK;  // Normal Buffer Work Mode
	DAC0_C1 &= ~DAC_C1_DACBFEN_MASK;  // Buffer Disabled
	
	DAC0_DAT0L = L_MASK(0x0000);
	DAC0_DAT0H = H_MASK(0x0000);
	
	return;
}


double VSetCalc(uint16_t input)
{
	double vSet;
	
	//=========================================
	// Overflow and Minimum Setpoint Protection
	//=========================================
	if(input > RPM_MAX)
	{
		input = RPM_MAX;
	}
	else if(input < RPM_MIN)
	{
		input = 0;
	}
	
	//==========================================
	// Motor Controller Vset based on data sheet
	//==========================================
	if(input == 0)
	{
		vSet = 0.0;
		
		PTE->PCOR = MASK(EN);                 // Motor Controller Enable Pin Set LOW
		
		g_SystemControlReg &= ~MOTOR_STATUS;  // Set status bit 0
	}
	else
	{
		vSet = ((((double)input - RPM_MIN)/(RPM_MAX - RPM_MIN)) * 4.9) + 0.1;
		
		PTE->PSOR = MASK(EN);                // Motor Controller Enable Pin Set HIGH
		
		g_SystemControlReg |= MOTOR_STATUS;  // Set status bit 1
	}
	
	return vSet;
}


void SetDAC(double vSet)
{
	uint16_t controlreg;
	
	controlreg = ((vSet * 4096)/ VREF) - 1;
	
	if(controlreg > 4095)
	{
		controlreg = 4095;
	}
	
	DAC0_DAT0L = L_MASK(controlreg);
	DAC0_DAT0H = H_MASK(controlreg);
		
	return;
}
