/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_uart.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TARGET_UART UART4

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void setupUART();
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void) {
	char ch;
	char txbuff[] = "Hello World aaron\r\n";
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	setupUART();

	/******* Delay *******/
	for (volatile int i = 0U; i < 10000000; i++)
		__asm("NOP");

//	PRINTF("%s", txbuff);

	UART_WriteBlocking(TARGET_UART, txbuff, sizeof(txbuff) - 1);

	while (1) {
		UART_ReadBlocking(TARGET_UART, &ch, 1);
		PRINTF("%c\r\n", ch);
	}
}

void setupUART() {
	uart_config_t config;
	UART_GetDefaultConfig(&config);
	config.baudRate_Bps = 57600;
	config.enableTx = true;
	config.enableRx = true;
	config.enableRxRTS = true;
	config.enableTxCTS = true;
	UART_Init(TARGET_UART, &config, CLOCK_GetFreq(kCLOCK_BusClk));
}
