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
#include "arch/ARM/STM32/F1/rcc.h"

arch::port		PORT_E(sys::port::PORT_E);
arch::pin		PIN_LED1(PORT_E, sys::port::PIN_0);
arch::pin		PIN_LED2(PORT_E, sys::port::PIN_1);
arch::pin		PIN_LED3(PORT_E, sys::port::PIN_14);
arch::pin		PIN_LED4(PORT_E, sys::port::PIN_15);

void delay() {
	for (int i = 0; i < 100000; i++);
}

int main() {
	uint32_t clk = 0;
	sys::result_t res = sys::RES_NONE;

	SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_2);

	arch::rcc::HSE::set_freq(25000000);
	arch::rcc::PREDIV2::set_div(5);
	arch::rcc::PLL2::set_mult(arch::rcc::PLL2::MULT_8);
	arch::rcc::PREDIV1::set_source(arch::rcc::PREDIV1::SRC_PLL2);
	arch::rcc::PREDIV1::set_div(5);
	arch::rcc::PLL::set_source(arch::rcc::PLL::SRC_PREDIV1);
	arch::rcc::PLL::set_mult(arch::rcc::PLL::MULT_9);

	arch::rcc::MCO::set_output(arch::rcc::MCO::OUT_XT1);

	arch::rcc::APB1::set_div(arch::rcc::APB1::DIV_2);
	arch::rcc::APB2::set_adc_div(arch::rcc::APB2::ADC_DIV_6);

	arch::rcc::HSE::enable();
	arch::rcc::PLL2::enable();
	arch::rcc::PLL::enable();

	arch::rcc::SYSCLK::set_source(arch::rcc::SYSCLK::SRC_PLL);

	clk = arch::rcc::SYSCLK::get_clk();
	clk = arch::rcc::APB1::get_clk();
	clk = arch::rcc::APB1::get_tim_clk();
	clk = arch::rcc::APB2::get_clk();
	clk = arch::rcc::APB2::get_tim_clk();
	clk = arch::rcc::APB2::get_adc_clk();








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
