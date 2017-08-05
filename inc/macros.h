#ifndef _MACROS_H_
#define _MACROS_H_

//===============
// General Macros
//===============
#define RESET (0)


//==============
// System Macros
//==============
#define SYS_BAUDRATE   (115200)
#define SYS_CLOCKSPEED (48000000)

#define PIT_PERIOD     (2399) //0.00001 seconds * 24MHz - 1


//==============
// Buffer Macros
//==============
#define BUFFER_SIZE (128)

#define WAITING     (0x00)
#define FILLING     (0x01)
#define READY       (0x02)


//========================
// Vset Calculation Macros
//========================
#define RPM_MIN (62)
#define RPM_MAX (10000)


//=======================
// Data Processing Macros
//=======================
#define ISNUMERIC(x) ((48 <= x) && (x <= 57))
#define IS_R(x)      ((x == 'r') || (x == 'R'))
#define IS_S(x)      ((x == 's') || (x == 'S'))
#define IS_L(x)      ((x == 'l') || (x == 'L'))
#define IS_T(x)      ((x == 't') || (x == 'T'))
#define IS_A(x)      ((x == 'a') || (x == 'A'))

#define BMASK (0x80)

#define MASK(x) (1UL << x)


//===========
// DAC Macros
//===========
#define VREF (3.0)
#define L_MASK(x) (0x00FF & x)
#define H_MASK(x) ((0x0F00 & x) >> 8)


//=============
// Tx Rx Macros
//=============
#define TRANSMIT_FLAG (0x01)


//===============================
// System Control Register Macros
//===============================
#define LASER1_STATUS (0x01)
#define LASER2_STATUS (0x02)
#define MOTOR_STATUS  (0x04)


//============
// GPIO Macros
//============
#define L1 (5)  // Laser 1 - Port E-5
#define L2 (4)  // Laser 2 - Port E-4

#define EN (3)  // Motor Enable - Port E-3

#endif
