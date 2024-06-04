#ifndef STM32F4_PIN_H
#define STM32F4_PIN_H

#include "system/interface/pin.h"
#include "stm32f4xx.h"
#include "port.h"

namespace arch {

class pin : public sys::ipin {
// Enums
public:
typedef enum PIN_T {
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15,
} pin_t;

public:
	pin(arch::port &port, pin_t pin)
	:
	port(port),
	pin_num(pin),
	pin_mask(1 << pin)
	{}

// Interface
public:
	inline sys::result_t enable_clock() override {
		return port.enable_clock();
	}

	inline sys::result_t disable_clock() override {
		return port.disable_clock();
	}

private:
	arch::port &port;
	pin_t pin_num;
	uint32_t pin_mask;
};
}


#endif /* STM32F4_PIN_H */