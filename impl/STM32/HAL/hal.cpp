#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#include "impl/STM32/F1/sys_tim.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#include "impl/STM32/F4/sys_tim.h"
#endif

#include "system/system.h"

static impl::core_tim	CORE_TIM;

extern "C"
HAL_StatusTypeDef HAL_Init(void) {
	sys::result_t res;
	res = CORE_TIM.init(1000);
	res = CORE_TIM.enable_irq();
	res = sys::set_sys_timer(CORE_TIM);
	return HAL_OK;
}

extern "C"
HAL_StatusTypeDef HAL_DeInit(void) {
	return HAL_OK;
}

extern "C"
uint32_t HAL_GetTick() {
	return sys::time_ms();
}

extern "C"
void HAL_Delay(uint32_t Delay)
{
	uint32_t tickstart = HAL_GetTick();
	uint32_t wait = Delay;

	/* Add a freq to guarantee minimum wait */
	if (wait < 0xffffffff)
	{
		wait += 1;
	}

	while ((HAL_GetTick() - tickstart) < wait)
	{
	}
}