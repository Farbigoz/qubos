#ifndef STM32F1_RCC_H
#define STM32F1_RCC_H

#include "stm32f1xx.h"
#include "system/system.h"


#define HSI_FREQ            8000000
#define HSE_DEFAULT_FREQ    8000000

#define HSI_ENABLE_WAIT     0xffff
#define HSE_ENABLE_WAIT     0xffff
#define PLL_ENABLE_WAIT     0xffff


#ifndef RCC_APB2ENR_IOPCEN
#define RCC_APB2ENR_IOPCEN (0x00U)
#endif
#ifndef RCC_APB2ENR_IOPDEN
#define RCC_APB2ENR_IOPDEN (0x00U)
#endif
#ifndef RCC_APB2ENR_IOPEEN
#define RCC_APB2ENR_IOPEEN (0x00U)
#endif
#ifndef RCC_APB2ENR_IOPFEN
#define RCC_APB2ENR_IOPFEN (0x00U)
#endif
#ifndef RCC_APB2ENR_IOPGEN
#define RCC_APB2ENR_IOPGEN (0x00U)
#endif
#ifndef RCC_APB2ENR_ADC3EN
#define RCC_APB2ENR_ADC3EN (0x00U)
#endif
#ifndef RCC_APB2ENR_TIM9EN
#define RCC_APB2ENR_TIM9EN (0x00U)
#endif
#ifndef RCC_APB2ENR_TIM10EN
#define RCC_APB2ENR_TIM10EN (0x00U)
#endif
#ifndef RCC_APB2ENR_TIM11EN
#define RCC_APB2ENR_TIM11EN (0x00U)
#endif



namespace arch {
	class rcc {
	public:
		class HSI;
		class HSE;
		class SYSCLK;
		class PLL;
		class PLL2;
		class PLL3;
		class PREDIV1;
		class PREDIV2;
		class AHB;
		class APB1;
		class APB2;

	public:
		class HSI {
		public:
			static const uint32_t CLK_FREQ = HSI_FREQ;

		public:
			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_HSION);
				int i = HSI_ENABLE_WAIT;
				while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline void disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_HSION);
			}

			static inline bool is_enable() {
				return READ_BIT(RCC->CR, RCC_CR_HSION) && READ_BIT(RCC->CR, RCC_CR_HSIRDY);
			}

			static inline uint32_t get_clk() {
				return CLK_FREQ;
			}
		};

		class HSE {
		public:
			volatile static inline uint32_t CLK_FREQ = HSE_DEFAULT_FREQ;

		public:
			static constexpr sys::result_t set_freq(uint32_t freq) {
				if ((freq < RCC_HSE_MIN) || (freq > RCC_HSE_MAX)) return sys::RES_ERROR;
				CLK_FREQ = freq;
				return sys::RES_OK;
			}

			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_HSEON);
				int i = HSE_ENABLE_WAIT;
				while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline void disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
			}

			static inline bool is_enable() {
				return READ_BIT(RCC->CR, RCC_CR_HSEON) && READ_BIT(RCC->CR, RCC_CR_HSERDY);
			}
			
			static inline uint32_t get_clk() {
				return CLK_FREQ;
			} 
		};

		class PLL {
		public:
			typedef enum {
				SRC_HSI,
				SRC_PREDIV1
			} source_t;

			typedef enum {
				MULT_4   = RCC_CFGR_PLLMULL4,
				MULT_5   = RCC_CFGR_PLLMULL5,
				MULT_6   = RCC_CFGR_PLLMULL6,
				MULT_6_5 = RCC_CFGR_PLLMULL6_5,
				MULT_7   = RCC_CFGR_PLLMULL7,
				MULT_8   = RCC_CFGR_PLLMULL8,
				MULT_9   = RCC_CFGR_PLLMULL9,
			} mult_t;

		public:
			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_PLLON);
				int i = PLL_ENABLE_WAIT;
				while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline sys::result_t disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
				return READ_BIT(RCC->CR, RCC_CR_PLLON) == RESET ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline bool is_enable() {
				return READ_BIT(RCC->CR, RCC_CR_PLLON) && READ_BIT(RCC->CR, RCC_CR_PLLRDY);
			}

			static sys::result_t set_source(source_t src) {
				if (is_enable()) return sys::RES_BUSY;

				if (src == SRC_HSI)
				{
					CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
					return READ_BIT(RCC->CFGR, RCC_CFGR_PLLSRC) == RESET ? sys::RES_OK : sys::RES_ERROR;
				}
				else
				{
					SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
					return READ_BIT(RCC->CFGR, RCC_CFGR_PLLSRC) == RCC_CFGR_PLLSRC ? sys::RES_OK : sys::RES_ERROR;
				}
			}

			static source_t get_source() {
				return READ_BIT(RCC->CFGR, RCC_CFGR_PLLSRC) == RCC_CFGR_PLLSRC ? SRC_PREDIV1 : SRC_HSI;
			}

			static sys::result_t set_mult(mult_t m) {
				if (is_enable()) return sys::RES_BUSY;

				SET_BIT(RCC->CFGR, m);
				return (READ_BIT(RCC->CFGR, RCC_CFGR_PLLMULL) == m) ? sys::RES_OK : sys::RES_ERROR;
			}

			static mult_t get_mult() {
				return (mult_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PLLMULL));
			}

			static uint32_t get_clk() {
				uint32_t clk;
				if (get_source() == SRC_HSI)
					clk = HSI::get_clk() / 2;
				else
					clk = PREDIV1::get_clk();

				switch (get_mult()) {
					case MULT_4:   return clk * 4;
					case MULT_5:   return clk * 5;
					case MULT_6:   return clk * 6;
					case MULT_6_5: return (clk * 13) / 2;
					case MULT_7:   return clk * 7;
					case MULT_8:   return clk * 8;
					case MULT_9:   return clk * 9;
					default: return 0;
				}
			}
		};

		class PLL2 {
		public:
			typedef enum {
				MULT_8  = RCC_CFGR2_PLL2MUL8,
				MULT_9  = RCC_CFGR2_PLL2MUL9,
				MULT_10 = RCC_CFGR2_PLL2MUL10,
				MULT_11 = RCC_CFGR2_PLL2MUL11,
				MULT_12 = RCC_CFGR2_PLL2MUL12,
				MULT_13 = RCC_CFGR2_PLL2MUL13,
				MULT_14 = RCC_CFGR2_PLL2MUL14,
				MULT_16 = RCC_CFGR2_PLL2MUL16,
				MULT_20 = RCC_CFGR2_PLL2MUL20,
			} mult_t;

		public:
			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_PLL2ON);
				int i = PLL_ENABLE_WAIT;
				while (READ_BIT(RCC->CR, RCC_CR_PLL2RDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline void disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);
			}

			static inline bool is_enable() {
				return READ_BIT(RCC->CR, RCC_CR_PLL2ON) && READ_BIT(RCC->CR, RCC_CR_PLL2RDY);
			}

			static sys::result_t set_mult(mult_t m) {
				if (is_enable()) return sys::RES_BUSY;

				SET_BIT(RCC->CFGR2, m);
				return (READ_BIT(RCC->CFGR2, RCC_CFGR2_PLL2MUL) == m) ? sys::RES_OK : sys::RES_ERROR;
			}

			static mult_t get_mult() {
				return (mult_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PLL2MUL));
			}

			static uint32_t get_clk() {
				uint32_t clk = PREDIV2::get_clk();
				switch (get_mult()) {
					case MULT_8:  return clk * 8;
					case MULT_9:  return clk * 9;
					case MULT_10: return clk * 10;
					case MULT_11: return clk * 11;
					case MULT_12: return clk * 12;
					case MULT_13: return clk * 13;
					case MULT_14: return clk * 14;
					case MULT_16: return clk * 16;
					case MULT_20: return clk * 20;
					default: return 0;
				}
			}
		};

		class PLL3 {
		public:
			typedef enum {
				MULT_8  = RCC_CFGR2_PLL3MUL8,
				MULT_9  = RCC_CFGR2_PLL3MUL9,
				MULT_10 = RCC_CFGR2_PLL3MUL10,
				MULT_11 = RCC_CFGR2_PLL3MUL11,
				MULT_12 = RCC_CFGR2_PLL3MUL12,
				MULT_13 = RCC_CFGR2_PLL3MUL13,
				MULT_14 = RCC_CFGR2_PLL3MUL14,
				MULT_16 = RCC_CFGR2_PLL3MUL16,
				MULT_20 = RCC_CFGR2_PLL3MUL20,
			} mult_t;

		public:
			static inline sys::result_t enable() {
				SET_BIT(RCC->CR, RCC_CR_PLL3ON);
				int i = PLL_ENABLE_WAIT;
				while (READ_BIT(RCC->CR, RCC_CR_PLL3RDY) == RESET)
					if (--i == 0)
						return sys::RES_TIMEOUT;

				return sys::RES_OK;
			}

			static inline void disable() {
				CLEAR_BIT(RCC->CR, RCC_CR_PLL3ON);
			}

			static inline bool is_enable() {
				return READ_BIT(RCC->CR, RCC_CR_PLL3ON) && READ_BIT(RCC->CR, RCC_CR_PLL3RDY);
			}

			static sys::result_t set_mult(mult_t m) {
				if (is_enable()) return sys::RES_BUSY;

				SET_BIT(RCC->CFGR2, m);
				return (READ_BIT(RCC->CFGR2, RCC_CFGR2_PLL3MUL) == m) ? sys::RES_OK : sys::RES_ERROR;
			}

			static mult_t get_mult() {
				return (mult_t)(READ_BIT(RCC->CFGR2, RCC_CFGR2_PLL3MUL));
			}
		};

		class PREDIV1 {
		public:
			typedef enum {
				SRC_HSE,
				SRC_PLL2
			} source_t;

		public:
			static sys::result_t set_source(source_t src) {
				if (PLL::is_enable()) return sys::RES_BUSY;
				
				if (src == SRC_HSE)
				{
					CLEAR_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC);
					return READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC) == RESET ? sys::RES_OK : sys::RES_ERROR;
				}
				else
				{
					SET_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC);
					return READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC) == RCC_CFGR2_PREDIV1SRC ? sys::RES_OK : sys::RES_ERROR;
				}
			}

			static source_t get_source() {
				return READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC) == RCC_CFGR2_PREDIV1SRC ? SRC_PLL2 : SRC_HSE;
			}

			static sys::result_t set_div(uint32_t div) {
				if (PLL::is_enable()) return sys::RES_BUSY;

				if ((div < 1) || (div > 16)) return sys::RES_ERROR;
				div -= 1;
				SET_BIT(RCC->CFGR2, div << RCC_CFGR2_PREDIV1_Pos);
				return READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1) == (div << RCC_CFGR2_PREDIV1_Pos) ? sys::RES_OK : sys::RES_ERROR;
			}

			static uint32_t get_div() {
				uint32_t div = READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1) >> RCC_CFGR2_PREDIV1_Pos;
				return div + 1;
			}

			static uint32_t get_clk() {
				uint32_t clk;
				if (get_source() == SRC_HSE)
					clk = HSE::get_clk();
				else
					clk = PLL2::get_clk();

				return clk / get_div();
			}
		};

		class PREDIV2 {
		public:
			static sys::result_t set_div(uint32_t div) {
				if (PLL2::is_enable() || PLL3::is_enable()) return sys::RES_BUSY;

				if ((div < 1) || (div > 16)) return sys::RES_ERROR;
				div -= 1;

				// MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV2, div << RCC_CFGR2_PREDIV2_Pos);
				SET_BIT(RCC->CFGR2, div << RCC_CFGR2_PREDIV2_Pos);
				return READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV2) == (div << RCC_CFGR2_PREDIV2_Pos) ? sys::RES_OK : sys::RES_ERROR;
			}

			static uint32_t get_div() {
				uint32_t div = READ_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV2) >> RCC_CFGR2_PREDIV2_Pos;
				return div + 1;
			}

			static uint32_t get_clk() {
				return HSE::get_clk() / get_div();
			}
		};

		class MCO {
		public:
			typedef enum {
				OUT_NONE         = RCC_CFGR_MCO_NOCLOCK,
				OUT_SYSCLK       = RCC_CFGR_MCO_SYSCLK,
				OUT_HSI          = RCC_CFGR_MCO_HSI,
				OUT_HSE          = RCC_CFGR_MCO_HSE,
				OUT_PLLCLK_DIV2  = RCC_CFGR_MCO_PLLCLK_DIV2,
				OUT_PLL2CLK      = RCC_CFGR_MCO_PLL2CLK,
				OUT_PLL3CLK_DIV2 = RCC_CFGR_MCO_PLL3CLK_DIV2,
				OUT_XT1          = RCC_CFGR_MCO_EXT_HSE,
				OUT_PLL3CLK      = RCC_CFGR_MCO_PLL3CLK,
			} output_t;

		public:
			static sys::result_t set_output(output_t out) {
				SET_BIT(RCC->CFGR, out);
				return READ_BIT(RCC->CFGR, RCC_CFGR_MCO) == out ? sys::RES_OK : sys::RES_ERROR;
			}

			static output_t get_output() {
				return (output_t)(READ_BIT(RCC->CFGR, RCC_CFGR_MCO));
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

			static uint32_t get_clk() {
				switch (get_source()) {
					case SRC_HSI: return HSI::get_clk();
					case SRC_HSE: return HSE::get_clk();
					case SRC_PLL: return PLL::get_clk();
					default: return 0;
				}
			}

			// todo: CSS
		};

		class AHB {
		public:
			typedef enum {
				DIV_1   = RCC_CFGR_HPRE_DIV1,
				DIV_2   = RCC_CFGR_HPRE_DIV2,
				DIV_4   = RCC_CFGR_HPRE_DIV4,
				DIV_8   = RCC_CFGR_HPRE_DIV8,
				DIV_16  = RCC_CFGR_HPRE_DIV16,
				DIV_64  = RCC_CFGR_HPRE_DIV64,
				DIV_128 = RCC_CFGR_HPRE_DIV128,
				DIV_256 = RCC_CFGR_HPRE_DIV256,
				DIV_512 = RCC_CFGR_HPRE_DIV512
			} div_t;

			typedef enum {
				CLK_DMA1       = RCC_AHBENR_DMA1EN,
				CLK_DMA2       = RCC_AHBENR_DMA2EN,
				CLK_SRAM       = RCC_AHBENR_SRAMEN,
				CLK_CRC        = RCC_AHBENR_CRCEN,
				CLK_OTG        = RCC_AHBENR_OTGFSEN,
				CLK_ETH_MAC    = RCC_AHBENR_ETHMACEN,
				CLK_ETH_MAC_TX = RCC_AHBENR_ETHMACTXEN,
				CLK_ETH_MAC_RX = RCC_AHBENR_ETHMACRXEN
			} periphery_clock_t;

		public:
			static sys::result_t set_div(div_t d) {
				SET_BIT(RCC->CFGR, d);
				return READ_BIT(RCC->CFGR, RCC_CFGR_HPRE) == d ? sys::RES_OK : sys::RES_ERROR;
			}

			static div_t get_div() {
				return (div_t) READ_BIT(RCC->CFGR, RCC_CFGR_HPRE);
			}
			
			static uint32_t get_clk() {
				uint32_t clk = SYSCLK::get_clk();
				switch (get_div()) {
					case DIV_1:   return clk / 1;
					case DIV_2:   return clk / 2;
					case DIV_4:   return clk / 4;
					case DIV_8:   return clk / 8;
					case DIV_16:  return clk / 16;
					case DIV_64:  return clk / 64;
					case DIV_128: return clk / 128;
					case DIV_256: return clk / 256;
					case DIV_512: return clk / 512;
					default: return 0;
				}
			}

			static sys::result_t enable(periphery_clock_t clk) {
				SET_BIT(RCC->AHBENR, clk);
				return READ_BIT(RCC->AHBENR, clk) == RESET ? sys::RES_ERROR : sys::RES_OK;
			}

			static sys::result_t disable(periphery_clock_t clk) {
				CLEAR_BIT(RCC->AHBENR, clk);
				return READ_BIT(RCC->AHBENR, clk) == RESET ? sys::RES_OK : sys::RES_ERROR;
			}
		};

		class APB1 {
		public:
			typedef enum {
				DIV_1  = RCC_CFGR_PPRE1_DIV1,
				DIV_2  = RCC_CFGR_PPRE1_DIV2,
				DIV_4  = RCC_CFGR_PPRE1_DIV4,
				DIV_8  = RCC_CFGR_PPRE1_DIV8,
				DIV_16 = RCC_CFGR_PPRE1_DIV16,
			} div_t;

			typedef enum {
				CLK_TIM2   = RCC_APB1ENR_TIM2EN,
				CLK_TIM3   = RCC_APB1ENR_TIM3EN,
				CLK_TIM4   = RCC_APB1ENR_TIM4EN,
				CLK_TIM5   = RCC_APB1ENR_TIM5EN,
				CLK_TIM6   = RCC_APB1ENR_TIM6EN,
				CLK_TIM7   = RCC_APB1ENR_TIM7EN,
				CLK_WWDGEN = RCC_APB1ENR_WWDGEN,
				CLK_SPI2   = RCC_APB1ENR_SPI2EN,
				CLK_SPI3   = RCC_APB1ENR_SPI3EN,
				CLK_UART2  = RCC_APB1ENR_USART2EN,
				CLK_UART3  = RCC_APB1ENR_USART3EN,
				CLK_UART4  = RCC_APB1ENR_UART4EN,
				CLK_UART5  = RCC_APB1ENR_UART5EN,
				CLK_I2C1   = RCC_APB1ENR_I2C1EN,
				CLK_I2C2   = RCC_APB1ENR_I2C2EN,
				CLK_CAN1   = RCC_APB1ENR_CAN1EN,
				CLK_CAN2   = RCC_APB1ENR_CAN2EN,
				CLK_BKP    = RCC_APB1ENR_BKPEN,
				CLK_PWR    = RCC_APB1ENR_PWREN,
				CLK_DAC    = RCC_APB1ENR_DACEN
			} periphery_clock_t;

		public:
			static sys::result_t set_div(div_t d) {
				// todo: check clock (max 36 MHz)
				SET_BIT(RCC->CFGR, d);
				return READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1) == d ? sys::RES_OK : sys::RES_ERROR;
			}

			static div_t get_div() {
				return (div_t) READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1);
			}

			static uint32_t get_clk() {
				uint32_t clk = AHB::get_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk / (2 << (div & (RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1) >> RCC_CFGR_PPRE1_Pos));
				else
					return clk;
			}

			static uint32_t get_tim_clk() {
				uint32_t clk = get_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk * 2;
				else
					return clk;
			}

			static sys::result_t enable(periphery_clock_t clk) {
				SET_BIT(RCC->APB1ENR, clk);
				return READ_BIT(RCC->APB1ENR, clk) == RESET ? sys::RES_ERROR : sys::RES_OK;
			}

			static sys::result_t disable(periphery_clock_t clk) {
				CLEAR_BIT(RCC->APB1ENR, clk);
				return READ_BIT(RCC->APB1ENR, clk) == RESET ? sys::RES_OK : sys::RES_ERROR;
			}
		};

		class APB2 {
		public:
			typedef enum {
				DIV_1  = RCC_CFGR_PPRE2_DIV1,
				DIV_2  = RCC_CFGR_PPRE2_DIV2,
				DIV_4  = RCC_CFGR_PPRE2_DIV4,
				DIV_8  = RCC_CFGR_PPRE2_DIV8,
				DIV_16 = RCC_CFGR_PPRE2_DIV16,
			} div_t;

			typedef enum {
				ADC_DIV_2 = RCC_CFGR_ADCPRE_DIV2,
				ADC_DIV_4 = RCC_CFGR_ADCPRE_DIV4,
				ADC_DIV_6 = RCC_CFGR_ADCPRE_DIV6,
				ADC_DIV_8 = RCC_CFGR_ADCPRE_DIV8,
			} adc_div_t;

			typedef enum {
				CLK_AFIO  = RCC_APB2ENR_AFIOEN,
				CLK_GPIOA = RCC_APB2ENR_IOPAEN,
				CLK_GPIOB = RCC_APB2ENR_IOPBEN,
				CLK_GPIOC = RCC_APB2ENR_IOPCEN,
				CLK_GPIOD = RCC_APB2ENR_IOPDEN,
				CLK_GPIOE = RCC_APB2ENR_IOPEEN,
				CLK_GPIOF = RCC_APB2ENR_IOPFEN,
				CLK_GPIOG = RCC_APB2ENR_IOPGEN,
				CLK_ADC1  = RCC_APB2ENR_ADC1EN,
				CLK_ADC2  = RCC_APB2ENR_ADC2EN,
				CLK_TIM1  = RCC_APB2ENR_TIM1EN,
				CLK_SPI1  = RCC_APB2ENR_SPI1EN,
				CLK_UART1 = RCC_APB2ENR_USART1EN,
				CLK_ADC3  = RCC_APB2ENR_ADC3EN,
				CLK_TIM9  = RCC_APB2ENR_TIM9EN,
				CLK_TIM10 = RCC_APB2ENR_TIM10EN,
				CLK_TIM11 = RCC_APB2ENR_TIM11EN,
			} periphery_clock_t;

		public:
			static sys::result_t set_div(div_t d) {
				SET_BIT(RCC->CFGR, d);
				return READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2) == d ? sys::RES_OK : sys::RES_ERROR;
			}

			static div_t get_div() {
				return (div_t) READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2);
			}

			static sys::result_t set_adc_div(adc_div_t d) {
				SET_BIT(RCC->CFGR, d);
				return READ_BIT(RCC->CFGR, RCC_CFGR_ADCPRE) == d ? sys::RES_OK : sys::RES_ERROR;
			}

			static adc_div_t get_adc_div() {
				return (adc_div_t) READ_BIT(RCC->CFGR, RCC_CFGR_ADCPRE);
			}

			static uint32_t get_clk() {
				uint32_t clk = AHB::get_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk / (2 << (div & (RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1) >> RCC_CFGR_PPRE1_Pos));
				else
					return clk;
			}

			static uint32_t get_tim_clk() {
				uint32_t clk = get_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk * 2;
				else
					return clk;
			}

			static uint32_t get_adc_clk() {
				uint32_t clk = get_clk();
				adc_div_t div = get_adc_div();
				return clk / (2 * (1 + (div >> RCC_CFGR_ADCPRE_Pos)));
			}

			static sys::result_t enable(periphery_clock_t clk) {
				SET_BIT(RCC->APB2ENR, clk);
				return READ_BIT(RCC->APB2ENR, clk) == RESET ? sys::RES_ERROR : sys::RES_OK;
			}

			static sys::result_t disable(periphery_clock_t clk) {
				CLEAR_BIT(RCC->APB2ENR, clk);
				return READ_BIT(RCC->APB2ENR, clk) == RESET ? sys::RES_OK : sys::RES_ERROR;
			}
		};
	};
}

#endif /* STM32F1_RCC_H */