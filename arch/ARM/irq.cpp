#if defined(STM32F1)
#include "stm32f1xx.h"
#elif defined(STM32F4)
#include "stm32f4xx.h"
#endif

#include "arch/ARM/irq.h"

extern "C"
void irq_handler() {
	arch::irq::handle(SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk);
}
