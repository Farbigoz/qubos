#ifndef STM32F1_PORT_H
#define STM32F1_PORT_H

#include "stm32f1xx.h"
#include "system/interface/port.h"


#ifndef GPIOC
#define GPIOC (nullptr)
#define RCC_APB2ENR_IOPCEN (0x00U)
#endif
#ifndef GPIOD
#define GPIOD (nullptr)
#define RCC_APB2ENR_IOPDEN (0x00U)
#endif
#ifndef GPIOE
#define GPIOE (nullptr)
#define RCC_APB2ENR_IOPEEN (0x00U)
#endif
#ifndef GPIOF
#define GPIOF (nullptr)
#define RCC_APB2ENR_IOPFEN (0x00U)
#endif
#ifndef GPIOG
#define GPIOG (nullptr)
#define RCC_APB2ENR_IOPGEN (0x00U)
#endif


namespace arch {

class port : public sys::port {
public:
	static inline GPIO_TypeDef *GPIO_PORT_MAP[] = {GPIOA, GPIOB, GPIOC,
												   GPIOD, GPIOE, GPIOF,
												   GPIOG, nullptr, nullptr,
												   nullptr, nullptr, nullptr};

	static inline const uint32_t GPIO_PINS_NUM = 16;
	static inline const uint32_t GPIO_PINS_MASK = 0xffffU;

public:
	typedef enum {
		GPIO_CFG_ANALOG = 0x00U,
		GPIO_CFG_INPUT  = 0x01U,
		GPIO_CFG_INPUT_PP_PD = 0x02U,

		GPIO_CFG_PP = 0x00U,
		GPIO_CFG_OD = 0x01U,
		GPIO_CFG_OUT = 0x00U,
		GPIO_CFG_ALT = 0x02U,

		GPIO_CFG_OUT_PP = GPIO_CFG_OUT & GPIO_CFG_PP,
		GPIO_CFG_OUT_OD = GPIO_CFG_OUT & GPIO_CFG_OD,
		GPIO_CFG_ALT_OUT_PP = GPIO_CFG_ALT & GPIO_CFG_PP,
		GPIO_CFG_ALT_OUT_OD = GPIO_CFG_ALT & GPIO_CFG_OD,
	} gpio_config_t;

	typedef enum  {
		GPIO_MODE_INPUT = 0x00U,
		GPIO_MODE_OUT_10MHZ = 0x01U,
		GPIO_MODE_OUT_2MHZ  = 0x02U,
		GPIO_MODE_OUT_50MHZ = 0x03U
	} gpio_mode_t;


public:
	port(port::port_t port)
	:
	port_num(port),
	gpio_port(GPIO_PORT_MAP[port])
	{}

public:
	uint32_t get_clock_freq() override {
		return 0; // todo
	}

	inline sys::result_t enable_clock() override {
		// todo: rework
		return enable_clock(port_num);
	}

	sys::result_t disable_clock() override {
		// todo:
		return sys::RES_OK;
	}

// Interface sys::periphery
public:
	sys::result_t deinit() override {
		// todo
		disable_clock();
		return sys::RES_OK;
	}

// Interface sys::port
public:
	sys::result_t deinit(pin_mask_t) override {
		// todo
		return sys::RES_OK;
	}

	sys::result_t init_output(sys::port::pin_mask_t mask, sys::pin::driver_t drv, sys::pin::pull_t pull, sys::pin::speed_t speed) override {
		gpio_config_t cfg;

		if (pull != sys::pin::PULL_NONE) return sys::RES_ERROR;		// Not supported

		clear(mask);
		if (set_speed(mask, speed) != sys::RES_OK) {
			deinit(mask);
			return sys::RES_ERROR;
		}

		switch (drv) {
			case sys::pin::DRV_PUSH_PULL:  cfg = GPIO_CFG_OUT_PP; break;
			case sys::pin::DRV_OPEN_DRAIN: cfg = GPIO_CFG_OUT_OD; break;
			default:
				return sys::RES_ERROR;
		}
		set_config(mask, cfg);

		return sys::RES_OK;
	}

	sys::result_t init_input(sys::port::pin_mask_t mask, sys::pin::pull_t pull, sys::pin::trigger_t trig) override {
		if (
				(set_pull(mask, pull) != sys::RES_OK) ||
				(set_irq_trig(mask, trig) != sys::RES_OK)
		) {
			deinit(mask);
			return sys::RES_ERROR;
		}

		return sys::RES_OK;
	}

	sys::result_t init_analog(sys::port::pin_mask_t mask) override {
		set_config(mask, GPIO_CFG_ANALOG);
		return sys::RES_OK;
	}

	sys::result_t init_alt(sys::port::pin_mask_t mask, sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::pull_t pull, sys::pin::speed_t speed) override {
		gpio_config_t cfg;

		if (pull != sys::pin::PULL_NONE) return sys::RES_ERROR;		// Not supported

		clear(mask);
		if (set_speed(mask, speed) != sys::RES_OK) {
			deinit(mask);
			return sys::RES_ERROR;
		}

		switch (drv) {
			case sys::pin::DRV_PUSH_PULL:  cfg = GPIO_CFG_ALT_OUT_PP; break;
			case sys::pin::DRV_OPEN_DRAIN: cfg = GPIO_CFG_ALT_OUT_OD; break;
			default:
				return sys::RES_ERROR;
		}
		set_config(mask, cfg);

		return sys::RES_OK;
	}


	using sys::port::init_output;
	using sys::port::init_input;
	using sys::port::init_analog;
	using sys::port::init_alt;


	sys::result_t set_driver(pin_mask_t mask, sys::pin::driver_t drv) override {
		gpio_config_t cfg;

		switch (drv) {
			case sys::pin::DRV_PUSH_PULL:  cfg = GPIO_CFG_PP; break;
			case sys::pin::DRV_OPEN_DRAIN: cfg = GPIO_CFG_OD; break;
			default:
				return sys::RES_ERROR;
		}

		gpio_port->CRL = unpack_config_4bits((mask >> 0) & 0xff, gpio_port->CRL, cfg << 2, 0x04U);
		gpio_port->CRH = unpack_config_4bits((mask >> 8) & 0xff, gpio_port->CRH, cfg << 2, 0x04U);

		return sys::RES_OK;
	}

	sys::result_t set_pull(pin_mask_t mask, sys::pin::pull_t pull) override {
		gpio_config_t cfg;

		switch (pull) {
			case sys::pin::PULL_NONE:
				cfg = GPIO_CFG_INPUT;
				break;

			case sys::pin::PULL_DOWN:
			case sys::pin::PULL_UP:
				cfg = GPIO_CFG_INPUT_PP_PD;
				break;

			default:
				return sys::RES_ERROR;
		}

		set_config(mask, cfg);

		if (pull == sys::pin::PULL_UP)
			set(mask);
		else
			clear(mask);

		return sys::RES_OK;
	}

	sys::result_t set_speed(pin_mask_t mask, sys::pin::speed_t speed) override {
		gpio_mode_t mode;
		switch (speed) {
			case sys::pin::SPEED_SLOW:      mode = GPIO_MODE_OUT_2MHZ; break;
			case sys::pin::SPEED_MID:       mode = GPIO_MODE_OUT_10MHZ; break;
			case sys::pin::SPEED_FAST:
			case sys::pin::SPEED_VERY_FAST: mode = GPIO_MODE_OUT_50MHZ; break;
			default:
				return sys::RES_ERROR;
		}

		set_mode(mask, mode);
		return sys::RES_OK;
	}

	sys::result_t set_alt(pin_mask_t mask, sys::pin::alt_t af) override {
		return sys::RES_ERROR;	// Not supported
	}

	sys::result_t set_irq_trig(pin_mask_t mask, sys::pin::trigger_t trig) override {
		uint32_t it, rising, falling;
		switch (trig) {
			case sys::pin::TRIG_NONE:
				it = 0;
				rising = 0;
				falling = 0;
				break;

			case sys::pin::TRIG_RISING:
				it = 1;
				rising = 1;
				falling = 0;
				break;

			case sys::pin::TRIG_FALLING:
				it = 1;
				rising = 0;
				falling = 1;
				break;

			case sys::pin::TRIG_RISING_FALLING:
				it = 1;
				rising = 1;
				falling = 1;
				break;

			default:
				return sys::RES_ERROR;
		}

		if (it == 0)
		{
			for (int i = 0; i < 4; i++)
				if ((mask >> (i*4)) & 0xFU)
					AFIO->EXTICR[i] = unpack_config_4bits((mask >> (i*4)) & 0xFU,  AFIO->EXTICR[i], 0xf);
			return sys::RES_OK;
		}
		else
		{
			enable_afio_clock();
			for (int i = 0; i < 4; i++)
				if ((mask >> (i*4)) & 0xFU)
					AFIO->EXTICR[i] = unpack_config_4bits((mask >> (i*4)) & 0xFU,  AFIO->EXTICR[i], port_num);
		}

		EXTI->IMR = unpack_config_1bits(mask, EXTI->IMR, it);
		EXTI->RTSR = unpack_config_1bits(mask, EXTI->RTSR, rising);
		EXTI->FTSR = unpack_config_1bits(mask, EXTI->FTSR, falling);

		return sys::RES_OK;
	}


	void set(pin_mask_t mask) override {
		gpio_port->BSRR = (mask & GPIO_PINS_MASK);
	}

	void set(pin_mask_t mask, bool state) override {
		if (state)	set(mask);
		else		clear(mask);
	}

	void clear(pin_mask_t mask) override {
		gpio_port->BSRR = (mask & GPIO_PINS_MASK) << GPIO_PINS_NUM;
	}

	void tgl(pin_mask_t mask) override {
		uint32_t odr = gpio_port->ODR;
		gpio_port->BSRR = ((odr & (mask & GPIO_PINS_MASK)) << GPIO_PINS_NUM) | (~odr & (mask & GPIO_PINS_MASK));
	}

	pin_mask_t state() override {
		return gpio_port->ODR;
	}

	pin_mask_t read() override {
		return gpio_port->IDR;
	}


public:
	void set_mode(sys::port::pin_mask_t mask, gpio_mode_t mode) {
		gpio_port->CRL = unpack_config_4bits((mask >> 0) & 0xff, gpio_port->CRL, mode, 0x03U);
		gpio_port->CRH = unpack_config_4bits((mask >> 8) & 0xff, gpio_port->CRH, mode, 0x03U);
	}

	void set_config(sys::port::pin_mask_t mask, gpio_config_t cfg) {
		gpio_port->CRL = unpack_config_4bits((mask >> 0) & 0xff, gpio_port->CRL, cfg << 2, 0x0CU);
		gpio_port->CRH = unpack_config_4bits((mask >> 8) & 0xff, gpio_port->CRH, cfg << 2, 0x0CU);
	}

private:
	// todo: вынести
	static void enable_afio_clock() {
		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
		(void)(tmpreg);
	}

	// todo: вынести в интерфейс периферии
	static sys::result_t enable_clock(sys::port::port_t port_num) {
		uint32_t en_bit;

		switch (port_num) {
			case sys::port::PORT_A: en_bit = RCC_APB2ENR_IOPAEN; break;
			case sys::port::PORT_B: en_bit = RCC_APB2ENR_IOPBEN; break;
			case sys::port::PORT_C: en_bit = RCC_APB2ENR_IOPCEN; break;
			case sys::port::PORT_D: en_bit = RCC_APB2ENR_IOPDEN; break;
			case sys::port::PORT_E: en_bit = RCC_APB2ENR_IOPEEN; break;
			case sys::port::PORT_F: en_bit = RCC_APB2ENR_IOPFEN; break;
			case sys::port::PORT_G: en_bit = RCC_APB2ENR_IOPGEN; break;
			default:
				return sys::RES_ERROR;
		}

		if (en_bit == 0)
			return sys::RES_ERROR;

		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB2ENR, en_bit);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->APB2ENR, en_bit);
		(void)(tmpreg);

		return sys::RES_OK;
	}

	static uint32_t unpack_config_1bits(uint32_t mask, uint32_t value, uint8_t config) {
		return (value & ~mask) | mask * config;
	}

	static uint32_t unpack_config_2bits(uint32_t mask, uint32_t value, uint8_t config, uint8_t config_mask = 0x03U) {
		// from project "zhele"
		mask = (mask & 0xff00)     << 8 | (mask & 0x00ff);
		mask = (mask & 0x00f000f0) << 4 | (mask & 0x000f000f);
		mask = (mask & 0x0C0C0C0C) << 2 | (mask & 0x03030303);
		mask = (mask & 0x22222222) << 1 | (mask & 0x11111111);
		return (value & ~(mask * (uint32_t)config_mask)) | mask * (uint32_t)config;
	}

	static uint32_t unpack_config_4bits(uint32_t mask, uint32_t value, uint8_t config, uint8_t config_mask = 0x0fU) {
		// from project "zhele"
		mask = (mask & 0xf0) << 12 | (mask & 0x0f);
		mask = (mask & 0x000C000C) << 6 | (mask & 0x00030003);
		mask = (mask & 0x02020202) << 3 | (mask & 0x01010101);
		//return (value & ~(mask * (uint32_t)config_mask)) | mask * (uint32_t)config;
		return (value & ~(mask * (uint32_t)config_mask)) | mask * ((uint32_t)(config & config_mask));
	}

private:
	port_t port_num;
	GPIO_TypeDef *gpio_port;
};

}


#endif /* STM32F1_PORT_H */