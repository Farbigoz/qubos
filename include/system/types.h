#ifndef SYSTEM_TYPES_H
#define SYSTEM_TYPES_H

#include "stdint.h"
#include "stdbool.h"
#include "stddef.h"


namespace sys {

	typedef enum RESULT_T {
		RES_UNEXPECTED	= -1000,
		RES_NO_SYS_TIM,
		RES_TIMEOUT,
		RES_BUSY,
		RES_NOT_ENABLED,
		RES_ERROR,
		RES_NONE		= 0,
		RES_OK
	} result_t;

	typedef void (*callback_t)(void *context);

	typedef uint64_t time_msk_t;
	typedef uint64_t time_ms_t;

}



#endif /* SYSTEM_TYPES_H */