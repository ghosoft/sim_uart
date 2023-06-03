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

#ifndef __EMU_UART_H__
#define __EMU_UART_H__

#include <stdint.h>
#include "main.h"

enum Emu_Uart_Tx_State {
	EU_TX_IDLE,
	EU_TX_START,
	EU_TX_DATA,
	EU_TX_STOP,
};

struct Emu_Uart_Typedef
{
	void (*set_tx)(uint8_t pin_state);

	enum Emu_Uart_Tx_State state;

	uint8_t buff[256];
	uint16_t byte_size;
	uint16_t byte_count;
	uint16_t bit_count;
};

void Emu_uart_tim_callback(struct Emu_Uart_Typedef *uart);

void Emu_uart_send(struct Emu_Uart_Typedef *uart, uint8_t *buff, uint16_t size);

#endif
