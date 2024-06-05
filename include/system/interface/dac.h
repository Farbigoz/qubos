#ifndef SYSTEM_INTERFACE_DAC_H
#define SYSTEM_INTERFACE_DAC_H

#include "system/system.h"
#include "system/signal.h"
#include "system/interface/periphery.h"
#include "system/interface/dma.h"

namespace sys {

class idac : public periphery_with_irq {
// Enums
public:
	typedef enum ALIGNMENT_T {
		ALIGN_LEFT,
		ALIGN_RIGHT
	} alignment_t;

	typedef enum RESOLUTION_T {
		RESOLUTION_6_BIT,
		RESOLUTION_8_BIT,
		RESOLUTION_10_BIT,
		RESOLUTION_12_BIT,
		RESOLUTION_16_BIT,
		RESOLUTION_24_BIT,
	} resolution_t;

	typedef enum EXT_TRIGGER_T {
		EXT_TRIG_NONE,
		EXT_TRIG_RISING,
		EXT_TRIG_FALLING,
		EXT_TRIG_RISING_FALLING
	} ext_trigger_t;

	typedef enum STATE_T {

	} state_t;

	typedef enum ERROR_T {

	} error_t;

// Signals
public:
	typedef Signal<idac&>			signal_conv_cplt_t;
	typedef Signal<idac&>			signal_conv_half_cplt_t;
	typedef Signal<idac&>			signal_abort_t;
	typedef Signal<idac&, error_t>	signal_error_t;

// Methods
public:
	virtual result_t init() = 0;

	virtual result_t set_ext_trigger(ext_trigger_t) = 0;
	virtual result_t set_alignment(alignment_t) = 0;
	virtual result_t set_resolution(resolution_t) = 0;
	virtual result_t set_dma(idma*) = 0;
	virtual result_t set_value() = 0;

	virtual ext_trigger_t get_ext_trigger() = 0;
	virtual alignment_t get_alignment() = 0;
	virtual resolution_t get_resolution() = 0;
	virtual uint8_t get_value_sizeof() = 0;
	virtual uint32_t get_value() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;

	virtual result_t start() = 0;
	virtual result_t stop() = 0;

	virtual result_t start_dma() = 0;
	virtual result_t stop_dma() = 0;

public:
	virtual ~idac() = default;

public:
	signal_conv_cplt_t		signal_conv_cplt;
	signal_conv_half_cplt_t	signal_conv_half_cplt;
	signal_abort_t			signal_abort;
	signal_error_t			signal_error;

protected:
	idac() {}
};
}


#endif /* SYSTEM_INTERFACE_DAC_H */