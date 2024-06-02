#ifndef SYSTEM_H
#define SYSTEM_H

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


namespace sys {

typedef enum {
	RES_TIMEOUT	= -3,
	RES_BUSY	= -2,
	RES_ERROR	= -1,
	RES_NONE	= 0,
	RES_OK		= 1,
} result_t;

typedef void (*callback_t)(void *context);


}



#endif /* SYSTEM_H */