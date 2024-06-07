#ifndef STM32F1_PIN_H
#define STM32F1_PIN_H

#include "system/interface/pin.h"
#include "arch/ARM/irq.h"

#if defined(STM32F1)
#include "arch/ARM/STM32/F1/port.h"
#elif defined(STM32F4)
#include "arch/ARM/STM32/F4/port.h"
#endif

namespace arch {

	class pin : public sys::pin {

	public:
		pin(arch::port &port, arch::port::pin_t pin)
				:
				sys::pin(),
				port(port),
				pin_mask(pin),
				irqn(get_irq_type(pin))
		{
			arch::irq::get_irq_signal(irqn).connect(
					irq_slot,
					[](void *ctx) { reinterpret_cast<arch::pin*>(ctx)->irq_handler(); },
					this
			);
		}

// Interface sys::periphery
	public:
		sys::result_t deinit() override {
			return port.deinit(pin_mask);
		}

		uint32_t get_clock_freq() override {
			return port.get_clock_freq();
		}

		sys::result_t enable_clock() override {
			return port.enable_clock();
		}

		sys::result_t disable_clock() override {
			return port.disable_clock();
		}

// Interface sys::periphery_with_irq
	public:
		sys::result_t set_irq_prior(uint32_t prior) override {
			return arch::irq::set_irq_prior(irqn, prior);
		}

		uint32_t get_irq_prior() override {
			return arch::irq::get_irq_prior(irqn);
		}

		bool is_irq() override {
			return arch::irq::is_irq(irqn);
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
			return port.init_output(pin_mask, drv, pull, speed);
		}

		inline sys::result_t init_input(pull_t pull, trigger_t trig) override {
			return port.init_input(pin_mask, pull, trig);
		}

		inline sys::result_t init_analog() override {
			return port.init_analog(pin_mask);
		}

		inline sys::result_t init_alt(alt_t af, driver_t drv, pull_t pull, speed_t speed) override {
			return port.init_alt(pin_mask, af, drv, pull, speed);
		}

		using sys::pin::init_output;
		using sys::pin::init_input;
		using sys::pin::init_analog;
		using sys::pin::init_alt;

		inline sys::result_t set_driver(driver_t drv) override {
			return port.set_driver(pin_mask, drv);
		}

		inline sys::result_t set_pull(pull_t pull) override {
			return port.set_pull(pin_mask, pull);
		}

		inline sys::result_t set_speed(speed_t speed) override {
			return port.set_speed(pin_mask, speed);
		}

		inline sys::result_t set_alt(alt_t af) override {
			return port.set_alt(pin_mask, af);
		}

		inline sys::result_t set_irq_trig(trigger_t trigger) override {
			return port.set_irq_trig(pin_mask, trigger);
		}


		// virtual driver_t get_driver() = 0;
		// virtual pull_t get_pull() = 0;
		// virtual speed_t get_speed() = 0;
		// virtual alt_t get_alt() = 0;
		// virtual trigger_t get_irq_trigger() = 0;

		inline void set() override {
			port.set(pin_mask);
		}

		inline void set(bool state) override {
			port.set(pin_mask, state);
		}

		inline void clear() override {
			port.clear(pin_mask);
		}

		inline void tgl() override {
			port.tgl(pin_mask);
		}

		inline bool state() override {
			return (port.state() & pin_mask) != 0;
		}

		inline bool read() override {
			return (port.read() & pin_mask) != 0;
		}

	private:
		void irq_handler() {
			if ((EXTI->PR & pin_mask) == 0) { return; }
			EXTI->PR = pin_mask;
			signal_irq.emit(*this);
		}

	private:
		static IRQn_Type get_irq_type(arch::port::pin_t pin) {
			switch (pin) {
				case arch::port::PIN_0:
					return EXTI0_IRQn;
				case arch::port::PIN_1:
					return EXTI1_IRQn;
				case arch::port::PIN_2:
					return EXTI2_IRQn;
				case arch::port::PIN_3:
					return EXTI3_IRQn;
				case arch::port::PIN_4:
					return EXTI4_IRQn;
				case arch::port::PIN_5:
				case arch::port::PIN_6:
				case arch::port::PIN_7:
				case arch::port::PIN_8:
				case arch::port::PIN_9:
					return EXTI9_5_IRQn;
				case arch::port::PIN_10:
				case arch::port::PIN_11:
				case arch::port::PIN_12:
				case arch::port::PIN_13:
				case arch::port::PIN_14:
				case arch::port::PIN_15:
					return EXTI15_10_IRQn;

				default:
					return NonMaskableInt_IRQn;
			}
		}

	private:
		IRQn_Type irqn;
		arch::port &port;
		arch::port::pin_mask_t pin_mask;
		arch::irq::irq_signal_t::SlotWithCtx irq_slot;
	};
}


#endif /* STM32F1_PIN_H */