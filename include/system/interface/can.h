#ifndef SYSTEM_INTERFACE_CAN_H
#define SYSTEM_INTERFACE_CAN_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"

namespace sys {

// todo: can filter

class ican : public periphery_transceiver {
// Enums
public:
	typedef enum STATE_T {
		STATE_RESET,
		STATE_READY,
		STATE_LISTENING,
		STATE_ERROR,
	} state_t;

	typedef enum FRAME_T {
		FRAME_STD,	// 11 bit
		FRAME_EXT	// 29 bit
	} frame_t;

	typedef enum ERROR_T {

	} error_t;

// Structures
public:
	typedef struct CAN_MSG_T {
		frame_t type;
		uint32_t id;
		uint8_t len;
		uint8_t data[8];
	} can_msg_t;

// Signals
public:
	typedef Signal<ican&, can_msg_t>	signal_rx_t;
	typedef Signal<ican&>				signal_tx_t;
	typedef Signal<ican&, error_t>		signal_error_t;

public:
	virtual result_t init() = 0;

	virtual result_t set_speed(uint32_t) = 0;

	virtual uint32_t get_speed() = 0;

	//virtual bool has_received() = 0;

	virtual result_t start() = 0;
	virtual result_t stop() = 0;

	virtual result_t transmit(can_msg_t) = 0;
	virtual result_t receive(can_msg_t) = 0;

	virtual result_t transmit_it(can_msg_t) = 0;
	virtual result_t receive_it(can_msg_t) = 0;

public:

protected:
	ican() {}
};
}

#endif /* SYSTEM_INTERFACE_CAN_H */