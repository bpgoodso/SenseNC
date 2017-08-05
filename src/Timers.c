#include <MKL25Z4.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern uint8_t g_TxRxFlag;

void Init_PIT(uint32_t period)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
  PIT->MCR |= PIT_MCR_FRZ_MASK;
  
  PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(period);
  PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK;
  
  PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
  
  NVIC_SetPriority(PIT_IRQn, 2);
  NVIC_ClearPendingIRQ(PIT_IRQn);
  NVIC_EnableIRQ(PIT_IRQn);
}

void PIT_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(PIT_IRQn);
  
  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
  
  //ISR WORK
  g_TxRxFlag |= TRANSMIT_FLAG;
}

void Start_PIT(void)
{
  PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PIT(void)
{
  PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}
