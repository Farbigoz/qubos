#ifndef SYSTEM_H
#define SYSTEM_H

#include "system/types.h"
#include "system/interface/sys_tim.h"


namespace sys {
	sys::result_t set_sys_timer(sys::sys_tim &st);
}



#endif /* SYSTEM_H */