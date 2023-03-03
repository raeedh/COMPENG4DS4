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
void producer_event(void *pvParameters);
void consumer_event(void *pvParameters);

typedef struct {
    SemaphoreHandle_t sem;

    int counter;
} wasd_handler;

int main(void) {
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();




	SemaphoreHandle_t	my_sem = xSemaphoreCreateBinary();

	int my_counter = 0;
	wasd_handler my_wasd = { my_sem, my_count };
	wasd_handler *my_wasd_ptr = &my_wasd;

	xSemaphoreGive(my_sem);

	status = xTaskCreate(producer_event, "producer", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer_event, "consumer", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	vTaskStartScheduler();
	while (1) {
	}
}

void producer_event(void *pvParameters) {
	wasd_handler *my_sem = (wasd_handler *)pvParameters;

	BaseType_t status1,
	char c;

	while (1) {
		status1 = xSemaphoreTake(my_sem->sem, portMAX_DELAY);


		if (status1 != pdPASS) {
			PRINTF("Failed to acquire consumer_semaphore\r\n");

			while (1)
				;
		}

		while (1) {
			scanf("%c", &c);

			switch (c) {
			case 'a':
				xSemaphoreGive(my_sem->sem);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				my_sem -> counter = 0;
				break;
			case 'd':
				xSemaphoreGive(my_sem->sem);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				my_sem -> counter = 1;
				break;
			case 'w':
				xSemaphoreGive(my_sem->sem);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				my_sem -> counter = 2;
				break;
			case 's':
				xSemaphoreGive(pmy_sem->sem);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				my_sem -> counter = 3;
				break;
			}
		}
	}
}

void consumer_event(void *pvParameters) {
		wasd_handler *my_sem = (wasd_handler *)pvParameters;
	BaseType_t status;

	while (1) {
		xSemaphoreGive(consumer_semaphore);
		status = xSemaphoreTake(producer1_semaphore, portMAX_DELAY);
		if (status != pdPASS) {
			PRINTF("Failed to acquire producer1_semaphore\r\n");
			while (1)
				;
		}
		switch (my_sem->counter) {
		case '0':
			PRINTF("left\r\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			break;
		case '1':
			PRINTF("right\r\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			break;
		case '2':
			PRINTF("up\r\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			break;
		case '3':
			PRINTF("down\r\n");
			vTaskDelay(1000 / portTICK_PERIOD_MS);
			break;
		}
	}

}
