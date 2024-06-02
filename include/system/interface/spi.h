#ifndef SYSTEM_INTERFACE_SPI_H
#define SYSTEM_INTERFACE_SPI_H

#include "system/system.h"
#include "system/periphery.h"
#include "system/signal.h"
#include "system/interface/dma.h"

namespace sys {

class ispi : public periphery_transceiver {
// Enums
public:
	typedef enum MODE_T {
		MODE_FULL_DUPLEX_MASTER,
		MODE_FULL_DUPLEX_SLAVE,
		MODE_HALF_DUPLEX_MASTER,
		MODE_HALF_DUPLEX_SLAVE,
		MODE_RX_ONLY_MASTER,
		MODE_RX_ONLY_SLAVE,
		MODE_TX_ONLY_MASTER,
		MODE_TX_ONLY_SLAVE,
	} mode_t;

	typedef enum DATA_SIZE_T {
		DATA_8BIT,
		DATA_16BIT
	} data_size_t;

	typedef enum BIT_ORDER_T {
		BIT_ORDER_FIRST_LEAST,
		BIT_ORDER_FIRST_MOST
	} bit_order_t;

	typedef enum CLOCK_PHASE_T {
		CLK_PHASE_1EDGE,
		CLK_PHASE_2EDGE
	} clock_phase_t;

	typedef enum CLOCK_POLARITY_T {
		CLK_POLARITY_LOW,
		CLK_POLARITY_HI
	} clock_polarity_t;

	// todo: nss

	typedef enum STATE_T {
		STATE_RESET,
		STATE_READY,
		STATE_BUSY,
		STATE_BUSY_TX,
		STATE_BUSY_RX,
		STATE_BUSY_TX_RX,
		STATE_ERROR,
		STATE_ABORT
	} state_t;

	typedef enum ERROR_T {
		ERROR_NONE,
		ERROR_MODF,
		ERROR_CRC,
		ERROR_OVR,
		ERROR_FRE,
		ERROR_DMA,
		ERROR_FLAG,
		ERROR_ABORT
	} error_t;

// Signals
public:
	typedef Signal<iuart&>			signal_tx_cplt_t;
	typedef Signal<iuart&>			signal_tx_half_cplt_t;
	typedef Signal<iuart&>			signal_rx_cplt_t;
	typedef Signal<iuart&>			signal_rx_half_cplt_t;
	typedef Signal<iuart&>			signal_tx_rx_cplt_t;
	typedef Signal<iuart&>			signal_tx_rx_half_cplt_t;
	typedef Signal<iuart&>			signal_idle_t;
	typedef Signal<iuart&>			signal_abort_t;
	typedef Signal<iuart&, error_t>	signal_error_t;

// Methods
public:
	// todo: 2 stop bits, 9 data bits

	virtual result_t init_master(mode_t) = 0;

	virtual result_t set_data_size(data_size_t) = 0;
	virtual result_t set_bit_order(bit_order_t) = 0;
	virtual result_t set_clk_phase(clock_phase_t) = 0;
	virtual result_t set_clk_polarity(clock_polarity_t) = 0;
	virtual result_t set_tx_dma(idma*) = 0;
	virtual result_t set_rx_dma(idma*) = 0;

	virtual data_size_t get_data_size() = 0;
	virtual bit_order_t get_bit_order() = 0;
	virtual clock_phase_t get_clk_phase() = 0;
	virtual clock_polarity_t get_clk_polarity() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;

	virtual result_t transmit(const uint8_t *p_data, size_t size, uint32_t timeout) = 0;
	virtual result_t receive(const uint8_t *p_data, size_t size, uint32_t timeout) = 0;
	virtual result_t transmit_receive(const uint8_t *p_tx_data, uint8_t *p_rx_data, size_t size, uint32_t timeout) = 0;
	virtual result_t abort() = 0;

	virtual result_t transmit_it(const uint8_t *p_data, size_t size) = 0;
	virtual result_t receive_it(const uint8_t *p_data, size_t size) = 0;
	virtual result_t transmit_receive_it(const uint8_t *p_tx_data, uint8_t *p_rx_data, size_t size) = 0;
	virtual result_t abort_it() = 0;

	virtual result_t transmit_dma(const uint8_t *p_data, size_t size) = 0;
	virtual result_t receive_dma(const uint8_t *p_data, size_t size) = 0;
	virtual result_t transmit_receive_dma(const uint8_t *p_tx_data, uint8_t *p_rx_data, size_t size) = 0;
	virtual result_t abort_dma() = 0;

public:
	virtual ~ispi() = default;

public:
	signal_tx_cplt_t			signal_tx_cplt;
	signal_tx_half_cplt_t		signal_tx_half_cplt;
	signal_rx_cplt_t			signal_rx_cplt;
	signal_rx_half_cplt_t		signal_rx_half_cplt;
	signal_tx_rx_cplt_t			signal_tx_rx_cplt;
	signal_tx_rx_half_cplt_t	signal_tx_rx_half_cplt;
	signal_idle_t				signal_idle;
	signal_abort_t				signal_abort;
	signal_error_t				signal_error;

protected:
	ispi() {}
};

}


#endif /* SYSTEM_INTERFACE_SPI_H */