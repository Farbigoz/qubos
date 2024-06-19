#ifndef STM32F1_PIN_H
#define STM32F1_PIN_H

#include "system/interface/pin.h"
#include "arch/ARM/irq.h"


namespace impl {

	class pin : public sys::pin {

	public:
		pin(sys::port &iport, port::pin_t pin)
		:
		sys::pin(),
		iport(iport),
		pin_mask(pin),
		irqn(get_irq_type(pin))
		{
			arch::irq::get_irq_signal(irqn).connect(
					irq_slot,
					[](void *ctx) { reinterpret_cast<impl::pin*>(ctx)->irq_handler(); },
					this
			);
		}

// Interface sys::periphery
	public:
		sys::result_t deinit() override {
			return iport.deinit(pin_mask);
		}

		uint32_t get_clock_freq() override {
			return iport.get_clock_freq();
		}

		sys::result_t enable_clock() override {
			return iport.enable_clock();
		}

		sys::result_t disable_clock() override {
			return iport.disable_clock();
		}

// Interface sys::periphery_with_irq
	public:
		sys::result_t set_irq_prior(uint32_t prior) override {
			return arch::irq::set_irq_prior(irqn, prior);
		}

		uint32_t get_irq_prior() override {
			return arch::irq::get_irq_prior(irqn);
		}

		bool irq_enabled() override {
			return arch::irq::is_enabled(irqn);
		}

		sys::result_t enable_irq() override {
			return arch::irq::enable_irq(irqn);
		}

		sys::result_t disable_irq() override {
			return arch::irq::disable_irq(irqn);
		}

// Interface sys::ipin
	public:
		inline sys::result_t init_output(driver_t drv, pull_t pull, speed_t speed) override {
			clear();
			return iport.init_output(pin_mask, drv, pull, speed);
		}

		inline sys::result_t init_input(pull_t pull, trigger_t trig) override {
			return iport.init_input(pin_mask, pull, trig);
		}

		inline sys::result_t init_analog() override {
			return iport.init_analog(pin_mask);
		}

		inline sys::result_t init_alt(alt_t af, driver_t drv, pull_t pull, speed_t speed) override {
			return iport.init_alt(pin_mask, af, drv, pull, speed);
		}

		using sys::pin::init_output;
		using sys::pin::init_input;
		using sys::pin::init_analog;
		using sys::pin::init_alt;

		inline sys::result_t set_driver(driver_t drv) override {
			return iport.set_driver(pin_mask, drv);
		}

		inline sys::result_t set_pull(pull_t pull) override {
			return iport.set_pull(pin_mask, pull);
		}

		inline sys::result_t set_speed(speed_t speed) override {
			return iport.set_speed(pin_mask, speed);
		}

		inline sys::result_t set_alt(alt_t af) override {
			return iport.set_alt(pin_mask, af);
		}

		inline sys::result_t set_irq_trig(trigger_t trigger) override {
			return iport.set_irq_trig(pin_mask, trigger);
		}


		// virtual driver_t get_driver() = 0;
		// virtual pull_t get_pull() = 0;
		// virtual speed_t get_speed() = 0;
		// virtual alt_t get_alt() = 0;
		// virtual trigger_t get_irq_trigger() = 0;

		inline void set() override {
			iport.set(pin_mask);
		}

		inline void set(bool state) override {
			iport.set(pin_mask, state);
		}

		inline void clear() override {
			iport.clear(pin_mask);
		}

		inline void tgl() override {
			iport.tgl(pin_mask);
		}

		inline bool state() override {
			return (iport.state() & pin_mask) != 0;
		}

		inline bool read() override {
			return (iport.read() & pin_mask) != 0;
		}

	private:
		void irq_handler() {
			if ((EXTI->PR & pin_mask) == 0) { return; }
			EXTI->PR = pin_mask;
			signal_irq.emit(*this);
		}

	private:
		static IRQn_Type get_irq_type(port::pin_t pin) {
			switch (pin) {
				case port::PIN_0:
					return EXTI0_IRQn;
				case port::PIN_1:
					return EXTI1_IRQn;
				case port::PIN_2:
					return EXTI2_IRQn;
				case port::PIN_3:
					return EXTI3_IRQn;
				case port::PIN_4:
					return EXTI4_IRQn;
				case port::PIN_5:
				case port::PIN_6:
				case port::PIN_7:
				case port::PIN_8:
				case port::PIN_9:
					return EXTI9_5_IRQn;
				case port::PIN_10:
				case port::PIN_11:
				case port::PIN_12:
				case port::PIN_13:
				case port::PIN_14:
				case port::PIN_15:
					return EXTI15_10_IRQn;

				default:
					return NonMaskableInt_IRQn;
			}
		}

	private:
		IRQn_Type irqn;
		sys::port &iport;
		sys::port::pin_mask_t pin_mask;
		arch::irq::irq_signal_t::SlotWithCtx irq_slot;
	};
}


#endif /* STM32F1_PIN_H */