#ifndef ARM_IRQ_H
#define ARM_IRQ_H

#include "system/interface/periphery.h"

namespace arch {
	class periphery_with_irq_impl : virtual public sys::periphery_with_irq {
	public:
		static inline const uint32_t MAX_IRQ_PRIOR = (1 << __NVIC_PRIO_BITS) - 1;

	public:
		virtual IRQn_Type get_irq_type() = 0;

	public:
		sys::result_t set_irq_prior(uint32_t prior) override {
			if (prior > MAX_IRQ_PRIOR)
				return sys::RES_ERROR;

			uint32_t prioritygroup = NVIC_GetPriorityGrouping();
			NVIC_SetPriority(get_irq_type(), NVIC_EncodePriority(prioritygroup, prior, 0));

			return sys::RES_OK;
		}

		uint32_t get_irq_prior() override {
			uint32_t prempt_prior, sub_prior;

			uint32_t prioritygroup = NVIC_GetPriorityGrouping();
			NVIC_DecodePriority(NVIC_GetPriority(get_irq_type()), prioritygroup, &prempt_prior, &sub_prior);

			return prempt_prior;
		}

		sys::result_t enable_irq() override {
			NVIC_EnableIRQ(get_irq_type());
			return sys::RES_OK;
		}

		sys::result_t disable_irq() override {
			NVIC_DisableIRQ(get_irq_type());
			return sys::RES_OK;
		}

		bool is_irq() override {
			return NVIC_GetEnableIRQ(get_irq_type());
		}

	protected:
		periphery_with_irq_impl() {}
	};
}

#endif /* ARM_IRQ_H */