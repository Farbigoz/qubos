#include "system/system.h"

static sys::sys_tim *p_system_timer = nullptr;
static sys::sys_tim::signal_irq_t::Slot system_timer_slot;

static volatile uint64_t time_mks_cnt = 0;
uint32_t tmp = 0;

static void sys_tim_slot_fn(sys::sys_tim& st) {
	tmp = st.get_cnt();
	time_mks_cnt += st.get_period_mks();
	tmp = st.get_cnt();
	tmp++;
}


sys::result_t sys::set_sys_timer(sys::sys_tim &st) {
	if (p_system_timer != nullptr) {
		p_system_timer->signal_irq.disconnect(system_timer_slot);
	}

	p_system_timer = &st;
	p_system_timer->signal_irq.connect(system_timer_slot, sys_tim_slot_fn);

	return sys::RES_OK;
}

bool sys::has_sys_timer() {
	return p_system_timer != nullptr;
}

uint64_t sys::time_mks() {
	return time_mks_cnt;
}

uint64_t sys::time_ms() {
	return time_mks_cnt / 1000;
}
