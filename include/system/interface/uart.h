#ifndef SYSTEM_INTERFACE_UART_H
#define SYSTEM_INTERFACE_UART_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"
#include "system/interface/dma.h"

namespace sys {

class uart : public periphery_transceiver {
// Enums
public:
	typedef enum MODE_T {
		MODE_FULL_DUPLEX,
		MODE_HALF_DUPLEX,
		MODE_TX_ONLY,
		MODE_RX_ONLY,
	} mode_t;

	typedef enum STOP_T {
		STOP_1_BIT,
		STOP_2_BIT,
		STOP_0_5_BIT,
		STOP_1_5_BIT
	} stop_t;

	typedef enum PARITY_T {
		PARITY_NONE,
		PARITY_EVEN,	// чётный
		PARITY_ODD,		// нечётный
	} parity_t;

	typedef enum LENGTH_T {
		LENGTH_8_BIT,
		LENGTH_9_BIT
	} length_t;

	typedef enum OVERSAMPLE_T {
		OVERSAMPLE_1_BIT,
		OVERSAMPLE_8_BIT,
		OVERSAMPLE_16_BIT
	} oversample_t;

	typedef enum STATE_T {
		STATE_NONE      = 0,
		STATE_ENABLED   = 1 << 0,
		STATE_IDLE      = 1 << 1,
		STATE_RX_BUSY   = 1 << 2,
		STATE_TX_BUSY   = 1 << 3,
		STATE_ERROR     = 1 << 4,
	} state_t;

	typedef enum ERROR_T {
		ERROR_NONE          = 0,
		ERROR_PARITY        = 1 << 0,		// Нарушен бит чётности
		ERROR_FRAMING       = 1 << 1,		// Несоответствие бодовой скорости
		ERROR_NOISE         = 1 << 2,		// Наличие шума в передаче
		ERROR_OVERRUN       = 1 << 3,		// Новый байт принят, но старый байт ещё не был прочитан из регистра
	} error_t;

// Signals
public:
	typedef Signal<uart&>			signal_tx_cplt_t;
	typedef Signal<uart&>			signal_tx_half_cplt_t;
	typedef Signal<uart&>			signal_rx_cplt_t;
	typedef Signal<uart&>			signal_rx_half_cplt_t;
	typedef Signal<uart&>			signal_idle_t;
	typedef Signal<uart&>			signal_abort_tx_t;
	typedef Signal<uart&>			signal_abort_rx_t;
	typedef Signal<uart&>			signal_abort_t;
	typedef Signal<uart&, error_t>	signal_error_t;


// Methods
public:
	virtual sys::result_t init_uart(mode_t m, stop_t s, parity_t p, length_t l, oversample_t o) = 0;

	virtual sys::result_t set_stop_bit(stop_t s) = 0;
	virtual sys::result_t set_parity(parity_t p) = 0;
	virtual sys::result_t set_length(length_t l) = 0;
	virtual sys::result_t set_oversample(oversample_t o) = 0;
	virtual sys::result_t set_baud(uint32_t baud) = 0;
	// virtual sys::result_t set_tx_dma(idma*) = 0;	// arch?
	// virtual sys::result_t set_rx_dma(idma*) = 0;	// arch?

	virtual stop_t get_stop_bit() = 0;
	virtual parity_t get_parity() = 0;
	virtual length_t get_length() = 0;
	virtual oversample_t get_oversample() = 0;
	virtual uint32_t get_baud() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;

	virtual sys::result_t enable() = 0;
	virtual sys::result_t disable() = 0;
	virtual sys::result_t reset_errors() = 0;

	virtual sys::result_t transmit(const uint8_t *p_data, size_t size, size_t *tx_len, sys::time_ms_t timeout) = 0;
	virtual sys::result_t receive(const uint8_t *p_data, size_t size, size_t *rx_len, sys::time_ms_t timeout) = 0;
	virtual sys::result_t abort() = 0;
	virtual sys::result_t abort_transmit() = 0;
	virtual sys::result_t abort_receive() = 0;

	virtual sys::result_t transmit_it(const uint8_t *p_data, size_t size) = 0;
	virtual sys::result_t receive_it(const uint8_t *p_data, size_t size) = 0;
	virtual sys::result_t abort_it() = 0;
	virtual sys::result_t abort_transmit_it() = 0;
	virtual sys::result_t abort_receive_it() = 0;

	virtual sys::result_t transmit_dma(const uint8_t *p_data, size_t size) = 0;
	virtual sys::result_t receive_dma(uint8_t *p_data, size_t size) = 0;
	virtual sys::result_t abort_dma() = 0;
	virtual sys::result_t abort_transmit_dma() = 0;
	virtual sys::result_t abort_receive_dma() = 0;

public:
	virtual ~uart() = default;

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
	uart() {}
};

inline sys::uart::state_t operator | (sys::uart::state_t a, sys::uart::state_t b) {
	return static_cast<sys::uart::state_t>((uint32_t)a | (uint32_t)b);
}

inline sys::uart::state_t& operator |= (sys::uart::state_t &a, sys::uart::state_t b) {
	a = static_cast<sys::uart::state_t>((uint32_t)a | (uint32_t)b);
	return a;
}

inline sys::uart::error_t operator | (sys::uart::error_t a, sys::uart::error_t b) {
	return static_cast<sys::uart::error_t>((uint32_t)a | (uint32_t)b);
}

inline sys::uart::error_t& operator |= (sys::uart::error_t &a, sys::uart::error_t b) {
	a = static_cast<sys::uart::error_t>((uint32_t)a | (uint32_t)b);
	return a;
}

}


#endif /* SYSTEM_INTERFACE_UART_H */