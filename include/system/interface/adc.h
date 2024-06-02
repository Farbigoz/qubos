#ifndef SYSTEM_INTERFACE_ADC_H
#define SYSTEM_INTERFACE_ADC_H

#include "system/system.h"
#include "system/signal.h"
#include "system/periphery.h"
#include "system/interface/dma.h"

namespace sys {

class iadc : public periphery_with_irq {
// Enums
public:
	typedef enum CHANNEL_T {
		CHAN_0,
		CHAN_1,
		CHAN_2,
		CHAN_3,
		CHAN_4,
		CHAN_5,
		CHAN_6,
		CHAN_7,
		CHAN_8,
		CHAN_9,
		CHAN_10,
		CHAN_11,
		CHAN_12,
		CHAN_13,
		CHAN_14,
		CHAN_15,
		CHAN_16,
		CHAN_17,
		CHAN_18
	} channel_t;

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
	typedef Signal<iadc&>			signal_conv_cplt_t;
	typedef Signal<iadc&>			signal_conv_half_cplt_t;
	typedef Signal<iadc&>			signal_abort_t;
	typedef Signal<iadc&, error_t>	signal_error_t;

public:
	virtual result_t init() = 0;

	virtual result_t set_ext_trigger(ext_trigger_t) = 0;
	virtual result_t set_alignment(alignment_t) = 0;
	virtual result_t set_resolution(resolution_t) = 0;
	virtual result_t set_scan_conv(bool) = 0;
	virtual result_t set_continuous_conv(bool) = 0;
	virtual result_t set_dma(idma*) = 0;

	virtual ext_trigger_t get_ext_trigger() = 0;
	virtual alignment_t get_alignment() = 0;
	virtual resolution_t get_resolution() = 0;
	virtual bool get_scan_conv() = 0;
	virtual bool get_continuous_conv() = 0;
	virtual uint8_t get_value_sizeof() = 0;
	virtual uint32_t get_value() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;

	virtual bool polling() = 0;

	virtual result_t start() = 0;
	virtual result_t stop() = 0;

	virtual result_t start_it() = 0;
	virtual result_t stop_it() = 0;

	virtual result_t start_dma() = 0;
	virtual result_t stop_dma() = 0;

public:
	virtual ~iadc() = default;

public:
	signal_conv_cplt_t		signal_conv_cplt;
	signal_conv_half_cplt_t	signal_conv_half_cplt;
	signal_abort_t			signal_abort;
	signal_error_t			signal_error;

protected:
	iadc() {}
};

}


#endif /* SYSTEM_INTERFACE_ADC_H */