#ifndef SYSTEM_PERIPHERY_H
#define SYSTEM_PERIPHERY_H

#include "system/system.h"


namespace sys {

class periphery {
	virtual result_t deinit() = 0;

	virtual uint32_t get_clock_freq() = 0;

	virtual sys::result_t enable_clock() = 0;
	virtual sys::result_t disable_clock() = 0;
};


class periphery_with_irq : public periphery {
public:
	virtual result_t set_irq_prior(uint32_t) = 0;
	virtual uint32_t get_irq_prior() = 0;

	virtual bool is_irq() = 0;
	virtual result_t enable_irq() = 0;
	virtual result_t disable_irq() = 0;
};


class periphery_transceiver : public periphery {
public:
	virtual result_t set_tx_irq_prior(uint32_t) = 0;
	virtual result_t set_rx_irq_prior(uint32_t) = 0;

	virtual uint32_t get_tx_irq_prior() = 0;
	virtual uint32_t get_rx_irq_prior() = 0;

	virtual bool tx_busy() = 0;
	virtual bool rx_busy() = 0;

	virtual bool is_tx_irq() = 0;
	virtual bool is_rx_irq() = 0;

	virtual result_t enable_tx_irq() = 0;
	virtual result_t enable_rx_irq() = 0;
	virtual result_t disable_tx_irq() = 0;
	virtual result_t disable_rx_irq() = 0;
};

}


#endif /* SYSTEM_PERIPHERY_H */