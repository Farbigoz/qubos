#include "system/interface/port.h"
#include "system/interface/pin.h"
#include "system/interface/adc.h"
#include "system/interface/dac.h"
#include "system/interface/dma.h"
#include "system/interface/can.h"
#include "system/interface/uart.h"
#include "system/interface/spi.h"
#include "system/interface/i2c.h"
#include "system/interface/fs.h"
#include "system/interface/pll.h"
#include "system/interface/flash.h"
#include "system/interface/tim.h"

#include "arch/ARM/STM32/F4/port.h"
#include "arch/ARM/STM32/F4/pin.h"

arch::port		PORT_C(sys::port::PORT_C);
arch::pin		PIN_LED1(PORT_C, sys::port::PIN_1);
arch::pin		PIN_LED2(PORT_C, sys::port::PIN_2);
arch::pin		PIN_LED3(PORT_C, sys::port::PIN_3);
arch::pin		PIN_LED4(PORT_C, sys::port::PIN_4);

void delay() {
	for (int i = 0; i < 100000; i++);
}

extern "C" {

void EXTI0_IRQHandler() {
	delay();
}

void EXTI1_IRQHandler() {
	delay();
}

unsigned irqnumber;

void EXTI2_IRQHandler() {
	irqnumber = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;

	if ((EXTI->PR & sys::port::PIN_2) == 0) { return; }
	EXTI->PR = sys::port::PIN_2;
}

void EXTI3_IRQHandler() {
	irqnumber = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;

	if ((EXTI->PR & sys::port::PIN_3) == 0) { return; }
	EXTI->PR = sys::port::PIN_3;
}

void EXTI4_IRQHandler() {
	irqnumber = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;

	if ((EXTI->PR & sys::port::PIN_4) == 0) { return; }
	EXTI->PR = sys::port::PIN_4;
}

void EXTI9_5_IRQHandler() {
	delay();
}

void EXTI15_10_IRQHandler() {
	delay();
}

}

int main() {
	PORT_C.enable_clock();

	PIN_LED1.init_output();
	// PIN_LED2.init_output();
	// PIN_LED3.init_output();
	// PIN_LED4.init_output();

	PIN_LED2.init_input(sys::pin::TRIG_RISING);
	PIN_LED2.set_irq_prior(0);
	PIN_LED2.enable_irq();

	PIN_LED3.init_input(sys::pin::TRIG_RISING);
	PIN_LED3.set_irq_prior(0);
	PIN_LED3.enable_irq();

	PIN_LED4.init_input(sys::pin::TRIG_RISING);
	PIN_LED4.set_irq_prior(0);
	PIN_LED4.enable_irq();


	// PIN_LED1.signal_irq

	while (1) {
		//delay();
		//PIN_LED1.tgl();
		//delay();
		//PIN_LED2.tgl();
		//delay();
		//PIN_LED3.tgl();
		//delay();
		//PIN_LED4.tgl();

		//PIN_LED1.set(PIN_LED4.read());


		delay();
		PIN_LED1.tgl();
	}
}