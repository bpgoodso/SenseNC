#include <MKL25Z4.h>
#include <stdint.h>
#include "functions.h"
#include "macros.h"
#include "data.h"

extern COMMAND_BUFFER g_CmdBuffer;

void Init_UART0(uint32_t baudrate)
{
	int clockspeed = SYS_CLOCKSPEED; // 48MHz
  
  uint32_t osr = 15;
  uint16_t sbr;
  uint8_t  temp;
  
  SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
  
  UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;
  
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
  SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
  
  PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
  PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
  
  sbr = (uint16_t)((clockspeed)/(baudrate * osr + 1));
  temp = UART0->BDH & ~(UART0_BDH_SBR(0x1F));
  
  UART0->BDH = temp | UART_BDH_SBR(((sbr & 0x1F00) >> 8));
  UART0->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);
  UART0->C4 |= UART0_C4_OSR(osr);
  
  UART0->C1  = 0;
  UART0->C3 |= 0;
  UART0->MA1 = 0;
  UART0->MA2 = 0;
  UART0->S1 |= 0X00;
  UART0->S2  = 0X00;
  UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK;
  
  NVIC_SetPriority(UART0_IRQn, 2);
  NVIC_ClearPendingIRQ(UART0_IRQn);
  NVIC_EnableIRQ(UART0_IRQn);

  UART0->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK;
	
	return;	
}

void UART0_IRQHandler(void)
{
	char charIn;
  
  NVIC_ClearPendingIRQ(UART0_IRQn);
  
  if(UART0->S1 & UART_S1_TDRE_MASK)  // Transmit Interrupt
  {
    UART0->C2 &= ~UART_C2_TIE_MASK;
  }
  
  if(UART0->S1 & UART_S1_RDRF_MASK) // Recieve Interrupt
  {
    charIn = UART0->D;
		
		if(charIn != 0x00)
		{
			LoadBuffer(&g_CmdBuffer, charIn);
		}
		
		SendChar(charIn);
  }
}
