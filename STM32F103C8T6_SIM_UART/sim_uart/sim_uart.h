/**
 * @file sim_uart.h
 * @author zhaitao (zhaitao.as@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-04
 * 
 * @copyright zhaitao.as@outlook.com (c) 2023
 * 
 */

#ifndef __SIM_UART_H__
#define __SIM_UART_H__

#include <stdint.h>
#include "main.h"

enum Sim_Uart_Tx_State {
	SU_TX_IDLE,
	SU_TX_START,
	SU_TX_DATA,
	SU_TX_STOP,
};

struct Sim_Uart_Typedef
{
	//GPIO_TypeDef *tx_port;
	//uint16_t tx_pin;
	void (*set_tx)(uint8_t pin_state);

	enum Sim_Uart_Tx_State state;

	uint8_t buff[256];
	uint16_t byte_size;
	uint16_t byte_count;
	uint16_t bit_count;
};

void sim_uart_tim_callback(struct Sim_Uart_Typedef *uart);

void sim_uart_send(struct Sim_Uart_Typedef *uart, uint8_t *buff, uint16_t size);

#endif //__SIM_UART_H__
