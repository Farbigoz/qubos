#ifndef STM32F4_PORT_H
#define STM32F4_PORT_H

#include "stm32f4xx.h"
#include "system/interface/port.h"
#include "arch/ARM/STM32/F4/clock.h"


#ifndef GPIOC
#define GPIOC nullptr
#define RCC_AHB1ENR_GPIOCEN (0x00U)
#endif
#ifndef GPIOD
#define GPIOD nullptr
#define RCC_AHB1ENR_GPIODEN (0x00U)
#endif
#ifndef GPIOE
#define GPIOE nullptr
#define RCC_AHB1ENR_GPIOEEN (0x00U)
#endif
#ifndef GPIOF
#define GPIOF nullptr
#define RCC_AHB1ENR_GPIOFEN (0x00U)
#endif
#ifndef GPIOG
#define GPIOG nullptr
#define RCC_AHB1ENR_GPIOGEN (0x00U)
#endif
#ifndef GPIOH
#define GPIOH nullptr
#define RCC_AHB1ENR_GPIOHEN (0x00U)
#endif
#ifndef GPIOI
#define GPIOI nullptr
#define RCC_AHB1ENR_GPIOIEN (0x00U)
#endif
#ifndef GPIOJ
#define GPIOJ nullptr
#define RCC_AHB1ENR_GPIOJEN (0x00U)
#endif
#ifndef GPIOK
#define GPIOK nullptr
#define RCC_AHB1ENR_GPIOKEN (0x00U)
#endif


namespace arch {

class port : public sys::port, public arch::clock {
// Constants
public:
	static inline GPIO_TypeDef *GPIO_PORT_MAP[] = {GPIOA, GPIOB, GPIOC,
												   GPIOD, GPIOE, GPIOF,
												   GPIOG, GPIOH, GPIOI,
												   GPIOJ, GPIOK, nullptr};

	static inline const uint32_t GPIO_PINS_NUM = 16;
	static inline const uint32_t GPIO_PINS_MASK = 0xffffU;

// Enums
public:
	typedef enum {
		GPIO_MODE_INPUT  = 0x00U,
		GPIO_MODE_OUTPUT = 0x01U,
		GPIO_MODE_ALT    = 0x02U,
		GPIO_MODE_ANALOG = 0x03U,
	} gpio_mode_t;

	typedef enum {
		GPIO_DRV_PP = 0x00U,
		GPIO_DRV_OD = 0x01U,
	} gpio_driver_t;

	typedef enum {
		GPIO_NOPULL   = 0x00U,
		GPIO_PULLUP   = 0x01U,
		GPIO_PULLDOWN = 0x02U,
	} gpio_pull_t;

	typedef enum {
		GPIO_SPEED_LOW       = 0x00U,
		GPIO_SPEED_MEDIUM    = 0x01U,
		GPIO_SPEED_HIGH      = 0x02U,
		GPIO_SPEED_VERY_HIGH = 0x03U,
	} gpio_speed_t;

	typedef enum {
		GPIO_ALT_FN0  = 0x00U,
		GPIO_ALT_FN1  = 0x01U,
		GPIO_ALT_FN2  = 0x02U,
		GPIO_ALT_FN3  = 0x03U,
		GPIO_ALT_FN4  = 0x04U,
		GPIO_ALT_FN5  = 0x05U,
		GPIO_ALT_FN6  = 0x06U,
		GPIO_ALT_FN7  = 0x07U,
		GPIO_ALT_FN8  = 0x08U,
		GPIO_ALT_FN9  = 0x09U,
		GPIO_ALT_FN10 = 0x0AU,
		GPIO_ALT_FN11 = 0x0BU,
		GPIO_ALT_FN12 = 0x0CU,
		GPIO_ALT_FN13 = 0x0DU,
		GPIO_ALT_FN14 = 0x0EU,
		GPIO_ALT_FN15 = 0x0FU,
	} gpio_alt_fn_t;

public:
	port(port::port_t port)
	:
	arch::clock(RCC->AHB1ENR, get_clock_en_bit(port)),
	port_num(port),
	gpio_port(GPIO_PORT_MAP[port])
	{}

// Interface periphery
public:
	sys::result_t deinit() override {
		// todo
		return sys::RES_OK;
	}

// Interface sys::port
public:
	sys::result_t deinit(pin_mask_t) override {
		// todo
		return sys::RES_OK;
	}

	sys::result_t init_output(pin_mask_t mask, sys::pin::driver_t drv, sys::pin::pull_t pull, sys::pin::speed_t speed) override {
		if (
				(set_speed(mask, speed) != sys::RES_OK) ||
				(set_driver(mask, drv) != sys::RES_OK) ||
				(set_pull(mask, pull) != sys::RES_OK)
		) {
			deinit(mask);
			return sys::RES_ERROR;
		}

		gpio_port->MODER = unpack_config_2bits(mask, gpio_port->MODER, GPIO_MODE_OUTPUT);
		return sys::RES_OK;
	}

	sys::result_t init_input(pin_mask_t mask, sys::pin::pull_t pull, sys::pin::trigger_t trig) override {
		if (
				(set_pull(mask, pull) != sys::RES_OK) ||
				(set_irq_trig(mask, trig) != sys::RES_OK)
		) {
			deinit(mask);
			return sys::RES_ERROR;
		}

		gpio_port->MODER = unpack_config_2bits(mask, gpio_port->MODER, GPIO_MODE_INPUT);
		return sys::RES_OK;
	}

	sys::result_t init_analog(pin_mask_t mask) override {
		gpio_port->MODER = unpack_config_2bits(mask, gpio_port->MODER, GPIO_MODE_ANALOG);
		return sys::RES_OK;
	}

	sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::pull_t pull, sys::pin::speed_t speed) override {
		if (
				(set_speed(mask, speed) != sys::RES_OK) ||
				(set_driver(mask, drv) != sys::RES_OK) ||
				(set_pull(mask, pull) != sys::RES_OK)
		) {
			deinit(mask);
			return sys::RES_ERROR;
		}

		gpio_port->MODER = unpack_config_2bits(mask, gpio_port->MODER, GPIO_MODE_ALT);
		return sys::RES_OK;
	}

	using sys::port::init_output;
	using sys::port::init_input;
	using sys::port::init_analog;
	using sys::port::init_alt;

	sys::result_t set_driver(pin_mask_t mask, sys::pin::driver_t drv) override {
		gpio_driver_t drv_cfg;

		switch (drv) {
			case sys::pin::DRV_PUSH_PULL:
				drv_cfg = GPIO_DRV_PP;
				break;
			case sys::pin::DRV_OPEN_DRAIN:
				drv_cfg = GPIO_DRV_OD;
				break;
			default:
				return sys::RES_ERROR;
		}

		gpio_port->OTYPER = unpack_config_1bits(mask, gpio_port->OTYPER, drv_cfg);
		return sys::RES_OK;
	}

	sys::result_t set_pull(pin_mask_t mask, sys::pin::pull_t pull) override {
		gpio_pull_t pull_cfg;

		switch (pull) {
			case sys::pin::PULL_NONE:
				pull_cfg = GPIO_NOPULL;
				break;
			case sys::pin::PULL_UP:
				pull_cfg = GPIO_PULLUP;
				break;
			case sys::pin::PULL_DOWN:
				pull_cfg = GPIO_PULLDOWN;
				break;
			default:
				return sys::RES_ERROR;
		}

		gpio_port->PUPDR = unpack_config_2bits(mask, gpio_port->PUPDR, pull_cfg);
		return sys::RES_OK;
	}

	sys::result_t set_speed(pin_mask_t mask, sys::pin::speed_t speed) override {
		gpio_speed_t speed_cfg;

		switch (speed) {
			case sys::pin::SPEED_SLOW:
				speed_cfg = GPIO_SPEED_LOW;
				break;
			case sys::pin::SPEED_MID:
				speed_cfg = GPIO_SPEED_MEDIUM;
				break;
			case sys::pin::SPEED_FAST:
				speed_cfg = GPIO_SPEED_HIGH;
				break;
			case sys::pin::SPEED_VERY_FAST:
				speed_cfg = GPIO_SPEED_VERY_HIGH;
				break;
			default:
				return sys::RES_ERROR;
		}

		gpio_port->OSPEEDR = unpack_config_2bits(mask, gpio_port->OSPEEDR, speed_cfg);
		return sys::RES_OK;
	}

	sys::result_t set_alt(pin_mask_t mask, sys::pin::alt_t af) override {
		gpio_alt_fn_t af_cfg;

		// TODO: Этот маппинг актуален только для STM32F405xx, STM32F415xx, STM32F407xx, STM32F417xx
		switch (af) {
			case sys::pin::ALT_0:
			case sys::pin::ALT_SWD:
			case sys::pin::ALT_JTAG:
				af_cfg = GPIO_ALT_FN0;
				break;

			case sys::pin::ALT_1:
			case sys::pin::ALT_TIM1:
			case sys::pin::ALT_TIM2:
				af_cfg = GPIO_ALT_FN1;
				break;

			case sys::pin::ALT_2:
			case sys::pin::ALT_TIM3:
			case sys::pin::ALT_TIM4:
			case sys::pin::ALT_TIM5:
				af_cfg = GPIO_ALT_FN2;
				break;

			case sys::pin::ALT_3:
			case sys::pin::ALT_TIM8:
			case sys::pin::ALT_TIM9:
			case sys::pin::ALT_TIM10:
			case sys::pin::ALT_TIM11:
				af_cfg = GPIO_ALT_FN3;
				break;

			case sys::pin::ALT_4:
			case sys::pin::ALT_I2C1:
			case sys::pin::ALT_I2C2:
			case sys::pin::ALT_I2C3:
				af_cfg = GPIO_ALT_FN4;
				break;

			case sys::pin::ALT_5:
			case sys::pin::ALT_SPI1:
			case sys::pin::ALT_SPI2:
				af_cfg = GPIO_ALT_FN5;
				break;

			case sys::pin::ALT_6:
			case sys::pin::ALT_SPI3:
				af_cfg = GPIO_ALT_FN6;
				break;

			case sys::pin::ALT_7:
			case sys::pin::ALT_UART1:
			case sys::pin::ALT_UART2:
			case sys::pin::ALT_UART3:
				af_cfg = GPIO_ALT_FN7;
				break;

			case sys::pin::ALT_8:
			case sys::pin::ALT_UART4:
			case sys::pin::ALT_UART5:
			case sys::pin::ALT_UART6:
			case sys::pin::ALT_UART7:
			case sys::pin::ALT_UART8:
				af_cfg = GPIO_ALT_FN8;
				break;

			case sys::pin::ALT_9:
			case sys::pin::ALT_CAN1:
			case sys::pin::ALT_CAN2:
			case sys::pin::ALT_TIM12:
			case sys::pin::ALT_TIM13:
			case sys::pin::ALT_TIM14:
				af_cfg = GPIO_ALT_FN9;
				break;

			case sys::pin::ALT_10:
			case sys::pin::ALT_USB_FS:
			case sys::pin::ALT_USB_HS:
				af_cfg = GPIO_ALT_FN10;
				break;

			case sys::pin::ALT_11:
			case sys::pin::ALT_ETH:
				af_cfg = GPIO_ALT_FN11;
				break;

			case sys::pin::ALT_12:
			case sys::pin::ALT_USB_FS_HS:
			case sys::pin::ALT_SDIO1:
				af_cfg = GPIO_ALT_FN12;
				break;

			case sys::pin::ALT_13:
			case sys::pin::ALT_DCMI:
				af_cfg = GPIO_ALT_FN13;
				break;

			case sys::pin::ALT_14:
			case sys::pin::ALT_LTDC:
				af_cfg = GPIO_ALT_FN14;
				break;

			case sys::pin::ALT_15:
				af_cfg = GPIO_ALT_FN15;
				break;

			default:
				return sys::RES_ERROR;
		}

		gpio_port->AFR[0] = unpack_config_4bits(mask & 0xff, gpio_port->AFR[0], af_cfg);
		gpio_port->AFR[1] = unpack_config_4bits((mask >> 8) & 0xff, gpio_port->AFR[1], af_cfg);

		return sys::RES_OK;
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
					SYSCFG->EXTICR[i] = unpack_config_4bits((mask >> (i*4)) & 0xFU,  SYSCFG->EXTICR[i], 0xf);
			return sys::RES_OK;
		}
		else
		{
			enable_syscfg_clock();
			for (int i = 0; i < 4; i++)
				if ((mask >> (i*4)) & 0xFU)
					SYSCFG->EXTICR[i] = unpack_config_4bits((mask >> (i*4)) & 0xFU,  SYSCFG->EXTICR[i], port_num);
		}

		EXTI->IMR = unpack_config_1bits(mask, EXTI->IMR, it);
		EXTI->RTSR = unpack_config_1bits(mask, EXTI->RTSR, rising);
		EXTI->FTSR = unpack_config_1bits(mask, EXTI->FTSR, falling);

		return sys::RES_OK;
	}

	// virtual sys::pin::driver_t	get_driver(pin_t) = 0;
	// virtual sys::pin::pull_t		get_pull(pin_t) = 0;
	// virtual sys::pin::speed_t	get_speed(pin_t) = 0;
	// virtual sys::pin::alt_t		get_alt(pin_t) = 0;
	// virtual sys::pin::trigger_t	get_irq_trigger(pin_t) = 0;

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


private:
	// todo: Перенести отсюда
	static void enable_syscfg_clock() {
		__IO uint32_t tmpreg;
		SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
		(void)tmpreg;
	}

	// todo: переделать включение тактирования
	static uint32_t get_clock_en_bit(port_t port_num) {
		switch (port_num) {
			case PORT_A: return RCC_AHB1ENR_GPIOAEN;
			case PORT_B: return RCC_AHB1ENR_GPIOBEN;
			case PORT_C: return RCC_AHB1ENR_GPIOCEN;
			case PORT_D: return RCC_AHB1ENR_GPIODEN;
			case PORT_E: return RCC_AHB1ENR_GPIOEEN;
			case PORT_F: return RCC_AHB1ENR_GPIOFEN;
			case PORT_G: return RCC_AHB1ENR_GPIOGEN;
			case PORT_H: return RCC_AHB1ENR_GPIOHEN;
			case PORT_I: return RCC_AHB1ENR_GPIOIEN;
			// todo J,K
			default:     return 0x00;
		}
	}

	static uint32_t unpack_config_1bits(uint32_t mask, uint32_t value, uint8_t config) {
		return (value & ~mask) | mask * config;
	}

	static uint32_t unpack_config_2bits(uint32_t mask, uint32_t value, uint8_t config) {
		// from project "zhele"
		mask = (mask & 0xff00)     << 8 | (mask & 0x00ff);
		mask = (mask & 0x00f000f0) << 4 | (mask & 0x000f000f);
		mask = (mask & 0x0C0C0C0C) << 2 | (mask & 0x03030303);
		mask = (mask & 0x22222222) << 1 | (mask & 0x11111111);
		return (value & ~(mask * 0x03)) | mask * config;
	}

	static uint32_t unpack_config_4bits(uint32_t mask, uint32_t value, uint8_t config) {
		// from project "zhele"
		mask = (mask & 0xf0) << 12 | (mask & 0x0f);
		mask = (mask & 0x000C000C) << 6 | (mask & 0x00030003);
		mask = (mask & 0x02020202) << 3 | (mask & 0x01010101);
		return (value & ~(mask * 0x0f)) | mask * config;
	}


	//void set_mode(pin_mask_t mask, uint32_t mode) {
	//	uint32_t tmp = 0x00;
	//	for (int pin_num = 0; pin_num < GPIO_PINS_NUM; pin_num++) {
	//		if ((mask & (1 << pin_num)) == 0) continue;
	//		tmp = gpio_port->MODER;
	//		tmp &= ~(GPIO_MODER_MODER0 << (pin_num * 2U));
	//		tmp |= ((mode & mode) << (pin_num * 2U));
	//		gpio_port->MODER = tmp;
	//	}
	//}

private:
	port_t port_num;
	GPIO_TypeDef *gpio_port;
};

}


#endif /* STM32F4_PORT_H */