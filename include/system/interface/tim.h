#ifndef SYSTEM_INTERFACE_TIM_H
#define SYSTEM_INTERFACE_TIM_H

#include "system/system.h"
#include "system/periphery.h"

namespace sys {
	class itim : public periphery_with_irq {
	public:
		class ich;
		class ich_input;
		class ich_output;
		class ich_pwm;

	public:
		typedef enum MODE_T {
			MODE_NORMAL,
			MODE_ONE_PULSE
		} mode_t;

		typedef enum COUNTER_MODE_T {
			CNT_MODE_UP,
			CNT_MODE_DOWN,
			CNT_MODE_CENTER_ALIGNED1,	///< Interrupt with counting down
			CNT_MODE_CENTER_ALIGNED2,	///< Interrupt with counting up
			CNT_MODE_CENTER_ALIGNED3,	///< Interrupt with counting both
		} counter_mode_t;

		typedef enum CHANNEL_T {
			CHANNEL_1,
			CHANNEL_2,
			CHANNEL_3,
			CHANNEL_4,
			CHANNEL_5,
			CHANNEL_6,
		} channel_t;

	public:
		virtual result_t init(mode_t, counter_mode_t) = 0;

		// Установка периода
		virtual result_t set_period(uint32_t) = 0;
		// Установка делителя
		virtual result_t set_prescaler(uint32_t) = 0;
		// Auto calc period and prescaler
		virtual result_t set_freq(float) = 0;
		// Установка количества переполнений для вызова прерывания
		virtual result_t set_repetition_counter(uint32_t) = 0;
		// Установка значения счётчика
		virtual result_t set_counter(uint32_t) = 0;

		// Запрос режима таймера
		virtual mode_t get_mode() = 0;
		// Запрос режима счётчика
		virtual counter_mode_t get_counter_mode() = 0;
		// Запрос частоты переполнения счётчика
		virtual float get_freq() = 0;
		// Запрос делителя
		virtual uint32_t get_prescaler() = 0;
		// Запрос периода переполнения
		virtual uint32_t get_period() = 0;
		// Запрос значения счётчика
		virtual uint32_t get_counter() = 0;

		// Перезапуск счётчика
		virtual result_t reset() = 0;
		// Запуск таймера
		virtual result_t start() = 0;
		// Остановка таймера
		virtual result_t stop() = 0;

	public:
		class ich {
		public:


		protected:
			ich() {}
		};


		class ich_input : public ich {
		public:

		protected:
			ich_input() {}
		};


		class ich_output : public ich {
		public:

		protected:
			ich_output() {}
		};


		class ich_pwm : public ich_output {
		public:

		protected:
			ich_pwm() {}
		};

	protected:
		itim() {}
	};
}

#endif /* SYSTEM_INTERFACE_TIM_H */