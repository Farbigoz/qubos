#ifndef SYSTEM_INTERFACE_CAN_H
#define SYSTEM_INTERFACE_CAN_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"

namespace sys {

// todo: can filter

class can : public periphery_transceiver {
// Enums
public:
	typedef uint32_t mailbox_t;
	typedef uint32_t id_t;

	typedef enum STATE_T {
		STATE_RESET,
		STATE_READY,
		STATE_LISTENING,
		STATE_ERROR,
	} state_t;

	typedef enum ID_LEN_T {
		ID_STD,	// 11 bit
		ID_EXT	// 29 bit
	} id_type_t;

	//typedef enum FRAME_T {
	//	RTR_DATA,
	//	RTR_REMOTE
	//} rtr_t;

	typedef enum ERROR_T {
		ERROR_NONE          = 0,
		ERROR_PROTOCOL_WARN = 1 << 0,
		ERROR_PASSIVE       = 1 << 1,
		ERROR_BUS_OFF       = 1 << 2,
		ERROR_STUFF         = 1 << 3,
		ERROR_FORM          = 1 << 4,
		ERROR_ACK           = 1 << 5,
		ERROR_RECESSIVE_BIT = 1 << 6,
		ERROR_DOMINANT_BIT  = 1 << 7,
		ERROR_CRC           = 1 << 8,
	} error_t;

// Structures
public:
	typedef struct CAN_MSG_T {
		id_type_t idtype;
		//rtr_t rtr;
		id_t id;
		uint8_t len;
		uint8_t data[8];
	} msg_t;

	typedef struct CAN_FILTER_T {
		id_t        id;
		id_t        mask;
		id_type_t   type;
	} filter_t;

public:
	static const uint32_t UNKNOWN_MAILBOX = -1;

// Signals
public:
	typedef Signal<sys::can&, sys::can::msg_t>		signal_rx_t;
	typedef Signal<sys::can&>						signal_tx_t;
	typedef Signal<sys::can&, sys::can::error_t>	signal_error_t;

public:
	virtual sys::result_t init(uint32_t speed) = 0;

	virtual sys::result_t set_speed(uint32_t s) = 0;
	virtual sys::result_t set_filter(uint32_t filter_num, sys::can::filter_t filter) = 0;

	virtual const uint32_t get_total_tx_mailboxes() = 0;
	virtual const uint32_t get_total_rx_mailboxes() = 0;
	virtual const uint32_t get_max_filters() = 0;
	virtual uint32_t get_tx_mailboxes_free_level() = 0;
	virtual uint32_t get_rx_mailboxes_fill_level() = 0;
	virtual mailbox_t get_free_tx_mailbox() = 0;
	virtual filter_t get_filter(uint32_t filter_num) = 0;
	virtual uint32_t get_speed() = 0;

	virtual bool is_tx_pend(sys::can::mailbox_t m) = 0;

	virtual sys::result_t start() = 0;	// enable
	virtual sys::result_t stop() = 0;	// disable

	// virtual sys::result_t transmit(sys::can::msg_t msg) = 0;
	// virtual sys::result_t receive(sys::can::msg_t msg) = 0;

	virtual sys::result_t push_tx(sys::can::msg_t msg, sys::can::mailbox_t m) = 0;
	virtual sys::result_t pull_rx(sys::can::msg_t &msg) = 0;
	virtual sys::result_t abort_tx(sys::can::mailbox_t m) = 0;


public:
	signal_rx_t		signal_rx;
	signal_tx_t		signal_tx;
	signal_error_t	signal_error;

protected:
	can() = default;
};
}

#endif /* SYSTEM_INTERFACE_CAN_H */