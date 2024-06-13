#ifndef SYSTEM_INTERFACE_SYS_TIM_H
#define SYSTEM_INTERFACE_SYS_TIM_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"


namespace sys {
// Допустим только один системный таймер

class sys_tim : public periphery_with_irq {
public:
	typedef Signal<sys_tim&> signal_irq_t;

public:
	virtual sys::result_t init(uint32_t mks) = 0;

	virtual sys::result_t set_period(uint32_t p) = 0;

	virtual uint32_t get_period() = 0;
	virtual uint32_t get_cnt() = 0;
	virtual uint32_t get_period_mks() = 0;

public:
	signal_irq_t signal_irq;

protected:
	sys_tim()
	{}
};
}


#endif /* SYSTEM_INTERFACE_SYS_TIM_H */