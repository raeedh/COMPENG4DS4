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
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void hello_task(void *pvParameters);
void timerCallbackFunction(TimerHandle_t timer_handle);
void timerCallbackFunction2(TimerHandle_t timer_handle, void *pvParameters);
void consumer_sem(void *pvParameters);
// void producer_sem(void *pvParameters);


/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    BaseType_t status;
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)malloc(1 * sizeof(SemaphoreHandle_t));
    // semaphores[0] = xSemaphoreCreateBinary(); // Producer semaphore
    semaphores[0] = xSemaphoreCreateBinary(); // Consumer semaphore

    status = xTaskCreate(hello_task, "Hello_task", 200, NULL, 2, NULL);
    if (status != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }

    // status = xTaskCreate(producer_sem, "producer", 200, (void *)semaphores, 2, NULL);
    // if (status != pdPASS)
    // {
    //     PRINTF("Task creation failed!.\r\n");
    //     while (1);
    // }

    status = xTaskCreate(consumer_sem, "consumer", 200, (void *)semaphores, 2, NULL);
    if (status != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1);
    }

    TimerHandle_t timer_handle2 = xTimerCreate("Periodic timer",
                                               1000 / portTICK_PERIOD_MS,
                                               pdTRUE,
                                               NULL,
                                               timerCallbackFunction2);

    status = xTimerStart(timer_handle2, 0);
    if (status != pdPASS)
    {
        PRINTF("Couldn't start the timer!.\r\n");
        while (1);
    }

    vTaskStartScheduler();
    while (1)
    {}
}

void hello_task(void *pvParameters)
{
    while (1)
    {
        PRINTF("Hello World\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void timerCallbackFunction(TimerHandle_t timer_handle)
{   
    PRINTF("Hello from the single shot timer callback.\r\n");
}

void timerCallbackFunction2(TimerHandle_t timer_handle, void *pvParameters)
{
    PRINTF("Hello from the periodic timer callback.\r\n");

    SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
    SemaphoreHandle_t consumer_semaphore = semaphores[0];
    BaseType_t status;

    xSemaphoreGive(consumer_semaphore);
}

void consumer_sem(void *pvParameters)
{
    SemaphoreHandle_t *semaphores = (SemaphoreHandle_t *)pvParameters;
    // SemaphoreHandle_t producer_semaphore = semaphores[0];
    SemaphoreHandle_t consumer_semaphore = semaphores[0];
    BaseType_t status;

    while (1)
    {
        status = xSemaphoreTake(consumer_semaphore, portMAX_DELAY);
        if (status != pdPASS)
        {
            PRINTF("Failed to acquire consumer_semaphore\r\n");
            while (1);
        }

        PRINTF("Hello World!\n");
    }
}
