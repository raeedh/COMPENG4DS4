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
#include "event_groups.h"
/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
void producer_event(void *pvParameters);
void consumer_event(void *pvParameters);
void consumer2_event(void *pvParameters);
int main(void) {
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
	EventGroupHandle_t event_group = xEventGroupCreate();
	status = xTaskCreate(producer_event, "producer", 200, (void*) event_group,
			2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer_event, "consumer", 200, (void*) event_group,
			3, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer2_event, "consumer", 200, (void*) event_group,
			3, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	vTaskStartScheduler();
	while (1) {
	}
}

#define receive_BIT (1 << 0)
#define echo_BIT (1 << 1)

int counter = 0;

void producer_event(void *pvParameters) {
	EventGroupHandle_t event_group = (EventGroupHandle_t) pvParameters;
	BaseType_t status;

	while (1) {
		counter++;
		xEventGroupSetBits(event_group, receive_BIT);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		xEventGroupSetBits(event_group, echo_BIT);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void consumer_event(void *pvParameters) {
	EventGroupHandle_t event_group = (EventGroupHandle_t) pvParameters;
	EventBits_t bits;
	while (1) {
		bits = xEventGroupWaitBits(event_group,
		receive_BIT,
		pdTRUE,
		pdFALSE,
		portMAX_DELAY);

		if ((bits & receive_BIT) == receive_BIT) {
			PRINTF("Received Value = %d\r\n", counter);
		}

	}
}


void consumer2_event(void *pvParameters) {
	EventGroupHandle_t event_group = (EventGroupHandle_t) pvParameters;
	EventBits_t bits;
	while (1) {
		bits = xEventGroupWaitBits(event_group,
 		echo_BIT,
		pdTRUE,
		pdFALSE,
		portMAX_DELAY);

		if ((bits & echo_BIT) == echo_BIT) {
			PRINTF("Received Value = %d\r\n", counter);
		}

	}
}
