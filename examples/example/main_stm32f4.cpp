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

#include "stm32f4xx_hal.h"

#include "impl/STM32/F4/port.h"
#include "impl/STM32/F4/pin.h"
#include "impl/STM32/F4/rcc.h"

#include "impl/STM32/HAL/can.h"



#ifndef __BYTE_ORDER
#  if ((defined __little_endian__) || (defined __big_endian__)) && (defined __TI_COMPILER_VERSION__)
#    define __LITTLE_ENDIAN __little_endian__
#    define __BIG_ENDIAN __big_endian__
#    if ( __little_endian__ != 0 )
#      define __BYTE_ORDER __little_endian__
#    elif ( __big_endian__ != 0 )
#      define __BYTE_ORDER __big_endian__
#    endif
#  elif (defined __unix__)
#    include <endian.h>
#  else
#    if (defined __BYTE_ORDER__)
#      if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#        define __BIG_ENDIAN __ORDER_BIG_ENDIAN__
#        define __BYTE_ORDER __BIG_ENDIAN
#      elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#        define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#        define __BYTE_ORDER __LITTLE_ENDIAN
#      endif
#    endif
#  endif
#endif

#ifndef __BYTE_ORDER
#error "__BYTE_ORDER not defined"
#endif


#if __BYTE_ORDER == __BIG_ENDIAN

#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)

#elif __BYTE_ORDER == __LITTLE_ENDIAN

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))
#endif


impl::port		PORT_C(sys::port::PORT_C);
impl::pin		PIN_LED1(PORT_C, sys::port::PIN_1);
impl::pin		PIN_LED2(PORT_C, sys::port::PIN_2);
impl::pin		PIN_LED3(PORT_C, sys::port::PIN_3);
impl::pin		PIN_LED4(PORT_C, sys::port::PIN_4);
impl::pin		PIN_LED13(PORT_C, sys::port::PIN_13);

impl::port		PORT_B(sys::port::PORT_B);
impl::pin		PIN_CAN_SYS_TX(PORT_B, sys::port::PIN_9);
impl::pin		PIN_CAN_SYS_RX(PORT_B, sys::port::PIN_8);

const impl::can::speed_cfg_t CAN_SPEED_CFGS[] = {
		{.speed=50000,  .bus_clk=42000000, .prescaler=56, .ts1=impl::can::TS1_12TQ, .ts2=impl::can::TS2_2TQ}
};

impl::can		CAN_SYS(CAN1, CAN_SPEED_CFGS);

void delay() {
	for (int i = 0; i < 100000; i++);
}


void pin_irq_handler(sys::pin &pin) {
	PIN_LED1.tgl();
}


sys::pin::signal_irq_t::Slot	pin1_irq_slot;
sys::pin::signal_irq_t::Slot	pin2_irq_slot;
sys::pin::signal_irq_t::Slot	pin3_irq_slot;


uint32_t test_var;
int main() {
	sys::result_t RESULT;
	//for (int i = 0; i < 0xffffff; i++);

	(*(__IO uint8_t *)(0x40023C00U) = (uint8_t)(FLASH_ACR_LATENCY_4WS));

	RESULT = impl::rcc::SYSCLK::set_source(impl::rcc::SYSCLK::SRC_HSI);

	RESULT = impl::rcc::HSE::set_freq(25000000);
	RESULT = impl::rcc::HSE::enable();
	//RESULT = impl::rcc::SW::set_source(impl::rcc::SW::SRC_HSE);

	RESULT = impl::rcc::PLL::disable();
	RESULT = impl::rcc::PLL::set_source(impl::rcc::PLL::SRC_HSE);
	RESULT = impl::rcc::PLL::set_prediv_m(25);
	RESULT = impl::rcc::PLL::set_mult_n(336);
	//RESULT = impl::rcc::PLL::set_mult_n(240);
	//RESULT = impl::rcc::PLL::set_mult_n(300);
	RESULT = impl::rcc::PLL::set_div_p(impl::rcc::PLL::DIV_P_2);
	RESULT = impl::rcc::PLL::enable();

	RESULT = impl::rcc::AHB::set_div(impl::rcc::AHB::DIV_1);
	RESULT = impl::rcc::APB1::set_div(impl::rcc::APB1::DIV_4);
	RESULT = impl::rcc::APB2::set_div(impl::rcc::APB2::DIV_2);

	//SET_BIT(RCC->CFGR, 0x04U << RCC_CFGR_PPRE1_Pos);

	RESULT = impl::rcc::SYSCLK::set_source(impl::rcc::SYSCLK::SRC_PLL);


	test_var = impl::rcc::APB1::calc_clk();

	HAL_Init();


	RESULT = PORT_B.enable_clock();
	RESULT = PORT_C.enable_clock();


	RESULT = PIN_CAN_SYS_TX.init_alt(sys::pin::ALT_CAN1);
	RESULT = PIN_CAN_SYS_RX.init_alt(sys::pin::ALT_CAN1, sys::pin::PULL_UP);

	RESULT = CAN_SYS.enable_clock();
	RESULT = CAN_SYS.init(50000);
	RESULT = CAN_SYS.start();
	test_var = CAN_SYS.get_total_tx_mailboxes();
	test_var = CAN_SYS.get_total_rx_mailboxes();
	test_var = CAN_SYS.get_max_filters();
	test_var = CAN_SYS.get_tx_mailboxes_free_level();
	test_var = CAN_SYS.get_rx_mailboxes_fill_level();
	test_var = CAN_SYS.get_free_tx_mailbox();
	test_var = CAN_SYS.get_speed();
	RESULT = CAN_SYS.set_filter(0, {.id=0x00000000, .mask=0x00000000, .type=sys::can::ID_EXT});

	sys::can::msg_t rx_msg;
	sys::can::msg_t tx_msg = {.idtype=sys::can::ID_EXT, .id = 0x12345678, .len=4, .data={0x00}};
	sys::can::mailbox_t mailbox;

	uint32_t *cnt = (uint32_t *)tx_msg.data;
	*cnt = 0;

	do {
		mailbox = CAN_SYS.get_free_tx_mailbox();
	} while (mailbox == sys::can::UNKNOWN_MAILBOX);
	test_var = CAN_SYS.push_tx(tx_msg, mailbox);

	while (1) {
		RESULT = CAN_SYS.pull_rx(rx_msg);
		if (RESULT != sys::RES_OK)
			continue;

		*cnt = NTOHL(*cnt);
		*cnt += 1;
		*cnt = HTONL(*cnt);

		do {
			mailbox = CAN_SYS.get_free_tx_mailbox();
		} while (mailbox == sys::can::UNKNOWN_MAILBOX);
		test_var = CAN_SYS.push_tx(tx_msg, mailbox);
	}

	//for (int i = 0; i <= 15; i++) {
	//	can_msg.data[0] = i;

	//	do {
	//		mailbox = CAN_SYS.get_free_tx_mailbox();
	//	} while (mailbox == sys::can::UNKNOWN_MAILBOX);

	//	test_var = CAN_SYS.push_tx(can_msg, mailbox);
	//}

	// PIN_LED3.set_alt(sys::pin::ALT_0);

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