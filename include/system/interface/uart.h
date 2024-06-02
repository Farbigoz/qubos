#ifndef SYSTEM_INTERFACE_UART_H
#define SYSTEM_INTERFACE_UART_H

#include "system/system.h"
#include "system/periphery.h"
#include "system/signal.h"
#include "system/interface/dma.h"

namespace sys {

class iuart : public periphery_transceiver {
// Enums
public:
	typedef enum STATE_T {

	} state_t;

	typedef enum ERROR_T {

	} error_t;

// Signals
public:
	typedef Signal<iuart&>			signal_tx_cplt_t;
	typedef Signal<iuart&>			signal_tx_half_cplt_t;
	typedef Signal<iuart&>			signal_rx_cplt_t;
	typedef Signal<iuart&>			signal_rx_half_cplt_t;
	typedef Signal<iuart&>			signal_idle_t;
	typedef Signal<iuart&>			signal_abort_tx_t;
	typedef Signal<iuart&>			signal_abort_rx_t;
	typedef Signal<iuart&>			signal_abort_t;
	typedef Signal<iuart&, error_t>	signal_error_t;


// Methods
public:
	// todo: 2 stop bits, 9 data bits

	virtual result_t init_uart() = 0;
	virtual result_t init_usart() = 0;
	virtual result_t init_halfduplex() = 0;

	virtual result_t set_oversampling(uint8_t oversampling) = 0;
	virtual result_t set_baud(uint32_t baud) = 0;
	virtual result_t set_tx_dma(idma*) = 0;
	virtual result_t set_rx_dma(idma*) = 0;

	virtual uint8_t  get_oversampling() = 0;
	virtual uint32_t get_baud() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;

	virtual result_t transmit(const uint8_t *p_data, size_t size, uint32_t timeout) = 0;
	virtual result_t receive(const uint8_t *p_data, size_t size, uint32_t timeout) = 0;
	virtual result_t abort() = 0;
	virtual result_t abort_transmit() = 0;
	virtual result_t abort_receive() = 0;

	virtual result_t transmit_it(const uint8_t *p_data, size_t size) = 0;
	virtual result_t receive_it(const uint8_t *p_data, size_t size) = 0;
	virtual result_t abort_it() = 0;
	virtual result_t abort_transmit_it() = 0;
	virtual result_t abort_receive_it() = 0;

	virtual result_t transmit_dma(const uint8_t *p_data, size_t size) = 0;
	virtual result_t receive_dma(const uint8_t *p_data, size_t size) = 0;
	virtual result_t abort_dma() = 0;
	virtual result_t abort_transmit_dma() = 0;
	virtual result_t abort_receive_dma() = 0;

public:
	virtual ~iuart() = default;

public:
	signal_tx_cplt_t		signal_tx_cplt;
	signal_tx_half_cplt_t	signal_tx_half_cplt;
	signal_rx_cplt_t		signal_rx_cplt;
	signal_rx_half_cplt_t	signal_rx_half_cplt;
	signal_idle_t			signal_idle;
	signal_abort_tx_t		signal_abort_tx;
	signal_abort_rx_t		signal_abort_rx;
	signal_abort_t			signal_abort;
	signal_error_t			signal_error;

protected:
	iuart() {}
};


class nulluart : public iuart {
public:
	nulluart() : iuart() {}

	virtual const char * postix() {
		return "null";
	}

	result_t init_uart()							override { return RES_OK; }
	result_t init_usart()							override { return RES_OK; }
	result_t init_halfduplex()						override { return RES_OK; }

	result_t set_oversampling(uint8_t oversampling)	override { return RES_OK; }
	result_t set_baud(uint32_t baud)				override { return RES_OK; }
	result_t set_tx_irq_prior(uint32_t)				override { return RES_OK; }
	result_t set_rx_irq_prior(uint32_t)				override { return RES_OK; }
	result_t set_tx_dma(idma*)						override { return RES_OK; }
	result_t set_rx_dma(idma*)						override { return RES_OK; }

	uint8_t  get_oversampling()						override { return 0; }
	uint32_t get_baud()								override { return 0; }
	uint32_t get_tx_irq_prior()						override { return 0; }
	uint32_t get_rx_irq_prior()						override { return 0; }

	bool tx_busy() override { return false; }
	bool rx_busy() override { return false; }

	result_t abort() override { return RES_OK; }

	result_t transmit(const uint8_t *p_data, size_t size, uint32_t timeout)	override { return RES_OK; }
	result_t receive(const uint8_t *p_data, size_t size, uint32_t timeout)	override { return RES_OK; }

	result_t transmit_it(const uint8_t *p_data, size_t size)	override { return RES_OK; }
	result_t receive_it(const uint8_t *p_data, size_t size)		override { return RES_OK; }

	result_t transmit_dma(const uint8_t *p_data, size_t size)	override { return RES_OK; }
	result_t receive_dma(const uint8_t *p_data, size_t size)	override { return RES_OK; }
};

}


#endif /* SYSTEM_INTERFACE_UART_H */