#ifndef STM32F4_RCC_H
#define STM32F4_RCC_H

#include "stm32f4xx.h"
#include "system/types.h"


#define HSI_FREQ            16000000
#define HSE_DEFAULT_FREQ    8000000

#define RCC_HSE_MIN         4000000U
#define RCC_HSE_MAX         26000000U

#define HSI_ENABLE_WAIT     0xffff
#define HSE_ENABLE_WAIT     0xffff
#define PLL_ENABLE_WAIT     0xffff


#ifndef RCC_AHB1ENR_GPIOAEN
#define RCC_AHB1ENR_GPIOAEN (0U)
#endif /* RCC_AHB1ENR_GPIOAEN */
#ifndef RCC_AHB1ENR_GPIOBEN
#define RCC_AHB1ENR_GPIOBEN (0U)
#endif /* RCC_AHB1ENR_GPIOBEN */
#ifndef RCC_AHB1ENR_GPIOCEN
#define RCC_AHB1ENR_GPIOCEN (0U)
#endif /* RCC_AHB1ENR_GPIOCEN */
#ifndef RCC_AHB1ENR_GPIODEN
#define RCC_AHB1ENR_GPIODEN (0U)
#endif /* RCC_AHB1ENR_GPIODEN */
#ifndef RCC_AHB1ENR_GPIOEEN
#define RCC_AHB1ENR_GPIOEEN (0U)
#endif /* RCC_AHB1ENR_GPIOEEN */
#ifndef RCC_AHB1ENR_GPIOFEN
#define RCC_AHB1ENR_GPIOFEN (0U)
#endif /* RCC_AHB1ENR_GPIOFEN */
#ifndef RCC_AHB1ENR_GPIOGEN
#define RCC_AHB1ENR_GPIOGEN (0U)
#endif /* RCC_AHB1ENR_GPIOGEN */
#ifndef RCC_AHB1ENR_GPIOHEN
#define RCC_AHB1ENR_GPIOHEN (0U)
#endif /* RCC_AHB1ENR_GPIOHEN */
#ifndef RCC_AHB1ENR_GPIOIEN
#define RCC_AHB1ENR_GPIOIEN (0U)
#endif /* RCC_AHB1ENR_GPIOIEN */
#ifndef RCC_AHB1ENR_GPIOJEN
#define RCC_AHB1ENR_GPIOJEN (0U)
#endif /* RCC_AHB1ENR_GPIOJEN */
#ifndef RCC_AHB1ENR_GPIOKEN
#define RCC_AHB1ENR_GPIOKEN (0U)
#endif /* RCC_AHB1ENR_GPIOKEN */
#ifndef RCC_AHB1ENR_CRCEN
#define RCC_AHB1ENR_CRCEN (0U)
#endif /* RCC_AHB1ENR_CRCEN */
#ifndef RCC_AHB1ENR_BKPSRAMEN
#define RCC_AHB1ENR_BKPSRAMEN (0U)
#endif /* RCC_AHB1ENR_BKPSRAMEN */
#ifndef RCC_AHB1ENR_CCMDATARAMEN
#define RCC_AHB1ENR_CCMDATARAMEN (0U)
#endif /* RCC_AHB1ENR_CCMDATARAMEN */
#ifndef RCC_AHB1ENR_DMA1EN
#define RCC_AHB1ENR_DMA1EN (0U)
#endif /* RCC_AHB1ENR_DMA1EN */
#ifndef RCC_AHB1ENR_DMA2EN
#define RCC_AHB1ENR_DMA2EN (0U)
#endif /* RCC_AHB1ENR_DMA2EN */
#ifndef RCC_AHB1ENR_DMA2DEN
#define RCC_AHB1ENR_DMA2DEN (0U)
#endif /* RCC_AHB1ENR_DMA2DEN */
#ifndef RCC_AHB1ENR_ETHMACEN
#define RCC_AHB1ENR_ETHMACEN (0U)
#endif /* RCC_AHB1ENR_ETHMACEN */
#ifndef RCC_AHB1ENR_ETHMACTXEN
#define RCC_AHB1ENR_ETHMACTXEN (0U)
#endif /* RCC_AHB1ENR_ETHMACTXEN */
#ifndef RCC_AHB1ENR_ETHMACRXEN
#define RCC_AHB1ENR_ETHMACRXEN (0U)
#endif /* RCC_AHB1ENR_ETHMACRXEN */
#ifndef RCC_AHB1ENR_ETHMACPTPEN
#define RCC_AHB1ENR_ETHMACPTPEN (0U)
#endif /* RCC_AHB1ENR_ETHMACPTPEN */
#ifndef RCC_AHB1ENR_OTGHSEN
#define RCC_AHB1ENR_OTGHSEN (0U)
#endif /* RCC_AHB1ENR_OTGHSEN */
#ifndef RCC_AHB1ENR_OTGHSULPIEN
#define RCC_AHB1ENR_OTGHSULPIEN (0U)
#endif /* RCC_AHB1ENR_OTGHSULPIEN */
// #ifndef RCC_AHB1ENR_RNGEN
// #define RCC_AHB1ENR_RNGEN (0U)
// #endif /* RCC_AHB1ENR_RNGEN */

#ifndef RCC_AHB2ENR_DCMIEN
#define RCC_AHB2ENR_DCMIEN (0U)
#endif /* RCC_AHB2ENR_DCMIEN */
#ifndef RCC_AHB2ENR_CRYPEN
#define RCC_AHB2ENR_CRYPEN (0U)
#endif /* RCC_AHB2ENR_CRYPEN */
#ifndef RCC_AHB2ENR_HASHEN
#define RCC_AHB2ENR_HASHEN (0U)
#endif /* RCC_AHB2ENR_HASHEN */
//#ifndef RCC_AHB2ENR_RNGEN
//#define RCC_AHB2ENR_RNGEN (0U)
//#endif /* RCC_AHB2ENR_RNGEN */
#ifndef RCC_AHB2ENR_OTGFSEN
#define RCC_AHB2ENR_OTGFSEN (0U)
#endif /* RCC_AHB2ENR_OTGFSEN */

#ifndef RCC_AHB3ENR_FSMCEN
#define RCC_AHB3ENR_FSMCEN (0U)
#endif /* RCC_AHB3ENR_FSMCEN */
#ifndef RCC_AHB3ENR_FSMEN
#define RCC_AHB3ENR_FSMEN (0U)
#endif /* RCC_AHB3ENR_FSMEN */
#ifndef RCC_AHB3ENR_QSPIEN
#define RCC_AHB3ENR_QSPIEN (0U)
#endif /* RCC_AHB3ENR_QSPIEN */

#ifndef RCC_AHB1LPENR_GPIOALPEN
#define RCC_AHB1LPENR_GPIOALPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOALPEN */
#ifndef RCC_AHB1LPENR_GPIOBLPEN
#define RCC_AHB1LPENR_GPIOBLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOBLPEN */
#ifndef RCC_AHB1LPENR_GPIOCLPEN
#define RCC_AHB1LPENR_GPIOCLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOCLPEN */
#ifndef RCC_AHB1LPENR_GPIODLPEN
#define RCC_AHB1LPENR_GPIODLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIODLPEN */
#ifndef RCC_AHB1LPENR_GPIOELPEN
#define RCC_AHB1LPENR_GPIOELPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOELPEN */
#ifndef RCC_AHB1LPENR_GPIOFLPEN
#define RCC_AHB1LPENR_GPIOFLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOFLPEN */
#ifndef RCC_AHB1LPENR_GPIOGLPEN
#define RCC_AHB1LPENR_GPIOGLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOGLPEN */
#ifndef RCC_AHB1LPENR_GPIOHLPEN
#define RCC_AHB1LPENR_GPIOHLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOHLPEN */
#ifndef RCC_AHB1LPENR_GPIOILPEN
#define RCC_AHB1LPENR_GPIOILPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOILPEN */
#ifndef RCC_AHB1LPENR_GPIOJLPEN
#define RCC_AHB1LPENR_GPIOJLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOJLPEN */
#ifndef RCC_AHB1LPENR_GPIOKLPEN
#define RCC_AHB1LPENR_GPIOKLPEN (0U)
#endif /* RCC_AHB1LPENR_GPIOKLPEN */
#ifndef RCC_AHB1LPENR_CRCLPEN
#define RCC_AHB1LPENR_CRCLPEN (0U)
#endif /* RCC_AHB1LPENR_CRCLPEN */
#ifndef RCC_AHB1LPENR_FLITFLPEN
#define RCC_AHB1LPENR_FLITFLPEN (0U)
#endif /* RCC_AHB1LPENR_FLITFLPEN */
#ifndef RCC_AHB1LPENR_SRAM1LPEN
#define RCC_AHB1LPENR_SRAM1LPEN (0U)
#endif /* RCC_AHB1LPENR_SRAM1LPEN */
#ifndef RCC_AHB1LPENR_SRAM2LPEN
#define RCC_AHB1LPENR_SRAM2LPEN (0U)
#endif /* RCC_AHB1LPENR_SRAM2LPEN */
#ifndef RCC_AHB1LPENR_BKPSRAMLPEN
#define RCC_AHB1LPENR_BKPSRAMLPEN (0U)
#endif /* RCC_AHB1LPENR_BKPSRAMLPEN */
#ifndef RCC_AHB1LPENR_SRAM3LPEN
#define RCC_AHB1LPENR_SRAM3LPEN (0U)
#endif /* RCC_AHB1LPENR_SRAM3LPEN */
#ifndef RCC_AHB1LPENR_DMA1LPEN
#define RCC_AHB1LPENR_DMA1LPEN (0U)
#endif /* RCC_AHB1LPENR_DMA1LPEN */
#ifndef RCC_AHB1LPENR_DMA2LPEN
#define RCC_AHB1LPENR_DMA2LPEN (0U)
#endif /* RCC_AHB1LPENR_DMA2LPEN */
#ifndef RCC_AHB1LPENR_DMA2DLPEN
#define RCC_AHB1LPENR_DMA2DLPEN (0U)
#endif /* RCC_AHB1LPENR_DMA2DLPEN */
#ifndef RCC_AHB1LPENR_ETHMACLPEN
#define RCC_AHB1LPENR_ETHMACLPEN (0U)
#endif /* RCC_AHB1LPENR_ETHMACLPEN */
#ifndef RCC_AHB1LPENR_ETHMACTXLPEN
#define RCC_AHB1LPENR_ETHMACTXLPEN (0U)
#endif /* RCC_AHB1LPENR_ETHMACTXLPEN */
#ifndef RCC_AHB1LPENR_ETHMACRXLPEN
#define RCC_AHB1LPENR_ETHMACRXLPEN (0U)
#endif /* RCC_AHB1LPENR_ETHMACRXLPEN */
#ifndef RCC_AHB1LPENR_ETHMACPTPLPEN
#define RCC_AHB1LPENR_ETHMACPTPLPEN (0U)
#endif /* RCC_AHB1LPENR_ETHMACPTPLPEN */
#ifndef RCC_AHB1LPENR_OTGHSLPEN
#define RCC_AHB1LPENR_OTGHSLPEN (0U)
#endif /* RCC_AHB1LPENR_OTGHSLPEN */
#ifndef RCC_AHB1LPENR_OTGHSULPILPEN
#define RCC_AHB1LPENR_OTGHSULPILPEN (0U)
#endif /* RCC_AHB1LPENR_OTGHSULPILPEN */

#ifndef RCC_AHB2LPENR_DCMILPEN
#define RCC_AHB2LPENR_DCMILPEN (0U)
#endif /* RCC_AHB2LPENR_DCMILPEN */
#ifndef RCC_AHB2LPENR_CRYPLPEN
#define RCC_AHB2LPENR_CRYPLPEN (0U)
#endif /* RCC_AHB2LPENR_CRYPLPEN */
#ifndef RCC_AHB2LPENR_HASHLPEN
#define RCC_AHB2LPENR_HASHLPEN (0U)
#endif /* RCC_AHB2LPENR_HASHLPEN */
#ifndef RCC_AHB2LPENR_RNGLPEN
#define RCC_AHB2LPENR_RNGLPEN (0U)
#endif /* RCC_AHB2LPENR_RNGLPEN */
#ifndef RCC_AHB2LPENR_OTGFSLPEN
#define RCC_AHB2LPENR_OTGFSLPEN (0U)
#endif /* RCC_AHB2LPENR_OTGFSLPEN */

#ifndef RCC_AHB3LPENR_FSMCLPEN
#define RCC_AHB3LPENR_FSMCLPEN (0U)
#endif /* RCC_AHB3LPENR_FSMCLPEN */
#ifndef RCC_AHB3LPENR_QSPILPEN
#define RCC_AHB3LPENR_QSPILPEN (0U)
#endif /* RCC_AHB3LPENR_QSPILPEN */

#ifndef RCC_APB1ENR_TIM2EN
#define RCC_APB1ENR_TIM2EN (0U)
#endif /* RCC_APB1ENR_TIM2EN */
#ifndef RCC_APB1ENR_TIM3EN
#define RCC_APB1ENR_TIM3EN (0U)
#endif /* RCC_APB1ENR_TIM3EN */
#ifndef RCC_APB1ENR_TIM4EN
#define RCC_APB1ENR_TIM4EN (0U)
#endif /* RCC_APB1ENR_TIM4EN */
#ifndef RCC_APB1ENR_TIM5EN
#define RCC_APB1ENR_TIM5EN (0U)
#endif /* RCC_APB1ENR_TIM5EN */
#ifndef RCC_APB1ENR_TIM6EN
#define RCC_APB1ENR_TIM6EN (0U)
#endif /* RCC_APB1ENR_TIM6EN */
#ifndef RCC_APB1ENR_TIM7EN
#define RCC_APB1ENR_TIM7EN (0U)
#endif /* RCC_APB1ENR_TIM7EN */
#ifndef RCC_APB1ENR_TIM12EN
#define RCC_APB1ENR_TIM12EN (0U)
#endif /* RCC_APB1ENR_TIM12EN */
#ifndef RCC_APB1ENR_TIM13EN
#define RCC_APB1ENR_TIM13EN (0U)
#endif /* RCC_APB1ENR_TIM13EN */
#ifndef RCC_APB1ENR_TIM14EN
#define RCC_APB1ENR_TIM14EN (0U)
#endif /* RCC_APB1ENR_TIM14EN */
#ifndef RCC_APB1ENR_WWDGEN
#define RCC_APB1ENR_WWDGEN (0U)
#endif /* RCC_APB1ENR_WWDGEN */
#ifndef RCC_APB1ENR_SPI2EN
#define RCC_APB1ENR_SPI2EN (0U)
#endif /* RCC_APB1ENR_SPI2EN */
#ifndef RCC_APB1ENR_SPI3EN
#define RCC_APB1ENR_SPI3EN (0U)
#endif /* RCC_APB1ENR_SPI3EN */
#ifndef RCC_APB1ENR_USART2EN
#define RCC_APB1ENR_USART2EN (0U)
#endif /* RCC_APB1ENR_USART2EN */
#ifndef RCC_APB1ENR_USART3EN
#define RCC_APB1ENR_USART3EN (0U)
#endif /* RCC_APB1ENR_USART3EN */
#ifndef RCC_APB1ENR_UART4EN
#define RCC_APB1ENR_UART4EN (0U)
#endif /* RCC_APB1ENR_UART4EN */
#ifndef RCC_APB1ENR_UART5EN
#define RCC_APB1ENR_UART5EN (0U)
#endif /* RCC_APB1ENR_UART5EN */
#ifndef RCC_APB1ENR_I2C1EN
#define RCC_APB1ENR_I2C1EN (0U)
#endif /* RCC_APB1ENR_I2C1EN */
#ifndef RCC_APB1ENR_I2C2EN
#define RCC_APB1ENR_I2C2EN (0U)
#endif /* RCC_APB1ENR_I2C2EN */
#ifndef RCC_APB1ENR_I2C3EN
#define RCC_APB1ENR_I2C3EN (0U)
#endif /* RCC_APB1ENR_I2C3EN */
#ifndef RCC_APB1ENR_CAN1EN
#define RCC_APB1ENR_CAN1EN (0U)
#endif /* RCC_APB1ENR_CAN1EN */
#ifndef RCC_APB1ENR_CAN2EN
#define RCC_APB1ENR_CAN2EN (0U)
#endif /* RCC_APB1ENR_CAN2EN */
#ifndef RCC_APB1ENR_PWREN
#define RCC_APB1ENR_PWREN (0U)
#endif /* RCC_APB1ENR_PWREN */
#ifndef RCC_APB1ENR_DACEN
#define RCC_APB1ENR_DACEN (0U)
#endif /* RCC_APB1ENR_DACEN */
#ifndef RCC_APB1ENR_UART7EN
#define RCC_APB1ENR_UART7EN (0U)
#endif /* RCC_APB1ENR_UART7EN */
#ifndef RCC_APB1ENR_UART8EN
#define RCC_APB1ENR_UART8EN (0U)
#endif /* RCC_APB1ENR_UART8EN */

#ifndef RCC_APB2ENR_TIM1EN
#define RCC_APB2ENR_TIM1EN (0U)
#endif /* RCC_APB2ENR_TIM1EN */
#ifndef RCC_APB2ENR_TIM8EN
#define RCC_APB2ENR_TIM8EN (0U)
#endif /* RCC_APB2ENR_TIM8EN */
#ifndef RCC_APB2ENR_USART1EN
#define RCC_APB2ENR_USART1EN (0U)
#endif /* RCC_APB2ENR_USART1EN */
#ifndef RCC_APB2ENR_USART6EN
#define RCC_APB2ENR_USART6EN (0U)
#endif /* RCC_APB2ENR_USART6EN */
#ifndef RCC_APB2ENR_ADC1EN
#define RCC_APB2ENR_ADC1EN (0U)
#endif /* RCC_APB2ENR_ADC1EN */
#ifndef RCC_APB2ENR_ADC2EN
#define RCC_APB2ENR_ADC2EN (0U)
#endif /* RCC_APB2ENR_ADC2EN */
#ifndef RCC_APB2ENR_ADC3EN
#define RCC_APB2ENR_ADC3EN (0U)
#endif /* RCC_APB2ENR_ADC3EN */
#ifndef RCC_APB2ENR_SDIOEN
#define RCC_APB2ENR_SDIOEN (0U)
#endif /* RCC_APB2ENR_SDIOEN */
#ifndef RCC_APB2ENR_SPI1EN
#define RCC_APB2ENR_SPI1EN (0U)
#endif /* RCC_APB2ENR_SPI1EN */
#ifndef RCC_APB2ENR_SPI4EN
#define RCC_APB2ENR_SPI4EN (0U)
#endif /* RCC_APB2ENR_SPI4EN */
#ifndef RCC_APB2ENR_SYSCFGEN
#define RCC_APB2ENR_SYSCFGEN (0U)
#endif /* RCC_APB2ENR_SYSCFGEN */
#ifndef RCC_APB2ENR_TIM9EN
#define RCC_APB2ENR_TIM9EN (0U)
#endif /* RCC_APB2ENR_TIM9EN */
#ifndef RCC_APB2ENR_TIM10EN
#define RCC_APB2ENR_TIM10EN (0U)
#endif /* RCC_APB2ENR_TIM10EN */
#ifndef RCC_APB2ENR_TIM11EN
#define RCC_APB2ENR_TIM11EN (0U)
#endif /* RCC_APB2ENR_TIM11EN */
#ifndef RCC_APB2ENR_SPI5EN
#define RCC_APB2ENR_SPI5EN (0U)
#endif /* RCC_APB2ENR_SPI5EN */
#ifndef RCC_APB2ENR_SPI6EN
#define RCC_APB2ENR_SPI6EN (0U)
#endif /* RCC_APB2ENR_SPI6EN */
#ifndef RCC_APB2ENR_SAI1EN
#define RCC_APB2ENR_SAI1EN (0U)
#endif /* RCC_APB2ENR_SAI1EN */
#ifndef RCC_APB2ENR_LTDCEN
#define RCC_APB2ENR_LTDCEN (0U)
#endif /* RCC_APB2ENR_LTDCEN */


namespace impl {
	class rcc {
	public:
		class HSI;				// Internal oscillator
		class HSE;				// External oscillator
		class PLL;
		class SYSCLK;
		class AHB;
		class HCLK;				// AHB Bus, core, memory, dma
		class FCLK;				// Core
		class CORTEX_TIM_CLK;	// Cortex system timer
		class APB1;
		class APB2;
		class MCO;				// Clock output
		class MCO2;				// Clock output

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

			static inline uint32_t calc_clk() {
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
				// todo: update clk
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

			static inline uint32_t calc_clk() {
				return CLK_FREQ;
			}
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
				int i = PLL_ENABLE_WAIT;
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

			static inline sys::result_t set_prediv_m(uint32_t m) {
				if ((m < 2) || (m > 0b111111)) return sys::RES_ERROR;
				SET_BIT(RCC->PLLCFGR, m << RCC_PLLCFGR_PLLM_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_Msk) == (m << RCC_PLLCFGR_PLLM_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline sys::result_t set_mult_n(uint32_t n) {
				if ((n < RCC_PLLN_MIN_VALUE) || (n > RCC_PLLN_MAX_VALUE)) return sys::RES_ERROR;
				MODIFY_REG(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk, n << RCC_PLLCFGR_PLLN_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk) == (n << RCC_PLLCFGR_PLLN_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline sys::result_t set_div_p(div_p_t p) {
				SET_BIT(RCC->PLLCFGR, p << RCC_PLLCFGR_PLLP_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk) == (p << RCC_PLLCFGR_PLLP_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline sys::result_t set_div_q(uint32_t q) {
				if ((q < 2) || (q > 0b1111)) return sys::RES_ERROR;
				SET_BIT(RCC->PLLCFGR, q << RCC_PLLCFGR_PLLQ_Pos);
				return (READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk) == (q << RCC_PLLCFGR_PLLQ_Pos)) ? sys::RES_OK : sys::RES_ERROR;
			}

			// todo set_div_r()

			static inline uint32_t get_prediv_m() {
				return READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_Msk) >> RCC_PLLCFGR_PLLM_Pos;
			}

			static inline uint32_t get_mult_n() {
				return READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_Msk) >> RCC_PLLCFGR_PLLN_Pos;
			}

			static inline div_p_t get_div_p() {
				return (div_p_t)(READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_Msk) >> RCC_PLLCFGR_PLLP_Pos);
			}

			static inline uint32_t get_div_q() {
				return READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_Msk) >> RCC_PLLCFGR_PLLQ_Pos;
			}

#if defined(RCC_PLLCFGR_PLLR)
			static inline uint32_t get_div_r() {
				return READ_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLR_Msk) >> RCC_PLLCFGR_PLLR_Pos;
			}
#endif

			static uint32_t calc_clk_vco() {
				uint32_t clk;
				if (get_source() == SRC_HSI)
					clk = HSI::calc_clk();
				else
					clk = HSE::calc_clk();

				return (clk / get_prediv_m()) * get_mult_n();
			}

			static uint32_t calc_clk_p() {
				uint32_t clk = calc_clk_vco();
				switch (get_div_p()) {
					case DIV_P_2: return clk / 2;
					case DIV_P_4: return clk / 4;
					case DIV_P_6: return clk / 6;
					case DIV_P_8: return clk / 8;
					default: return 0;
				}
			}

			static uint32_t calc_clk_q() {
				return calc_clk_vco() / get_div_q();
			}

#if defined(RCC_PLLCFGR_PLLR)
			static uint32_t calc_clk_r() {
				return calc_clk_vco() / get_div_r();
			}
#endif
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
				sys::result_t res = (READ_BIT(RCC->CFGR, RCC_CFGR_SW << (RCC_CFGR_SWS_Pos - RCC_CFGR_SW_Pos)) == (src << (RCC_CFGR_SWS_Pos - RCC_CFGR_SW_Pos))) ? sys::RES_OK : sys::RES_ERROR;
				if (res == sys::RES_OK) AHB::update_clk();
				return res;
			}

			static inline source_t get_source() {
				return (source_t)READ_BIT(RCC->CFGR, RCC_CFGR_SW);
			}

			// todo: CSS

			static uint32_t calc_clk() {
				switch (get_source()) {
					case SRC_HSI: return HSI::calc_clk();
					case SRC_HSE: return HSE::calc_clk();
					case SRC_PLL: return PLL::calc_clk_p();
					default: return 0;
				}
			}


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
				CLK_GPIOA      = RCC_AHB1ENR_GPIOAEN,
				CLK_GPIOB      = RCC_AHB1ENR_GPIOBEN,
				CLK_GPIOC      = RCC_AHB1ENR_GPIOCEN,
				CLK_GPIOD      = RCC_AHB1ENR_GPIODEN,
				CLK_GPIOE      = RCC_AHB1ENR_GPIOEEN,
				CLK_GPIOF      = RCC_AHB1ENR_GPIOFEN,
				CLK_GPIOG      = RCC_AHB1ENR_GPIOGEN,
				CLK_GPIOH      = RCC_AHB1ENR_GPIOHEN,
				CLK_GPIOI      = RCC_AHB1ENR_GPIOIEN,
				CLK_GPIOJ      = RCC_AHB1ENR_GPIOJEN,
				CLK_GPIOK      = RCC_AHB1ENR_GPIOKEN,
				CLK_CRC        = RCC_AHB1ENR_CRCEN,
				CLK_BKPSRAM    = RCC_AHB1ENR_BKPSRAMEN,
				CLK_CCMDATARAM = RCC_AHB1ENR_CCMDATARAMEN,
				CLK_DMA1       = RCC_AHB1ENR_DMA1EN,
				CLK_DMA2       = RCC_AHB1ENR_DMA2EN,
				CLK_DMA2D      = RCC_AHB1ENR_DMA2DEN,
				CLK_ETHMAC     = RCC_AHB1ENR_ETHMACEN,
				CLK_ETHMACTX   = RCC_AHB1ENR_ETHMACTXEN,
				CLK_ETHMACRX   = RCC_AHB1ENR_ETHMACRXEN,
				CLK_ETHMACPTP  = RCC_AHB1ENR_ETHMACPTPEN,
				CLK_OTGHS      = RCC_AHB1ENR_OTGHSEN,
				CLK_OTGHSULPI  = RCC_AHB1ENR_OTGHSULPIEN,
#ifdef RCC_AHB1ENR_RNGEN
				CLK_RNG        = RCC_AHB1ENR_RNGEN,
#endif /* RCC_AHB1ENR_RNGEN */
			} periphery_clock1_t;

			typedef enum {
				CLK_DCMI  = RCC_AHB2ENR_DCMIEN,
				CLK_CRYP  = RCC_AHB2ENR_CRYPEN,
				CLK_HASH  = RCC_AHB2ENR_HASHEN,
#ifdef RCC_AHB2ENR_RNGEN
				CLK_RNG   = RCC_AHB2ENR_RNGEN,
#endif /* RCC_AHB2ENR_RNGEN */
				CLK_OTGFS = RCC_AHB2ENR_OTGFSEN,
			} periphery_clock2_t;

			typedef enum {
				CLK_FSMC = RCC_AHB3ENR_FSMCEN,
				CLK_FSM  = RCC_AHB3ENR_FSMEN,
				CLK_QSPI = RCC_AHB3ENR_QSPIEN,
			} periphery_clock3_t;

			/*
			typedef enum {
				LP_CLK_GPIOA     = RCC_AHB1LPENR_GPIOALPEN,
				LP_CLK_GPIOB     = RCC_AHB1LPENR_GPIOBLPEN,
				LP_CLK_GPIOC     = RCC_AHB1LPENR_GPIOCLPEN,
				LP_CLK_GPIOD     = RCC_AHB1LPENR_GPIODLPEN,
				LP_CLK_GPIOE     = RCC_AHB1LPENR_GPIOELPEN,
				LP_CLK_GPIOF     = RCC_AHB1LPENR_GPIOFLPEN,
				LP_CLK_GPIOG     = RCC_AHB1LPENR_GPIOGLPEN,
				LP_CLK_GPIOH     = RCC_AHB1LPENR_GPIOHLPEN,
				LP_CLK_GPIOI     = RCC_AHB1LPENR_GPIOILPEN,
				LP_CLK_GPIOJ     = RCC_AHB1LPENR_GPIOJLPEN,
				LP_CLK_GPIOK     = RCC_AHB1LPENR_GPIOKLPEN,
				LP_CLK_CRC       = RCC_AHB1LPENR_CRCLPEN,
				LP_CLK_FLITF     = RCC_AHB1LPENR_FLITFLPEN,
				LP_CLK_SRAM1     = RCC_AHB1LPENR_SRAM1LPEN,
				LP_CLK_SRAM2     = RCC_AHB1LPENR_SRAM2LPEN,
				LP_CLK_BKPSRAM   = RCC_AHB1LPENR_BKPSRAMLPEN,
				LP_CLK_SRAM3     = RCC_AHB1LPENR_SRAM3LPEN,
				LP_CLK_DMA1      = RCC_AHB1LPENR_DMA1LPEN,
				LP_CLK_DMA2      = RCC_AHB1LPENR_DMA2LPEN,
				LP_CLK_DMA2D     = RCC_AHB1LPENR_DMA2DLPEN,
				LP_CLK_ETHMAC    = RCC_AHB1LPENR_ETHMACLPEN,
				LP_CLK_ETHMACTX  = RCC_AHB1LPENR_ETHMACTXLPEN,
				LP_CLK_ETHMACRX  = RCC_AHB1LPENR_ETHMACRXLPEN,
				LP_CLK_ETHMACPTP = RCC_AHB1LPENR_ETHMACPTPLPEN,
				LP_CLK_OTGHS     = RCC_AHB1LPENR_OTGHSLPEN,
				LP_CLK_OTGHSULPI = RCC_AHB1LPENR_OTGHSULPILPEN,
			} periphery_lp_clock1_t;

			typedef enum {
				LP_CLK_DCMI  = RCC_AHB2LPENR_DCMILPEN,
				LP_CLK_CRYP  = RCC_AHB2LPENR_CRYPLPEN,
				LP_CLK_HASH  = RCC_AHB2LPENR_HASHLPEN,
				LP_CLK_RNG   = RCC_AHB2LPENR_RNGLPEN,
				LP_CLK_OTGFS = RCC_AHB2LPENR_OTGFSLPEN,
			} periphery_lp_clock2_t;

			typedef enum {
				LP_CLK_FSMC = RCC_AHB3LPENR_FSMCLPEN,
				LP_CLK_QSPI = RCC_AHB3LPENR_QSPILPEN
			} periphery_lp_clock3_t;
			*/

		public:
			volatile static inline uint32_t CLK_FREQ = 0;

		public:
			static sys::result_t set_div(div_t d) {
				SET_BIT(RCC->CFGR, d);
				sys::result_t res = READ_BIT(RCC->CFGR, RCC_CFGR_HPRE) == d ? sys::RES_OK : sys::RES_ERROR;
				if (res == sys::RES_OK) update_clk();
				return res;
			}

			static div_t get_div() {
				return (div_t) READ_BIT(RCC->CFGR, RCC_CFGR_HPRE);
			}

			static uint32_t calc_clk() {
				uint32_t clk = SYSCLK::calc_clk();
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

			static sys::result_t enable(periphery_clock1_t clk) {
				SET_BIT(RCC->AHB1ENR, clk);
				return READ_BIT(RCC->AHB1ENR, clk) == RESET ? sys::RES_ERROR : sys::RES_OK;
			}

			static sys::result_t disable(periphery_clock1_t clk) {
				CLEAR_BIT(RCC->AHB1ENR, clk);
				return READ_BIT(RCC->AHB1ENR, clk) == RESET ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline void update_clk() {
				CLK_FREQ = calc_clk();

				HCLK::update_clk();
				FCLK::update_clk();
				CORTEX_TIM_CLK::update_clk();
				APB1::update_clk();
				APB2::update_clk();
			}
		};

		class HCLK {
		public:
			volatile static inline uint32_t CLK_FREQ = 0;

		public:
			inline static uint32_t calc_clk() {
				return AHB::calc_clk();
			}

			static inline void update_clk() {
				CLK_FREQ = calc_clk();
			}
		};

		class FCLK {
		public:
			volatile static inline uint32_t CLK_FREQ = 0;

		public:
			inline static uint32_t calc_clk() {
				return AHB::calc_clk();
			}

			static inline void update_clk() {
				CLK_FREQ = calc_clk();
			}
		};

		class CORTEX_TIM_CLK {
		public:
			volatile static inline uint32_t CLK_FREQ = 0;

		public:
			inline static uint32_t calc_clk() {
				return AHB::calc_clk() / 8;
			}

			static inline void update_clk() {
				CLK_FREQ = calc_clk();
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
				CLK_TIM2    = RCC_APB1ENR_TIM2EN,
				CLK_TIM3    = RCC_APB1ENR_TIM3EN,
				CLK_TIM4    = RCC_APB1ENR_TIM4EN,
				CLK_TIM5    = RCC_APB1ENR_TIM5EN,
				CLK_TIM6    = RCC_APB1ENR_TIM6EN,
				CLK_TIM7    = RCC_APB1ENR_TIM7EN,
				CLK_TIM12   = RCC_APB1ENR_TIM12EN,
				CLK_TIM13   = RCC_APB1ENR_TIM13EN,
				CLK_TIM14   = RCC_APB1ENR_TIM14EN,
				// RCC_APB1ENR_LPTIM1EN
				// RCC_APB1ENR_RTCAPBEN
				CLK_WWDG    = RCC_APB1ENR_WWDGEN,
				CLK_SPI2    = RCC_APB1ENR_SPI2EN,
				CLK_SPI3    = RCC_APB1ENR_SPI3EN,
				// RCC_APB1ENR_SPDIFRXEN
				CLK_USART2  = RCC_APB1ENR_USART2EN,
				CLK_USART3  = RCC_APB1ENR_USART3EN,
				CLK_UART4   = RCC_APB1ENR_UART4EN,
				CLK_UART5   = RCC_APB1ENR_UART5EN,
				CLK_I2C1    = RCC_APB1ENR_I2C1EN,
				CLK_I2C2    = RCC_APB1ENR_I2C2EN,
				CLK_I2C3    = RCC_APB1ENR_I2C3EN,
				// RCC_APB1ENR_FMPI2C1EN
				CLK_CAN1    = RCC_APB1ENR_CAN1EN,
				CLK_CAN2    = RCC_APB1ENR_CAN2EN,
				// RCC_APB1ENR_CAN3EN
				CLK_PWR     = RCC_APB1ENR_PWREN,
				CLK_DAC     = RCC_APB1ENR_DACEN,
				CLK_UART7   = RCC_APB1ENR_UART7EN,
				CLK_UART8   = RCC_APB1ENR_UART8EN,
			} periphery_clock_t;

		public:
			volatile static inline uint32_t CLK_FREQ = 0;

		public:
			static sys::result_t set_div(div_t d) {
				// todo: check clock (max 42 MHz)
				MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1_Msk, d);
				return READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1_Msk) == d ? sys::RES_OK : sys::RES_ERROR;
			}

			static div_t get_div() {
				return (div_t) READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1_Msk);
			}

			static uint32_t calc_clk() {
				uint32_t clk = AHB::calc_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk / (2 << ((div & (RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1)) >> RCC_CFGR_PPRE1_Pos));
				else
					return clk;
			}

			static uint32_t get_tim_clk() {
				uint32_t clk = calc_clk();
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

			static inline void update_clk() {
				CLK_FREQ = calc_clk();
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
				CLK_TIM1   = RCC_APB2ENR_TIM1EN,
				CLK_TIM8   = RCC_APB2ENR_TIM8EN,
				CLK_USART1 = RCC_APB2ENR_USART1EN,
				CLK_USART6 = RCC_APB2ENR_USART6EN,
				// RCC_APB2ENR_UART9EN
				// RCC_APB2ENR_UART10EN
				CLK_ADC1   = RCC_APB2ENR_ADC1EN,
				CLK_ADC2   = RCC_APB2ENR_ADC2EN,
				CLK_ADC3   = RCC_APB2ENR_ADC3EN,
				CLK_SDIO   = RCC_APB2ENR_SDIOEN,
				CLK_SPI1   = RCC_APB2ENR_SPI1EN,
				CLK_SPI4   = RCC_APB2ENR_SPI4EN,
				CLK_SYSCFG = RCC_APB2ENR_SYSCFGEN,
				// RCC_APB2ENR_EXTITEN
				CLK_TIM9   = RCC_APB2ENR_TIM9EN,
				CLK_TIM10  = RCC_APB2ENR_TIM10EN,
				CLK_TIM11  = RCC_APB2ENR_TIM11EN,
				CLK_SPI5   = RCC_APB2ENR_SPI5EN,
				CLK_SPI6   = RCC_APB2ENR_SPI6EN,
				CLK_SAI1   = RCC_APB2ENR_SAI1EN,
				// RCC_APB2ENR_SAI2EN
				// RCC_APB2ENR_DFSDM1EN
				// RCC_APB2ENR_DFSDM2EN
				CLK_LTDC   = RCC_APB2ENR_LTDCEN,
				// RCC_APB2ENR_DSIEN
			} periphery_clock_t;

		public:
			volatile static inline uint32_t CLK_FREQ = 0;

		public:
			static sys::result_t set_div(div_t d) {
				SET_BIT(RCC->CFGR, d);
				return READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2) == d ? sys::RES_OK : sys::RES_ERROR;
			}

			static div_t get_div() {
				return (div_t) READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2);
			}

			static uint32_t calc_clk() {
				uint32_t clk = AHB::calc_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk / (2 << (div & (RCC_CFGR_PPRE1_0 | RCC_CFGR_PPRE1_1) >> RCC_CFGR_PPRE1_Pos));
				else
					return clk;
			}

			static uint32_t get_tim_clk() {
				uint32_t clk = calc_clk();
				div_t div = get_div();
				if (div & RCC_CFGR_PPRE1_2)
					return clk * 2;
				else
					return clk;
			}

			static sys::result_t enable(periphery_clock_t clk) {
				SET_BIT(RCC->APB2ENR, clk);
				return READ_BIT(RCC->APB2ENR, clk) == RESET ? sys::RES_ERROR : sys::RES_OK;
			}

			static sys::result_t disable(periphery_clock_t clk) {
				CLEAR_BIT(RCC->APB2ENR, clk);
				return READ_BIT(RCC->APB2ENR, clk) == RESET ? sys::RES_OK : sys::RES_ERROR;
			}

			static inline void update_clk() {
				CLK_FREQ = calc_clk();
			}
		};

	};
}


#endif /* STM32F4_RCC_H */