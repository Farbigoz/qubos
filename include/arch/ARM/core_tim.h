#ifndef ARM_SYS_TIM_H
#define ARM_SYS_TIM_H

#include "system/types.h"
#include "system/interface/sys_tim.h"
#include "arch/ARM/irq.h"

// need previous include "core_cmX.h" and "rcc.h"
// example: "impl/STM32/F1/sys_tim.h"


namespace arch {
class core_tim : public sys::sys_tim {
public:
	core_tim() {
		arch::irq::get_irq_signal(SysTick_IRQn).connect(
				irq_slot,
				[](void *ctx) {
					auto inst = reinterpret_cast<arch::core_tim*>(ctx);
					inst->signal_irq.emit(*inst);
				},
				this
		);
	}

// clock
public:
	uint32_t get_clock_freq() override {
		//return rcc::CORTEX_TIM_CLK::calc_clk();
		return impl::rcc::CORTEX_TIM_CLK::CLK_FREQ;
	}

	sys::result_t enable_clock() override {
		return sys::RES_OK;
	}

	sys::result_t disable_clock() override {
		return sys::RES_ERROR;
	}

// periphery
public:
	sys::result_t deinit() override {
		// todo
		return sys::RES_OK;
	}

	sys::result_t set_irq_prior(uint32_t prior) override {
		return arch::irq::set_irq_prior(SysTick_IRQn, prior);
	}

	uint32_t get_irq_prior() override {
		return arch::irq::get_irq_prior(SysTick_IRQn);
	}

	bool irq_enabled() override {
		return arch::irq::is_enabled(SysTick_IRQn);
	}

	sys::result_t enable_irq() override {
		SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
		return arch::irq::enable_irq(SysTick_IRQn);
	}

	sys::result_t disable_irq() override {
		CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
		return arch::irq::disable_irq(SysTick_IRQn);
	}

// sys_tim
public:
	sys::result_t init(uint32_t mks) override {
		uint64_t period = ((uint64_t)get_clock_freq() * (uint64_t)mks) / 1000000UL;
		return set_period(period);
	}

	sys::result_t set_period(uint32_t p) override {
		if ((p - 1UL) > SysTick_LOAD_RELOAD_Msk)
			return sys::RES_ERROR;

		uint32_t int_bit = READ_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
		CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);

		SysTick->LOAD = p - 1UL;
		SysTick->VAL = 0UL;

		SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | int_bit);

		return sys::RES_OK;
	}

	uint32_t get_period() override {
		return SysTick->LOAD;
	}

	uint32_t get_cnt() override {
		return SysTick->VAL;
	}

	uint32_t get_period_mks() override {
		//return (1000000 * (SysTick->LOAD + 1)) / get_clock_freq();
		return (uint32_t)(((float)(SysTick->LOAD + 1) / (float)get_clock_freq()) * 1000000.0f);
	}

private:
	arch::irq::irq_signal_t::SlotWithCtx irq_slot;
};
}


#endif /* ARM_SYS_TIM_H */