#ifndef SYSTEM_INTERFACE_I2C_H
#define SYSTEM_INTERFACE_I2C_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"
#include "system/interface/dma.h"


// todo


namespace sys {

class ii2c : public periphery_transceiver {
// Enums
public:
	typedef enum MODE_T {
		MODE_MASTER,
		MODE_SLAVE
	} mode_t;

	typedef enum SPEED_T {
		SPEED_100K,
		SPEED_400K
	} speed_t;

	typedef enum ADDRESS_T {
		ADDRESS_7BIT,
		ADDRESS_10BIT
	} address_len_t;

	typedef enum STATE_T {

	} state_t;

	typedef enum ERROR_T {

	} error_t;

// Signals
public:
	typedef Signal<uart&>			signal_tx_cplt_t;
	typedef Signal<uart&>			signal_tx_half_cplt_t;
	typedef Signal<uart&>			signal_rx_cplt_t;
	typedef Signal<uart&>			signal_rx_half_cplt_t;
	typedef Signal<uart&>			signal_abort_tx_t;
	typedef Signal<uart&>			signal_abort_rx_t;
	typedef Signal<uart&>			signal_abort_t;
	typedef Signal<uart&, error_t>	signal_error_t;


// Methods
public:
	virtual result_t init(mode_t) = 0;

	virtual result_t set_tx_dma(idma*) = 0;
	virtual result_t set_rx_dma(idma*) = 0;

	virtual result_t set_speed(speed_t) = 0;
	virtual result_t set_addr_len(address_len_t) = 0;

	virtual speed_t get_speed() = 0;
	virtual address_len_t get_addr_len() = 0;
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
	virtual ~ii2c() = default;

public:
	signal_tx_cplt_t		signal_tx_cplt;
	signal_tx_half_cplt_t	signal_tx_half_cplt;
	signal_rx_cplt_t		signal_rx_cplt;
	signal_rx_half_cplt_t	signal_rx_half_cplt;
	signal_abort_tx_t		signal_abort_tx;
	signal_abort_rx_t		signal_abort_rx;
	signal_abort_t			signal_abort;
	signal_error_t			signal_error;

protected:
	ii2c() {}
};


}


#endif /* SYSTEM_INTERFACE_I2C_H */