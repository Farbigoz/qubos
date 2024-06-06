#include "stm32f4xx.h"
#include "arch/ARM/irq.h"

extern "C"
void irq_handler() {
	arch::irq::handle((IRQn_Type)(SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk));
}
