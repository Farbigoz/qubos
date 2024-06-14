#ifndef STM32F1_DMA_H
#define STM32F1_DMA_H

#include <array>
#include <limits>
#include <algorithm>
#include "stm32f1xx.h"
#include "system/types.h"
#include "system/interface/dma.h"


namespace arch {

class dma : public sys::dma {
public:
	static constexpr uint32_t DMA_NUM = 2;
	static constexpr uint32_t DMA_CHAN_NUM[DMA_NUM] = {7, 5};
	static constexpr uint32_t DMA_MAX_CHAN_NUM = *std::max_element(DMA_CHAN_NUM, DMA_CHAN_NUM+std::size(DMA_CHAN_NUM));

	static inline DMA_TypeDef *DMA_MAP[DMA_NUM] = {DMA1, DMA2};
	static inline DMA_Channel_TypeDef *DMA_CHANNEL_MAP[DMA_NUM][DMA_MAX_CHAN_NUM] = {
			{DMA1_Channel1, DMA1_Channel2, DMA1_Channel3, DMA1_Channel4, DMA1_Channel5, DMA1_Channel6, DMA1_Channel7},
			{DMA2_Channel1, DMA2_Channel2, DMA2_Channel3, DMA2_Channel4, DMA2_Channel5, nullptr, nullptr}
	};
	static inline IRQn_Type DMA_CH_IRQ_MAP[DMA_NUM][DMA_MAX_CHAN_NUM] = {
			{DMA1_Channel1_IRQn, DMA1_Channel2_IRQn, DMA1_Channel3_IRQn, DMA1_Channel4_IRQn, DMA1_Channel5_IRQn, DMA1_Channel6_IRQn, DMA1_Channel7_IRQn},
			{DMA2_Channel1_IRQn, DMA2_Channel2_IRQn, DMA2_Channel3_IRQn, DMA2_Channel4_IRQn, DMA2_Channel5_IRQn, NonMaskableInt_IRQn, NonMaskableInt_IRQn}
	};

public:
	typedef enum {
		DMA_1,
		DMA_2,
	} dma_t;

	typedef enum {
		CHANNEL_1,
		CHANNEL_2,
		CHANNEL_3,
		CHANNEL_4,
		CHANNEL_5,
		CHANNEL_6,
		CHANNEL_7,
	} channel_t;

	typedef enum {
		CH_GLOBAL_INT			= DMA_ISR_GIF1,
		CH_TRANSFER_CMP			= DMA_ISR_TCIF1,
		CH_TRANSFER_HALF_CMP	= DMA_ISR_HTIF1,
		CH_TRANSFER_ERROR		= DMA_ISR_TEIF1,
	} int_status_flag_t;

public:
	dma(dma_t dma_num, channel_t chan_num)
	:
	dma_num(dma_num),
	chan_num(chan_num),
	dma_def(DMA_MAP[dma_num]),
	ch_def(DMA_CHANNEL_MAP[dma_num][chan_num]),
	transaction_size(0)
	{
		irq::get_irq_signal(DMA_CH_IRQ_MAP[dma_num][chan_num]).connect(
				irq_slot,
				[](void *ctx) { reinterpret_cast<arch::dma *>(ctx)->irq_handler(); },
				this
		);
	}

// clock
public:
	uint32_t get_clock_freq() override {
		return rcc::AHB::CLK_FREQ;
	}

	sys::result_t enable_clock() override {
		if (dma_num == DMA_1)
			return rcc::AHB::enable(rcc::AHB::CLK_DMA1);
		else
			return rcc::AHB::enable(rcc::AHB::CLK_DMA2);
	}

	sys::result_t disable_clock() override {
		if (dma_num == DMA_1)
			return rcc::AHB::disable(rcc::AHB::CLK_DMA1);
		else
			return rcc::AHB::disable(rcc::AHB::CLK_DMA2);
	}

// periphery
public:
	sys::result_t deinit() override {
		// todo
		return sys::RES_OK;
	}

	sys::result_t enable_irq() override {
		return irq::enable_irq(DMA_CH_IRQ_MAP[dma_num][chan_num]);
	}

	sys::result_t disable_irq() override {
		return irq::disable_irq(DMA_CH_IRQ_MAP[dma_num][chan_num]);
	}

	bool irq_enabled() override {
		return irq::is_enabled(DMA_CH_IRQ_MAP[dma_num][chan_num]);
	}

	sys::result_t set_irq_prior(uint32_t prior) override {
		return irq::set_irq_prior(DMA_CH_IRQ_MAP[dma_num][chan_num], prior);
	}

	uint32_t get_irq_prior() override {
		return irq::get_irq_prior(DMA_CH_IRQ_MAP[dma_num][chan_num]);
	}

// dma
public:
	sys::result_t init(direction_t dir, data_align_t per_align, data_align_t mem_align, bool per_inc, bool mem_inc, bool circular, prior_t prior) override {
		if (set_direction(dir)            != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_per_data_align(per_align) != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_mem_data_align(mem_align) != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_per_inc(per_inc)          != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_mem_inc(mem_inc)          != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_circular(circular)        != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_priority(prior)           != sys::RES_OK) { deinit(); return sys::RES_ERROR; }

		return sys::RES_OK;
	}


	sys::result_t set_direction(direction_t d) override {
		// todo: if enabled return RES_ERROR
		uint32_t reg;

		switch (d) {
			case sys::dma::DIR_MEM_TO_PER:
				reg = DMA_CCR_DIR;	// read from memory | mem2mem disabled
				break;
			case sys::dma::DIR_PER_TO_PER:
			case sys::dma::DIR_PER_TO_MEM:
				reg = RESET;		// read from periphery | mem2mem disabled
				break;
			case sys::dma::DIR_MEM_TO_MEM:
				reg = DMA_CCR_DIR | DMA_CCR_MEM2MEM;	// read from memory | mem2mem enabled
				break;
			default:
				return sys::RES_ERROR;
		}

		MODIFY_REG(ch_def->CCR, DMA_CCR_DIR_Msk | DMA_CCR_MEM2MEM_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_DIR_Msk | DMA_CCR_MEM2MEM_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t set_per_data_align(data_align_t align) override {
		uint32_t reg;

		switch (align) {
			case sys::dma::DATA_ALIGN_BYTE:
				reg = RESET;
				break;
			case sys::dma::DATA_ALIGN_HALFWORD:
				reg = DMA_CCR_PSIZE_0;
				break;
			case sys::dma::DATA_ALIGN_WORD:
				reg = DMA_CCR_PSIZE_1;
				break;
			default:
				return sys::RES_ERROR;
		}

		MODIFY_REG(ch_def->CCR, DMA_CCR_PSIZE_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_PSIZE_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t set_mem_data_align(data_align_t align) override {
		uint32_t reg;
		switch (align) {
			case sys::dma::DATA_ALIGN_BYTE:
				reg = RESET;
				break;
			case sys::dma::DATA_ALIGN_HALFWORD:
				reg = DMA_CCR_MSIZE_0;
				break;
			case sys::dma::DATA_ALIGN_WORD:
				reg = DMA_CCR_MSIZE_1;
				break;
			default:
				return sys::RES_ERROR;
		}

		MODIFY_REG(ch_def->CCR, DMA_CCR_MSIZE_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_MSIZE_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t set_per_inc(bool inc) override {
		uint32_t reg;
		if (inc)
			reg = DMA_CCR_PINC;
		else
			reg = RESET;

		MODIFY_REG(ch_def->CCR, DMA_CCR_PINC_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_PINC_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t set_mem_inc(bool inc) override {
		uint32_t reg;
		if (inc)
			reg = DMA_CCR_MINC;
		else
			reg = RESET;

		MODIFY_REG(ch_def->CCR, DMA_CCR_MINC_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_MINC_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t set_circular(bool circ) override {
		uint32_t reg;
		if (circ)
			reg = DMA_CCR_CIRC;
		else
			reg = RESET;

		MODIFY_REG(ch_def->CCR, DMA_CCR_CIRC_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_CIRC_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t set_priority(prior_t p) override {
		uint32_t reg;
		switch (p) {
			case sys::dma::PRIOR_LOW:
				reg = RESET;
				break;
			case sys::dma::PRIOR_MEDIUM:
				reg = DMA_CCR_PL_0;
				break;
			case sys::dma::PRIOR_HIGH:
				reg = DMA_CCR_PL_1;
				break;
			case sys::dma::PRIOR_VERY_HIGH:
				reg = DMA_CCR_PL_1 | DMA_CCR_PL_0;
				break;
			default:
				return sys::RES_ERROR;
		}

		MODIFY_REG(ch_def->CCR, DMA_CCR_PL_Msk, reg);
		return READ_BIT(ch_def->CCR, DMA_CCR_PL_Msk) == reg ? sys::RES_OK : sys::RES_ERROR;
	}


	direction_t get_direction() override {
		if (READ_BIT(ch_def->CCR, DMA_CCR_DIR_Msk | DMA_CCR_MEM2MEM_Msk) == (DMA_CCR_DIR))
			return DIR_MEM_TO_PER;
		else if (READ_BIT(ch_def->CCR, DMA_CCR_DIR_Msk | DMA_CCR_MEM2MEM_Msk) == (DMA_CCR_DIR | DMA_CCR_MEM2MEM))
			return DIR_MEM_TO_MEM;
		else
			return DIR_PER_TO_MEM;
	}

	data_align_t get_per_data_align() override {
		// todo
		return DATA_ALIGN_WORD;
	}

	data_align_t get_mem_data_align() override {
		// todo
		return DATA_ALIGN_WORD;
	}

	bool get_per_inc() override {
		// todo
		return false;
	}

	bool get_mem_inc() override {
		// todo
		return true;
	}

	bool get_circular() override {
		// todo
		return false;
	}

	prior_t get_priority() override {
		// todo
		return PRIOR_MEDIUM;
	}

	state_t get_state() override {
		// todo
		return STATE_NONE;
	}

	error_t get_error() override {
		// todo
		return ERROR_NONE;
	}

	size_t get_counter() override {
		return ch_def->CNDTR;
	}

	size_t get_pos() override {
		return transaction_size - ch_def->CNDTR;
	}


	sys::result_t enable() override {
		SET_BIT(ch_def->CCR, DMA_CCR_EN);
		return READ_BIT(ch_def->CCR, DMA_CCR_EN) == DMA_CCR_EN ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t disable() override {
		CLEAR_BIT(ch_def->CCR, DMA_CCR_EN);
		return READ_BIT(ch_def->CCR, DMA_CCR_EN) == RESET ? sys::RES_OK : sys::RES_ERROR;
	}

	bool is_enabled() override {
		return READ_BIT(ch_def->CCR, DMA_CCR_EN) == DMA_CCR_EN;
	}


	sys::result_t start(const volatile void *p_src, volatile void *p_dst, size_t size) override {
		if (is_enabled())
			return sys::RES_BUSY;

		// todo: check word|halfword align

		// Clear all flags
		SET_BIT(dma_def->IFCR, CH_GLOBAL_INT  << (chan_num * 4));
		CLEAR_BIT(ch_def->CCR, DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);

		if (size > std::numeric_limits<uint16_t>::max())
			return sys::RES_ERROR;

		transaction_size = size;
		ch_def->CNDTR = size;
		switch (get_direction()) {
			case sys::dma::DIR_MEM_TO_PER:
				ch_def->CPAR = (uint32_t)p_dst;
				ch_def->CMAR = (uint32_t)p_src;
				break;
			default:
				ch_def->CPAR = (uint32_t)p_src;
				ch_def->CMAR = (uint32_t)p_dst;
				break;
		}

		return enable();
	}

	sys::result_t abort() override {
		// Clear all flags
		SET_BIT(dma_def->IFCR, CH_GLOBAL_INT  << (chan_num * 4));
		return disable();
	}


	sys::result_t start_it(const volatile void *p_src, void volatile *p_dst, size_t size) override {
		if (is_enabled())
			return sys::RES_BUSY;

		// todo: check word|halfword align

		CLEAR_BIT(ch_def->CCR, DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);
		// Clear all flags
		SET_BIT(dma_def->IFCR, CH_GLOBAL_INT  << (chan_num * 4));

		if (size > std::numeric_limits<uint16_t>::max())
			return sys::RES_ERROR;

		transaction_size = size;
		ch_def->CNDTR = size;
		switch (get_direction()) {
			case sys::dma::DIR_MEM_TO_PER:
				ch_def->CPAR = (uint32_t)p_dst;
				ch_def->CMAR = (uint32_t)p_src;
				break;
			default:
				ch_def->CPAR = (uint32_t)p_src;
				ch_def->CMAR = (uint32_t)p_dst;
				break;
		}

		SET_BIT(ch_def->CCR, DMA_CCR_TCIE | DMA_CCR_HTIE | DMA_CCR_TEIE);

		return enable();
	}

	sys::result_t abort_it() override {
		// Clear all flags
		SET_BIT(dma_def->IFCR, CH_GLOBAL_INT  << (chan_num * 4));

		disable();

		if (irq_enabled())
			signal_abort.emit(*this);

		return sys::RES_OK;
	}

private:
	void irq_handler() {
		if ((dma_def->ISR & (CH_TRANSFER_ERROR  << (chan_num * 4))) != RESET)
		{
			SET_BIT(dma_def->IFCR, CH_TRANSFER_ERROR << (chan_num * 4));
			signal_error.emit(*this, ERROR_NONE);
		}

		if ((dma_def->ISR & (CH_TRANSFER_HALF_CMP  << (chan_num * 4))) != RESET)
		{
			SET_BIT(dma_def->IFCR, CH_TRANSFER_HALF_CMP << (chan_num * 4));
			signal_half_cplt.emit(*this);
		}

		if ((dma_def->ISR & (CH_TRANSFER_CMP  << (chan_num * 4))) != RESET)
		{
			SET_BIT(dma_def->IFCR, CH_GLOBAL_INT << (chan_num * 4));
			signal_cplt.emit(*this);
		}
	}


private:
	dma_t dma_num;
	channel_t chan_num;

	DMA_TypeDef *dma_def;
	DMA_Channel_TypeDef *ch_def;

	irq::irq_signal_t::SlotWithCtx	irq_slot;

	uint32_t transaction_size;
};
}


#endif /* STM32F1_DMA_H */