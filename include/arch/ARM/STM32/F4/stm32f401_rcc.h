#ifndef STM32F401_RCC_H
#define STM32F401_RCC_H

#include "stm32f4xx.h"
#include "system/types.h"


namespace arch {
	class rcc {
	public:
		class HSI;
		class HSE;
		class SYSCLK;
		class PLL;

	public:
		class HSI {
		public:
			static const uint32_t CLK_FREQ = 16000000;

		public:
			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_HSION);
				int i = 0xffff;
				while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline void disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_HSION);
			}

			static inline bool is_enable() {
				return SET_BIT(RCC->CR, RCC_CR_HSION) && READ_BIT(RCC->CR, RCC_CR_HSIRDY);
			}
		};

		class HSE {
		public:
			volatile static inline uint32_t CLK_FREQ = 8000000;

		public:
			static constexpr sys::result_t set_freq(uint32_t freq) {
				if ((freq < 3000000) || (freq > 25000000)) return sys::RES_ERROR;
				CLK_FREQ = freq;
				return sys::RES_OK;
			}

			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_HSEON);
				int i = 0xffff;
				while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline void disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
			}

			static inline bool is_enable() {
				return SET_BIT(RCC->CR, RCC_CR_HSEON) && READ_BIT(RCC->CR, RCC_CR_HSERDY);
			}
		};

		class SYSCLK {
		public:
			typedef enum {
				SRC_HSI = RCC_CFGR_SW_HSI,
				SRC_HSE = RCC_CFGR_SW_HSE,
				SRC_PLL = RCC_CFGR_SW_PLL
			} source_t;

		public:
			static inline sys::result_t set_source(source_t src) {
				SET_BIT(RCC->CFGR, src);
				return (READ_BIT(RCC->CFGR, RCC_CFGR_SW << (RCC_CFGR_SWS_Pos - RCC_CFGR_SW_Pos)) == (src << (RCC_CFGR_SWS_Pos - RCC_CFGR_SW_Pos))) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline source_t get_source() {
				return (source_t)READ_BIT(RCC->CFGR, RCC_CFGR_SW);
			}

			// todo: CSS
		};

		class PLL {
		public:
			typedef enum {
				SRC_HSI = RCC_PLLCFGR_PLLSRC_HSI,
				SRC_HSE = RCC_PLLCFGR_PLLSRC_HSE
			} source_t;

			typedef enum {
				DIV_P_2 = 0x00U,
				DIV_P_4 = 0x01U,
				DIV_P_6 = 0x02U,
				DIV_P_8 = 0x03U,
			} div_p_t;

		public:
			static inline sys::result_t set_source(source_t src) {
				SET_BIT(RCC->PLLCFGR, src);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC) == src) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline source_t get_source() {
				return (source_t)READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC);
			}

			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_PLLON);
				int i = 0xfff;
				while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;
				return sys::RES_OK;
			}

			static inline sys::result_t disable() {
				if (SYSCLK::get_source() == SYSCLK::SRC_PLL)
					return sys::RES_ERROR;
				CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
				return sys::RES_OK;
			}

			static inline bool is_enable() {
				return SET_BIT(RCC->CR, RCC_CR_PLLON) && READ_BIT(RCC->CR, RCC_CR_PLLRDY);
			}

			static inline sys::result_t set_predivM(uint32_t m) {
				if ((m < 2) || (m > 63)) return sys::RES_ERROR;
				SET_BIT(RCC->PLLCFGR, m << RCC_PLLCFGR_PLLM_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_Msk) == (m << RCC_PLLCFGR_PLLM_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline sys::result_t set_multN(uint32_t n) {
				if ((n < 50) || (n > 432)) return sys::RES_ERROR;
				SET_BIT(RCC->PLLCFGR, n << RCC_PLLCFGR_PLLN_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk) == (n << RCC_PLLCFGR_PLLN_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline sys::result_t set_divP(div_p_t p) {
				SET_BIT(RCC->PLLCFGR, p << RCC_PLLCFGR_PLLP_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk) == (p << RCC_PLLCFGR_PLLP_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline sys::result_t set_divQ(uint32_t q) {
				if ((q < 2) || (q > 15)) return sys::RES_ERROR;
				SET_BIT(RCC->PLLCFGR, q << RCC_PLLCFGR_PLLQ_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk) == (q << RCC_PLLCFGR_PLLQ_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}
		};

	};
}


void test_rcc() {
	sys::result_t RESULT;
	//for (int i = 0; i < 0xffffff; i++);

	(*(__IO uint8_t *)(0x40023C00U) = (uint8_t)(FLASH_ACR_LATENCY_4WS));

	RESULT = arch::rcc::SYSCLK::set_source(arch::rcc::SYSCLK::SRC_HSI);

	RESULT = arch::rcc::HSE::set_freq(25000000);
	RESULT = arch::rcc::HSE::enable();
	//RESULT = arch::rcc::SW::set_source(arch::rcc::SW::SRC_HSE);

	RESULT = arch::rcc::PLL::disable();
	RESULT = arch::rcc::PLL::set_source(arch::rcc::PLL::SRC_HSE);
	RESULT = arch::rcc::PLL::set_predivM(25);
	RESULT = arch::rcc::PLL::set_multN(336);
	//RESULT = arch::rcc::PLL::set_multN(240);
	RESULT = arch::rcc::PLL::set_divP(arch::rcc::PLL::DIV_P_4);
	RESULT = arch::rcc::PLL::enable();

	//SET_BIT(RCC->CFGR, 0x04U << RCC_CFGR_PPRE1_Pos);

	RESULT = arch::rcc::SW::set_source(arch::rcc::SW::SRC_PLL);
}


#endif /* STM32F401_RCC_H */