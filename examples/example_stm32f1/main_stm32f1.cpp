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

#include "arch/ARM/STM32/F1/rcc.h"
#include "arch/ARM/STM32/F1/port.h"
#include "arch/ARM/STM32/F1/pin.h"
#include "arch/ARM/STM32/F1/iomux.h"

arch::port		PORT_E(sys::port::PORT_E);
arch::port		PORT_D(sys::port::PORT_D);

arch::pin		PIN_LED1(PORT_E, sys::port::PIN_0);
arch::pin		PIN_LED2(PORT_E, sys::port::PIN_1);
arch::pin		PIN_LED3(PORT_E, sys::port::PIN_14);
arch::pin		PIN_LED4(PORT_E, sys::port::PIN_15);

arch::pin		PIN_UART2_TX(PORT_D, sys::port::PIN_5);
arch::pin		PIN_UART2_RX(PORT_D, sys::port::PIN_6);

void delay() {
	for (int i = 0; i < 100000; i++);
}

int main() {
	uint32_t clk = 0;
	sys::result_t res = sys::RES_NONE;

	SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_2);

	res = arch::rcc::HSE::set_freq(25000000);
	res = arch::rcc::PREDIV2::set_div(5);
	res = arch::rcc::PLL2::set_mult(arch::rcc::PLL2::MULT_8);
	res = arch::rcc::PREDIV1::set_source(arch::rcc::PREDIV1::SRC_PLL2);
	res = arch::rcc::PREDIV1::set_div(5);
	res = arch::rcc::PLL::set_source(arch::rcc::PLL::SRC_PREDIV1);
	res = arch::rcc::PLL::set_mult(arch::rcc::PLL::MULT_9);

	res = arch::rcc::MCO::set_output(arch::rcc::MCO::OUT_XT1);

	res = arch::rcc::APB1::set_div(arch::rcc::APB1::DIV_2);
	res = arch::rcc::APB2::set_adc_div(arch::rcc::APB2::ADC_DIV_6);

	res = arch::rcc::HSE::enable();
	res = arch::rcc::PLL2::enable();
	res = arch::rcc::PLL::enable();

	res = arch::rcc::SYSCLK::set_source(arch::rcc::SYSCLK::SRC_PLL);

	//clk = arch::rcc::SYSCLK::get_clk();
	//clk = arch::rcc::APB1::get_clk();
	//clk = arch::rcc::APB1::get_tim_clk();
	//clk = arch::rcc::APB2::get_clk();
	//clk = arch::rcc::APB2::get_tim_clk();
	//clk = arch::rcc::APB2::get_adc_clk();

	res = arch::iomux().enable_clock();
	res = arch::iomux().set_remap(sys::iomux::REMAP_UART2, sys::iomux::REMAP_NUM_1);

	PORT_D.enable_clock();
	PIN_UART2_TX.init_alt(sys::pin::ALT_NONE, sys::pin::DRV_PUSH_PULL, sys::pin::SPEED_VERY_FAST);
	PIN_UART2_RX.init_input(sys::pin::PULL_NONE);





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
