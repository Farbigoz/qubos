#ifndef SYSTEM_INTERFACE_TIM_H
#define SYSTEM_INTERFACE_TIM_H

#include "system/types.h"
#include "system/interface/periphery.h"

namespace sys {
	class itim : public periphery_with_irq {
	public:
		typedef enum COUNTER_MODE_T {
			CNT_MODE_UP,
			CNT_MODE_DOWN,
			CNT_MODE_CENTER_ALIGNED
		} counter_mode_t;

	public:
		virtual result_t init(counter_mode_t) = 0;

		virtual result_t set_freq(uint32_t) = 0;
		virtual result_t set_period(uint32_t) = 0;
		virtual result_t set_prescaler(uint32_t) = 0;

		virtual uint32_t get_freq() = 0;
		virtual uint32_t get_period() = 0;
		virtual uint32_t get_prescaler() = 0;
		virtual uint32_t get_counter() = 0;
		virtual uint32_t get_clock_freq() = 0;

		virtual result_t start() = 0;
		virtual result_t stop() = 0;

	protected:
		itim() {}
	};
}

#endif /* SYSTEM_INTERFACE_TIM_H */