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

#include "arch/ARM/STM32/F1/port.h"
#include "arch/ARM/STM32/F1/pin.h"

arch::port		PORT_E(sys::port::PORT_E);
arch::pin		PIN_LED1(PORT_E, sys::port::PIN_0);
arch::pin		PIN_LED2(PORT_E, sys::port::PIN_1);
arch::pin		PIN_LED3(PORT_E, sys::port::PIN_14);
arch::pin		PIN_LED4(PORT_E, sys::port::PIN_15);

void delay() {
	for (int i = 0; i < 100000; i++);
}

int main() {
	PORT_E.enable_clock();
	//auto mask = sys::port::PIN_0 | sys::port::PIN_1 | sys::port::PIN_14 | sys::port::PIN_15;
	//PORT_E.init_output(mask);

	PIN_LED2.init_output();
	PIN_LED3.init_output();

	PIN_LED2.tgl();

	while (1) {
		PIN_LED2.tgl();
		PIN_LED3.tgl();
		delay();
		//PORT_E.tgl(mask);
	}
}