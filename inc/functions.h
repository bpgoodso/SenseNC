#include <stdint.h>
#include "data.h"

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

void Init_UART0(uint32_t baudrate);

void Init_DAC(void);
void SetDAC(double vSet);

//============================
// Buffer Function Definitions
//============================
void ClearBuffer(COMMAND_BUFFER* cb);
void LoadBuffer(COMMAND_BUFFER* cb, char input);
void StoreInBuffer(COMMAND_BUFFER* cb, char input);
void BufferCopy(char* src, char* dest);


//==============================
// Transmit Function Definitions
//==============================
void SendChar(char input);
void SendString(char* string);


//====================================
// Command Decode Function Definitions
//====================================
void ProcessCommand(COMMAND_BUFFER* cb);


//=============================
// Command Function Definitions
//=============================
void SystemStatus(void);


//=============================
// RPM Set Function Definitions
//=============================
double   VSetCalc(uint16_t input);
void     SetPinOut(double vSet);
uint16_t ExtractRPM(COMMAND_BUFFER* cb, uint8_t placecount);


//==========================
// GPIO Function Definitions
//==========================
void Init_GPIO(void);


//===========================
// Timer Function Definitions
//===========================
void Init_PIT(uint32_t period);
void PIT_IRQHandler(void);
void Start_PIT(void);
void Stop_PIT(void);

#endif
