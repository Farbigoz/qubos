#ifndef SYSTEM_INTERFACE_DMA_H
#define SYSTEM_INTERFACE_DMA_H

#include "system/types.h"
#include "system/signal.h"
#include "system/interface/periphery.h"

namespace sys {

class dma : public periphery_with_irq {
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

	typedef enum PRIOR_T {
		PRIOR_LOW,
		PRIOR_MEDIUM,
		PRIOR_HIGH,
		PRIOR_VERY_HIGH
	} prior_t;

	typedef enum STATE_T {
		STATE_NONE		= 0,
		STATE_RESET		= 1 << 0,
		STATE_READY		= 1 << 1,
		STATE_BUSY		= 1 << 2,
		STATE_TIMEOUT	= 1 << 3,
		STATE_ABORT		= 1 << 4,
		STATE_ERROR		= 1 << 5,
	} state_t;

	typedef enum ERROR_T {
		ERROR_NONE			= 0,
		ERROR_TRANSFER		= 1 << 0,
		ERROR_DIRECT_MODE	= 1 << 1,
		ERROR_TIMEOUT		= 1 << 2,
	} error_t;

// Signals
public:
	typedef Signal<dma&>			signal_cplt_t;
	typedef Signal<dma&>			signal_half_cplt_t;
	typedef Signal<dma&>			signal_abort_t;
	typedef Signal<dma&, error_t>	signal_error_t;

// Methods
public:
	virtual sys::result_t init(direction_t dir, data_align_t per_align, data_align_t mem_align, bool per_inc, bool mem_inc, bool circular, prior_t prior) = 0;

	virtual sys::result_t set_direction(direction_t d) = 0;
	virtual sys::result_t set_per_data_align(data_align_t align) = 0;
	virtual sys::result_t set_mem_data_align(data_align_t align) = 0;
	virtual sys::result_t set_per_inc(bool inc) = 0;
	virtual sys::result_t set_mem_inc(bool inc) = 0;
	virtual sys::result_t set_circular(bool circ) = 0;
	virtual sys::result_t set_priority(prior_t p) = 0;

	virtual direction_t get_direction() = 0;
	virtual data_align_t get_per_data_align() = 0;
	virtual data_align_t get_mem_data_align() = 0;
	virtual bool get_per_inc() = 0;
	virtual bool get_mem_inc() = 0;
	virtual bool get_circular() = 0;
	virtual prior_t get_priority() = 0;
	virtual state_t get_state() = 0;
	virtual error_t get_error() = 0;
	virtual size_t get_counter() = 0;
	virtual size_t get_pos() = 0;

	virtual sys::result_t enable() = 0;
	virtual sys::result_t disable() = 0;

	virtual sys::result_t start(void *p_src, void *p_dst, size_t size) = 0;
	virtual sys::result_t abort() = 0;

	virtual sys::result_t start_it(void *p_src, void *p_dst, size_t size) = 0;
	virtual sys::result_t abort_it() = 0;

public:
	virtual ~dma() = default;

public:
	signal_cplt_t		signal_cplt;
	signal_half_cplt_t	signal_half_cplt;
	signal_abort_t		signal_abort;
	signal_error_t		signal_error;

protected:
	constexpr dma() {}
};

inline sys::dma::state_t operator | (sys::dma::state_t a, sys::dma::state_t b) {
	return static_cast<sys::dma::state_t>((uint32_t)a | (uint32_t)b);
}

inline sys::dma::state_t& operator |= (sys::dma::state_t &a, sys::dma::state_t b) {
	a = static_cast<sys::dma::state_t>((uint32_t)a | (uint32_t)b);
	return a;
}

inline sys::dma::error_t operator | (sys::dma::error_t a, sys::dma::error_t b) {
	return static_cast<sys::dma::error_t>((uint32_t)a | (uint32_t)b);
}

inline sys::dma::error_t& operator |= (sys::dma::error_t &a, sys::dma::error_t b) {
	a = static_cast<sys::dma::error_t>((uint32_t)a | (uint32_t)b);
	return a;
}

}

#endif /* SYSTEM_INTERFACE_DMA_H */