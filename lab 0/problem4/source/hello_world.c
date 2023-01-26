/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "problem4.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define GPIOA	((GPIO_Struct*) 0x400FF000)
#define GPIOB	((GPIO_Struct*) 0x400FF040)
#define GPIOC	((GPIO_Struct*) 0x400FF080)
#define GPIOD	((GPIO_Struct*) 0x400FF0C0)
#define GPIOE	((GPIO_Struct*) 0x400FF100)

#define BOARD_LED_GPIO_BLUE    	 	GPIOC
#define BOARD_LED_GPIO_PIN_BLUE	 	8
#define BOARD_LED_GPIO_GREEN     	GPIOC
#define BOARD_LED_GPIO_PIN_GREEN 	9
#define BOARD_LED_GPIO_RED     		GPIOD
#define BOARD_LED_GPIO_PIN_RED		1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void) {
    volatile uint32_t i = 0;
    for (i = 0; i < 2000000; ++i) {
        __asm("NOP");
        /* delay */
    }
}

/*!
 * @brief Main function
 */
int main(void) {
    /* Board pin, clock, debug console init */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\nGPIO Driver example\r\n");
    PRINTF("\r\nThe LED is blinking.\r\n");

    /* Init output LED GPIO. */
    initPin(BOARD_LED_GPIO_BLUE, BOARD_LED_GPIO_PIN_BLUE);
    initPin(BOARD_LED_GPIO_GREEN, BOARD_LED_GPIO_PIN_GREEN);
    initPin(BOARD_LED_GPIO_RED, BOARD_LED_GPIO_PIN_RED);

    while (1) {
        delay();
        togglePin(BOARD_LED_GPIO_BLUE, 1u << BOARD_LED_GPIO_PIN_BLUE);
        delay();
        togglePin(BOARD_LED_GPIO_BLUE, 1u << BOARD_LED_GPIO_PIN_BLUE);
        delay();
        togglePin(BOARD_LED_GPIO_GREEN, 1u << BOARD_LED_GPIO_PIN_GREEN);
        delay();
        togglePin(BOARD_LED_GPIO_GREEN, 1u << BOARD_LED_GPIO_PIN_GREEN);
        delay();
        togglePin(BOARD_LED_GPIO_RED, 1u << BOARD_LED_GPIO_PIN_RED);
        delay();
        togglePin(BOARD_LED_GPIO_RED, 1u << BOARD_LED_GPIO_PIN_RED);
    }
}
