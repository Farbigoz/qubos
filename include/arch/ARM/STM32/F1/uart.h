#ifndef STM32F1_UART_H
#define STM32F1_UART_H

#include "stm32f1xx.h"
#include "arch/ARM/STM32/F1/rcc.h"
#include "system/types.h"
#include "system/interface/uart.h"


namespace arch {
class uart : public sys::uart {
public:
	inline static USART_TypeDef* UART_MAP[] = {USART1, USART2, USART3, UART4, UART5};

	inline static const rcc::bus_t BUS_MAP[] = {rcc::BUS_APB2,
												rcc::BUS_APB1,
												rcc::BUS_APB1,
												rcc::BUS_APB1,
												rcc::BUS_APB1};

	inline static const uint32_t CLOCK_MAP[] = {rcc::APB2::CLK_UART1,
												rcc::APB1::CLK_UART2,
												rcc::APB1::CLK_UART3,
												rcc::APB1::CLK_UART4,
												rcc::APB1::CLK_UART5};

	inline static const IRQn_Type IRQ_MAP[] = {USART1_IRQn,
											   USART2_IRQn,
											   USART3_IRQn,
											   UART4_IRQn,
											   UART5_IRQn};

public:
	typedef enum {
		UART_1,
		UART_2,
		UART_3,
		UART_4,
		UART_5,
		UART_6,
	} uart_t;

public:
	uart(uart_t u)
	:
	uart_num(u),
	uart_def(UART_MAP[u])
	{}

public:
	sys::result_t deinit() override {
		// todo: rcc reset
		return sys::RES_OK;
	}

// clock
public:
	uint32_t get_clock_freq() override {
		switch (BUS_MAP[uart_num]) {
			case rcc::BUS_APB1: return rcc::APB1::get_clk();
			case rcc::BUS_APB2: return rcc::APB2::get_clk();
			case rcc::BUS_AHB:  return rcc::AHB::get_clk();
			default: return 0;
		}
	}

	sys::result_t enable_clock() override {
		switch (BUS_MAP[uart_num]) {
			case rcc::BUS_AHB:
				return rcc::AHB::enable((rcc::AHB::periphery_clock_t) CLOCK_MAP[uart_num]);
			case rcc::BUS_APB1:
				return rcc::APB1::enable((rcc::APB1::periphery_clock_t) CLOCK_MAP[uart_num]);
			case rcc::BUS_APB2:
				return rcc::APB2::enable((rcc::APB2::periphery_clock_t) CLOCK_MAP[uart_num]);
		}
	}

	sys::result_t disable_clock() override {
		switch (BUS_MAP[uart_num]) {
			case rcc::BUS_AHB:
				return rcc::AHB::disable((rcc::AHB::periphery_clock_t) CLOCK_MAP[uart_num]);
			case rcc::BUS_APB1:
				return rcc::APB1::disable((rcc::APB1::periphery_clock_t) CLOCK_MAP[uart_num]);
			case rcc::BUS_APB2:
				return rcc::APB2::disable((rcc::APB2::periphery_clock_t) CLOCK_MAP[uart_num]);
		}
	}

// periphery
public:

// uart
public:
	sys::result_t init_uart(mode_t m, stop_t s, parity_t p, length_t l, oversample_t o) override {
		disable();

		switch (m) {
			case sys::uart::MODE_FULL_DUPLEX:
				SET_BIT(uart_def->CR1, USART_CR1_TE | USART_CR1_RE);
				CLEAR_BIT(uart_def->CR3, USART_CR3_HDSEL);
				break;

			case sys::uart::MODE_HALF_DUPLEX:
				SET_BIT(uart_def->CR1, USART_CR1_TE | USART_CR1_RE);
				SET_BIT(uart_def->CR3, USART_CR3_HDSEL);
				break;

			case sys::uart::MODE_RX_ONLY:
				SET_BIT(uart_def->CR1, USART_CR1_RE);
				CLEAR_BIT(uart_def->CR1, USART_CR1_TE);
				CLEAR_BIT(uart_def->CR3, USART_CR3_HDSEL);
				break;

			case sys::uart::MODE_TX_ONLY:
				SET_BIT(uart_def->CR1, USART_CR1_TE);
				CLEAR_BIT(uart_def->CR1, USART_CR1_RE);
				CLEAR_BIT(uart_def->CR3, USART_CR3_HDSEL);
				break;

			default:
				return sys::RES_ERROR;
		}

		if (set_stop_bit(s)   != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_parity(p)     != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_length(l)     != sys::RES_OK) { deinit(); return sys::RES_ERROR; }
		if (set_oversample(o) != sys::RES_OK) { deinit(); return sys::RES_ERROR; }

		return sys::RES_OK;
	}

	sys::result_t set_stop_bit(stop_t s) override {
		switch (s) {
			case sys::uart::STOP_1_BIT:
				MODIFY_REG(uart_def->CR2, USART_CR2_STOP_Msk, 0);
				break;

			case sys::uart::STOP_2_BIT:
				MODIFY_REG(uart_def->CR2, USART_CR2_STOP_Msk, USART_CR2_STOP_1);
				break;

			case sys::uart::STOP_0_5_BIT:
				MODIFY_REG(uart_def->CR2, USART_CR2_STOP_Msk, USART_CR2_STOP_0);
				break;

			case sys::uart::STOP_1_5_BIT:
				MODIFY_REG(uart_def->CR2, USART_CR2_STOP_Msk, USART_CR2_STOP_1 | USART_CR2_STOP_0);
				break;

			default:
				return sys::RES_ERROR;
		}
		return sys::RES_OK;
	}

	sys::result_t set_parity(parity_t p) override {
		switch (p) {
			case sys::uart::PARITY_NONE:
				MODIFY_REG(uart_def->CR1, USART_CR1_PCE | USART_CR1_PS, 0);
				break;
			case sys::uart::PARITY_EVEN:
				MODIFY_REG(uart_def->CR1, USART_CR1_PCE | USART_CR1_PS, USART_CR1_PCE | 0);
				break;
			case sys::uart::PARITY_ODD:
				MODIFY_REG(uart_def->CR1, USART_CR1_PCE | USART_CR1_PS, USART_CR1_PCE | USART_CR1_PS);
				break;
			default:
				return sys::RES_ERROR;
		}
		return sys::RES_OK;
	}

	sys::result_t set_length(length_t l) override {
		switch (l) {
			case sys::uart::LENGTH_8_BIT:
				CLEAR_BIT(uart_def->CR1, USART_CR1_M);
				break;
			case sys::uart::LENGTH_9_BIT:
				SET_BIT(uart_def->CR1, USART_CR1_M);
				break;
			default:
				return sys::RES_ERROR;
		}
		return sys::RES_OK;
	}

	sys::result_t set_oversample(oversample_t o) override {
#ifndef USART_CR1_OVER8
		if (o != OVERSAMPLE_16_BIT)
			return sys::RES_ERROR;
#else
		// todo
		switch (o) {
			case sys::iuart::OVERSAMPLE_16_BIT:
				break;

			case sys::iuart::OVERSAMPLE_8_BIT:
				break;

			case sys::iuart::OVERSAMPLE_1_BIT:
				break;

			default:
				return sys::RES_ERROR;
		}
#endif

		return sys::RES_OK;
	}

	sys::result_t set_baud(uint32_t new_baud) override {
		// todo: calc mantissa + calc fraction
		baud = new_baud;
		uart_def->BRR = get_clock_freq() / new_baud;
		return sys::RES_OK;
	}

	stop_t get_stop_bit() override {
		switch (READ_REG(uart_def->CR2) & USART_CR2_STOP_Msk) {
			case USART_CR2_STOP_0: return STOP_0_5_BIT;
			case USART_CR2_STOP_1: return STOP_2_BIT;
			case USART_CR2_STOP_1 | USART_CR2_STOP_0: return STOP_1_5_BIT;
			default: return STOP_1_BIT;
		}
	}

	parity_t get_parity() override {
		switch (READ_REG(uart_def->CR1) & (USART_CR1_PCE | USART_CR1_PS)) {
			case USART_CR1_PCE: return PARITY_EVEN;
			case USART_CR1_PCE | USART_CR1_PS: return PARITY_ODD;
			default: return PARITY_NONE;
		}
	}

	length_t get_length() override {
		if (READ_BIT(uart_def->CR1, USART_CR1_M) == RESET)
			return LENGTH_8_BIT;
		else
			return LENGTH_9_BIT;
	}

	oversample_t get_oversample() override {
#ifndef USART_CR1_OVER8
		return OVERSAMPLE_16_BIT;
#else
		// todo:
		return OVERSAMPLE_16_BIT;
#endif
	}

	uint32_t get_baud() override {
		return baud;
	}

	state_t get_state() override {
		state_t state = STATE_NONE;

		// Включён
		if ((READ_REG(uart_def->CR1) & USART_CR1_UE) != RESET)
			state |= STATE_ENABLED;

		// Линия IDLE обнаружена
		if ((READ_REG(uart_def->SR) & USART_SR_IDLE) != RESET)
			state |= STATE_IDLE;

		// Приём включён и регистр приёма пуст
		if (((READ_REG(uart_def->CR1) & USART_CR1_RE) != RESET) & ((READ_REG(uart_def->SR) & USART_SR_RXNE) == RESET))
			state |= STATE_RX_BUSY;

		// Передача включена и не завершена
		if (((READ_REG(uart_def->CR1) & USART_CR1_TE) != RESET) & ((READ_REG(uart_def->SR) & USART_SR_TC) == RESET))
			state |= STATE_TX_BUSY;

		if (get_error() != ERROR_NONE)
			state |= STATE_ERROR;

		return state;
	}

	error_t get_error() override {
		error_t error = ERROR_NONE;

		if ((READ_REG(uart_def->SR) & USART_SR_PE) != RESET)
			error |= ERROR_PARITY;

		if ((READ_REG(uart_def->SR) & USART_SR_FE) != RESET)
			error |= ERROR_FRAMING;

		if ((READ_REG(uart_def->SR) & USART_SR_NE) != RESET)
			error |= ERROR_NOISE;

		if ((READ_REG(uart_def->SR) & USART_SR_ORE) != RESET)
			error |= ERROR_OVERRUN;

		return error;
	}



	sys::result_t enable() override {
		SET_BIT(uart_def->CR1, USART_CR1_UE);
		return (READ_REG(uart_def->CR1) & USART_CR1_UE) != RESET ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t disable() override {
		CLEAR_BIT(uart_def->CR1, USART_CR1_UE);
		return (READ_REG(uart_def->CR1) & USART_CR1_UE) == RESET ? sys::RES_OK : sys::RES_ERROR;
	}



	sys::result_t transmit(const uint8_t *p_data, size_t size, uint32_t timeout) override {

	}

	sys::result_t receive(const uint8_t *p_data, size_t size, uint32_t timeout) override {

	}

	sys::result_t abort() override {

	}

	sys::result_t abort_transmit() override {

	}

	sys::result_t abort_receive() override {

	}



private:
	uint32_t baud;
	uart_t uart_num;
	USART_TypeDef *uart_def;
};
}


#endif /* STM32F1_UART_H */