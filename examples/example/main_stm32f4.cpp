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
#include "arch/ARM/STM32/F4/rcc.h"

arch::port		PORT_C(sys::port::PORT_C);
arch::pin		PIN_LED1(PORT_C, sys::port::PIN_1);
arch::pin		PIN_LED2(PORT_C, sys::port::PIN_2);
arch::pin		PIN_LED3(PORT_C, sys::port::PIN_3);
arch::pin		PIN_LED4(PORT_C, sys::port::PIN_4);
arch::pin		PIN_LED13(PORT_C, sys::port::PIN_13);

void delay() {
	for (int i = 0; i < 100000; i++);
}


void pin_irq_handler(sys::pin &pin) {
	PIN_LED1.tgl();
}


sys::pin::signal_irq_t::Slot	pin1_irq_slot;
sys::pin::signal_irq_t::Slot	pin2_irq_slot;
sys::pin::signal_irq_t::Slot	pin3_irq_slot;


int main() {
	test_rcc();

	PORT_C.enable_clock();

	PIN_LED3.set_alt(sys::pin::ALT_0);

	//PIN_LED2.signal_irq.connect(pin1_irq_slot, pin_irq_handler);
	//PIN_LED3.signal_irq.connect(pin2_irq_slot, pin_irq_handler);
	//PIN_LED4.signal_irq.connect(pin3_irq_slot, pin_irq_handler);

	PIN_LED13.init_output();

	//PIN_LED1.init_output();
	// PIN_LED2.init_output();
	// PIN_LED3.init_output();
	//PIN_LED4.init_output();

	//PIN_LED2.init_input(sys::pin::TRIG_RISING);
	//PIN_LED2.set_irq_prior(0);
	//PIN_LED2.enable_irq();

	//PIN_LED3.init_input(sys::pin::TRIG_FALLING);
	//PIN_LED3.set_irq_prior(0);
	//PIN_LED3.enable_irq();

	//PIN_LED4.init_input(sys::pin::TRIG_RISING);
	//PIN_LED4.set_irq_prior(0);
	//PIN_LED4.enable_irq();

	//a = g_pfnVectors[0];

	//EXTI15_10_IRQHandler();


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

		for (int i= 0; i < 10; i++)
			delay();
		PIN_LED4.tgl();
		PIN_LED13.tgl();

		//PIN_LED1.tgl();
	}
}