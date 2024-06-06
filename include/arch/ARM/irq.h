#ifndef ARM_IRQ_H
#define ARM_IRQ_H

#include "system/signal.h"
#include "system/interface/periphery.h"


namespace arch {
	class irq {
	public:
		typedef sys::Signal<> irq_signal_t;

	public:
		static inline const uint32_t MAX_IRQ_PRIOR = (1 << __NVIC_PRIO_BITS) - 1;

	public:
		static sys::result_t set_irq_prior(IRQn_Type irqn, uint32_t prior) {
			if (prior > MAX_IRQ_PRIOR)
				return sys::RES_ERROR;

			uint32_t prioritygroup = NVIC_GetPriorityGrouping();
			NVIC_SetPriority(irqn, NVIC_EncodePriority(prioritygroup, prior, 0));

			return sys::RES_OK;
		}

		static uint32_t get_irq_prior(IRQn_Type irqn) {
			uint32_t prempt_prior, sub_prior;

			uint32_t prioritygroup = NVIC_GetPriorityGrouping();
			NVIC_DecodePriority(NVIC_GetPriority(irqn), prioritygroup, &prempt_prior, &sub_prior);

			return prempt_prior;
		}

		static sys::result_t enable_irq(IRQn_Type irqn) {
			NVIC_EnableIRQ(irqn);
			return sys::RES_OK;
		}

		static sys::result_t disable_irq(IRQn_Type irqn) {
			NVIC_DisableIRQ(irqn);
			return sys::RES_OK;
		}

		static bool is_irq(IRQn_Type irqn) {
			return NVIC_GetEnableIRQ(irqn);
		}

		inline static void handle(uint8_t irqn) {
			if (irqn < 0) return;
			if (irqn >= ARM_IRQ_VEC_LEN) return;

			if (irq_signal[irqn].slot_cnt() == 0)
				while(1) {}	// Has not IRQ handler

			irq_signal[irqn].emit();
		}

		inline static irq_signal_t& get_irq_signal(IRQn_Type irqn) {
			return irq_signal[irqn+16];		// + 16 ARM-CORTEX interrupts
		}

	private:
		irq() {}

	private:
		inline static irq_signal_t irq_signal[ARM_IRQ_VEC_LEN];
	};
}

#endif /* ARM_IRQ_H */