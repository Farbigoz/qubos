#ifndef STM32F1_IOMUX_H
#define STM32F1_IOMUX_H

#include "stm32f1xx.h"

#include "arch/ARM/STM32/F1/rcc.h"

#include "system/types.h"
#include "system/interface/iomux.h"


/*
                                        CAN1
 ┌──────────────────────┬───────────────────┬───────────────────┬───────────────────┐
 │ Alternative Function │ CAN1_REMAP = 0b00 │ CAN1_REMAP = 0b10 │ CAN1_REMAP = 0b11 │
 ├──────────────────────┼───────────────────┼───────────────────┼───────────────────┤
 │       CAN1_RX        │       PA11        │       PB8         │       PD0         │
 ├──────────────────────┼───────────────────┼───────────────────┼───────────────────┤
 │       CAN1_TX        │       PA12        │       PB9         │       PD1         │
 └──────────────────────┴───────────────────┴───────────────────┴───────────────────┘

                                        CAN2
 ┌──────────────────────┬─────────────────────────────┬─────────────────────────────┐
 │ Alternative Function │      CAN2_REMAP = 0b0       │       CAN2_REMAP = 0b1      │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       CAN2_RX        │            PB12             │             PB5             │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       CAN2_TX        │            PB13             │             PB6             │
 └──────────────────────┴─────────────────────────────┴─────────────────────────────┘

                                        TIM5
 ┌──────────────────────┬─────────────────────────────┬─────────────────────────────┐
 │ Alternative Function │    TIM5_CH4_REMAP = 0b0     │     TIM5_CH4_REMAP = 0b1    │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       TIM5_CH4       │             PA3             │             LSI             │
 └──────────────────────┴─────────────────────────────┴─────────────────────────────┘

                                        TIM4
 ┌──────────────────────┬─────────────────────────────┬─────────────────────────────┐
 │ Alternative Function │      TIM4_REMAP = 0b0       │       TIM4_REMAP = 0b1      │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       TIM4_CH1       │             PB6             │            PD12             │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       TIM4_CH2       │             PB7             │            PD13             │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       TIM4_CH3       │             PB8             │            PD14             │
 ├──────────────────────┼─────────────────────────────┼─────────────────────────────┤
 │       TIM4_CH4       │             PB9             │            PD15             │
 └──────────────────────┴─────────────────────────────┴─────────────────────────────┘

                                        TIM3
 ┌──────────────────────┬───────────────────┬───────────────────┬───────────────────┐
 │ Alternative Function │ TIM3_REMAP = 0b00 │ TIM3_REMAP = 0b10 │ TIM3_REMAP = 0b11 │
 ├──────────────────────┼───────────────────┼───────────────────┼───────────────────┤
 │       TIM3_CH1       │        PA6        │        PB4        │        PC6        │
 ├──────────────────────┼───────────────────┼───────────────────┼───────────────────┤
 │       TIM3_CH2       │        PA7        │        PB5        │        PC7        │
 ├──────────────────────┼───────────────────┴───────────────────┼───────────────────┤
 │       TIM3_CH3       │                  PB0                  │        PC8        │
 ├──────────────────────┼───────────────────────────────────────┼───────────────────┤
 │       TIM3_CH4       │                  PB1                  │        PC9        │
 └──────────────────────┴───────────────────────────────────────┴───────────────────┘

 // todo

 */


namespace arch {
class iomux : public sys::iomux {
public:
	iomux() = default;

public:
	sys::result_t deinit() override {
		return sys::RES_OK;
	}

// sys::clock interface
public:
	uint32_t get_clock_freq() override {
		return arch::rcc::APB2::get_clk();
	}

	sys::result_t enable_clock() override {
		return arch::rcc::APB2::enable(rcc::APB2::CLK_AFIO);
	}

	sys::result_t disable_clock() override {
		return arch::rcc::APB2::disable(rcc::APB2::CLK_AFIO);
	}


// sys::iomux interface
public:
	bool support() override {
		return true;
	}

	sys::result_t set_remap(alt_remap_t alt, remap_num_t num) override {
		return set_remap_static(alt, num);
	}

	remap_num_t get_remap_num(alt_remap_t alt) override {
		return get_remap_num_static(alt);
	}

// static
public:
	static sys::result_t set_remap_static(alt_remap_t alt, remap_num_t num) {
		uint32_t pos;
		uint32_t mask;
		__IO uint32_t *reg;

		if (get_cfg(alt, &pos, &mask, &reg) == sys::RES_ERROR)
			return sys::RES_ERROR;

		if ((num << pos) & (~mask))
			return sys::RES_ERROR;

		SET_BIT(*reg, num << pos);

		return sys::RES_OK;
	}

	static remap_num_t get_remap_num_static(alt_remap_t alt) {
		uint32_t pos;
		uint32_t mask;
		__IO uint32_t *reg;

		if (get_cfg(alt, &pos, &mask, &reg) == sys::RES_ERROR)
			return REMAP_NUM_0;

		uint32_t num = READ_BIT(*reg, mask) >> pos;

		return (remap_num_t)num;
	}
	
private:
	static sys::result_t get_cfg(alt_remap_t alt, uint32_t *pos, uint32_t *mask, __IO uint32_t **reg) {
		switch (alt) {
			case sys::iomux::REMAP_SPI1:
				*pos = AFIO_MAPR_SPI1_REMAP_Pos;
				*mask = AFIO_MAPR_SPI1_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_I2C1:
				*pos = AFIO_MAPR_I2C1_REMAP_Pos;
				*mask = AFIO_MAPR_I2C1_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_UART1:
				*pos = AFIO_MAPR_USART1_REMAP_Pos;
				*mask = AFIO_MAPR_USART1_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_UART2:
				*pos = AFIO_MAPR_USART2_REMAP_Pos;
				*mask = AFIO_MAPR_USART2_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_UART3:
				*pos = AFIO_MAPR_USART3_REMAP_Pos;
				*mask = AFIO_MAPR_USART3_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_TIM1:
				*pos = AFIO_MAPR_TIM1_REMAP_Pos;
				*mask = AFIO_MAPR_TIM1_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_TIM2:
				*pos = AFIO_MAPR_TIM2_REMAP_Pos;
				*mask = AFIO_MAPR_TIM2_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_TIM3:
				*pos = AFIO_MAPR_TIM3_REMAP_Pos;
				*mask = AFIO_MAPR_TIM3_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_TIM4:
				*pos = AFIO_MAPR_TIM4_REMAP_Pos;
				*mask = AFIO_MAPR_TIM4_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_CAN1:
				*pos = AFIO_MAPR_CAN_REMAP_Pos;
				*mask = AFIO_MAPR_CAN_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_TIM5_CH4:
				*pos = AFIO_MAPR_TIM5CH4_IREMAP_Pos;
				*mask = AFIO_MAPR_TIM5CH4_IREMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_ETH:
				*pos = AFIO_MAPR_ETH_REMAP_Pos;
				*mask = AFIO_MAPR_ETH_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_CAN2:
				*pos = AFIO_MAPR_CAN2_REMAP_Pos;
				*mask = AFIO_MAPR_CAN2_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_EMAC_MII_RMII:
				*pos = AFIO_MAPR_MII_RMII_SEL_Pos;
				*mask = AFIO_MAPR_MII_RMII_SEL_Msk;
				*reg = &AFIO->MAPR;
				break;
				// todo: swj
			case sys::iomux::REMAP_SPI3:
				*pos = AFIO_MAPR_SPI3_REMAP_Pos;
				*mask = AFIO_MAPR_SPI3_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_TIM2_IT:
				*pos = AFIO_MAPR_TIM2ITR1_IREMAP_Pos;
				*mask = AFIO_MAPR_TIM2ITR1_IREMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
			case sys::iomux::REMAP_EMAC_PTP_PPS:
				*pos = AFIO_MAPR_PTP_PPS_REMAP_Pos;
				*mask = AFIO_MAPR_PTP_PPS_REMAP_Msk;
				*reg = &AFIO->MAPR;
				break;
#ifdef AFIO_MAPR2_TIM9_REMAP
				case sys::iomux::REMAP_TIM9:
				*pos = AFIO_MAPR2_TIM9_REMAP_Pos;
				*mask = AFIO_MAPR2_TIM9_REMAP_Msk;
				*reg = &AFIO->MAPR2;
				break;
#endif
#ifdef AFIO_MAPR2_TIM10_REMAP
				case sys::iomux::REMAP_TIM10:
				*pos = AFIO_MAPR2_TIM10_REMAP_Pos;
				*mask = AFIO_MAPR2_TIM10_REMAP_Msk;
				*reg = &AFIO->MAPR2;
				break;
#endif
#ifdef AFIO_MAPR2_TIM11_REMAP
				case sys::iomux::REMAP_TIM11:
				*pos = AFIO_MAPR2_TIM11_REMAP_Pos;
				*mask = AFIO_MAPR2_TIM11_REMAP_Msk;
				*reg = &AFIO->MAPR2;
				break;
#endif
#ifdef AFIO_MAPR2_TIM9_REMAP
				case sys::iomux::REMAP_TIM13:
				*pos = AFIO_MAPR2_TIM13_REMAP_Pos;
				*mask = AFIO_MAPR2_TIM13_REMAP_Msk;
				*reg = &AFIO->MAPR2;
				break;
#endif
#ifdef AFIO_MAPR2_TIM9_REMAP
				case sys::iomux::REMAP_TIM14:
				*pos = AFIO_MAPR2_TIM14_REMAP_Pos;
				*mask = AFIO_MAPR2_TIM14_REMAP_Msk;
				*reg = &AFIO->MAPR2;
				break;
#endif
			default:
				return sys::RES_ERROR;
		}
		return sys::RES_OK;
	}
};
}

#endif /* STM32F1_IOMUX_H */