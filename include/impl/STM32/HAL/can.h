#ifndef STM32_HAL_CAN_H
#define STM32_HAL_CAN_H

#include <initializer_list>
#include <vector>
#include "system/interface/can.h"

#if defined(STM32F1)
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal_can.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal_can.h"
#endif /* STM32F1 */


namespace impl {

class can : public sys::can {
public:
	static const uint32_t TX_MAILBOX_CNT = 3;
	static const uint32_t RX_MAILBOX_CNT = 3;
	static const uint32_t FILTER_CNT = 14;

public:
	typedef enum TIME_SEGMENT_1_T {
		TS1_1TQ = CAN_BS1_1TQ,
		TS1_2TQ = CAN_BS1_2TQ,
		TS1_3TQ = CAN_BS1_3TQ,
		TS1_4TQ = CAN_BS1_4TQ,
		TS1_5TQ = CAN_BS1_5TQ,
		TS1_6TQ = CAN_BS1_6TQ,
		TS1_7TQ = CAN_BS1_7TQ,
		TS1_8TQ = CAN_BS1_8TQ,
		TS1_9TQ = CAN_BS1_9TQ,
		TS1_10TQ = CAN_BS1_10TQ,
		TS1_11TQ = CAN_BS1_11TQ,
		TS1_12TQ = CAN_BS1_12TQ,
		TS1_13TQ = CAN_BS1_13TQ,
		TS1_14TQ = CAN_BS1_14TQ,
		TS1_15TQ = CAN_BS1_15TQ,
		TS1_16TQ = CAN_BS1_16TQ,
	} ts1_t;

	typedef enum TIME_SEGMENT_2_T {
		TS2_1TQ = CAN_BS2_1TQ,
		TS2_2TQ = CAN_BS2_2TQ,
		TS2_3TQ = CAN_BS2_3TQ,
		TS2_4TQ = CAN_BS2_4TQ,
		TS2_5TQ = CAN_BS2_5TQ,
		TS2_6TQ = CAN_BS2_6TQ,
		TS2_7TQ = CAN_BS2_7TQ,
		TS2_8TQ = CAN_BS2_8TQ,
	} ts2_t;

public:
	typedef struct SPEED_CFG_T {
		uint32_t speed;
		uint32_t bus_clk;
		uint32_t prescaler;
		ts1_t ts1;
		ts2_t ts2;
	} speed_cfg_t;

public:
	// can(CAN_TypeDef *can_def, const std::initializer_list<speed_cfg_t> cfgs)
	// :
	// hcan(),
	// cfgs_begin(cfgs.begin()),
	// cfgs_end(cfgs.end()),
	// txMailBox()
	// {
	// 	hcan.Instance = can_def;
	// }

	can(CAN_TypeDef *can_def, const speed_cfg_t *cfgs_begin, const speed_cfg_t *cfgs_end)
	:
	hcan(),
	cfgs_begin(cfgs_begin),
	cfgs_end(cfgs_end),
	txMailBox()
	{
		hcan.Instance = can_def;
	}

	template<typename _Tp, size_t _Nm>
	can(CAN_TypeDef *can_def, _Tp (&__arr)[_Nm])
	:
	hcan(),
	cfgs_begin(__arr),
	cfgs_end(__arr + _Nm),
	txMailBox()
	{
		hcan.Instance = can_def;
	}

// periphery
public:
	sys::result_t deinit() override {
		HAL_CAN_DeInit(&hcan);
		return disable_clock();
	}

// clock
public:
	uint32_t get_clock_freq() override {
		return impl::rcc::APB1::calc_clk();
	}

	sys::result_t enable_clock() override {
		if (hcan.Instance == CAN1)
			return rcc::APB1::enable(rcc::APB1::CLK_CAN1);
		else if (hcan.Instance == CAN2)
			return rcc::APB1::enable(rcc::APB1::CLK_CAN2);
		else
			return sys::RES_ERROR;
	}

	sys::result_t disable_clock() override {
		if (hcan.Instance == CAN1)
			return rcc::APB1::disable(rcc::APB1::CLK_CAN1);
		else if (hcan.Instance == CAN2)
			return rcc::APB1::disable(rcc::APB1::CLK_CAN2);
		else
			return sys::RES_ERROR;
	}

// periphery txrx
public:
	sys::result_t set_tx_irq_prior(uint32_t) override {
		// todo
		return sys::RES_ERROR;
	}

	sys::result_t set_rx_irq_prior(uint32_t) override {
		// todo
		return sys::RES_ERROR;
	}

	uint32_t get_tx_irq_prior() override {
		// todo
		return 0;
	}

	uint32_t get_rx_irq_prior() override {
		// todo
		return 0;
	}

	bool tx_busy() override {
		return true;
	}

	bool rx_busy() override {
		return true;
	}

	bool is_tx_irq() override {
		// todo
		return false;
	}

	bool is_rx_irq() override {
		// todo
		return false;
	}

	sys::result_t enable_tx_irq() override {
		// todo
		return sys::RES_ERROR;
	}

	sys::result_t enable_rx_irq() override {
		// todo
		return sys::RES_ERROR;
	}

	sys::result_t disable_tx_irq() override {
		// todo
		return sys::RES_ERROR;
	}

	sys::result_t disable_rx_irq() override {
		// todo
		return sys::RES_ERROR;
	}

// can
public:
	sys::result_t init(uint32_t s) override {
		auto speed_cfg = find_speed_cfg(s);
		if (speed_cfg == nullptr) {
			deinit();
			return sys::RES_ERROR;
		}

		hcan.Init.Prescaler = speed_cfg->prescaler;
		hcan.Init.Mode = CAN_MODE_NORMAL;
		hcan.Init.SyncJumpWidth = CAN_SJW_3TQ;
		hcan.Init.TimeSeg1 = speed_cfg->ts1;
		hcan.Init.TimeSeg2 = speed_cfg->ts2;
		hcan.Init.TimeTriggeredMode = DISABLE;
		hcan.Init.AutoBusOff = ENABLE;
		hcan.Init.AutoWakeUp = DISABLE;
		hcan.Init.AutoRetransmission = ENABLE;
		hcan.Init.ReceiveFifoLocked = DISABLE;
		hcan.Init.TransmitFifoPriority = ENABLE;

#if USE_HAL_CAN_REGISTER_CALLBACKS == 1
		hcan.MspInitCallback = nullptr;
#endif

		return HAL_CAN_Init(&hcan) == HAL_OK ? sys::RES_OK : sys::RES_ERROR;
	}


	sys::result_t set_speed(uint32_t s) override {
		return init(s);
	}

	sys::result_t set_filter(uint32_t filter_num, filter_t filter) override {
		CAN_FilterTypeDef	rx_filter;

		if (filter_num >= FILTER_CNT)
			return sys::RES_ERROR;

		if (hcan.Instance == CAN1)
			rx_filter.FilterBank = filter_num;
		else
			rx_filter.FilterBank = filter_num + FILTER_CNT;

		if (filter.type == ID_STD)
		{
			rx_filter.FilterIdHigh = (uint16_t)(filter.id << 5);
			rx_filter.FilterIdLow = 0x0000;
			rx_filter.FilterMaskIdHigh = (uint16_t)(filter.mask << 5);
			rx_filter.FilterMaskIdLow = 0x0000;
		}
		else
		{
			rx_filter.FilterIdHigh = (uint16_t)(filter.id >> 13);
			rx_filter.FilterIdLow = (uint16_t)(filter.id << 3) | 0x04;
			rx_filter.FilterMaskIdHigh = (uint16_t)(filter.mask >> 13);
			rx_filter.FilterMaskIdLow = (uint16_t)(filter.mask << 3) | 0x04;
		}

		rx_filter.FilterScale = CAN_FILTERSCALE_32BIT;
		rx_filter.FilterMode = CAN_FILTERMODE_IDMASK;
		rx_filter.FilterFIFOAssignment = CAN_RX_FIFO0;
		rx_filter.FilterActivation = ENABLE;



		//rx_filter.FilterBank = 0;
		//rx_filter.FilterMode = CAN_FILTERMODE_IDMASK;
		//rx_filter.FilterScale = CAN_FILTERSCALE_32BIT;
		//rx_filter.FilterIdHigh = 0x0000;
		//rx_filter.FilterIdLow = 0x0000;
		//rx_filter.FilterMaskIdHigh = 0x0000;
		//rx_filter.FilterMaskIdLow = 0x0000;
		//rx_filter.FilterFIFOAssignment = CAN_RX_FIFO0;
		//rx_filter.FilterActivation = ENABLE;

		return (HAL_CAN_ConfigFilter(&hcan, &rx_filter) == HAL_OK) ? sys::RES_OK : sys::RES_ERROR;
	}


	const uint32_t get_total_tx_mailboxes() override {
		return TX_MAILBOX_CNT;
	}

	const uint32_t get_total_rx_mailboxes() override {
		return RX_MAILBOX_CNT;
	}

	const uint32_t get_max_filters() override {
		return FILTER_CNT;
	}

	mailbox_t get_tx_mailboxes_free_level() override {
		return HAL_CAN_GetTxMailboxesFreeLevel(&hcan);
	}

	uint32_t get_rx_mailboxes_fill_level() override {
		return HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0);
	}

	mailbox_t get_free_tx_mailbox() override {
		uint32_t tsr = READ_REG(hcan.Instance->TSR);

		if ((READ_BIT(tsr, CAN_TSR_TME0) != 0U) ||
			(READ_BIT(tsr, CAN_TSR_TME1) != 0U) ||
			(READ_BIT(tsr, CAN_TSR_TME2) != 0U)) {
			/* Select an empty transmit mailbox */
			return READ_BIT(tsr, CAN_TSR_CODE) >> CAN_TSR_CODE_Pos;
		}

		return UNKNOWN_MAILBOX;
	}

	filter_t get_filter(uint32_t filter_num) override {
		filter_t filter = {};

		if (filter_num >= FILTER_CNT)
			return filter;

		// todo
		return filter;
	}

	uint32_t get_speed() override {
		uint32_t ts1v = READ_BIT(hcan.Instance->BTR, CAN_BTR_TS1_Msk) >> CAN_BTR_TS1_Pos;
		uint32_t ts2v = READ_BIT(hcan.Instance->BTR, CAN_BTR_TS2_Msk) >> CAN_BTR_TS2_Pos;
		return get_clock_freq() / (hcan.Init.Prescaler * (ts1v + 1 + ts2v + 1 + 1));
	}


	bool is_tx_pend(sys::can::mailbox_t m) override {
		if (m >= TX_MAILBOX_CNT)
			return true;

		return HAL_CAN_IsTxMessagePending(&hcan, 1 << m);
	}


	sys::result_t start() override {
		return HAL_CAN_Start(&hcan) == HAL_OK ? sys::RES_OK : sys::RES_ERROR;
	}

	sys::result_t stop() override {
		return HAL_CAN_Stop(&hcan) == HAL_OK ? sys::RES_OK : sys::RES_ERROR;
	}


	sys::result_t transmit(msg_t msg) {
		CAN_TxHeaderTypeDef txHeader;

		if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan) == 0)
			return sys::RES_BUSY;

		if (msg.idtype == ID_EXT)
			txHeader.IDE = CAN_ID_EXT;
		else
			txHeader.IDE = CAN_ID_STD;

		//if (msg.rtr == RTR_DATA)
		//	txHeader.RTR = CAN_RTR_DATA;
		//else
		//	txHeader.RTR = CAN_RTR_REMOTE;
		txHeader.RTR = CAN_RTR_DATA;	// todo: rtr

		txHeader.StdId = msg.id;
		txHeader.ExtId = msg.id;
		txHeader.DLC = msg.len;
		txHeader.TransmitGlobalTime = DISABLE;

		if (HAL_CAN_AddTxMessage(&hcan, &txHeader, msg.data, &txMailBox) != HAL_OK)
			return sys::RES_ERROR;

		return sys::RES_OK;
	}

	sys::result_t receive(msg_t msg) {
		CAN_RxHeaderTypeDef rx_header;

		// Доступны ли сообщения для считывания
		if ((hcan.Instance->RF0R & CAN_RF0R_FMP0) == 0U)
			return sys::RES_NONE;

		if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rx_header, msg.data) == HAL_ERROR)
			return sys::RES_ERROR;

		//if (rx_header.RTR == CAN_RTR_DATA)
		//	msg.rtr = RTR_DATA;
		//else
		//	msg.rtr = RTR_REMOTE;

		if (rx_header.IDE == CAN_ID_EXT)
		{
			msg.idtype = ID_EXT;
			msg.id = rx_header.ExtId;
		}
		else
		{
			msg.idtype = ID_STD;
			msg.id = rx_header.StdId;
		}

		msg.len = rx_header.DLC;

		return sys::RES_OK;
	}

	sys::result_t push_tx(sys::can::msg_t msg, sys::can::mailbox_t m) override {
		uint32_t mailbox_mask = 1 << m;

		if (m >= TX_MAILBOX_CNT)
			return sys::RES_ERROR;

		if ((hcan.State != HAL_CAN_STATE_READY) && (hcan.State != HAL_CAN_STATE_LISTENING))
			return sys::RES_NOT_ENABLED;

		if (HAL_CAN_IsTxMessagePending(&hcan, mailbox_mask))
			return sys::RES_BUSY;

		/* Set up the Id */
		if (msg.idtype == ID_STD)
			hcan.Instance->sTxMailBox[m].TIR = ((msg.id << CAN_TI0R_STID_Pos) | CAN_RTR_DATA);
		else
			hcan.Instance->sTxMailBox[m].TIR = ((msg.id << CAN_TI0R_EXID_Pos) | CAN_ID_EXT | CAN_RTR_DATA);

		/* Set up the DLC */
		hcan.Instance->sTxMailBox[m].TDTR = msg.len;

		/* Set up the Transmit Global Time mode */
		//if (pHeader->TransmitGlobalTime == ENABLE)
		//{
		//	SET_BIT(hcan->Instance->sTxMailBox[transmitmailbox].TDTR, CAN_TDT0R_TGT);
		//}

		/* Set up the data field */
		WRITE_REG(hcan.Instance->sTxMailBox[m].TDHR,
				  ((uint32_t)msg.data[7] << CAN_TDH0R_DATA7_Pos) |
				  ((uint32_t)msg.data[6] << CAN_TDH0R_DATA6_Pos) |
				  ((uint32_t)msg.data[5] << CAN_TDH0R_DATA5_Pos) |
				  ((uint32_t)msg.data[4] << CAN_TDH0R_DATA4_Pos));
		WRITE_REG(hcan.Instance->sTxMailBox[m].TDLR,
				  ((uint32_t)msg.data[3] << CAN_TDL0R_DATA3_Pos) |
				  ((uint32_t)msg.data[2] << CAN_TDL0R_DATA2_Pos) |
				  ((uint32_t)msg.data[1] << CAN_TDL0R_DATA1_Pos) |
				  ((uint32_t)msg.data[0] << CAN_TDL0R_DATA0_Pos));

		/* Request transmission */
		SET_BIT(hcan.Instance->sTxMailBox[m].TIR, CAN_TI0R_TXRQ);

		return sys::RES_OK;
	}

	sys::result_t pull_rx(sys::can::msg_t &msg) override {
		CAN_RxHeaderTypeDef rx_header;

		if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) == 0)
			return sys::RES_NONE;

		if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rx_header, msg.data) == HAL_ERROR)
			return sys::RES_ERROR;

		//if (rx_header.RTR == CAN_RTR_DATA)
		//	msg.rtr = RTR_DATA;
		//else
		//	msg.rtr = RTR_REMOTE;

		if (rx_header.IDE == CAN_ID_EXT)
		{
			msg.idtype = ID_EXT;
			msg.id = rx_header.ExtId;
		}
		else
		{
			msg.idtype = ID_STD;
			msg.id = rx_header.StdId;
		}

		msg.len = rx_header.DLC;

		return sys::RES_OK;
	}

	sys::result_t abort_tx(sys::can::mailbox_t m) override {
		uint32_t mailbox_mask = 1 << m;

		if (m >= TX_MAILBOX_CNT)
			return sys::RES_ERROR;

		return (HAL_CAN_AbortTxRequest(&hcan, mailbox_mask) == HAL_OK) ? sys::RES_OK : sys::RES_ERROR;
	}


private:
	const speed_cfg_t * find_speed_cfg(uint32_t speed) {
		for (const speed_cfg_t *cfg = cfgs_begin; cfg != cfgs_end; cfg++)
			if (cfg->bus_clk == get_clock_freq() && cfg->speed == speed)
				return cfg;
		return nullptr;
	}

private:
	CAN_HandleTypeDef hcan;

	const speed_cfg_t *cfgs_begin;
	const speed_cfg_t *cfgs_end;

	uint32_t txMailBox;
};

}


#endif /* STM32_HAL_CAN_H */