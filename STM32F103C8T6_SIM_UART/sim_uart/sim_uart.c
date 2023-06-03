/**
 * @file sim_uart.c
 * @author zhaitao (zhaitao.as@outlook.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-04
 * 
 * @copyright zhaitao.as@outlook.com (c) 2023
 * 
 */

#include "sim_uart.h"

#include <string.h>

void Emu_uart_tim_callback(struct Emu_Uart_Typedef *uart)
{

	switch (uart->state) {
	case EU_TX_IDLE:
		if (uart->byte_size > 0) {
			uart->byte_count = uart->byte_size;
			uart->state = EU_TX_START;
		}
		break;

	case EU_TX_START:
		uart->set_tx(0);
		uart->bit_count = 0;
		uart->state = EU_TX_DATA;
		break;

	case EU_TX_DATA:

		if ((1 << uart->bit_count) & uart->buff[uart->byte_size - uart->byte_count]) {
			uart->set_tx(1);
		} else {
			uart->set_tx(0);
		}
		uart->bit_count++;

		if (uart->bit_count >= 8) {
			uart->byte_count--;
			uart->state = EU_TX_STOP;
		}

		break;

	case EU_TX_STOP:
		uart->set_tx(1);
		if (uart->byte_count == 0) {
			uart->byte_size = 0;
			uart->state = EU_TX_IDLE;
		} else {
			uart->state = EU_TX_START;
		}
		break;

	default:
		uart->state = EU_TX_IDLE;
		break;
	}
}

void Emu_uart_send(struct Emu_Uart_Typedef *uart, uint8_t *buff, uint16_t size)
{
	memcpy(uart->buff, buff, size);

	uart->byte_size = size;
}