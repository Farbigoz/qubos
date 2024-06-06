#include "stdint.h"

extern uint32_t _estack;
extern void Reset_Handler();
void irq_handler();

const uint32_t IRQ_VECTOR[ARM_IRQ_VEC_LEN] __attribute__((section(".isr_vector"))) = {
		[0] = (uint32_t)&_estack,
		[1] = (uint32_t)&Reset_Handler,
		[2 ... ARM_IRQ_VEC_LEN-1] = (uint32_t)&irq_handler
};
