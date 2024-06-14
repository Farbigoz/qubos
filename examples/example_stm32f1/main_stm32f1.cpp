#include "system/system.h"

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

#include "arch/ARM/STM32/F1/sys_tim.h"
#include "arch/ARM/STM32/F1/rcc.h"
#include "arch/ARM/STM32/F1/port.h"
#include "arch/ARM/STM32/F1/pin.h"
#include "arch/ARM/STM32/F1/iomux.h"
#include "arch/ARM/STM32/F1/uart.h"

arch::port		PORT_E(sys::port::PORT_E);
arch::port		PORT_D(sys::port::PORT_D);

arch::pin		PIN_LED1(PORT_E, sys::port::PIN_0);
arch::pin		PIN_LED2(PORT_E, sys::port::PIN_1);
arch::pin		PIN_LED3(PORT_E, sys::port::PIN_14);
arch::pin		PIN_LED4(PORT_E, sys::port::PIN_15);

arch::pin		PIN_UART2_TX(PORT_D, sys::port::PIN_5);
arch::pin		PIN_UART2_RX(PORT_D, sys::port::PIN_6);

arch::pin		PIN_UART3_TX(PORT_D, sys::port::PIN_8);
arch::pin		PIN_UART3_RX(PORT_D, sys::port::PIN_9);

arch::uart		UART2(arch::uart::UART_2);


arch::core_tim	CORE_TIM;

void delay() {
	for (int i = 0; i < 100000; i++);
}

void sys_tick_signal_slot_fn(sys::sys_tim&) {
	PIN_UART3_TX.tgl();

	PIN_LED2.tgl();
	PIN_LED3.tgl();
}

sys::sys_tim::signal_irq_t::Slot sys_tick_signal_slot;

arch::dma	uart_tx_dma(arch::dma::DMA_1, arch::dma::CHANNEL_7);
arch::dma	uart_rx_dma(arch::dma::DMA_1, arch::dma::CHANNEL_6);


int dma_test = 0;

void dma_cplt_slot_fn(sys::dma&) {
	dma_test++;
}

void dma_half_cplt_slot_fn(sys::dma&) {
	dma_test++;
}

void dma_error_cplt_slot_fn(sys::dma&, sys::dma::error_t) {
	dma_test++;
}

sys::dma::signal_cplt_t::Slot		dma_cplt_slot;
sys::dma::signal_half_cplt_t::Slot	dma_half_cplt_slot;
sys::dma::signal_error_t::Slot		dma_error_cplt_slot;


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

	//clk = arch::rcc::SYSCLK::calc_clk();
	//clk = arch::rcc::APB1::calc_clk();
	//clk = arch::rcc::APB1::get_tim_clk();
	//clk = arch::rcc::APB2::calc_clk();
	//clk = arch::rcc::APB2::get_tim_clk();
	//clk = arch::rcc::APB2::get_adc_clk();

	res = arch::iomux().enable_clock();
	res = arch::iomux().set_remap(sys::iomux::REMAP_UART2, sys::iomux::REMAP_NUM_1);
	//res = arch::iomux().set_remap(sys::iomux::REMAP_UART3, sys::iomux::REMAP_NUM_3);

	PORT_D.enable_clock();

	PIN_UART2_TX.init_alt(sys::pin::ALT_NONE, sys::pin::DRV_PUSH_PULL, sys::pin::SPEED_VERY_FAST);
	PIN_UART2_RX.init_input(sys::pin::PULL_NONE);

	PIN_UART3_TX.init_output();

	res = CORE_TIM.init(1000);
	CORE_TIM.signal_irq.connect(sys_tick_signal_slot, sys_tick_signal_slot_fn);
	res = CORE_TIM.enable_irq();

	res = sys::set_sys_timer(CORE_TIM);





	res = uart_tx_dma.enable_clock();
	res = uart_tx_dma.init(sys::dma::DIR_MEM_TO_PER, sys::dma::DATA_ALIGN_BYTE, sys::dma::DATA_ALIGN_BYTE, false, true, false, sys::dma::PRIOR_MEDIUM);
	//res = uart_tx_dma.set_irq_prior(5);
	//res = uart_tx_dma.enable_irq();

	res = uart_rx_dma.enable_clock();
	res = uart_rx_dma.init(sys::dma::DIR_PER_TO_MEM, sys::dma::DATA_ALIGN_BYTE, sys::dma::DATA_ALIGN_BYTE, false, true, false, sys::dma::PRIOR_MEDIUM);

	//uart_tx_dma.signal_cplt.connect(dma_cplt_slot, dma_cplt_slot_fn);
	//uart_tx_dma.signal_half_cplt.connect(dma_half_cplt_slot, dma_half_cplt_slot_fn);
	//uart_tx_dma.signal_error.connect(dma_error_cplt_slot, dma_error_cplt_slot_fn);

	uint8_t tx_buff[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	uint8_t rx_buff[sizeof(tx_buff)] = {0x00};

	res = UART2.enable_clock();
	res = UART2.init_uart(sys::uart::MODE_FULL_DUPLEX, sys::uart::STOP_1_BIT, sys::uart::PARITY_NONE, sys::uart::LENGTH_8_BIT, sys::uart::OVERSAMPLE_16_BIT);
	res = UART2.set_baud(9600);
	res = UART2.enable();

	res = UART2.set_rx_dma(&uart_rx_dma);
	res = UART2.set_tx_dma(&uart_tx_dma);
	res = UART2.receive_dma(rx_buff, sizeof(rx_buff));
	res = UART2.transmit_dma(tx_buff, 5);//sizeof(tx_buff));

	// size_t tx_cnt = 0;
	// UART2.transmit(tx_buff, sizeof(tx_buff), &tx_cnt, 100);

	PORT_E.enable_clock();
	//auto mask = sys::port::PIN_0 | sys::port::PIN_1 | sys::port::PIN_14 | sys::port::PIN_15;
	//PORT_E.init_output(mask);

	PIN_LED2.init_output();
	PIN_LED3.init_output();

	PIN_LED2.tgl();

	while (1) {
		//PIN_LED2.tgl();
		//PIN_LED3.tgl();
		//delay();
		//PORT_E.tgl(mask);
	}
}
