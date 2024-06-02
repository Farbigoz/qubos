#ifndef SYSTEM_INTERFACE_DMA_H
#define SYSTEM_INTERFACE_DMA_H

#include "system/system.h"
#include "system/signal.h"
#include "system/periphery.h"

namespace sys {

class idma : public periphery_with_irq {
// Enums
public:
	typedef enum DIRECTION_T {
		DIR_PER_TO_MEM,
		DIR_MEM_TO_PER,
		DIR_MEM_TO_MEM,
		DIR_PER_TO_PER
	} direction_t;

	typedef enum DATA_ALIGN_T {
		DATA_ALIGN_BYTE,
		DATA_ALIGN_HALFWORD,
		DATA_ALIGN_WORD,
	} data_align_t;

	typedef enum STATE_T {
		STATE_RESET,
		STATE_READY,
		STATE_BUSY,
		STATE_TIMEOUT,
		STATE_ERROR,
		STATE_ABORT
	} state_t;

	typedef enum ERROR_T {
		ERROR_NONE,
		ERROR_TRANSFER,
		ERROR_DIRECT_MODE,
		ERROR_TIMEOUT,
	} error_t;

// Signals
public:
	typedef Signal<idma&>			signal_cplt_t;
	typedef Signal<idma&>			signal_half_cplt_t;
	typedef Signal<idma&>			signal_abort_t;
	typedef Signal<idma&, error_t>	signal_error_t;

// Methods
public:
	virtual result_t init() = 0;

	virtual result_t set_direction(direction_t) = 0;
	virtual result_t set_per_inc(bool) = 0;
	virtual result_t set_mem_inc(bool) = 0;
	virtual result_t set_circular(bool) = 0;
	virtual result_t set_per_data_align(uint8_t) = 0;
	virtual result_t set_mem_data_align(uint8_t) = 0;

	virtual direction_t get_direction() = 0;
	virtual bool get_per_inc() = 0;
	virtual bool get_mem_inc() = 0;
	virtual bool get_circular() = 0;
	virtual uint8_t get_per_data_align() = 0;
	virtual uint8_t get_mem_data_align() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;
	virtual uint32_t get_counter() = 0;
	virtual uint32_t get_pos() = 0;

	virtual result_t start(void *p_src, void *p_dst, size_t size) = 0;
	virtual result_t abort() = 0;

	virtual result_t start_it(void *p_src, void *p_dst, size_t size) = 0;
	virtual result_t abort_it() = 0;

public:
	virtual ~idma() = default;

public:
	signal_cplt_t		signal_cplt;
	signal_half_cplt_t	signal_half_cplt;
	signal_abort_t		signal_abort;
	signal_error_t		signal_error;

protected:
	idma() {}
};
}

#endif /* SYSTEM_INTERFACE_DMA_H */