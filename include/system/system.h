#ifndef SYSTEM_H
#define SYSTEM_H

#include "system/types.h"
#include "system/interface/sys_tim.h"


namespace sys {
	sys::result_t set_sys_timer(sys::sys_tim &st);

	bool has_sys_timer();

	time_ms_t time_ms();
	time_msk_t time_mks();
}



#endif /* SYSTEM_H */