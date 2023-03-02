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

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

void hello_task3(void *pvParameters);
void hello_task4(void *pvParameters);

char *usr_str;

TaskHandle_t t_handle_3;
TaskHandle_t t_handle_4;

int main(void) {
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	usr_str = malloc(sizeof(char) * 100);

	status = xTaskCreate(hello_task3, "Hello_task3", 200, (void*) usr_str, 2, &t_handle_3);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	status = xTaskCreate(hello_task4, "Hello_task4", 200, (void*) usr_str, 3, &t_handle_4);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	vTaskStartScheduler();
	for (;;)
		;
}

void hello_task3(void *pvParameters) {
	while (1) {
		PRINTF("Enter a string input\n");
		scanf("%s", usr_str);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
		xTaskNotifyGive(t_handle_4);
		vTaskDelete(NULL);
	}
}

void hello_task4(void *pvParameters) {
	while (1) {
		ulTaskNotifyTake(pdTRUE, 100);

		PRINTF("Hello %s.\r\n", usr_str);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
