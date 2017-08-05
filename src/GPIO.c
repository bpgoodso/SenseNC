#include <MKL25Z4.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

void Init_GPIO(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// Initialize Pins for GPIO
	PORTE->PCR[L1] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[L2] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[EN] &= ~PORT_PCR_MUX_MASK;

	PORTE->PCR[L1] |= PORT_PCR_MUX(1);
	PORTE->PCR[L2] |= PORT_PCR_MUX(1);
	PORTE->PCR[EN] |= PORT_PCR_MUX(1);
	
	// Set Ports to Outputs
	PTE->PDDR |= (MASK(L1) | MASK(L2) | MASK(EN));
	
	// Initialize Signals Low
	PTE->PCOR = MASK(L1);
	PTE->PCOR = MASK(L2);
	PTE->PCOR = MASK(EN);
	
	return;
}
