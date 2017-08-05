#include <stdint.h>
#include "macros.h"

#ifndef _DATA_H_
#define _DATA_H_

typedef struct
{
	char buffer[(BUFFER_SIZE)];
	uint8_t head;
	
	uint8_t state;
	
}COMMAND_BUFFER;

#endif
