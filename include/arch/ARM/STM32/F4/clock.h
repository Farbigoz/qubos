#ifndef STM32F4_CLOCK_H
#define STM32F4_CLOCK_H

#include "system/interface/clock.h"


namespace arch {
class clock : virtual public sys::clock {
public:
	clock(volatile uint32_t& reg, uint32_t bit)
	:
	reg(reg),
	bit(bit)
	{}

// Interface sys::clock
public:
	uint32_t get_clock_freq() override {
		return 0;	// todo
	}

	sys::result_t enable_clock() override {
		__IO uint32_t tmpreg = 0x00U;
		SET_BIT(reg, bit);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(reg, bit);
		(void)(tmpreg);

		return sys::RES_OK;
	}

	sys::result_t disable_clock() override {
		CLEAR_BIT(reg, bit);
		return sys::RES_OK;
	}

private:
	volatile uint32_t& reg;
	uint32_t bit;
};
}


#endif /* STM32F4_CLOCK_H */