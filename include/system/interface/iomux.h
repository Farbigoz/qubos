#ifndef SYSTEM_INTERFACE_I2C_H
#define SYSTEM_INTERFACE_I2C_H

#include "system/system.h"
#include "system/interface/periphery.h"


namespace sys {

class iomux : virtual public periphery {
public:
	// Для МК в которых поддерживается переназначение групп входов/выходов
	typedef enum REMAP_T {
		REMAP_ADC1_ETRGINJ,		// STM32F103|AT32F403A|AT32F407 - ADC1 external trigger injected conversion {0: EXTI_15, 1: TIM8_CH4}
		REMAP_ADC1_ETRGREG,		// STM32F103|AT32F403A|AT32F407 - ADC1 external trigger regular conversion  {0: EXTI_11, 1: TIM8_TRGO}
		REMAP_ADC2_ETRGINJ,		// STM32F103|AT32F403A|AT32F407 - ADC1 external trigger injected conversion {0: EXTI_15, 1: TIM8_CH4}
		REMAP_ADC2_ETRGREG,		// STM32F103|AT32F403A|AT32F407 - ADC1 external trigger regular conversion  {0: EXTI_11, 1: TIM8_TRGO}

		REMAP_TIM1,
		REMAP_TIM2,
		REMAP_TIM3,
		REMAP_TIM4,
		// REMAP_TIM5,
		// REMAP_TIM6,
		// REMAP_TIM7,
		// REMAP_TIM8,
		REMAP_TIM9,
		// REMAP_TIM10,
		// REMAP_TIM11,
		// REMAP_TIM12,
		// REMAP_TIM13,
		// REMAP_TIM14,
		// REMAP_TIM15,
		// REMAP_TIM16,
		// REMAP_TIM17,
		// REMAP_TIM18,

		REMAP_TIM5_CH4,

		REMAP_TIM2_IT,		// STM32F107 - 0: Ethernet PTP calibration, 1: USB OTG calibration

		REMAP_I2C1,
		// REMAP_I2C2,
		REMAP_I2C3,
		// REMAP_I2C4,

		REMAP_SPI1,
		REMAP_SPI2,
		REMAP_SPI3,
		REMAP_SPI4,
		// REMAP_SPI5,
		// REMAP_SPI6,
		// REMAP_QSPI,
		REMAP_SPIM,

		// REMAP_I2S1,
		// REMAP_I2S2,
		// REMAP_I2S3,

		REMAP_UART1,
		REMAP_UART2,
		REMAP_UART3,
		REMAP_UART4,
		REMAP_UART5,
		REMAP_UART6,
		REMAP_UART7,
		REMAP_UART8,

		// REMAP_USB_FS,
		// REMAP_USB_HS,
		// REMAP_USB_FS_HS,

		REMAP_CAN1,
		REMAP_CAN2,

		REMAP_SDIO2,

		RAMAP_EMAC_PTP_PPS,
		REMAP_EMAC_MII_RMII

	} alt_remap_t;

public:
};
}


#endif /* SYSTEM_INTERFACE_I2C_H */