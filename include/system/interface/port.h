#ifndef SYSTEM_INTERFACE_PORT_H
#define SYSTEM_INTERFACE_PORT_H

#include "system/types.h"
#include "system/interface/periphery.h"
#include "system/interface/pin.h"



namespace sys {

class port : public periphery {
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
		PORT_J,
		PORT_K,
	} port_t;

	typedef enum PIN_T : uint32_t {
		PIN_0	= 1U << 0,
		PIN_1	= 1U << 1,
		PIN_2	= 1U << 2,
		PIN_3	= 1U << 3,
		PIN_4	= 1U << 4,
		PIN_5	= 1U << 5,
		PIN_6	= 1U << 6,
		PIN_7	= 1U << 7,
		PIN_8	= 1U << 8,
		PIN_9	= 1U << 9,
		PIN_10	= 1U << 10,
		PIN_11	= 1U << 11,
		PIN_12	= 1U << 12,
		PIN_13	= 1U << 13,
		PIN_14	= 1U << 14,
		PIN_15	= 1U << 15,
		PIN_16	= 1U << 16,
		PIN_17	= 1U << 17,
		PIN_18	= 1U << 18,
		PIN_19	= 1U << 19,
		PIN_20	= 1U << 20,
		PIN_21	= 1U << 21,
		PIN_22	= 1U << 22,
		PIN_23	= 1U << 23,
		PIN_24	= 1U << 24,
		PIN_25	= 1U << 25,
		PIN_26	= 1U << 26,
		PIN_27	= 1U << 27,
		PIN_28	= 1U << 28,
		PIN_29	= 1U << 29,
		PIN_30	= 1U << 30,
		PIN_31	= 1U << 31,
		PIN_ALL	= 0xffffffff
	} pin_t;

	typedef uint32_t pin_mask_t;

public:
	virtual sys::result_t deinit(pin_mask_t mask) = 0;
	virtual sys::result_t init_output(pin_mask_t mask, sys::pin::driver_t drv, sys::pin::pull_t pull, sys::pin::speed_t speed) = 0;
	virtual sys::result_t init_input(pin_mask_t mask, sys::pin::pull_t pull, sys::pin::trigger_t trig) = 0;
	virtual sys::result_t init_analog(pin_mask_t mask) = 0;
	virtual sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::pull_t pull, sys::pin::speed_t speed) = 0;

	virtual sys::result_t set_driver(pin_mask_t mask, sys::pin::driver_t drv) = 0;
	// ! Не во всех микроконтроллерах есть возможность установки PULL для выхода OPEN-DRAIN
	virtual sys::result_t set_pull(pin_mask_t mask, sys::pin::pull_t pull) = 0;
	// ! Не во всех микроконтроллерах есть возможность установки скорости пина
	virtual sys::result_t set_speed(pin_mask_t mask, sys::pin::speed_t speed) = 0;
	// ! Не во всех микроконтроллерах есть возможность назначения определённой функции пину, где-то она ограничена
	virtual sys::result_t set_alt(pin_mask_t mask, sys::pin::alt_t af) = 0;
	virtual sys::result_t set_irq_trig(pin_mask_t mask, sys::pin::trigger_t trig) = 0;

	// virtual sys::pin::driver_t	get_driver(pin_t) = 0;
	// virtual sys::pin::pull_t		get_pull(pin_t) = 0;
	// virtual sys::pin::speed_t	get_speed(pin_t) = 0;
	// virtual sys::pin::alt_t		get_alt(pin_t) = 0;
	// virtual sys::pin::trigger_t	get_irq_trigger(pin_t) = 0;

	virtual void set(pin_mask_t mask) = 0;
	virtual void set(pin_mask_t mask, bool state) = 0;
	virtual void clear(pin_mask_t mask) = 0;
	virtual void tgl(pin_mask_t mask) = 0;
	virtual pin_mask_t state() = 0;
	virtual pin_mask_t read() = 0;


public:
	inline sys::result_t init_output(pin_mask_t mask) {
		return init_output(mask, sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, pin::SPEED_FAST);
	}

	inline sys::result_t init_output(pin_mask_t mask, sys::pin::driver_t drv) {
		return init_output(mask, drv, sys::pin::PULL_NONE, pin::SPEED_FAST);
	}

	inline sys::result_t init_output(pin_mask_t mask, sys::pin::driver_t drv, sys::pin::pull_t pull) {
		return init_output(mask, drv, pull, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_output(pin_mask_t mask, sys::pin::driver_t drv, sys::pin::speed_t speed) {
		return init_output(mask, drv, sys::pin::PULL_NONE, speed);
	}

	inline sys::result_t init_output(pin_mask_t mask, sys::pin::pull_t pull) {
		return init_output(mask, sys::pin::DRV_PUSH_PULL, pull, pin::SPEED_FAST);
	}

	inline sys::result_t init_output(pin_mask_t mask, sys::pin::pull_t pull, sys::pin::speed_t speed) {
		return init_output(mask, sys::pin::DRV_PUSH_PULL, pull, speed);
	}

	inline sys::result_t init_output(pin_mask_t mask, sys::pin::speed_t speed) {
		return init_output(mask, sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, speed);
	}

	inline sys::result_t init_input(pin_mask_t mask) {
		return init_input(mask, sys::pin::PULL_NONE, pin::TRIG_NONE);
	}

	inline sys::result_t init_input(pin_mask_t mask, sys::pin::pull_t pull) {
		return init_input(mask, pull, pin::TRIG_NONE);
	}

	inline sys::result_t init_input(pin_mask_t mask, sys::pin::trigger_t trig) {
		return init_input(mask, sys::pin::PULL_NONE, trig);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af) {
		return init_alt(mask, af, sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::driver_t drv) {
		return init_alt(mask, af, drv, sys::pin::PULL_NONE, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::pull_t pull) {
		return init_alt(mask, af, drv, pull, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::driver_t drv, sys::pin::speed_t speed) {
		return init_alt(mask, af, drv, sys::pin::PULL_NONE, speed);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::pull_t pull) {
		return init_alt(mask, af, sys::pin::DRV_PUSH_PULL, pull, sys::pin::SPEED_FAST);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::pull_t pull, sys::pin::speed_t speed) {
		return init_alt(mask, af, sys::pin::DRV_PUSH_PULL, pull, speed);
	}

	inline sys::result_t init_alt(pin_mask_t mask, sys::pin::alt_t af, sys::pin::speed_t speed) {
		return init_alt(mask, af, sys::pin::DRV_PUSH_PULL, sys::pin::PULL_NONE, speed);
	}


protected:
	port() {}
};

inline sys::port::pin_mask_t operator | (sys::port::pin_t pin_a, sys::port::pin_t pin_b) {
	return static_cast<sys::port::pin_mask_t>((uint32_t)pin_a | (uint32_t)pin_b);
}

}


#endif /* SYSTEM_INTERFACE_PORT_H */