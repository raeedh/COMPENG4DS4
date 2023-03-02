/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void timerCallbackFunction2(TimerHandle_t timer_handle);
void consumer_sem(void *pvParameters);
// void producer_sem(void *pvParameters);

SemaphoreHandle_t *semaphores;

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void) {
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	semaphores = (SemaphoreHandle_t*) malloc(1 * sizeof(SemaphoreHandle_t));
	semaphores[0] = xSemaphoreCreateBinary(); // Consumer semaphore

	status = xTaskCreate(consumer_sem, "consumer", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	TimerHandle_t timer_handle2 = xTimerCreate("Periodic timer",
			1000 / portTICK_PERIOD_MS,
			pdTRUE,
			NULL, timerCallbackFunction2);

	status = xTimerStart(timer_handle2, 0);
	if (status != pdPASS) {
		PRINTF("Couldn't start the timer!.\r\n");
		while (1)
			;
	}

	vTaskStartScheduler();
	while (1) {
	}
}

void timerCallbackFunction2(TimerHandle_t timer_handle) {
//	PRINTF("Hello from the periodic timer callback.\r\n");

	SemaphoreHandle_t consumer_semaphore = semaphores[0];
	BaseType_t status;

	xSemaphoreGive(consumer_semaphore);
}

void consumer_sem(void *pvParameters) {
	SemaphoreHandle_t consumer_semaphore = semaphores[0];
	BaseType_t status;

	while (1) {
		status = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		if (status != pdPASS) {
			PRINTF("Failed to acquire consumer_semaphore\r\n");
			while (1)
				;
		}

		PRINTF("Hello World!\n");
	}
}
