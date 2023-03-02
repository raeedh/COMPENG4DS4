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
void consumer_left(void *pvParameters);
void consumer_right(void *pvParameters);
void consumer_up(void *pvParameters);
void consumer_down(void *pvParameters);

int main(void) {
	BaseType_t status;
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t*) malloc(5 * sizeof(SemaphoreHandle_t));
	semaphores[0] = xSemaphoreCreateBinary(); //Producer1_sem left
	semaphores[1] = xSemaphoreCreateBinary(); //Producer2_sem right
	semaphores[2] = xSemaphoreCreateBinary(); //Producer3_sem up
	semaphores[3] = xSemaphoreCreateBinary(); //Producer4_sem down
	semaphores[4] = xSemaphoreCreateCounting(4, 4); //consumer_sem

	status = xTaskCreate(producer_event, "producer", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer_left, "consumer_left", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer_right, "consumer_right", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer_up, "consumer_up", 200, (void*) semaphores, 2, NULL);
	if (status != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}
	status = xTaskCreate(consumer_down, "consumer_down", 200, (void*) semaphores, 2, NULL);
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
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t*) pvParameters;
	SemaphoreHandle_t producer1_semaphore = semaphores[0];
	SemaphoreHandle_t producer2_semaphore = semaphores[1];
	SemaphoreHandle_t producer3_semaphore = semaphores[2];
	SemaphoreHandle_t producer4_semaphore = semaphores[3];
	SemaphoreHandle_t consumer_semaphore = semaphores[4];

	BaseType_t status1, status2, status3, status4;
	char c;

	while (1) {
		status1 = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		status2 = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		status3 = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
		status4 = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);

		if (status1 != pdPASS || status2 != pdPASS || status3 != pdPASS || status4 != pdPASS) {
			PRINTF("Failed to acquire consumer_semaphore\r\n");

			while (1)
				;
		}

		while (1) {
			scanf("%c", &c);

			switch (c) {
			case 'a':
				xSemaphoreGive(producer1_semaphore);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				break;
			case 'd':
				xSemaphoreGive(producer2_semaphore);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				break;
			case 'w':
				xSemaphoreGive(producer3_semaphore);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				break;
			case 's':
				xSemaphoreGive(producer4_semaphore);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				break;
			}
		}
	}
}

void consumer_left(void *pvParameters) {
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t*) pvParameters;
	SemaphoreHandle_t producer1_semaphore = semaphores[0];
	SemaphoreHandle_t consumer_semaphore = semaphores[4];
	BaseType_t status;

	while (1) {
		xSemaphoreGive(consumer_semaphore);
		status = xSemaphoreTake(producer1_semaphore, portMAX_DELAY);
		if (status != pdPASS) {
			PRINTF("Failed to acquire producer1_semaphore\r\n");
			while (1)
				;
		}
		PRINTF("left\n");
	}

}

void consumer_right(void *pvParameters) {
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t*) pvParameters;
	SemaphoreHandle_t producer2_semaphore = semaphores[1];
	SemaphoreHandle_t consumer_semaphore = semaphores[4];
	BaseType_t status;

	while (1) {
		xSemaphoreGive(consumer_semaphore);
		status = xSemaphoreTake(producer2_semaphore, portMAX_DELAY);
		if (status != pdPASS) {
			PRINTF("Failed to acquire producer2_semaphore\r\n");
			while (1)
				;
		}
		PRINTF("right\n");
	}

}

void consumer_up(void *pvParameters) {
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t*) pvParameters;
	SemaphoreHandle_t producer3_semaphore = semaphores[2];
	SemaphoreHandle_t consumer_semaphore = semaphores[4];
	BaseType_t status;

	while (1) {
		xSemaphoreGive(consumer_semaphore);
		status = xSemaphoreTake(producer3_semaphore, portMAX_DELAY);
		if (status != pdPASS) {
			PRINTF("Failed to acquire producer3_semaphore\r\n");
			while (1)
				;
		}
		PRINTF("up\n");
	}

}

void consumer_down(void *pvParameters) {
	SemaphoreHandle_t *semaphores = (SemaphoreHandle_t*) pvParameters;
	SemaphoreHandle_t producer4_semaphore = semaphores[3];
	SemaphoreHandle_t consumer_semaphore = semaphores[4];
	BaseType_t status;

	while (1) {
		xSemaphoreGive(consumer_semaphore);
		status = xSemaphoreTake(producer4_semaphore, portMAX_DELAY);
		if (status != pdPASS) {
			PRINTF("Failed to acquire producer4_semaphore\r\n");
			while (1)
				;
		}
		PRINTF("down\n");
	}

}
