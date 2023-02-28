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




void producer_queue(void* pvParameters);
void consumer_queue(void* pvParameters);


QueueHandle_t queue1;

int main(void)
{
BaseType_t status;
/* Init board hardware. */
BOARD_InitBootPins();
BOARD_InitBootClocks();
BOARD_InitDebugConsole();

queue1 = xQueueCreate(10, sizeof(char *));


if (queue1 == NULL)
{
PRINTF("Queue creation failed!.\r\n");
while (1);
}


status = xTaskCreate(producer_queue, "producer", 200, (void*)queue1, 2, NULL);
if (status != pdPASS)
{
PRINTF("Task creation failed!.\r\n");
while (1);
}
status = xTaskCreate(consumer_queue, "consumer", 200, (void*)queue1, 3, NULL);
if (status != pdPASS)
{
PRINTF("Task creation failed!.\r\n");
while (1);
}


vTaskStartScheduler();

while (1)
{}

}


void producer_queue(void* pvParameters)
{
QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
BaseType_t status;
char* usr_str;
usr_str = malloc(sizeof(char) * 10);
while(1)
{
printf("please enter a string\n");
scanf("%s", usr_str);
status = xQueueSend(queue1, (void*) &usr_str, portMAX_DELAY);
if (status != pdPASS)
{
PRINTF("Queue Send failed!.\r\n");
while (1);
}
vTaskDelay(1000 / portTICK_PERIOD_MS);
}

vTaskDelete(NULL);

}

void consumer_queue(void* pvParameters)
{
QueueHandle_t queue1 = (QueueHandle_t)pvParameters;
BaseType_t status;

char* receive_str;

while(1)
{
status = xQueueReceive(queue1, (void *) &receive_str, portMAX_DELAY);

if (status != pdPASS)
{
PRINTF("Queue Receive failed!.\r\n");

while (1);
}

PRINTF("Received Value = %s\r\n", receive_str);
}

}

