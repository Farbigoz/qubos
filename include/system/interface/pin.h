#ifndef SYSTEM_INTERFACE_PIN_H
#define SYSTEM_INTERFACE_PIN_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"

namespace sys {

class pin : virtual public periphery_with_irq {
// Enums
public:
	typedef enum SPEED_T {
		SPEED_SLOW,
		SPEED_MID,
		SPEED_FAST,
		SPEED_VERY_FAST
	} speed_t;

	typedef enum DRIVER_T {
		DRV_PUSH_PULL,		///< Подтяжка
		DRV_OPEN_DRAIN,		///< Открытый выход
	} driver_t;

	typedef enum PULL_T {
		PULL_NONE,				///< Без подтяжки
		PULL_UP,				///< Подтяжка к положительному потенциалу
		PULL_DOWN,				///< Подтяжка к земле
	} pull_t;

	typedef enum TRIGGER_T {
		TRIG_NONE,				///< Отключено
		TRIG_RISING,			///< По возрастающему фронту
		TRIG_FALLING,			///< По спадающему фронту
		TRIG_RISING_FALLING,	///< По смене фронта
	} trigger_t;

	typedef enum ALT_T {
		ALT_NONE,

		// Обезличенная функция (Для МК, которые не поддерживают назначения функции определённому пину)
		// ALT,

		// Обезличенные функции (Для МК, которые поддерживают назначения функции определённому пину)
		ALT_0,
		ALT_1,
		ALT_2,
		ALT_3,
		ALT_4,
		ALT_5,
		ALT_6,
		ALT_7,
		ALT_8,
		ALT_9,
		ALT_10,
		ALT_11,
		ALT_12,
		ALT_13,
		ALT_14,
		ALT_15,

		// Функции отладки/перепрошивки
		ALT_SWD,
		ALT_JTAG,

		// Функции внешнего тактирования
		ALT_RTC,

		// Функции периферии
		ALT_TIM1,
		ALT_TIM2,
		ALT_TIM3,
		ALT_TIM4,
		ALT_TIM5,
		ALT_TIM6,
		ALT_TIM7,
		ALT_TIM8,
		ALT_TIM9,
		ALT_TIM10,
		ALT_TIM11,
		ALT_TIM12,
		ALT_TIM13,
		ALT_TIM14,
		ALT_TIM15,
		ALT_TIM16,
		ALT_TIM17,
		ALT_TIM18,

		ALT_I2C1,
		ALT_I2C2,
		ALT_I2C3,
		ALT_I2C4,

		ALT_SPI1,
		ALT_SPI2,
		ALT_SPI3,
		ALT_SPI4,
		ALT_SPI5,
		ALT_SPI6,
		ALT_QSPI,

		ALT_I2S1,
		ALT_I2S2,
		ALT_I2S3,

		ALT_UART1,
		ALT_UART2,
		ALT_UART3,
		ALT_UART4,
		ALT_UART5,
		ALT_UART6,
		ALT_UART7,
		ALT_UART8,

		ALT_USB_FS,
		ALT_USB_HS,
		ALT_USB_FS_HS,

		ALT_CAN1,
		ALT_CAN2,

		ALT_SDIO1,
		ALT_SDIO2,

		ALT_ETH,
		ALT_DCMI,
		ALT_LTDC,

		_ALT_END,
	} alt_t;

// Signals
public:
	typedef Signal<pin&>	signal_irq_t;

// Methods
public:
	virtual sys::result_t init_output(driver_t drv, pull_t pull, speed_t speed) = 0;
	virtual sys::result_t init_input(pull_t pull, sys::pin::trigger_t trig) = 0;
	virtual sys::result_t init_analog() = 0;
	virtual sys::result_t init_alt(alt_t af, driver_t drv, pull_t pull, speed_t speed) = 0;

	virtual sys::result_t set_driver(driver_t drv) = 0;
	virtual sys::result_t set_pull(pull_t pull) = 0;
	virtual sys::result_t set_speed(speed_t speed) = 0;
	virtual sys::result_t set_alt(alt_t af) = 0;
	virtual sys::result_t set_irq_trig(trigger_t trig) = 0;

	// virtual driver_t get_driver() = 0;
	// virtual pull_t get_pull() = 0;
	// virtual speed_t get_speed() = 0;
	// virtual alt_t get_alt() = 0;
	// virtual trigger_t get_irq_trigger() = 0;

	virtual void set() = 0;
	virtual void set(bool v) = 0;
	virtual void clear() = 0;
	virtual void tgl() = 0;

	virtual bool state() = 0;
	virtual bool read() = 0;

public:
	virtual ~pin() = default;

	inline sys::result_t init_output() {
		return init_output(sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, pin::SPEED_FAST);
	}

	inline sys::result_t init_output(sys::pin::driver_t drv) {
		return init_output(drv, sys::pin::PULL_NONE, pin::SPEED_FAST);
	}

	inline sys::result_t init_output(sys::pin::driver_t drv, sys::pin::pull_t pull) {
		return init_output(drv, pull, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_output(sys::pin::driver_t drv, sys::pin::speed_t speed) {
		return init_output(drv, sys::pin::PULL_NONE, speed);
	}

	inline sys::result_t init_output(sys::pin::pull_t pull) {
		return init_output(sys::pin::DRV_PUSH_PULL, pull, pin::SPEED_FAST);
	}

	inline sys::result_t init_output(sys::pin::pull_t pull, sys::pin::speed_t speed) {
		return init_output(sys::pin::DRV_PUSH_PULL, pull, speed);
	}

	inline sys::result_t init_output(sys::pin::speed_t speed) {
		return init_output(sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, speed);
	}

	inline sys::result_t init_input() {
		return init_input(sys::pin::PULL_NONE, sys::pin::TRIG_NONE);
	}

	inline sys::result_t init_input(sys::pin::pull_t pull) {
		return init_input(pull, sys::pin::TRIG_NONE);
	}

	inline sys::result_t init_input(sys::pin::trigger_t trig) {
		return init_input(sys::pin::PULL_NONE, trig);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af) {
		return init_alt(af, sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af, sys::pin::driver_t drv) {
		return init_alt(af, drv, sys::pin::PULL_NONE, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::pull_t pull) {
		return init_alt(af, drv, pull, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::speed_t speed) {
		return init_alt(af, drv, sys::pin::PULL_NONE, speed);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af, sys::pin::pull_t pull) {
		return init_alt(af, sys::pin::DRV_PUSH_PULL, pull, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af, sys::pin::pull_t pull, sys::pin::speed_t speed) {
		return init_alt(af, sys::pin::DRV_PUSH_PULL, pull, speed);
	}

	inline sys::result_t init_alt(sys::pin::alt_t af, sys::pin::speed_t speed) {
		return init_alt(af, sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, speed);
	}

public:
	signal_irq_t	signal_irq;

protected:
	pin() {}

	// копирование
	//ipin(const ipin&) = delete;
	//ipin& operator=(const ipin&) = delete;

	// перемещение
	//ipin(ipin&&) = delete;
	//ipin& operator=(ipin&&) = delete;
};




class nullpin : public pin {
public:
	nullpin() : pin()
	{}

	//result_t init_output()				override { return RES_OK; }
	//result_t init_input()				override { return RES_OK; }
	//result_t init_analog()				override { return RES_OK; }
	//result_t init_alt(alt_t)			override { return RES_OK; }
	result_t deinit()					override { return RES_OK; }
	result_t set_driver(driver_t d)		override { return RES_OK; }
	result_t set_pull(pull_t p)			override { return RES_OK; }
	result_t set_speed(speed_t s)		override { return RES_OK; }
	result_t set_alt(alt_t a)			override { return RES_OK; }
	result_t set_irq_trig(trigger_t)	override { return RES_OK; }
	result_t set_irq_prior(uint32_t)	override { return RES_OK; }

	//driver_t get_driver()				override { return DRV_PUSH_PULL; }
	//pull_t get_pull()					override { return PULL_NONE; }
	//speed_t get_speed()					override { return SPEED_SLOW; }
	//alt_t get_alt()						override { return ALT_NONE; }
	//trigger_t get_irq_trigger()			override { return TRIG_NONE; }
	uint32_t get_irq_prior()			override { return 0; }
	uint32_t get_clock_freq()			override { return 0; }

	result_t enable_clock()				override { return RES_OK; }
	result_t disable_clock()			override { return RES_OK; }

	bool is_irq()						override { return false; }
	result_t enable_irq()				override { return RES_OK; }
	result_t disable_irq()				override { return RES_OK; }
	void set()							override {}
	void set(bool v)					override {}
	void clear()						override {}
	void tgl()							override {}
	bool state()						override { return true; }
	bool read()							override { return true; }

	void trig_irq()						{ signal_irq.emit(*this); }
};

}


#endif /* SYSTEM_INTERFACE_GPIO_H */