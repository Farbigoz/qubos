#ifndef STM32F4_PORT_H
#define STM32F4_PORT_H

#include "system/interface/port.h"
#include "stm32f4xx.h"


namespace arch {

class port : public sys::iport {
// Constants
public:
	static inline const GPIO_TypeDef *GPIO_PORT_MAP[] = {GPIOA, GPIOB, GPIOC,
														 GPIOD, GPIOE, GPIOF,
														 GPIOG, GPIOH, GPIOI};

// Enums
public:
	typedef enum {
		PORT_A,
		PORT_B,
		PORT_C,
		PORT_D,
		PORT_E,
		PORT_F,
		PORT_G,
		PORT_H,
		PORT_I,
	} port_t;

public:
	port(port::port_t port)
	:
	port_num(port),
	gpio_port(GPIO_PORT_MAP[port])
	{}

	inline const GPIO_TypeDef *get_gpio_port() {
		return gpio_port;
	}

// Interface
public:
	uint32_t get_clock_freq() override {
		return 0;	// todo
	}

	sys::result_t enable_clock() override {
		uint32_t enable_clock_bit = get_clock_en_bit();

		if (enable_clock_bit == 0x00)
			return sys::RES_ERROR;

		__IO uint32_t tmpreg = 0x00U;
		SET_BIT(RCC->AHB1ENR, enable_clock_bit);
		/* Delay after an RCC peripheral clock enabling */
		tmpreg = READ_BIT(RCC->AHB1ENR, enable_clock_bit);
		(void)(tmpreg);

		return sys::RES_OK;
	}

	sys::result_t disable_clock() override {
		uint32_t enable_clock_bit = get_clock_en_bit();

		if (enable_clock_bit == 0x00)
			return sys::RES_ERROR;

		CLEAR_BIT(RCC->AHB1ENR, enable_clock_bit);

		return sys::RES_OK;
	}

private:
	uint32_t get_clock_en_bit() {
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
			default:     return 0x00;
		}
	}

private:
	port_t port_num;
	const GPIO_TypeDef *gpio_port;
};
}


#endif /* STM32F4_PORT_H */