#include "system/system.h"

static sys::sys_tim *system_timer = nullptr;


sys::result_t sys::set_sys_timer(sys::sys_tim &st) {
	system_timer = &st;
	return sys::RES_OK;
}