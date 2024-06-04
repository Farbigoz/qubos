#ifndef SYSTEM_INTERFACE_PIN_H
#define SYSTEM_INTERFACE_PIN_H

#include "system/system.h"
#include "system/signal.h"
#include "system/periphery.h"

namespace sys {

class ipin : public periphery_with_irq {
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

		ALT_SWD,
		ALT_JTAG,

		ALT_RTC,

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

		ALT_CAN1,
		ALT_CAN2,

		ALT_ETH,
	} alt_t;

// Signals
public:
	typedef Signal<ipin&>	signal_irq_t;

// Methods
public:
	virtual sys::result_t init_output() = 0;
	virtual sys::result_t init_input() = 0;
	virtual sys::result_t init_analog() = 0;
	virtual sys::result_t init_alt(alt_t) = 0;

	virtual sys::result_t set_driver(driver_t) = 0;
	virtual sys::result_t set_pull(pull_t) = 0;
	virtual sys::result_t set_speed(speed_t) = 0;
	virtual sys::result_t set_alt(alt_t) = 0;
	virtual sys::result_t set_irq_trig(trigger_t) = 0;

	virtual driver_t get_driver() = 0;
	virtual pull_t get_pull() = 0;
	virtual speed_t get_speed() = 0;
	virtual alt_t get_alt() = 0;
	virtual trigger_t get_irq_trigger() = 0;

	virtual void set() = 0;
	virtual void set(bool v) = 0;
	virtual void clear() = 0;
	virtual void tgl() = 0;

	virtual bool state() = 0;
	virtual bool read() = 0;

public:
	virtual ~ipin() = default;

public:
	signal_irq_t	signal_irq;

protected:
	ipin() {}

	// копирование
	//ipin(const ipin&) = delete;
	//ipin& operator=(const ipin&) = delete;

	// перемещение
	//ipin(ipin&&) = delete;
	//ipin& operator=(ipin&&) = delete;
};




class nullpin : public ipin {
public:
	nullpin() : ipin()
	{}

	result_t init_output()				override { return RES_OK; }
	result_t init_input()				override { return RES_OK; }
	result_t init_analog()				override { return RES_OK; }
	result_t init_alt(alt_t)			override { return RES_OK; }
	result_t deinit()					override { return RES_OK; }
	result_t set_driver(driver_t d)		override { return RES_OK; }
	result_t set_pull(pull_t p)			override { return RES_OK; }
	result_t set_speed(speed_t s)		override { return RES_OK; }
	result_t set_alt(alt_t a)			override { return RES_OK; }
	result_t set_irq_trig(trigger_t)	override { return RES_OK; }
	result_t set_irq_prior(uint32_t)	override { return RES_OK; }

	driver_t get_driver()				override { return DRV_PUSH_PULL; }
	pull_t get_pull()					override { return PULL_NONE; }
	speed_t get_speed()					override { return SPEED_SLOW; }
	alt_t get_alt()						override { return ALT_NONE; }
	trigger_t get_irq_trigger()			override { return TRIG_NONE; }
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