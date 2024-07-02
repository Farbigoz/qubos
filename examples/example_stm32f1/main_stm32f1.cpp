#include <cstring>
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

#include "impl/STM32/F1/sys_tim.h"
#include "impl/STM32/F1/rcc.h"
#include "impl/STM32/F1/port.h"
#include "impl/STM32/F1/pin.h"
#include "impl/STM32/F1/iomux.h"
#include "impl/STM32/F1/uart.h"

#include "impl/STM32/HAL/can.h"

#include "stm32f1xx_hal.h"


impl::port		PORT_A(sys::port::PORT_A);
impl::port		PORT_D(sys::port::PORT_D);
impl::port		PORT_E(sys::port::PORT_E);

impl::pin		PIN_LED1(PORT_E, sys::port::PIN_0);
impl::pin		PIN_LED2(PORT_E, sys::port::PIN_1);
impl::pin		PIN_LED3(PORT_E, sys::port::PIN_14);
impl::pin		PIN_LED4(PORT_E, sys::port::PIN_15);

impl::pin		PIN_UART2_TX(PORT_D, sys::port::PIN_5);
impl::pin		PIN_UART2_RX(PORT_D, sys::port::PIN_6);

impl::pin		PIN_UART3_TX(PORT_D, sys::port::PIN_8);
impl::pin		PIN_UART3_RX(PORT_D, sys::port::PIN_9);

impl::pin		PIN_CAN1_TX(PORT_A, sys::port::PIN_12);
impl::pin		PIN_CAN1_RX(PORT_A, sys::port::PIN_11);

impl::uart		UART2(impl::uart::UART_2);


impl::core_tim	CORE_TIM;



void sys_tick_signal_slot_fn(sys::sys_tim&) {
	PIN_UART3_TX.tgl();

	PIN_LED2.tgl();
	PIN_LED3.tgl();
}

sys::sys_tim::signal_irq_t::Slot sys_tick_signal_slot;

impl::dma	uart_tx_dma(impl::dma::DMA_1, impl::dma::CHANNEL_7);
impl::dma	uart_rx_dma(impl::dma::DMA_1, impl::dma::CHANNEL_6);


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


#include "ethernetif.h"
#include "netif/ethernet.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/udp.h"

static struct netif gnetif;
static struct udp_pcb *pcb = NULL;

ip4_addr_t addr;
ip4_addr_t mask;
ip4_addr_t gate;
ip4_addr_t dest;

extern uint32_t SystemCoreClock;


static void mss_eth_recv( void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port )
{
	//if( ( pcb->remote_port == port ) && ( pcb->remote_ip.addr == addr->addr ) )
	//{
	//}

	/*
	struct pbuf *p_send = pbuf_alloc( PBUF_TRANSPORT, p->tot_len, PBUF_RAM ); // PBUF_REF
	if( !p_send )
		while (1);

	// копирование данных
	memcpy( p_send->payload, p->payload, p->tot_len );
	// PBUF_REF: p->payload = buf;

	// отправка сообщения
	err_t res = udp_sendto(pcb, p_send, &dest, 23456);

	// освобождение памяти
	pbuf_free( p_send );

	if( res != ERR_OK ) netif_set_up( &gnetif );
	 */
	udp_sendto(pcb, p, &dest, 23456);

	pbuf_free( p );
}

const impl::can::speed_cfg_t CAN_SPEED_CFGS[] = {
		{.speed=50000,  .bus_clk=36000000, .prescaler=40, .ts1=impl::can::TS1_15TQ, .ts2=impl::can::TS2_2TQ},
		{.speed=100000, .bus_clk=36000000, .prescaler=20, .ts1=impl::can::TS1_15TQ, .ts2=impl::can::TS2_2TQ},
};

//static impl::can	TEST_CAN(CAN1, {{36000000, 50000, impl::can::TS1_1TQ, impl::can::TS2_1TQ}, {36000000, 100000, impl::can::TS1_2TQ, impl::can::TS2_2TQ}});
impl::can	SYS_CAN(CAN1, CAN_SPEED_CFGS);

uint32_t test_var = 0;

int main() {
	uint32_t clk = 0;
	sys::result_t res = sys::RES_NONE;

	SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_2);

	res = impl::rcc::HSE::set_freq(25000000);
	res = impl::rcc::PREDIV2::set_div(5);
	res = impl::rcc::PLL2::set_mult(impl::rcc::PLL2::MULT_8);
	res = impl::rcc::PREDIV1::set_source(impl::rcc::PREDIV1::SRC_PLL2);
	res = impl::rcc::PREDIV1::set_div(5);
	res = impl::rcc::PLL::set_source(impl::rcc::PLL::SRC_PREDIV1);
	res = impl::rcc::PLL::set_mult(impl::rcc::PLL::MULT_9);

	res = impl::rcc::MCO::set_output(impl::rcc::MCO::OUT_XT1);

	res = impl::rcc::APB1::set_div(impl::rcc::APB1::DIV_2);
	res = impl::rcc::APB2::set_adc_div(impl::rcc::APB2::ADC_DIV_6);

	res = impl::rcc::HSE::enable();
	res = impl::rcc::PLL2::enable();
	res = impl::rcc::PLL::enable();

	res = impl::rcc::SYSCLK::set_source(impl::rcc::SYSCLK::SRC_PLL);

	//clk = impl::rcc::SYSCLK::calc_clk();
	//clk = impl::rcc::APB1::calc_clk();
	//clk = impl::rcc::APB1::get_tim_clk();
	//clk = impl::rcc::APB2::calc_clk();
	//clk = impl::rcc::APB2::get_tim_clk();
	//clk = impl::rcc::APB2::get_adc_clk();

	res = impl::iomux().enable_clock();
	res = impl::iomux().set_remap(sys::iomux::REMAP_UART2, sys::iomux::REMAP_NUM_1);
	//res = impl::iomux().set_remap(sys::iomux::REMAP_UART3, sys::iomux::REMAP_NUM_3);


	res = PORT_A.enable_clock();
	res = PIN_CAN1_TX.init_alt(sys::pin::ALT_NONE, sys::pin::DRV_PUSH_PULL, sys::pin::SPEED_VERY_FAST);
	res = PIN_CAN1_RX.init_input(sys::pin::PULL_NONE);

	res = SYS_CAN.enable_clock();
	res = SYS_CAN.init(50000);
	res = SYS_CAN.start();
	test_var = SYS_CAN.get_total_tx_mailboxes();
	test_var = SYS_CAN.get_total_rx_mailboxes();
	test_var = SYS_CAN.get_max_filters();
	test_var = SYS_CAN.get_tx_mailboxes_free_level();
	test_var = SYS_CAN.get_rx_mailboxes_fill_level();
	test_var = SYS_CAN.get_free_tx_mailbox();
	test_var = SYS_CAN.get_speed();

	sys::can::msg_t can_msg = {.idtype=sys::can::ID_EXT, .id = 0x12345678, .len=1, .data={0x00}};

	sys::can::mailbox_t mailbox;
	for (int i = 0; i <= 255; i++) {
		can_msg.data[0] = i;

		do {
			mailbox = SYS_CAN.get_free_tx_mailbox();
		} while (mailbox == sys::can::UNKNOWN_MAILBOX);

		res = SYS_CAN.push_tx(can_msg, mailbox);

		HAL_Delay(500);
	}

	PORT_D.enable_clock();

	PIN_UART2_TX.init_alt(sys::pin::ALT_NONE, sys::pin::DRV_PUSH_PULL, sys::pin::SPEED_VERY_FAST);
	PIN_UART2_RX.init_input(sys::pin::PULL_NONE);

	PIN_UART3_TX.init_output();

	res = CORE_TIM.init(1000);
	CORE_TIM.signal_irq.connect(sys_tick_signal_slot, sys_tick_signal_slot_fn);
	res = CORE_TIM.enable_irq();

	res = sys::set_sys_timer(CORE_TIM);

	SystemCoreClock = impl::rcc::HCLK::CLK_FREQ;


	lwip_init();

	IP4_ADDR(&addr, 192, 168,   0, 2 );
	IP4_ADDR(&dest, 192, 168,   0, 1 );
	IP4_ADDR(&gate, 192, 168,   0, 1 );
	IP4_ADDR(&mask, 255, 255, 255, 0 );
	uint16_t port = 23456;

	if( !netif_add( &gnetif, &addr, &mask, &gate, NULL, ethernetif_init, ethernet_input ) )
	{
		while(1);
	}

	/* Registers the default network interface */
	netif_set_default( &gnetif );

	/* Set the link callback function, this function is called on change of link status*/
	netif_set_link_callback( &gnetif, ethernetif_update_config );


	// создание сокета
	struct udp_pcb *pcb = udp_new();
	if( pcb == NULL )
		while (1);

	// привязка к адресу
	if( udp_bind( pcb, &addr, port ) != ERR_OK )
		while (1);

	// установка адреса отправки
	//if( udp_connect( pcb, &dest, port ) != ERR_OK )
	//	while (1);

	// установка функции приёма
	udp_recv( pcb, mss_eth_recv, NULL );

	uint32_t send_tick = HAL_GetTick();
	uint8_t byte = 0x00;

	while (1) {
		ethernetif_input( &gnetif );

		/* Check link status */
		if( netif_is_link_up( &gnetif ) )
		{
			/* When the netif is fully configured this function must be called */
			netif_set_up( &gnetif );
		}
		else
		{
			/* When the netif link is down this function must be called */
			netif_set_down( &gnetif );
		}

		continue;

		if ((HAL_GetTick() - send_tick) > 2500) {
			send_tick = HAL_GetTick();

			struct pbuf *p = pbuf_alloc( PBUF_TRANSPORT, sizeof(byte), PBUF_RAM ); // PBUF_REF
			if( !p )
				while (1);

			// копирование данных
			memcpy( p->payload, &byte, sizeof(byte) );
			// PBUF_REF: p->payload = buf;

			// отправка сообщения
			//err_t res = udp_send( pcb, p );
			err_t res = udp_sendto(pcb, p, &dest, port);

			// освобождение памяти
			pbuf_free( p );

			if( res != ERR_OK ) netif_set_up( &gnetif );

			byte++;
		}

	}


	/*
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
	 */

}
